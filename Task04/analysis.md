\# TASK 4 – Structure Forensics: Savings Account Interest



\## Task 4.1 – Locate the Two Defects

1\. \*\*Why Balances Remain Unchanged (Pass-by-Value):\*\* `void addInterest(struct account a, float rate)` receives a \*\*copy\*\* of `list\[i]` on the stack. Modifying `a.balance` updates only the local copy, which is destroyed when `addInterest()` returns.

2\. \*\*Why `printf("%d %f\\n", p.number, p.balance);` Fails to Compile:\*\* `p` is a \*\*pointer\*\* (`struct account \*`), not a structure variable. Applying the dot operator (`.`) to a pointer produces a compiler error (`request for member 'number' in something not a structure or union`). It must use the arrow operator (`p->number`, `p->balance`).



\## Task 4.2 – Address Forensic Evidence

\* Printing `(void \*)\&list` in `main()` vs. `(void \*)\&a` inside `inspect\_by\_value()` produces \*\*two distinct stack memory addresses\*\* (e.g., `0x000000...61FE10` vs. `0x000000...61FDF0`), proving `a` is an independent copy.

\* Passing `\&list\[i]` into `addInterest(struct account \*a, ...)` prints the \*\*exact same address\*\* as `\&list\[i]`, modifying the original array element in place.



\## Task 4.4 – Guidelines for Passing Structures

\* \*\*Pass by Value (`struct T x`):\*\* Only for tiny read-only structs ($\\le 16$ bytes, e.g., `struct point { int x, y; }`) that fit in CPU registers.

\* \*\*Pass by Pointer (`struct T \*x`):\*\* Whenever the function must \*\*modify\*\* the caller's structure in place.

\* \*\*Pass by `const` Pointer (`const struct T \*x`):\*\* Whenever reading medium/large structures (`> 16 bytes`) to avoid copying overhead while preventing accidental mutation.



\## Alternative Concept and Complexity Analysis (`list\[i] = addInterest(list\[i], 4)`)

\* \*\*Time Complexity:\*\* Both run in \*\*$O(1)$\*\* per account. However, pass-by-value + return copies `sizeof(struct account)` (`8 bytes`) \*\*twice\*\* per call (`16 bytes` moved), whereas passing a pointer copies \*\*one 8-byte address\*\* (`8 bytes` total) and modifies `balance` directly in memory. For large structs (e.g., `128 bytes`), pass-by-pointer avoids `256 bytes` of memory traffic per call.

\* \*\*Space Complexity:\*\* Pass-by-pointer uses \*\*$O(1)$\*\* stack space (`8 bytes` for one pointer); pass-by-value + return allocates `2 × sizeof(struct account)` bytes of stack frame space for the parameter copy and return slot.



