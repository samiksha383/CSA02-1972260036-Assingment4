#include <stdio.h>

struct account {
    int number;
    float balance;
};

void inspect_by_value(struct account a)
{
    printf("  [Inside inspect_by_value] Address of copy 'a' = %p (Balance: %.2f)\n",
           (void *)&a, a.balance);
    a.balance += a.balance * 4.0f / 100.0f;
}

void addInterest(struct account *a, float rate)
{
    if (!a) return;
    printf("  [Inside addInterest ptr]  Address pointed by 'a' = %p\n", (void *)a);
    a->balance = a->balance + (a->balance * rate / 100.0f);
}

int main(void)
{
    struct account list[3] = {{101, 5000.0f}, {102, 12000.0f}, {103, 800.0f}};
    struct account *p = list;

    printf("=== Task 4.2: Memory Address Forensic Proof ===\n");
    printf("  [In main] Address of list[0]               = %p\n", (void *)&list[0]);
    inspect_by_value(list[0]);
    printf("  [After pass-by-value] list[0].balance      = %.2f (Unchanged!)\n\n", list[0].balance);

    printf("=== Task 4.3: Repaired Pointer Implementation ===\n");
    for (int i = 0; i < 3; i++) {
        addInterest(&list[i], 4.0f);
    }

    printf("\nUpdated Balances (using pointer -> operator):\n");
    for (int i = 0; i < 3; i++) {
        printf("  Account %d: Rs %.2f\n", (p + i)->number, (p + i)->balance);
    }

    return 0;
}
