# CSA02 – C Programming Assignment 4
**Structures, Nested Structures, Unions, Storage Classes, and System Design**

* **Student Name:** Samiksha
* **Register Number:** 1972260036
* **Compiler:** GCC 16.2.0 (`WinLibs x86_64-w64-mingw32`)
* **Compile Command:** `gcc -Wall -Wextra <folder>\<source.c> -o <folder>\<output.exe>`
* **Run Command:** `.\<folder>\<output.exe>`

## Task Summary & Results

| Task | Folder | Topic | Summary of Findings & Results |
| :--- | :--- | :--- | :--- |
| **Task 1** | `Task01/` | Data Design Review | Diagnosed 6 parallel-array deficiencies; redesigned clinic register with nested `Date` and `BloodPressure` structs (`92 bytes`) and pointer-safe `addPatient()`. |
| **Task 2** | `Task02/` | Nested Structures | Implemented courier parcel tracking with nested `address` and `date` structs (`44 bytes`), weight selection sort (`132 bytes` per swap), and dot/arrow access paths. |
| **Task 3** | `Task03/` | Unions & Memory Layout | Built `12-byte` tagged-union weather sensor packet (`40%` memory savings over `20-byte` struct) and demonstrated IEEE-754 bit reinterpretation (`31.5f` -> `1107034112`). |
| **Task 4** | `Task04/` | Structure Forensics | Proved pass-by-value stack copying via memory address inspection (`%p`), fixed pointer `.` vs `->` bug, and documented structure passing guidelines. |
| **Task 5** | `Task05/` | Storage Classes | Implemented token counters using `auto`, `static` local, multi-file `extern` global, and `register` loop variables; analyzed unspecified argument evaluation order. |
| **Task 6** | `Task06/` | Design Challenge | Built complete College Canteen Inventory & Billing system using tagged unions, safe stock deduction, 2-day expiry alerts, and descending revenue sorting. |
