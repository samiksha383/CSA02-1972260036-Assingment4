#include <stdio.h>

/* External linkage declarations from token_extern.c */
extern int global_veg_token;
extern int global_nonveg_token;
int next_global_veg(void);
int next_global_nonveg(void);

/* Complete the Code: (b) Static local variable counter */
int next_token(void)
{
    static int token = 1000;
    return ++token;
}

/* Task 5.2: Independent static local counter for Non-Veg */
int next_nonveg_token(void)
{
    static int token = 2000;
    return ++token;
}

/* (a) Automatic local variable counter (resets every call!) */
int auto_token(void)
{
    int token = 1000;
    return ++token;
}

/* Alternative Concept: Caller-owned counter passed by pointer */
int next_ptr_token(int *counter)
{
    return ++(*counter);
}

int main(void)
{
    /* Complete the Code expected output */
    int s1 = next_token(), s2 = next_token(), s3 = next_token();
    int a1 = auto_token(), a2 = auto_token(), a3 = auto_token();
    printf("static: %d %d %d\n", s1, s2, s3);
    printf("auto : %d %d %d\n\n", a1, a2, a3);

    /* (c) Global extern across two files + (d) register loop variable */
    printf("Global extern (Veg / Non-Veg) with register loop variable:\n");
    for (register int i = 0; i < 3; i++) {
        printf("  Iter %d -> Veg: %d | Non-Veg: %d\n",
               i + 1, next_global_veg(), next_global_nonveg());
    }

    /* Task 5.2: Independent static Non-Veg counter */
    printf("\nStatic Non-Veg tokens: %d %d\n",
           next_nonveg_token(), next_nonveg_token());

    /* Alternative Concept: Caller-owned pointer counters (zero code duplication) */
    int veg_cnt = 1000, nonveg_cnt = 2000;
    printf("Pointer counters (Veg / Non-Veg): %d / %d\n",
           next_ptr_token(&veg_cnt), next_ptr_token(&nonveg_cnt));

    return 0;
}
