#include <stdio.h>

struct date { int day, month, year; };
struct address { char city[20]; int pincode; };
struct parcel { int id; float weight; struct address to; struct date booked; };

/* Flat alternative structure for sizeof comparison */
struct flat_parcel {
    int id;
    float weight;
    char to_city[20];
    int to_pincode;
    int day, month, year;
};

/* TODO 1: Print parcel details using the -> operator */
void print_parcel(const struct parcel *p)
{
    printf("%d %.1f kg %s-%d %02d/%02d/%04d\n",
           p->id,
           p->weight,
           p->to.city,
           p->to.pincode,
           p->booked.day,
           p->booked.month,
           p->booked.year);
}

/* TODO 2: Selection sort of parcels in ascending order of weight */
void sort_by_weight(struct parcel p[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (p[j].weight < p[min_idx].weight) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            struct parcel temp = p[i];
            p[i] = p[min_idx];
            p[min_idx] = temp;
        }
    }
}

int main(void)
{
    struct parcel list[3] = {
        {501, 4.5f, {"Madurai", 625001}, {12, 10, 2026}},
        {502, 1.2f, {"Chennai", 600077}, {12, 10, 2026}},
        {503, 2.8f, {"Coimbatore", 641001}, {13, 10, 2026}}
    };

    sort_by_weight(list, 3);
    for (int i = 0; i < 3; i++) print_parcel(&list[i]);

    printf("\nBytes copied per struct assignment: %zu bytes (3x = %zu bytes per swap)\n",
           sizeof(struct parcel), 3 * sizeof(struct parcel));
    printf("sizeof(nested struct parcel) = %zu bytes | sizeof(flat_parcel) = %zu bytes\n",
           sizeof(struct parcel), sizeof(struct flat_parcel));
    return 0;
}
