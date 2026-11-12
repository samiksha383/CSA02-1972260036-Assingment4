#include <stdio.h>

enum kind { TEMPERATURE, HUMIDITY, STATUS };

/* Tagged union design (12 bytes) */
struct reading {
    enum kind type; /* tag: tells which union member is valid */
    union {
        float celsius;
        int percent;
        char status[8];
    } value;
};

/* Non-union struct design for size comparison (20 bytes) */
struct reading_struct_only {
    enum kind type;
    float celsius;
    int percent;
    char status[8];
};

/* TODO 1: Switch on r->type to print only the valid union member */
void show(const struct reading *r)
{
    switch (r->type) {
        case TEMPERATURE:
            printf("Temp %.1f C\n", r->value.celsius);
            break;
        case HUMIDITY:
            printf("Humidity %d %%\n", r->value.percent);
            break;
        case STATUS:
            printf("Status %s\n", r->value.status);
            break;
        default:
            printf("Unknown packet type\n");
            break;
    }
}

int main(void)
{
    struct reading log[3] = {
        {TEMPERATURE, {.celsius = 31.5f}},
        {HUMIDITY,    {.percent = 68}},
        {STATUS,      {.status = "OK"}}
    };

    printf("sizeof union = %zu, sizeof struct reading = %zu\n",
           sizeof log[0].value, sizeof log[0]);
    for (int i = 0; i < 3; i++) show(&log[i]);

    printf("\nsizeof(struct reading_struct_only) = %zu bytes (wastes 8 bytes/packet)\n",
           sizeof(struct reading_struct_only));

    /* Task 3.4: Misuse Experiment - write float celsius, read int percent */
    struct reading bad;
    bad.type = TEMPERATURE;
    bad.value.celsius = 31.5f;
    printf("\n=== Misuse Experiment ===\n");
    printf("Stored float celsius = %.1f -> Reading int percent gives: %d (0x%08X IEEE-754 bits!)\n",
           bad.value.celsius, bad.value.percent, (unsigned int)bad.value.percent);

    return 0;
}
