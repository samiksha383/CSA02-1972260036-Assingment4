\# TASK 3 – Unions and Memory Layout: Weather-Station Sensor Packets



\## Task 3.1 – Structure vs. Tagged Union Design

\* \*\*Plain Structure (`struct reading\_struct\_only`):\*\* Allocates separate memory for `type`, `celsius`, `percent`, and `status` simultaneously, wasting 8 unused bytes on every single packet.

\* \*\*Tagged Union (`struct reading`):\*\* Combines an `enum kind type` tag with a `union` that overlays `celsius`, `percent`, and `status\[8]` at the exact same memory offset. Because a weather packet carries \*\*only one\*\* measurement at a time, the tagged union saves \*\*40% memory\*\* (8 KB saved per 1,000 packets) while remaining completely type-safe via the `type` tag.



\## Task 3.2 – Size Prediction \& Alignment Explanation

\* \*\*Plain Structure:\*\* `4 (enum) + 4 (float) + 4 (int) + 8 (char) = 20 bytes`.

\* \*\*Union (`value`):\*\* Size equals its largest member (`char status\[8]` = \*\*8 bytes\*\*), aligned to `4 bytes` (`float`/`int`).

\* \*\*Tagged Union (`struct reading`):\*\* `4 (enum tag) + 8 (union value) = 12 bytes` (no padding needed because `8` is already a multiple of `4`).

\* \*\*Why 12 bytes and not `4 + 4 + 4 + 8` (20 bytes)?\*\* In a `union`, all members share the \*\*same starting memory address\*\* (overlapping storage), so the union occupies only the size of its single largest member (`8 bytes`), not the sum of all members (`4 + 4 + 8 = 16 bytes`).



\## Task 3.4 – Misuse Experiment \& Explanation

\* Storing `bad.value.celsius = 31.5f` writes the IEEE-754 single-precision bit pattern `0x41FC0000` into the union's 4 bytes.

\* Reading `bad.value.percent` reinterprets those exact raw bits as a 32-bit signed `int`, outputting \*\*`1107034112`\*\* (`0x41FC0000` in decimal) — completely meaningless garbage humidity.



\## Alternative Concept and Complexity Analysis



| Storage Design | Time to Read Packet | Space per Packet | Notes |

| :--- | :--- | :--- | :--- |

| \*\*Tagged Union Array (Chosen)\*\* | \*\*$O(1)$\*\* (Direct index + switch) | \*\*12 bytes\*\* | Contiguous cache-friendly memory; zero heap fragmentation. |

| \*\*Three Separate Arrays\*\* | \*\*$O(1)$\*\* (If reading by type) | \*\*4–8 bytes\*\* (no tag needed) | Loses chronological arrival order unless an extra timestamp/index array is maintained. |

| \*\*`malloc` + `void \*` Pointer Array\*\* | \*\*$O(1)$\*\* (Two pointer dereferences) | \*\*8 B pointer + 4–8 B payload + \~16 B heap header = \~32 bytes\*\* | Wastes \*\*2.6× more RAM\*\* due to 64-bit pointers and `malloc` metadata, and loses type safety. |



