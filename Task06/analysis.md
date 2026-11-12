\# TASK 6 – Design Challenge: College Canteen Inventory \& Billing



\## Stage 1 – Problem Interpretation \& Testable Requirements

\* \*\*Entities:\*\* `CanteenItem` (packaged, cooked, or combo), `Date` (`day, month, year`), and `TimeOfDay` (`hour, minute`).

\* \*\*Rules \& Testable Statements:\*\*

&#x20; 1. `stock` must never drop below `0`; any order with `qty > stock` must be rejected with zero revenue added.

&#x20; 2. All money is stored in integer \*\*paise\*\* (`long`) so `revenue\_paise == units\_sold \* price\_paise` with zero floating-point drift.

&#x20; 3. Any `ITEM\_PACKAGED` item whose expiry date is within `<= 2` days of `today` triggers an expiry warning.

&#x20; 4. The end-of-day report must list all items sorted in descending order of `revenue\_paise`.



\## Stage 2 – Data Model Justification

\* \*\*Nested Structures:\*\* `Date` (`expiry`) and `TimeOfDay` (`prepared\_time`) are nested inside `CanteenItem` for clean date/time arithmetic.

\* \*\*Tagged Union (`ItemKind kind` + `union meta`):\*\* An item is exclusively packaged (`Date expiry`), cooked (`TimeOfDay prepared\_time`), or a combo (`int sub\_item\_ids`), so overlaying them in a `12-byte` union saves memory compared to storing all three fields simultaneously.

\* \*\*Array of Structures:\*\* `CanteenItem menu\[MAX\_ITEMS]` keeps all records contiguous in CPU cache for fast sorting and scanning.



\## Stage 3 – Critical Design Decisions

\* \*\*Safe Stock Update:\*\* Validate `items\[i].stock >= qty` \*\*before\*\* deducting `stock` or incrementing `revenue\_paise`.

\* \*\*Expiry Calculation:\*\* Convert `(day, month, year)` to an ordinal day count (`year \* 365 + month \* 30 + day`) to compute `expiry\_days - today\_days <= 2` cleanly without string parsing.

\* \*\*Storage Class Scope:\*\* Keep the inventory array inside `main()` and pass pointers (`CanteenItem \*` / `const CanteenItem \*`) to functions rather than using globals, allowing multiple canteen counters to coexist safely.



\## Stage 4 – Pseudocode

```text

RECORD\_SALE(items, count, item\_id, qty):

&#x20;   find item with items\[i].id == item\_id

&#x20;   if not found or items\[i].stock < qty:

&#x20;       print "SALE REJECTED" and return FALSE

&#x20;   items\[i].stock <- items\[i].stock - qty

&#x20;   items\[i].revenue\_paise <- items\[i].revenue\_paise + (items\[i].price\_paise \* qty)

&#x20;   return TRUE



CHECK\_EXPIRY(items, count, today):

&#x20;   for i <- 0 to count - 1:

&#x20;       if items\[i].kind == ITEM\_PACKAGED:

&#x20;           if DAYS(items\[i].meta.expiry) - DAYS(today) <= 2:

&#x20;               print "WARNING:", items\[i].name

```



\## Stage 5 \& Alternative Concept (Linked List vs. Array of Structures)



| Operation / Metric | Array of Structures (`CanteenItem menu\[]`) | Singly Linked List (`Node \*head`) |

| :--- | :--- | :--- |

| \*\*Search by ID\*\* | \*\*$O(n)$\*\* (Fast sequential cache scan) | \*\*$O(n)$\*\* (Pointer chasing; cache misses) |

| \*\*Add New Item\*\* | \*\*$O(1)$\*\* amortized (Append at `count`) | \*\*$O(1)$\*\* (Insert at head) |

| \*\*Remove Item\*\* | \*\*$O(n)$\*\* (Shift subsequent structs left) | \*\*$O(n)$\*\* to find + \*\*$O(1)$\*\* pointer unlink |

| \*\*Extra Memory\*\* | \*\*0 bytes\*\* per item | \*\*8 bytes\*\* per item (`struct Node \*next`) + \~16 B `malloc` header |



\*\*Conclusion:\*\* Because a college canteen menu has a bounded size (`<= 100` items) and requires sorting by revenue at the end of the day, a contiguous \*\*array of structures\*\* is faster, simpler, and avoids heap fragmentation.



