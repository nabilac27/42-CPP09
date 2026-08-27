<p align="center">
  <img src="https://cdn-icons-png.flaticon.com/512/6132/6132222.png" width="60" alt="C++ Logo">
</p>

<h1 align="center">CPP Module 09</h1>

## Overview
CPP Module 09 focuses on the **Standard Template Library (STL)** and introduces more advanced usage of **containers, algorithms, parsing, and sorting**.

| Exercise | Description | Container |
|----------|-------------|---------------|
| **ex00 — Bitcoin Exchange** | Calculate the value of Bitcoin on a given date using historical exchange-rate data. | `std::map` |
| **ex01 — Reverse Polish Notation** | Evaluate mathematical expressions written in Reverse Polish Notation. | `std::stack` |
| **ex02 — PmergeMe** | Sort a sequence of positive integers using the Ford-Johnson merge-insertion algorithm. | `std::vector`, `std::deque` |



**Each exercise** requires the use of at least **one STL container**, with the final exercise requiring two different containers.


---


## Concepts Learned 

<details>
<summary><b>STL</b></summary>

### Standard Template Library (STL)

The **Standard Template Library**, or STL, is a collection of reusable C++ components.

It mainly consists of:

* **Containers** for storing data.

* **Algorithms** for searching, sorting, and manipulating data.

* **Iterators** for navigating through containers.

---


### Containers

A **container** is a class that stores a collection of objects.

- Different containers are designed for different operations.


    ```shell
            | Container     | Description                                          |
            | ------------- | ---------------------------------------------------- |
            | `std::vector` | Dynamic array with fast random access.               |
            | `std::list`   | Doubly linked list with fast insertion and deletion. |
            | `std::deque`  | Double-ended queue with fast insertion at both ends. |
            | `std::stack`  | Last-in, first-out container adapter.                |
            | `std::set`    | Stores unique values in sorted order.                |
            | `std::map`    | Stores sorted key-value pairs.                       |
    ```



---

### Algorithms
**C++ STL Algorithm Library** provides predefined functions for performing common operations such as searching, sorting, counting, comparing, and modifying data stored in containers. 

These algorithms are mainly defined in the `<algorithm>` header files.

Common types of algorithms:
1. `std::find()` : Searches for an element and returns its iterator if present.
2. `std::distance()` : Calculates the number of increments needed to go from one iterator to another.
3. `sort()`:  Arranges elements in a given range into ascending order by default.

---

### Iterators

An **iterator** is an object that behaves similarly to a pointer and allows you to **traverse and access elements** in a container.


- STL algorithms such as `std::sort()`, `std::find()`, and `std::count()` work with iterators.

- An iterator can be declared using the container's iterator type:

    ```cpp
        std::vector<int>::iterator it;
    ```

    Or obtained directly from the container:

    ```cpp
        std::vector<int>::iterator it = v.begin();
    ```

### Common Iterator Functions
- `.begin()`  → Returns an iterator pointing to the first element.
- `.end()`  →  Returns an iterator pointing one position past the last element.

---

### Algorithm + Iterator
```shell
        Container
            │
            ▼
        Iterators
        ┌───┴───┐
     begin()  end()
        │       │
        └───┬───┘
            ▼
        Algorithm
            │
            ▼
       operates on
          range
```

For example:

```cpp
        std::sort(v.begin(), v.end());

        v.begin()   → start of the range
        v.end()     → one position past the last element
        std::sort() → operates on that range
```


```cpp
    begin()                       end()
       ↓                           ↓
    [10] [30] [20] [40] [50]     [end]
     └────────── range ────────────┘
                    │
                    ▼
                std::sort()
                    │
                    ▼
             [10] [20] [30] [40] [50]
```

</details>

---

<details>
<summary><b><code>std::map</code></b></summary>

----

- `std::map` stores **key-value pairs**.
- Each **key is unique**.
- Elements are automatically **sorted by key**.
- Supports ordered operations such as `lower_bound()` and `upper_bound()`.

    ```cpp
            #include <map>

            std::map<key_type, value_type> map;
    ```

- In Bitcoin Exchange:

    ```cpp
            std::map<std::string, double> database;
    ```

    ```text
            std::map <    KEY      ,  VALUE  >
                        ↓           ↓
                    std::string     double
                        ↓           ↓
                        date          rate
    ```

- Example:

    ```text
            2011-01-01 → 0.3
            2011-01-02 → 0.4
            2011-01-03 → 10
    ```

    ### Iterator

    ```cpp
        std::map<std::string, double>::const_iterator it;
    ```

    Each map element is a key-value pair:

    ```text
            map element
                │
            ┌────┴────┐
            ↓         ↓
        first     second
            ↓         ↓
        KEY       VALUE
            ↓         ↓
        date        rate
    ```

    ```cpp
        it->first;   // date
        it->second;  // exchange rate
    ```

### `lower_bound()` vs `upper_bound()`

- **`lower_bound()`**

    Returns an iterator to the **first key greater than or equal to (`>=`)** the requested key.

    ```cpp
        it = database.lower_bound(date);
    ```

    Example:

    ```text
        Requested: 2011-01-06

        2011-01-01
        2011-01-04  ← closest earlier date
        2011-01-10  ← lower_bound()
    ```

    ```text
        lower_bound(x) → first key >= x
    ```

    If the exact date exists, `lower_bound()` points directly to it:

    ```text
        Requested: 2011-01-04

        2011-01-01
        2011-01-04  ← lower_bound()
        2011-01-10
    ```

---

- **`upper_bound()`**

    Returns an iterator to the **first key greater than (`>`)** the requested key.

    ```cpp
        it = database.upper_bound(date);
    ```

    Example:

    ```text
        Requested: 2011-01-06

        2011-01-01
        2011-01-04  ← closest earlier date
        2011-01-10  ← upper_bound()
    ```

    Then move one position backward:

    ```cpp
        --it;
    ```

    ```text
        2011-01-04  ← result
    ```

    It also works when the exact date exists:

    ```text
        Requested: 2011-01-04

        2011-01-01
        2011-01-04  ← result after --it
        2011-01-10  ← upper_bound()
    ```

    Therefore Bitcoin Exchange can simply use:

    ```cpp
        it = database.upper_bound(date);

        if (it == database.begin())
            return (false);

        --it;
    ```

    This gives the **exact date if it exists**, otherwise the **closest earlier date**.

- **Summary**

    ```text
        map              → key → value

        it->first        → key / date
        it->second       → value / rate

        begin()          → first element
        end()            → after last element

        lower_bound(x)   → first key >= x
        upper_bound(x)   → first key >  x

        --it             → previous element
    ```

    https://www.geeksforgeeks.org/cpp/map-associative-containers-the-c-standard-template-library-stl/

</details>

---

<details>
<summary><b><code>std::stack</code></b></summary>

---

- `std::stack` is a container adapter that follows **LIFO**:

    ```text
        Last In, First Out
    ```

- The last value pushed into the stack is the first one removed.

    ```cpp
        #include <stack>

        std::stack<value_type> stack;
    ```

- In RPN:

    ```cpp
        std::stack<int> numbers;
    ```

    ```text
    std::stack < VALUE >
                   ↓
                  int
                   ↓
                operand
    ```

- Example:

    ```text
        push(7)
        push(3)

        stack:

            TOP
            ↓
            [3]
            [7]
    ```

### Main Operations

- **`push()`**

    Adds a value to the top of the stack.

    ```cpp
        numbers.push(7);
        numbers.push(3);
    ```

    ```text
        TOP
         ↓
        [3]
        [7]
    ```

- **`top()`**

    Returns the value currently at the top.

    ```cpp
    int value = numbers.top();
    ```

    ```text
        TOP
         ↓
        [3]  → top() = 3
        [7]
    ```

    `top()` does **not** remove the value.

- **`pop()`**

    Removes the top value.

    ```cpp
        numbers.pop();
    ```

    Before:

    ```text
        [3] ← TOP
        [7]
    ```

    After:

    ```text
        [7] ← TOP
    ```

    `pop()` does **not return** the removed value.

    So normally:

    ```cpp
        int value = numbers.top();
        numbers.pop();
    ```

- **`size()`**

    Returns the number of elements.

    ```cpp
        numbers.size();
    ```

- **`empty()`**

    Checks whether the stack contains no elements.

    ```cpp
        numbers.empty();
    ```

</details>


---

<details>
<summary><b><code>std::vector</code></b></summary>

---

- Dynamic array that stores elements in **contiguous memory**.
- Fast random access with `operator[]`.
- Efficient `push_back()`.
- Inserting/removing in the middle can be expensive because elements may need to move.

    ```cpp
        #include <vector>

        std::vector<int> numbers;
    ```

    ```text
        [3][5][9][7][4]
        ↑  ↑  ↑  ↑  ↑
        contiguous memory
    ```

- **Common Operations**

    ```cpp
        numbers.push_back(5);    // add at end
        numbers.pop_back();      // remove last
        numbers[0];              // access by index
        numbers.size();          // number of elements
        numbers.begin();         // first element
        numbers.end();           // after last element
    ```
- **Summary**

    ```text
        vector
        → dynamic array
        → contiguous memory
        → fast random access
        → efficient push_back()
    ```

- Used in `PmergeMe` as one of the two containers for Ford-Johnson sorting.

</details>

---


<details>
<summary><b><code>std::deque</code></b></summary>

---

- `deque` means **double-ended queue**.
- Supports efficient insertion/removal at **both front and back**.
- Unlike `vector`, its elements are not guaranteed to be stored in one contiguous memory block.
- Still supports random access with `operator[]`.

    ```cpp
        #include <deque>

        std::deque<int> numbers;
    ```

- **Common Operations**

    ```cpp
        numbers.push_back(5);     // add at back
        numbers.push_front(5);    // add at front

        numbers.pop_back();       // remove back
        numbers.pop_front();      // remove front

        numbers[0];               // random access
        numbers.size();
        numbers.begin();
        numbers.end();
    ```

- `Vector` vs `Deque`

    ```text
                        vector              deque
        ────────────────────────────────────────────
        Memory          contiguous          segmented
        push_back       fast                fast
        push_front      expensive           fast
        random access   yes                 yes
    ```

- **Summary**

    ```text
        deque
        → double-ended queue
        → fast front + back operations
        → random access
        → non-contiguous storage
    ```

- Used in `PmergeMe` as the second container for Ford-Johnson sorting.

</details>

---


<details>
<summary><b>Reverse Polish Notation</b></summary>

---

- RPN places the **operator after its operands**.

    ```text
        Normal:
        7 + 3

        RPN:
        7 3 +
    ```

- It is naturally evaluated using a `std::stack`.

- **Main Idea**

    ```text
        NUMBER
        ↓
        push()

        OPERATOR
        ↓
        pop right
        pop left
        ↓
        calculate left OP right
        ↓
        push(result)

        END
        ↓
        exactly 1 value must remain
    ```

    Example:

    ```text
        Expression: 7 7 * 7 7 + -

        Token     Stack           Operation
        ────────────────────────────────────────
        7         [7]             push(7)

        7         [7, 7]          push(7)

        *         [49]            7 * 7 = 49
                                push(49)

        7         [49, 7]         push(7)

        7         [49, 7, 7]      push(7)

        +         [49, 14]        7 + 7 = 14
                                push(14)

        -         [35]            49 - 14 = 35
                                push(35)

        Result: 35
    ```

- **Important**

  - For `-` and `/`, operand order matters:

      ```cpp
          int right = numbers.top();
          numbers.pop();

          int left = numbers.top();
          numbers.pop();
      ```

  - Then:

      ```text
      left - right
      left / right
      ```

- **Summary**

    ```text
        RPN number    → push
        RPN operator  → pop 2 → calculate → push
        final stack   → must contain exactly 1 result
    ```

</details>


---

<details>
<summary><b>Ford-Johnson Algorithm (merge-insertion sort)</b></summary>

---

- The **Ford–Johnson algorithm**, also called the **merge-insertion sort**, is a sorting algorithm designed to sort elements using a small number of comparisons.

- Basic Idea:
  
    ```cpp
        Numbers
        ↓
        Make pairs
        ↓
        Compare each pair
        ↓
        Separate small and big elements
        ↓
        Sort the big elements
        ↓
        Insert the small elements
        ↓
        Sorted result
    ```

- In one sentence: Ford–Johnson first creates ordered pairs, recursively sorts the larger elements, and then inserts the smaller elements in a carefully chosen order.
</details>

---

## Exercises

<details>
<summary><b>Ex00</b></summary>

---

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
- If an exact date does not exist, the **closest earlier date** is used.
- Each value must be between `0` and `1000`.

- **Program Flow**

    ```text
                    ./btc input.txt
                            │
                            ▼
                    BitcoinExchange btc
                            │
                ┌───────────┴───────────┐
                ▼                       ▼
        loadDataCsv()            processInputTxt()
                │                       │
                ▼                       ▼
            data.csv                 input.txt
                │                       │
                ▼                       ▼
        load date → rate          read each line
                │                       │
                ▼                       ▼
            std::map              processInputLine()
                                        │
                                        ▼
                                    parseDateValue()
                                         │
                            ┌────────────┴────────────┐
                            ▼                         ▼
                        isValidDate()             isValidValue()
                            │                         │
                            └────────────┬────────────┘
                                        ▼
                                findExchangeRate()
                                        │
                                        ▼
                                `map::upper_bound()`
                                        │
                                        ▼
                            exact / closest lower date
                                        │
                                        ▼
                                value × exchange rate
                                        │
                                        ▼
                                        output
    ```

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

      ```text
          3 × 0.3 = 0.9
      ```

  - Output:

      ```text
          2011-01-03 => 3 = 0.9
    ```


</details>

---

<details>
<summary><b>Ex01</b></summary>

## ex01 | RPN

- The goal of **RPN (Reverse Polish Notation)** is to calculate a mathematical expression where the operator comes after the numbers.

- Normal notation:
  
    ```cpp
        7 * 7 - 7
    ```
- RPN:

    ```cpp
        7 7 * 7 -
    ```

- **Program Flow**
  
    ```cpp
                    Read token
                        │
          ┌─────────────┼─────────────┐
          │             │             │
          ▼             ▼             ▼
       Number        Operator       Invalid
          │             │             │
          ▼             ▼             ▼
   Convert to int   Need 2 values    Error
          │             │
          ▼             ▼
       push()       pop() → right
                        │
                        ▼
                   pop() → left
                        │
                        ▼
                    calculate()
                        │
                        ▼
                  push(result)
                        │
          ┌─────────────┘
          │
          ▼
     Read next token
          │
          ▼
   End of expression
          │
          ▼
   stack.size() == 1?
       ┌──┴──┐
       ▼     ▼
      YES    NO
       │      │
       ▼      ▼
     Print   Error
     result
    ````

    ```cpp
        NUMBER   → push
        OPERATOR → pop, pop, calculate, push
        END      → stack must contain exactly 1 value
    ```

- **Example**

    ```shell
        Expression: 7 7 * 7 -

        Token           Stack
        ──────────────────────
        7               [7]

        7               [7, 7]

        *               [49]

        7               [49, 7]

        -               [42]

        Result: 42
    ```

    ```shell
        Expression: 7 7 * 7 7 + -

        Token           Stack               Operation
        ────────────────────────────────────────────────────────
        7               [7]                 push(7)

        7               [7, 7]              push(7)

        *               [49]                pop 7, pop 7
                                            7 * 7 = 49
                                            push(49)

        7               [49, 7]             push(7)

        7               [49, 7, 7]          push(7)

        +               [49, 14]            pop 7, pop 7
                                            7 + 7 = 14
                                            push(14)

        -               [35]                pop 14 → right
                                            pop 49 → left
                                            49 - 14 = 35
                                            push(35)

        Result: 35
    ```
</details>

---

<details>
<summary><b>Ex02</b></summary>
</details>

---


## Resources
- https://www.geeksforgeeks.org/cpp/containers-cpp-stl/
- https://www.geeksforgeeks.org/cpp/c-magicians-stl-algorithms/
- https://www.geeksforgeeks.org/cpp/iterators-c-stl/
- https://cplusplus.com/reference/stack/stack/

