#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 20

typedef struct { int day, month, year; } Date;
typedef struct { int hour, minute; } TimeOfDay;

typedef enum { ITEM_PACKAGED, ITEM_COOKED, ITEM_COMBO } ItemKind;

typedef struct {
    int id;
    char name[30];
    ItemKind kind;
    long price_paise;
    int stock;
    long revenue_paise;
    union {
        Date expiry;              /* ITEM_PACKAGED */
        TimeOfDay prepared_time;  /* ITEM_COOKED */
        int sub_item_ids[3];      /* ITEM_COMBO (up to 3 items) */
    } meta;
} CanteenItem;

long date_to_days(Date d)
{
    return (long)d.year * 365L + (long)d.month * 30L + (long)d.day;
}

int record_sale(CanteenItem *items, int count, int item_id, int qty)
{
    if (qty <= 0) return 0;
    for (int i = 0; i < count; i++) {
        if (items[i].id == item_id) {
            if (items[i].stock < qty) {
                printf("[SALE REJECTED] %s: Requested %d, only %d in stock!\n",
                       items[i].name, qty, items[i].stock);
                return 0;
            }
            items[i].stock -= qty;
            long sale_amt = items[i].price_paise * qty;
            items[i].revenue_paise += sale_amt;
            printf("[SALE OK]       %s x%d -> Rs %ld.%02ld (Remaining stock: %d)\n",
                   items[i].name, qty, sale_amt / 100, sale_amt % 100, items[i].stock);
            return 1;
        }
    }
    printf("[SALE REJECTED] Item ID %d not found.\n", item_id);
    return 0;
}

void check_expiry_warnings(const CanteenItem *items, int count, Date today)
{
    long today_days = date_to_days(today);
    printf("\n=== Expiry Warning Report (As of %02d/%02d/%04d) ===\n",
           today.day, today.month, today.year);
    int warnings = 0;
    for (int i = 0; i < count; i++) {
        if (items[i].kind == ITEM_PACKAGED) {
            long diff = date_to_days(items[i].meta.expiry) - today_days;
            if (diff <= 2) {
                printf("  [WARNING] %-16s (ID %d) expires on %02d/%02d/%04d (%ld days left)!\n",
                       items[i].name, items[i].id,
                       items[i].meta.expiry.day, items[i].meta.expiry.month,
                       items[i].meta.expiry.year, diff);
                warnings++;
            }
        }
    }
    if (!warnings) printf("  No items expiring within 2 days.\n");
}

void print_revenue_summary(CanteenItem *items, int count)
{
    for (int i = 0; i < count - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < count; j++) {
            if (items[j].revenue_paise > items[max_idx].revenue_paise) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            CanteenItem tmp = items[i];
            items[i] = items[max_idx];
            items[max_idx] = tmp;
        }
    }

    long grand_rev = 0;
    printf("\n=== Daily Revenue Summary (Sorted Descending) ===\n");
    printf("%-4s | %-18s | %-10s | %-6s | %-12s\n",
           "ID", "Item Name", "Category", "Stock", "Revenue");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        const char *cat = (items[i].kind == ITEM_PACKAGED) ? "Packaged" :
                          (items[i].kind == ITEM_COOKED)   ? "Cooked" : "Combo";
        printf("%-4d | %-18s | %-10s | %-6d | Rs %6ld.%02ld\n",
               items[i].id, items[i].name, cat, items[i].stock,
               items[i].revenue_paise / 100, items[i].revenue_paise % 100);
        grand_rev += items[i].revenue_paise;
    }
    printf("------------------------------------------------------------\n");
    printf("Total Canteen Revenue: Rs %ld.%02ld\n", grand_rev / 100, grand_rev % 100);
}

int main(void)
{
    Date today = {12, 11, 2026};

    CanteenItem menu[MAX_ITEMS] = {
        {101, "Paneer Sandwich", ITEM_PACKAGED, 4500L, 10, 0L, {.expiry = {13, 11, 2026}}},
        {102, "Fruit Juice Box", ITEM_PACKAGED, 2500L, 20, 0L, {.expiry = {25, 12, 2026}}},
        {103, "Masala Dosa",     ITEM_COOKED,   5000L, 15, 0L, {.prepared_time = {8, 30}}},
        {104, "Lunch Combo",     ITEM_COMBO,    8500L,  5, 0L, {.sub_item_ids = {101, 102, 103}}}
    };
    int count = 4;

    printf("=== Canteen Sales Transactions ===\n");
    record_sale(menu, count, 103, 6);
    record_sale(menu, count, 104, 4);
    record_sale(menu, count, 101, 3);
    record_sale(menu, count, 104, 5);

    check_expiry_warnings(menu, count, today);
    print_revenue_summary(menu, count);

    return 0;
}
