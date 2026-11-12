\# TASK 2 – From Requirement to Nested Structures: Courier Parcel Tracking



\## Task 2.1 – Entity Identification \& Nesting Hierarchy

1\. \*\*`Date`\*\* (`day`, `month`, `year`) — Nested inside `Parcel` for `booking\_date`.

2\. \*\*`ContactAddress`\*\* (`name`, `city`, `pincode`) — Nested \*\*twice\*\* inside `Parcel` (once for `sender` and once for `receiver`).

3\. \*\*`ServiceType` (`enum`)\*\* (`NORMAL`, `EXPRESS`) — Stored inside `Parcel`.

4\. \*\*`Parcel`\*\* (`id`, `weight`, `booking\_date`, `sender`, `receiver`, `service`, `charge\_paise`) — Top-level entity stored in the daily bookings array.



\## Task 2.2 – Complete `typedef` Structure Definitions

```c

typedef struct { int day, month, year; } Date;

typedef struct { char name\[40]; char city\[20]; int pincode; } ContactAddress;

typedef enum { SERVICE\_NORMAL, SERVICE\_EXPRESS } ServiceType;



typedef struct {

&#x20;   int id;

&#x20;   float weight;

&#x20;   Date booking\_date;

&#x20;   ContactAddress sender;

&#x20;   ContactAddress receiver;

&#x20;   ServiceType service;

&#x20;   long charge\_paise;

} Parcel;



Parcel daily\_bookings\[500];

```



\## Task 2.3 – Pseudocode for Operations

```text

(a) SORT\_BY\_WEIGHT(parcels, n):

&#x20;   for i <- 0 to n - 2:

&#x20;       min\_idx <- i

&#x20;       for j <- i + 1 to n - 1:

&#x20;           if parcels\[j].weight < parcels\[min\_idx].weight:

&#x20;               min\_idx <- j

&#x20;       if min\_idx != i:

&#x20;           swap(parcels\[i], parcels\[min\_idx])



(b) LIST\_BY\_RECEIVER\_CITY(parcels, n, target\_city):

&#x20;   for i <- 0 to n - 1:

&#x20;       if strcmp(parcels\[i].receiver.city, target\_city) == 0:

&#x20;           PRINT\_PARCEL(\&parcels\[i])

```



\## Task 2.4 – Access Paths for Third Parcel's Receiver PIN Code

\* \*\*(i) Using array and dot operator:\*\* `daily\_bookings\[2].receiver.pincode` (or `list\[2].to.pincode` in the starter code).

\* \*\*(ii) Using structure pointer (`Parcel \*ptr = \&daily\_bookings\[2]`) and arrow operator:\*\* `ptr->receiver.pincode` (or `ptr->to.pincode`).



\## Bytes Copied \& Alternative Concept (Nested vs. Flat Structure)

\* \*\*Bytes Copied per Swap:\*\* `sizeof(struct parcel)` is \*\*44 bytes\*\* (`4 + 4 + 24 + 12`). A 3-step swap (`temp = p\[i]; p\[i] = p\[min]; p\[min] = temp;`) copies \*\*`3 × 44 = 132 bytes`\*\*.

\* \*\*Nested vs. Flat Structure:\*\*

&#x20; \* \*\*Access Paths:\*\* Nested uses `p.to.pincode` / `p->to.pincode`; flat uses `p.to\_pincode` / `p->to\_pincode`.

&#x20; \* \*\*Type Reuse:\*\* Nested structures allow reusing `struct address` for both `sender` and `receiver` and writing standalone helper functions like `validate\_pincode(const struct address \*)`. A flat structure duplicates `sender\_city`, `sender\_pincode`, `receiver\_city`, and `receiver\_pincode`.

&#x20; \* \*\*Size (`sizeof`):\*\* Both `struct parcel` and `struct flat\_parcel` measure \*\*44 bytes\*\* because all member alignments (`4-byte int/float`) match identically.



