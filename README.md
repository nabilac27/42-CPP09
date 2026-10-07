<p align="center">
  <img src="https://cdn-icons-png.flaticon.com/512/6132/6132222.png" width="60" alt="C++ Logo">
</p>

<h1 align="center">CPP Module 09</h1>

## Overview
CPP Module 09 focuses on the **Standard Template Library (STL)** and introduces more advanced usage of **containers, algorithms, parsing, and sorting**.


| Exercise | Description | Container |
|----------|-------------|---------------|
| **ex00 — Bitcoin Exchange** | Calculate the value of Bitcoin on a given date using historical exchange-rate data. | `std::map` |
| **ex01 — Reverse Polish Notation** | Evaluate mathematical expressions written in Reverse Polish Notation. | `std::list` |
| **ex02 — PmergeMe** | Sort a sequence of positive integers using the Ford-Johnson merge-insertion algorithm. | `std::vector`, `std::deque` |


Each exercise requires the use of at least one **STL container**, with the final exercise requiring two different containers.


---

## Concepts Learned 

<details>
<summary><b>STL</b></summary>

### Standard Template Library (STL)

The Standard Template Library, or STL, is a collection of reusable C++ components.

It mainly consists of:

* Containers for storing data.

* Algorithms for searching, sorting, and manipulating data.

* Iterators for navigating through containers.

---

### Containers

A container is a class that stores a collection of objects.

- Different containers are designed for different operations.

    ```shell

            | Container     | Description                                          |
            | ------------- | ---------------------------------------------------- |
            | `std::vector` | Dynamic array with fast random access.               |
            | `std::list`   | Doubly linked list with fast insertion and deletion. |
            | `std::deque`  | Double-ended queue with fast insertion at both ends. |
            | `std::stack`  | Last-in, first-out container adapter.                |
            | `std::map`    | Stores sorted key-value pairs.                       |

    ```

---

### Algorithms

C++ STL Algorithm Library provides predefined functions for performing common operations such as searching, sorting, counting, comparing, and modifying data stored in containers. 

These algorithms are mainly defined in the `<algorithm>` header files.

- Common types of algorithms:

    ```shell

            | Functions         | Description                                                                      |
            | ----------------- | -------------------------------------------------------------------------------- |
            | `std::find()`     | Searches for an element and returns its iterator if present.                     |
            | `std::distance()` | Calculates the number of increments needed to go from one iterator to another.   |
            | `sort()`          | Arranges elements in a given range into ascending order by default.              |
    ```

---

### Iterators

An iterator is an object that behaves similarly to a pointer and allows you to traverse and access elements in a container.

- STL algorithms such as `std::sort()`, `std::find()`, and `std::count()` work with iterators.

- An iterator can be declared using the container's iterator type:

    ```cpp

        std::vector<int>::iterator it;

    ```

    Or obtained directly from the container:

    ```cpp

        std::vector<int>::iterator it = v.begin();

    ```

- Common Iterator Functions
    ```shell

            | Functions         | Description                                                                      |
            | ----------------- | -------------------------------------------------------------------------------- |
            | `.begin()`        | Returns an iterator pointing to the first element.                               |
            | `.end()`          | Returns an iterator pointing one position past the last element.                 |
    ```

</details>

---

<details>
<summary><b><code>std::map</code></b></summary>

---

- `std::map` stores **sorted key-value pairs**.
- Each key is unique.

    ```cpp
        #include <map>

        std::map<std::string, double> database;
    ```
- In Bitcoin Exchange:
  
    ```cpp
    std::map <    KEY      ,  VALUE  >
                ↓            ↓
                date          rate

    ```

- Iterator

    ```cpp
        std::map<std::string, double>::const_iterator it;

        it->first;   // key / date
        it->second;  // value / rate

        lower_bound() vs upper_bound()

        lower_bound(x) → first key >= x
        upper_bound(x) → first key >  x
    ```
- Bitcoin Exchange uses:

    ```cpp
        it = database.upper_bound(date);

        if (it == database.begin())
            return (false);

        --it;
    ```
- This gives the exact date if it exists, otherwise the closest earlier date.

- Summary

    ```shell
        map              → key → value
        it->first        → key
        it->second       → value
        begin()          → first element
        end()            → after last element
        lower_bound(x)   → first key >= x
        upper_bound(x)   → first key > x
        --it             → previous element
    ```
</details>

---

<details>
<summary><b><code>std::list</code></b></summary>

---

- `std::list` is a doubly linked list.
- No random access with operator[].
- Efficient insertion/removal when the position is known.

    ```cpp
        #include <list>

        std::list<long long> numbers;

        [3] ↔ [5] ↔ [9]
        ↑             ↑
        front         back

        In RPN, the back is used like the top of a stack:

        numbers.push_back(8);   // add
        numbers.back();         // read last
        numbers.pop_back();     // remove last

        std::stack          std::list
        ──────────────────────────────
        push(x)             push_back(x)
        top()               back()
        pop()               pop_back()
        size()              size()
        empty()             empty()
    ```

- Summary

    ```shell
        list
        → doubly linked list
        → no operator[]
        → no random access
        → fast front/back operations
        → back() can act like stack top
    ```
</details>

---

<details>
<summary><b><code>std::vector</code></b></summary>

---

- Dynamic array using contiguous memory.
- Fast random access with operator`[]`.
- Efficient `push_back()`.
- Middle insertion/removal can be expensive.

    ```cpp
        #include <vector>

        std::vector<int> numbers;
    ```

- Common Operations

    ```cpp
        numbers.push_back(5);
        numbers.pop_back();
        numbers[0];
        numbers.size();
        numbers.begin();
        numbers.end();
    ````

- Summary

    ```cpp
        vector
        → dynamic array
        → contiguous memory
        → fast random access
        → efficient push_back()
    ```
- Used in `PmergeMe` as one of the two containers for `Ford-Johnson sorting`.

</details>

---

<details>
<summary><b><code>std::deque</code></b></summary>

----

- `deque` means double-ended queue.
- Fst insertion/removal at both ends.
- Supports random access with operator`[]`.
- Memory is not guaranteed to be contiguous.
    ```cpp
        #include <deque>

        std::deque<int> numbers;
    ```

- Common Operations

    ```cpp
        numbers.push_back(5);
        numbers.push_front(5);

        numbers.pop_back();
        numbers.pop_front();

        numbers[0];
        numbers.size();
        numbers.begin();
        numbers.end();
    ```

- `vector` vs `deque` vs `list`

    ```cpp
                        vector       deque        list
        ───────────────────────────────────────────────
        Memory          contiguous   segmented    linked
        Random access   yes          yes          no
        operator[]      yes          yes          no
    ```

- Used in `PmergeMe` as the second container for `Ford-Johnson sorting`.

</details>

---

## Exercises

<details>
<summary><b>ex00 | Bitcoin Exchange</b></summary>

## ex00 | Bitcoin Exchange

- A program that calculates the value of Bitcoin on a given date using historical exchange rates from `data.csv`.

- The program uses two files:

    ```text
        data.csv                    input.txt
        ────────                    ─────────
        date,exchange_rate          date | value

        2011-01-03,0.3              2011-01-03 | 3
        2011-01-09,0.32             2011-01-09 | 2
            │                           │
            ▼                           ▼
        historical rates           values to calculate
    ```

- `data.csv` contains the historical Bitcoin exchange rates.

- `input.txt` contains the requested dates and Bitcoin amounts.

- The exchange rates are stored in a `std::map`.

- If an exact date does not exist, the closest earlier date is used.

- Each value must be between `0` and `1000`.

- **Example**
    
    ```bash
        ./btc input.txt
    ```

  -  input.txt

      ```text
          date        | value
          2011-01-03  | 3

      ```

  - data.csv

      ```text
          date        ,exchange_rate
          2011-01-03  ,0.3

      ```

  - Calculation:

      ```cpp
          3 × 0.3 = 0.9
      ```

  - Output:

      ```cpp
          2011-01-03 => 3 = 0.9
    ```

</details>



---
<details>
<summary><b>ex01 | RPN</b></summary>

## ex01 | RPN

- The goal of RPN (Reverse Polish Notation) is to calculate a mathematical expression where the operator comes after the numbers.

- Normal notation:

   ```text
   7 * 7 - 7
   ```

- RPN:

   ```text
   7 7 * 7 -
   ```

- In this implementation, a `std::list` stores the operands:

   ```cpp
   std::list<long long> numbers;
   ```

- The back of the list acts like the top of a stack:

   ```text
   [7] ↔ [3]
         ↑
         back
   ```

-  **Example**

   ```text
   Expression: 7 7 * 7 7 + -

   Token           List                Operation
   ─────────────────────────────────────────────────────────
   7               [7]                 push_back(7)

   7               [7, 7]              push_back(7)

   *               [49]                7 * 7 = 49
                                       push_back(49)

   7               [49, 7]             push_back(7)

   7               [49, 7, 7]          push_back(7)

   +               [49, 14]            7 + 7 = 14
                                       push_back(14)

   -               [35]                right = 14
                                       left  = 49
                                       49 - 14 = 35
                                       push_back(35)

   Result: 35
   ```

- **Summary**

   ```text
      NUMBER
         ↓
      push_back()

      OPERATOR
         ↓
      back() → right
      pop_back()
         ↓
      back() → left
      pop_back()
         ↓
      calculate(left, right, operator)
         ↓
      push_back(result)

      END
         ↓
      size() == 1
         ↓
      numbers.back()
         ↓
      RESULT
   ```

</details>

---

<details>
<summary><b>ex02 | PmergeMe</b></summary>

## ex02 | PmergeMe

- `PmergeMe` sorts a sequence of positive integers using the **Ford-Johnson algorithm**, also known as **merge-insertion sort**.

- The algorithm is designed to sort elements using a small number of comparisons.

- Reference: [Merge-insertion sort - Wikipedia](https://en.wikipedia.org/wiki/Merge-insertion_sort)

- The same algorithm is executed separately using:

    ```cpp
    std::vector<int>
    std::deque<int>
    ```


### Ford-Johnson Algorithm

The algorithm follows these main steps:

1. **Make pairs**
   
    - Group the elements into pairs. 
    
    - If the number of elements is odd, keep one element unpaired as a straggler.

2. **Compare each pair**
    - Compare the two elements and arrange them as: (small, big)

3. **Recursively sort the larger elements**
    - Take the larger element from each pair and recursively sort them using Ford-Johnson.

4. **Insert the first smaller element**
    - Insert the element paired with the smallest element of the sorted main chain at the beginning.

5. **Insert the remaining smaller elements**
    - Insert them in a specially chosen order and use binary search to find their positions.


### Main Logic
- 
    ```cpp
            Numbers
            │
            ▼
            Make pairs
            │
            ▼
            Order each pair
            (small, big)
            │
            ▼
            Recursively sort BIG values
            │
            ▼
            Create Main + Pending chains
            │
            ▼
            Insert first pending
            │
            ▼
            Insert remaining pending
            │
            ├── Jacobsthal    → WHICH element to insert next
            └── Binary Search → WHERE to insert it
            │
            ▼
            Insert straggler
            │
            ▼
        SORTED
    ```

### Example

- Input:
    ```cpp
    3 2 1 6 5 9 7 11
    ```
            ↓ make pairs
    ```cpp
    (3,2) (1,6) (5,9) (7,11)
    ```
        ↓ order each pair
    ```cpp
    (2,3) (1,6) (5,9) (7,11)
     ↑ ↑
     │ └── big
     └──── small
    ```
        ↓ recursively sort by BIG values

    ```cpp
    3 6 9 11
    ```
    ↓ create chains

    ```cp
    Main:       3 6 9 11

    Pending:
                2 → partner 3
                1 → partner 6
                5 → partner 9
                7 → partner 11
    ```
        ↓ insert first pending

    ```cpp
    2 3 6 9 11
    ```
        ↓ insert remaining pending

    ```cpp
    Jacobsthal    → WHICH element comes next
    Binary Search → WHERE it should be inserted
    ```
        ↓
    ```cpp
    1 2 3 5 6 7 9 11
    ```

- **Jacobsthal Insertion Order**

    `Ford-Johnson` does not simply insert the pending elements from left to right.
 
    - The uninserted elements are divided into groups:

        2, 2, 6, 10, 22, 42, ...

    - The elements inside each group are processed in reverse order.

    - ❗ This ordering is related to the `Jacobsthal sequence` and is chosen so that the binary-search ranges are often one less than a power of two:
        
        1, 3, 7, 15, 31, ...


    - These sizes are efficient for `binary search` because the search tree can be balanced, 
        
        helping reduce the worst-case number of comparisons.



- So the two ideas have different jobs:

    - **Jacobsthal**            

        ↓

        WHICH pending element should I insert next?


    - **Binary Search**

        ↓

        WHERE should I insert that element?


- Partner-Limited Binary Search


    Each pending value remains associated with its larger partner:


    small → partner

    ```cpp
        2 → 3
        1 → 6
        5 → 9
        7 → 11
    ```

  Because:

    small < partner

    - the pending value never needs to be searched after its partner.
    - Therefore, binary search is performed only from the beginning of the main chain up to, but not including, its partner:

        ```cpp
            partnerPosition = std::find(mainChain.begin(), mainChain.end(), partner);

            position        = std::lower_bound(mainChain.begin(), partnerPosition, value);

            mainChain.insert(position, value);
        ```

- This restricted search range is an important part of `Ford-Johnson`.

    - **`Straggler`**

        If the input contains an odd number of elements:

        3 2 1 6 5

        - one element has no partner:

        ```cpp
        Pairs:
                    (2,3) (1,6)

        Straggler:
                    5
        ```

    - The `straggler` is kept aside and inserted into the sorted chain later using `binary search`.


### Implementation
- 
    ```cpp
        Ford-Johnson               PmergeMe
        ────────────────────────────────────────────
        Make pairs              →  makePairs()

        Sort pairs recursively  →  sortPairs()

        Create chains           →  createChains()

        Insert first pending    →  insertFirstPending()

        Jacobsthal order        →  generateInsertionOrder()

        Binary insertion        →  insertPending()

        Insert odd element      →  insertStraggler()
    ```


### Key Idea
- `Ford-Johnson` pairs the elements, recursively sorts the larger elements, then inserts the smaller elements in a specially chosen `Jacobsthal`-based order using `binary search`.

    ```cpp
        PAIR        → create (small, big)

        RECURSION   → sort the big values

        MAIN CHAIN  → sorted big values

        PENDING     → small values waiting to be inserted

        JACOBSTHAL  → WHICH pending element to insert next

        BINARY      → WHERE to insert that element

        STRAGGLER   → leftover element when input size is odd
    ```


</details>

---

## Resources

- https://www.geeksforgeeks.org/cpp/containers-cpp-stl/

- https://www.geeksforgeeks.org/cpp/c-magicians-stl-algorithms/

- https://www.geeksforgeeks.org/cpp/iterators-c-stl/

- https://cplusplus.com/reference/stack/stack/

