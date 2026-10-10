
# PmergeMe: Ford–Johnson / Merge-Insertion Sort

`PmergeMe` sorts a sequence of positive integers using the **Ford–Johnson algorithm**, also known as **merge-insertion sort**.

The algorithm is designed to minimize the number of comparisons, particularly in the worst case.

The same algorithm is implemented separately using two STL containers:

```cpp
std::vector<int>
std::deque<int>
```

**Reference:** [Merge-insertion sort - Wikipedia](https://en.wikipedia.org/wiki/Merge-insertion_sort)

---

## 1. Ford–Johnson Algorithm

The algorithm follows these main steps:

1. **Make pairs**
   - Group the input elements into pairs.
   - If the number of elements is odd, keep the last element aside as a `straggler`.

2. **Compare each pair**
   - Compare both elements and arrange them as `(small, big)`.

3. **Recursively sort the larger elements**
   - Extract the larger element from each pair.
   - Recursively sort them using **`Ford–Johnson`**.
   - Keep each smaller element associated with its larger partner.

      **Create the main and pending chains**
   - `Main chain`: sorted larger elements.
   - `Pending chain`: smaller elements waiting to be inserted.

4. **Insert the first pending element**
   - Insert `b1`, the smaller element paired with the smallest larger element, at the beginning.

5. **Insert the remaining pending elements**
   - Use the **`Jacobsthal sequence`** to determine the insertion order.
   - Use **`partner-limited binary search`** to find each insertion position.
   - Insert the `straggler` if one exists.

### Example

**Input:**

```text
3 2 1 6 5 9 7 11
```

**Step 1: Make pairs**

```text
(3,2) (1,6) (5,9) (7,11)
```

**Step 2: Order each pair**

```text
(2,3)   (1,6)   (5,9)   (7,11)
(b1,a1) (b2,a2) (b3,a3) (b4,a4)
 ↑ ↑
 │ └── big
 └──── small
```

**Step 3: Recursively sort the larger elements**

```text
3 6 9 11
```

**Create chains**

```text
Main chain:
    3 
    6 
    9 
    11

Pending chain:
    b1 = 2
    b2 = 1
    b3 = 5  
    b4 = 7
```

**Step 4: Insert the first pending element**

```text
Insert b1 = 2

Main chain:
  2 3 6 9 11
```

**Step 5: Insert the remaining pending elements**

```text
Jacobsthal    → WHICH element to insert next
Binary search → WHERE to insert it

Insertion order:
b3 → b2 → b4

Final result:
1 2 3 5 6 7 9 11
```

---

## 2. Jacobsthal Sequence

The Jacobsthal sequence determines **which pending element to insert next**.

**Sequence:**

```text
0, 1, 1, 3, 5, 11, 21, 43, ...
```

**Formula:**

```text
J(n) = J(n-1) + 2 × J(n-2)
```

Each number is the previous number plus twice the number before it.

**Insertion checkpoints:**

```text
1 → 3 → 5 → 11 → 21 → 43
```

```text
📍 Checkpoint 1:   b1

📍 Checkpoint 3:   b3 → b2

📍 Checkpoint 5:   b5 → b4

📍 Checkpoint 11:  b8 → b7 → b6

📍 Checkpoint 21:  b21 → b20 → b19 → b18 → b17 → b16 → b15 → b14 → b13 → b12

📍 Checkpoint 43:  b43 → b42 → b41 → b40 → b39 → b38 → b37 → b36 → b35 → b34 → b33 → 
                   b32 → b31 → b30 → b29 → b28 → b27 → b26 → b25 → b24 → b23 → b22
```

**Rule:** Jump to the next `Jacobsthal` checkpoint, then insert backward toward the previous checkpoint.

### Example: 4 Pending Elements

```text
Pending:    b1   b2   b3   b4
            ↓         ↓
Checkpoint: 1         3       (next is 5)

📍 Checkpoint 1:   b1
📍 Checkpoint 3:   b3 → b2
📍 Checkpoint 5:   b5 → b4

Insertion order:
b1 → b3 → b2 → b4
```

### Example: 8 Pending Elements

```text
Checkpoints: 1 → 3 → 5 → 11

📍 Checkpoint 1:   b1
📍 Checkpoint 3:   b3 → b2
📍 Checkpoint 5:   b5 → b4
📍 Checkpoint 11:  b8 → b7 → b6
                (stop at b8 because b9–b11 don't exist)

Final insertion order:
b1 → b3 → b2 → b5 → b4 → b8 → b7 → b6
```

### Why Jacobsthal?

The pending elements are divided into insertion groups with sizes:

```text
2, 2, 6, 10, 22, 42, ...
```

Elements within each group are inserted in reverse order.

This ordering helps keep binary-search ranges near sizes of:

```text
1, 3, 7, 15, 31, ...
```

These sizes are one less than a power of two and allow efficient worst-case binary search.

| Search range size | Maximum comparisons |
| ----------------- | ------------------- |
| 1                 | 1                   |
| 2–3               | 2                   |
| 4–7               | 3                   |
| 8–15              | 4                   |
| 16–31             | 5                   |

Jacobsthal-based insertion ordering helps avoid unnecessary comparisons.

**Jacobsthal chooses the insertion order. It does not sort the values directly.**

---

## 3. Binary Search (`std::lower_bound`)

Binary search finds an insertion position by repeatedly dividing the search range in half instead of checking every element sequentially.

In Ford–Johnson, each pending element `bᵢ` is associated with a larger partner `aᵢ`.

```text
small → partner

2 → 3
1 → 6
5 → 9
7 → 11
```

Because:

```text
small <= partner
```

The pending element can be inserted without searching beyond its partner.

Therefore, binary search only examines the sorted main chain from the beginning up to, but **excluding, its partner's position**.

### Example

```text
Pending element: b3 = 8
Partner:         a3 = 56

Main chain:
[5] [6] [7] [56]

Search range:
[5] [6] [7] | [56]
             ↑ partner excluded

Insert 8:
[5] [6] [7] [8] [56]
```

---

## 4. Straggler

When the input contains an odd number of elements, the last element has no partner.

**Example:**

```text
Input:
3 2 1 6 5

Pairs:
(2,3) (1,6)

Straggler:
5
```

The straggler is kept aside while the paired elements are processed.

It is later inserted into the sorted main chain using binary search.


---

## 5. Key Idea

Ford–Johnson combines pairing, recursion, Jacobsthal insertion ordering, and binary search to minimize comparisons.

```text
PAIR
  ↓
Create (small, big) pairs
  ↓
RECURSION
  ↓
Sort the larger elements
  ↓
MAIN CHAIN
  ↓
Sorted larger elements
  ↓
PENDING CHAIN
  ↓
Smaller elements waiting to be inserted
  ↓
JACOBSTHAL
  ↓
Choose WHICH pending element to insert
  ↓
BINARY SEARCH
  ↓
Find WHERE to insert it
  ↓
STRAGGLER
  ↓
Insert the leftover element, if any
  ↓
SORTED SEQUENCE
```

### Summary

| Concept | Purpose |
| ------- | ------- |
| **Ford–Johnson** | Complete merge-insertion sorting algorithm |
| **Pairing** | Organizes elements into `(small, big)` pairs |
| **Recursion** | Sorts the larger elements |
| **Main chain** | Maintains sorted elements |
| **Pending chain** | Stores smaller elements waiting for insertion |
| **Jacobsthal** | Determines WHICH pending element to insert next |
| **Binary search** | Determines WHERE the element belongs |
| **Straggler** | Leftover element when the input size is odd |

### In short

The goal of **`Ford–Johnson (Merge-Insertion Sort)`** is to sort elements using as **few comparisons\*** as possible,
`Jacobsthal` decides **WHICH** element to insert next. `Binary search` decides **WHERE** that element belongs.


- **\*Comparison** is one decision about the relative order of two elements, usually using <, >, or an equivalent comparator.