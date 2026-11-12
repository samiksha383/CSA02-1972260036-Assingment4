\# TASK 1 – Data Design Review: Primary Health Centre Register



\## Task 1.1 – Diagnosis of Six Design Deficiencies

1\. \*\*Parallel Arrays (`name\[]`, `age\[]`, `phone\[]`, `bp\[]`, `visitDate\[]`):\*\* Patient attributes are decoupled across five separate arrays. Any bug in indexing or sorting desynchronizes records, attaching one patient's blood pressure or phone number to another patient.

2\. \*\*10-Digit Phone in `char\[10]`:\*\* A 10-digit Indian mobile number (`"9840112233"`) requires \*\*11 bytes\*\* (10 digits + `'\\0'`). `strcpy(phone\[count], p)` writes `'\\0'` out of bounds, corrupting adjacent memory.

3\. \*\*Blood Pressure Stored in One `float`:\*\* Blood pressure consists of two independent integer measurements (systolic and diastolic, e.g., `120/80`). Storing it as a `float` loses diastolic precision (`120.80` cannot flag hypertensive emergencies accurately).

4\. \*\*Visit Date in `char\[8]`:\*\* A formatted date `"12/11/2026"` requires \*\*11 bytes\*\* (`dd/mm/yyyy` + `'\\0'`). Even compact `"12112026"` overflows `char\[8]` due to the missing null terminator, and text dates cannot be easily filtered by month or year.

5\. \*\*No Bounds Check on `count`:\*\* When the 101st patient arrives (`count >= 100`), `addPatient()` writes past array boundaries, causing stack/heap corruption or a crash.

6\. \*\*Global State \& Unsafe `strcpy`:\*\* Global arrays prevent managing multiple clinic branches simultaneously, and unbounded `strcpy` risks buffer overflows on long patient names (`char\[20]`).



\## Task 1.2 – Repaired Design

Implemented in `Task01/task1.c` using nested `Date` and `BloodPressure` structs inside `Patient`, wrapped inside `PatientRegister` with `addPatient(PatientRegister \*reg, const Patient \*p)` enforcing `MAX\_PATIENTS` bounds.



\## Task 1.3 – Design Defence (88 words)

Grouping all patient attributes into a single `Patient` structure enforces data integrity: every field belonging to a patient lives contiguously in memory and moves together as one unit. Sorting by age requires swapping a single `Patient` struct (`temp = a\[i]`) rather than manually synchronizing five separate arrays. Passing a `const Patient \*` pointer to functions avoids copying large data blocks and permits compiler type-checking. Finally, adding new clinical fields (such as blood group or diagnosis) requires editing only `struct Patient` without rewriting function signatures or swap logic.



\## Alternative Concept and Complexity Analysis (Array of Structs vs. Parallel Arrays)

\* \*\*When Parallel Arrays (SoA) Are Preferred:\*\* In high-performance analytics or SIMD vectorization where a query scans only \*\*one\*\* attribute across millions of patients (e.g., computing average `age` without loading `name` or `phone` into CPU cache lines).

\* \*\*Sorting $n$ Patients:\*\*

&#x20; \* \*\*Time Complexity:\*\* Both require \*\*$O(n^2)$\*\* comparisons (or $O(n \\log n)$ with `qsort`). However, per swap, \*\*Array of Structs\*\* performs \*\*1 struct swap\*\* (`\~88 bytes`), whereas \*\*Parallel Arrays\*\* perform \*\*5 separate array swaps\*\* (`5` index updates + `3` `strcpy` calls per swap).

&#x20; \* \*\*Space \& Padding:\*\* `struct Patient` uses `50 (char) + 2 (padding) + 4 (int) + 15 (char) + 1 (padding) + 8 (BP) + 12 (Date) = 92 bytes` (`3 bytes` internal alignment padding), whereas parallel arrays use `89 bytes` per patient with zero inter-field padding.



