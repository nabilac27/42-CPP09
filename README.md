<p align="center">
  <img src="https://cdn-icons-png.flaticon.com/512/6132/6132222.png" width="60" alt="C++ Logo">
</p>

<h1 align="center">CPP Module 09</h1>

## Overview
CPP Module 09 focuses on the **Standard Template Library (STL)** and introduces more advanced usage of **containers, algorithms, parsing, and sorting**.

The module contains three exercises:
| Exercise | Description | Main Concepts |
|----------|-------------|---------------|
| **ex00 — Bitcoin Exchange** | Calculate the value of Bitcoin on a given date using historical exchange-rate data. | `std::map`, file parsing, dates, iterators, validation |
| **ex01 — Reverse Polish Notation** | Evaluate mathematical expressions written in Reverse Polish Notation. | `std::stack`, parsing, arithmetic operations |
| **ex02 — PmergeMe** | Sort a sequence of positive integers using the Ford-Johnson merge-insertion algorithm. | `std::vector`, `std::deque`, Ford-Johnson algorithm, timing, iterators |



**Each exercise** requires the use of at least **one STL container**, with the final exercise requiring two different containers.

```cpp
                         CPP09
                           │
          ┌────────────────┼────────────────┐
          │                │                │
          ▼                ▼                ▼
        ex00             ex01             ex02
      Bitcoin            RPN            PmergeMe
      Exchange
          │                │                │
          ▼                ▼                ▼
      std::map          std::stack       std::vector
                                           +
                                         std::deque
          │                │                │
          ▼                ▼                ▼
       Parsing          Parsing          Sorting
          │                │                │
          ▼                ▼                ▼
      Date lookup       Operators      Ford-Johnson
          │                │                │
          ▼                ▼                ▼
     Exchange rate       Result          Benchmark
````

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


- Common member functions:
  
    ```shell
        | Member function | `vector`  | `deque`  | `list`  | Purpose                   |
        | --------------- | --------- | -------- | ------- | ------------------------- |
        | `push_back()`   |     ✅    |    ✅    |    ✅   | Add at the back            |
        | `pop_back()`    |     ✅    |    ✅    |    ✅   | Remove from the back       |
        | `size()`        |     ✅    |    ✅    |    ✅   | Number of elements         |
        | `empty()`       |     ✅    |    ✅    |    ✅   | Check if empty             |
        | `begin()`       |     ✅    |    ✅    |    ✅   | Iterator to first element  |
        | `end()`         |     ✅    |    ✅    |    ✅   | Iterator past last element |
        | `front()`       |     ✅    |    ✅    |    ✅   | First element              |
        | `back()`        |     ✅    |    ✅    |    ✅   | Last element               |
        | `clear()`       |     ✅    |    ✅    |    ✅   | Remove all elements        |
    ```
- There are also container-specific functions.
    for example, vector has:
    ```shell
        capacity()
        reserve()
    ```
    list has:
    ```shell
        push_front()
        pop_front()
    ````

---

### Algorithms
**C++ STL Algorithm Library** provides predefined functions for performing common operations such as searching, sorting, counting, comparing, and modifying data stored in containers. 

These algorithms are mainly defined in the `<algorithm>` header files.

Common types of algorithms:
1. `std::find()` : Searches for an element and returns its iterator if present.
2. `std::min_element()` : Return an iterator to the smallest element.
3. `std::max_element()` : Return an iterator to the largest element.
4. `std::distance()` : Calculates the number of increments needed to go from one iterator to another.
5. `sort()`:  Arranges elements in a given range into ascending order by default.

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
<summary><b>`std::map`</b></summary>
</details>

---

<details>
<summary><b>`std::stack`</b></summary>
</details>

---

<details>
<summary><b>`std::vector`</b></summary>
</details>

---

<details>
<summary><b>`std::deque`</b></summary>
</details>

---

<details>
<summary><b>Reverse Polish Notation</b></summary>
</details>

---

<details>
<summary><b>Ford-Johnson Algorithm (merge-insertion sort)</b></summary>

---

The **Ford–Johnson algorithm**, also called the **merge-insertion sort**, is a sorting algorithm designed to sort elements using a small number of comparisons.

Basic Idea:
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

- Goal
    
    The goal of this exercise is to create a program called btc that calculates the value of a given amount of Bitcoin on a specific date.
    
- The program uses:
    - A provided CSV database containing historical Bitcoin exchange rates.
    - An input file containing dates and Bitcoin amounts.

- For every input line, the program finds the exchange rate corresponding to the requested date.
- If the exact date does not exist in the database, the program must use the closest earlier date.


Program Flow:
```cpp
                 ./btc input.txt
                        │
                        ▼
                Open input file
                        │
                        ▼
                  Read each line
                        │
                        ▼
                 Parse date/value
                        │
              ┌─────────┴─────────┐
              ▼                   ▼
        Validate date        Validate value
              │                   │
              └─────────┬─────────┘
                        ▼
                 Search std::map
                        │
                        ▼
              Find closest date
                        │
                        ▼
             rate × input value
                        │
                        ▼
                     Output

```
</details>

---

<details>
<summary><b>Ex01</b></summary>

### Program Flow
```cpp
                 Read token
                     │
          ┌──────────┴──────────┐
          │                     │
       Number                Operator
          │                     │
          ▼                     ▼
       push()             Need 2 operands
                                │
                                ▼
                             pop()
                                │
                                ▼
                          Perform operation
                                │
                                ▼
                             push()
````

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

