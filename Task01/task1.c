#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define NAME_LEN 50
#define PHONE_LEN 15

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int systolic;
    int diastolic;
} BloodPressure;

typedef struct {
    char name[NAME_LEN];
    int age;
    char phone[PHONE_LEN];
    BloodPressure bp;
    Date visitDate;
} Patient;

typedef struct {
    Patient records[MAX_PATIENTS];
    int count;
} PatientRegister;

/* Safe insertion accepting a structure pointer */
int addPatient(PatientRegister *reg, const Patient *p)
{
    if (!reg || !p || reg->count >= MAX_PATIENTS) {
        fprintf(stderr, "Error: Register full or invalid patient record.\n");
        return 0;
    }
    reg->records[reg->count] = *p;
    reg->count++;
    return 1;
}

/* Sorting by age now swaps a single struct instead of 5 parallel arrays */
void sortByAge(PatientRegister *reg)
{
    for (int i = 0; i < reg->count - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < reg->count; j++) {
            if (reg->records[j].age < reg->records[min_idx].age) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            Patient temp = reg->records[i];
            reg->records[i] = reg->records[min_idx];
            reg->records[min_idx] = temp;
        }
    }
}

void printRegister(const PatientRegister *reg)
{
    printf("=== Primary Health Centre Register (%d Patients) ===\n", reg->count);
    for (int i = 0; i < reg->count; i++) {
        const Patient *p = &reg->records[i];
        printf("%d. %-18s | Age: %2d | Phone: %-10s | BP: %3d/%-3d | Date: %02d/%02d/%04d\n",
               i + 1, p->name, p->age, p->phone,
               p->bp.systolic, p->bp.diastolic,
               p->visitDate.day, p->visitDate.month, p->visitDate.year);
    }
    printf("\n");
}

int main(void)
{
    PatientRegister clinic = { .count = 0 };

    Patient p1 = {"Meenakshi Sundaram", 64, "9840112233", {140, 90}, {12, 11, 2026}};
    Patient p2 = {"Arun Kumar", 28, "9840998877", {118, 76}, {12, 11, 2026}};
    Patient p3 = {"Lakshmi Devi", 52, "9444123456", {130, 85}, {11, 11, 2026}};

    addPatient(&clinic, &p1);
    addPatient(&clinic, &p2);
    addPatient(&clinic, &p3);

    printf("Before Sorting:\n");
    printRegister(&clinic);

    sortByAge(&clinic);
    printf("After Sorting by Age:\n");
    printRegister(&clinic);

    printf("sizeof(Patient) = %zu bytes\n", sizeof(Patient));
    return 0;
}
