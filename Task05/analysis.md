\# TASK 5 – Storage Classes: The Same Counter Four Ways



\## Task 5.1 \& 5.2 – Four Implementations \& Two-Counter Modification Effort

1\. \*\*`auto` (`int token = 1000;`):\*\* Resets to `1000` on every call, always returning `1001`. Cannot maintain state across calls.

2\. \*\*`static` Local (`static int token = 1000;`):\*\* Initialized once in `.data` segment; retains value across calls (`1001, 1002, 1003`). Supporting separate \*\*Veg\*\* and \*\*Non-Veg\*\* counters requires duplicating the function (`next\_nonveg\_token()`) or passing a category flag with an internal `static int tokens` array.

3\. \*\*Global + `extern` (`global\_veg\_token` in `token\_extern.c`):\*\* Shared across multiple `.c` files. Supporting two counters requires adding a second global variable (`global\_nonveg\_token`) and `extern` declaration—high coupling and high risk of accidental modification by any file.

4\. \*\*`register` (`for (register int i = 0; ...)`):\*\* Hints the compiler to store loop counter `i` in a CPU register. Block scope, automatic lifetime, uninitialized if not assigned.



\## Task 5.3 – Storage Class Comparison \& Inquiries



| Storage Class | Scope | Lifetime | Default Initial Value | Accidental Modification Risk |

| :--- | :--- | :--- | :--- | :--- |

| \*\*`auto`\*\* | Block (local) | Function call | Garbage (indeterminate) | None (isolated per call) |

| \*\*`static` (local)\*\* | Block (local) | Entire program run | `0` | Low (only modifiable inside that function) |

| \*\*`extern` (global)\*\* | File / Program-wide | Entire program run | `0` | \*\*High\*\* (any file can overwrite it) |

| \*\*`register`\*\* | Block (local) | Block execution | Garbage (indeterminate) | None (local + no memory address) |



\* \*\*Why `\&reg\_var` is Illegal in C:\*\* A `register` variable may reside inside a CPU hardware register rather than addressable RAM, so it has no memory address (`\&` triggers a compile-time error).

\* \*\*Unspecified Argument Evaluation Order:\*\* Writing `printf("%d %d %d", next\_token(), next\_token(), next\_token())` can print `1003 1002 1001` (right-to-left evaluation on x86 cdecl) or `1001 1002 1003` (left-to-right), because C leaves the evaluation order of function arguments \*\*unspecified\*\*. Always assign calls to separate variables first.



\## Alternative Concept (`int next\_token(int \*counter)`)

\* \*\*Time \& Space:\*\* \*\*$O(1)$\*\* time and \*\*$O(1)$\*\* space (4 bytes owned by the caller).

\* \*\*Maintainability:\*\* Far superior to `static` or `extern`—supporting 2, 10, or 100 independent counters requires \*\*zero changes\*\* to `next\_token()`; the caller simply passes `\&veg\_counter` or `\&nonveg\_counter`.



