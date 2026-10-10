<p align="center">
  <img src="https://cdn-icons-png.flaticon.com/512/6132/6132222.png" width="60" alt="C++ Logo">
</p>

<h1 align="center">CPP Module 09</h1>

## Overview
CPP Module 09 focuses on the **Standard Template Library (STL)** and introduces more advanced usage of **containers, algorithms, parsing, and sorting**.


| Exercise | Description | Container |
|----------|-------------|---------------|
| **ex00 — Bitcoin Exchange** | Calculate the value of Bitcoin on a given date using historical exchange-rate data. | `std::map` |
| **ex01 — Reverse Polish Notation** | Evaluate mathematical expressions written in `Reverse Polish Notation`. | `std::list` |
| **ex02 — PmergeMe** | Sort a sequence of positive integers using the `Ford-Johnson merge-insertion` algorithm. | `std::vector`, `std::deque` |


Each exercise requires the use of at least one **STL container**, with the final exercise requiring two different containers.


---

## Concepts Learned 

<details>
<summary><b>STL</b></summary>

### Standard Template Library (STL)

The **Standard Template Library**, or **STL**, is a collection of reusable C++ components.

It mainly consists of:

* **Containers** for storing data.

* **Algorithms** for searching, sorting, and manipulating data.

* **Iterators** for navigating through containers.

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

- **`std::map`** stores **sorted key-value pairs**.
- Each `key` is unique.

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

- **Summary**

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

- **`std::list`** is a **doubly linked list**.
- No random access with `operator[]`.
- Efficient insertion/removal when the position is known.

    ```cpp
        #include <list>

        std::list<long long> numbers;

        [3] ↔ [5] ↔ [9]
        ↑             ↑
        front         back
    ```

- In **`RPN`**, the `back` is used like the `top` of a `stack`:
    ```cpp
        numbers.push_back(8);   // add element to the back
        numbers.back();         // read last element
        numbers.pop_back();     // remove last last element


        std::stack          std::list
        ──────────────────────────────
        push(x)             push_back(x)
        top()               back()
        pop()               pop_back()
        size()              size()
        empty()             empty()
    ```

- **List-based Stack Example**
  ```cpp
        Initial:        []

        push_back(3):   [3]

        push_back(5):   [3] ↔ [5]

        push_back(9):   [3] ↔ [5] ↔ [9]
                        ↑             ↑
                        front          back

        back()      :   9

        pop_back()  :   [3] ↔ [5]
                        ↑       ↑
                        front    back

        push_back(7):   [3] ↔ [5] ↔ [7]
                        ↑             ↑
                        front          back
    ```
</details>

---

<details>
<summary><b><code>std::vector</code></b></summary>

---

- **Dynamic `array`** using contiguous memory.
- Fast random access with operator`[]`.
- Efficient `push_back()`.

    ```cpp
        #include <vector>

        std::vector<int> numbers;
    ```

- **Common Operations**

    ```cpp
        numbers.push_back(5);  // Add at the end
        numbers.pop_back();    // Remove last element
        numbers.back();        // Access last element
        numbers[0];            // Access element by index
        numbers.size();        // Number of elements
        numbers.begin();       // Iterator to first element
        numbers.end();         // Iterator past last element
    ```

    ```cpp
    Index:       0     1     2
               ┌─────┬─────┬─────┐
    Vector:    │  3  │  5  │  9  │
               └─────┴─────┴─────┘
                 ↑           ↑
              begin()       back()
    ```

- Used in `PmergeMe` as one of the two containers for `Ford-Johnson sorting`.

</details>

---

<details>
<summary><b><code>std::deque</code></b></summary>

----

- **`deque`** means double-ended queue.
- Fst insertion/removal at both ends.
- Supports random access with `operator[]`.
- Memory is not guaranteed to be contiguous.
    ```cpp
        #include <deque>

        std::deque<int> numbers;
    ```

- **Common Operations**

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

- Used in `PmergeMe` as the second container for `Ford-Johnson sorting`.

</details>

---

<details>
<summary><b><code>std::vector</code> vs <code>std::deque</code> vs <code>std::list</code></b></summary>

----

- **Visual comparison**
  - **`std::vector`** | **Dynamic array**
    - Elements are stored next to each other in **contiguous memory**. 
    - Very **fast indexing** with numbers[i].

        ```cpp
            [3] [5] [9] [7]
        ```

  - **`std::list`** | **Doubly linked list**
    - Elements are **not contiguous** in memory.
    - **Efficient** insertion and removal using iterators.

        ```cpp
            [3] <-> [5] <-> [9] <-> [7]
        ```


  - **`std::deque`** | **Double-ended queue**
    - Elements stored in **segmented memory** (multiple blocks).
    - **Efficient** insertion and removal at both ends, plus **fast indexing** with numbers[i].

        ```cpp
            Block 1       Block 2
            [3][5]        [9][7]

        ```
    <details><summary><b>Contiguous vs Segmented Memory</b></summary>
    
    ---

     - **Contiguous**
        
                Memory addresses (illustrative):

                1000   1004   1008   1012
                ↓      ↓      ↓      ↓
                [ 3 ] [ 5 ] [ 9 ] [ 7 ]

        - All elements are stored next to each other.
        - For example, if each int occupies 4 bytes, their addresses differ by 4 bytes.
    
    - **Segmented**
            
                Memory addresses (illustrative):

                Block A                  Block B
                1000   1004              5000   5004
                ↓      ↓                 ↓      ↓
                [ 3 ] [ 5 ]             [ 9 ] [ 7 ]
                    contiguous              contiguous

                Different memory locations
            
        - Elements within each block are contiguous, 
        - but the blocks themselves can be stored at completely different memory addresses.
        - The deque maintains an internal structure that keeps track of these blocks.
    ---
    </details>


- **Common operations**

    ```shell
        | Operation        | `std::vector` | `std::list` | `std::deque` |
        |------------------|---------------|-------------|--------------|
        | `push_front(x)`  | ❌            | ✅          | ✅           |
        | `push_back(x)`   | ✅            | ✅          | ✅           |
        | `pop_front()`    | ❌            | ✅          | ✅           |
        | `pop_back()`     | ✅            | ✅          | ✅           |
    ````

- **Summary**
    ```cpp
                        vector       deque        list
        ───────────────────────────────────────────────
        Memory          contiguous   segmented    linked
        Random access   yes          yes          no
        operator[]      yes          yes          no
    ```
  
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

  -  **input.txt**

      ```text
          date        | value
          2011-01-03  | 3

      ```

  - **data.csv**

      ```text
          date        ,exchange_rate
          2011-01-03  ,0.3

      ```

  - **Calculation**

      ```cpp
          3 × 0.3 = 0.9
      ```

  - **Output**

      ```cpp
          2011-01-03 => 3 = 0.9
    ```

- **Exchange Rate Lookup**

    ```cpp
            it = database.upper_bound(date);

            if (it == database.begin())
                return (printError("Error: no earlier date available."));

            --it;
    ```
    - `upper_bound()` returns an iterator to the first key strictly greater than the requested date.
    - Decrementing the iterator selects the latest date less than or equal to the requested date.

### Logic Flow

```cpp
    main(argc, argv)
    │
    ├── 1. Validate arguments
    │   ├── argc != 2 → Print error → return 1
    │   └── argc == 2 → Continue
    │
    ├── 2. Create BitcoinExchange object
    │   └── Initialize an empty std::map<string, double>
    │
    ├── 3. loadDataCsvFile("data.csv")
    │   ├── Open CSV database
    │   ├── Skip header
    │   └── Read each line
    │       ├── Split by ','
    │       ├── Trim whitespace
    │       ├── Convert exchange rate to double
    │       ├── Validate date
    │       ├── Invalid entry → Skip
    │       └── Valid entry → database[date] = rate
    │
    ├── 4. processInputTxtFile(argv[1])
    │   ├── Open input file
    │   ├── Validate "date | value" header
    │   └── Read each line
    │       │
    │       └── processInputLine(line)
    │           │
    │           ├── parseKeyDate()
    │           │   ├── Find '|'
    │           │   ├── Reject missing/multiple separators
    │           │   └── Extract date and value
    │           │
    │           ├── isValidDate()
    │           │   ├── Check YYYY-MM-DD format
    │           │   ├── Check year, month, day
    │           │   └── Check leap years
    │           │
    │           ├── isValidValue()
    │           │   ├── Parse numeric value
    │           │   ├── Reject invalid input
    │           │   ├── Reject negative values
    │           │   └── Reject values > 1000
    │           │
    │           └── findExchangeRate()
    │               ├── Check database is not empty
    │               ├── database.upper_bound(date)
    │               ├── Move to closest earlier/equal date
    │               ├── result = value * exchangeRate
    │               └── Print result
    │
    ├── 5. Exception handling
    │   ├── Exception → Print error → return 1
    │   └── No exception → Continue
    │
    └── 6. return 0
```

</details>



---
<details>
<summary><b>ex01 | RPN</b></summary>

## ex01 | RPN

- This program evaluates mathematical expressions written in **`Reverse Polish Notation (RPN)`**.
- The program takes an **`RPN` expression** as a command-line argument and prints the calculated result to standard output.

  - **Expression** : mathematical calculation written as a **`string`**.
  - **Operands**: Single-digit numbers (**0–9**). 
  - **Operators**: **`+`, `-`, `*`, `/`**
  - **Error handling**: **Invalid expressions** or **calculation errors** are reported to standard error (stderr).


- The goal of **`RPN`** is to calculate a mathematical expression where the **operator comes after the numbers**.

  - Normal notation

     ```text
     7 * 7 - 7
     ```

  - **`RPN`**

     ```text
     7 7 * 7 -
     ```

  - In this implementation, a **`std::list`** stores the operands:

     ```cpp
     std::list<long long> numbers;
     ```

     - I'm using **`std::list`** as a `stack`, following **LIFO: Last In, First Out**.
    - The `back` is the last element of the **`list`** and represent the top of the stack.

  - The `back` of the `list` acts like the top of a `stack`:

     ```text
    front             back
    ↓                 ↓
    [ 7 ] <---------> [ 3 ]
                        ↑
                    (stack) top
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

   -               [35]                49 - 14 = 35
                                       push_back(35)

   Result: 35
   ```



</details>

---

<details>
<summary><b>ex02 | <a href="ex02/README.md">PmergeMe</a></b></summary>

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
    - Take the larger element from each pair and recursively sort them using `Ford-Johnson`.

4. **Insert the first smaller element**
    - Insert the element paired with the smallest element of the sorted main chain at the beginning.

5. **Insert the remaining smaller elements**
    - Insert them in a specially chosen order and use binary search to find their positions.


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

