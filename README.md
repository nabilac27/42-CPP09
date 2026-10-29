<p align="center">
  <img src="https://cdn-icons-png.flaticon.com/512/6132/6132222.png" width="60" alt="C++ Logo">
</p>

<h1 align="center">CPP Module 09</h1>

## Overview

CPP Module 09 focuses on the **Standard Template Library (STL)**: containers, algorithms, parsing and sorting.

| Exercise | Description | Container |
|----------|-------------|-----------|
| ex00 — Bitcoin Exchange | Calculate the value of Bitcoin on a given date using historical exchange rates. | `std::map` |
| ex01 — Reverse Polish Notation | Evaluate expressions written in Reverse Polish Notation. | `std::list` |
| ex02 — PmergeMe | Sort positive integers with the Ford-Johnson merge-insertion algorithm. | `std::vector`, `std::deque` |

Each exercise requires at least one STL container. The last one requires two different containers.

## Concepts Learned

<details>
<summary><b>STL basics</b></summary>

The **STL** is a collection of reusable C++ components:

- **Containers** store data.
- **Algorithms** search, sort and manipulate data (`<algorithm>`).
- **Iterators** traverse containers. They behave like pointers.

| Container | Description |
|-----------|-------------|
| `std::vector` | Dynamic array with fast random access |
| `std::list` | Doubly linked list with fast insertion and deletion |
| `std::deque` | Double-ended queue with fast insertion at both ends |
| `std::stack` | Last-in, first-out container adapter |
| `std::map` | Sorted key-value pairs with unique keys |

| Algorithm | Description |
|-----------|-------------|
| `std::find()` | Searches for an element and returns its iterator |
| `std::distance()` | Counts the steps between two iterators |
| `std::sort()` | Sorts a range in ascending order by default |

```cpp
std::vector<int>::iterator it = v.begin();   // first element
v.end();                                     // one past the last element
```

</details>

<details>
<summary><b><code>std::map</code></b></summary>

Stores **sorted key-value pairs**. Each key is unique.

```cpp
#include <map>

std::map<std::string, double> database;   // date -> rate

it->first;    // key (date)
it->second;   // value (rate)
```

| Function | Returns |
|----------|---------|
| `lower_bound(x)` | First key `>= x` |
| `upper_bound(x)` | First key `> x` |

Bitcoin Exchange uses it to find the exact date, or the closest earlier one:

```cpp
it = database.upper_bound(date);
if (it == database.begin())
    return (false);    // no earlier date
--it;
```

</details>

<details>
<summary><b><code>std::list</code></b></summary>

A **doubly linked list**. It has no `operator[]`, but insertion and removal are efficient once the position is known.

```cpp
#include <list>

std::list<long long> numbers;   // [3] <-> [5] <-> [9]
                                // front          back
```

In RPN, `back` acts as the top of a stack:

| `std::stack` | `std::list` |
|--------------|-------------|
| `push(x)` | `push_back(x)` |
| `top()` | `back()` |
| `pop()` | `pop_back()` |

</details>

<details>
<summary><b><code>std::vector</code></b></summary>

A **dynamic array** in contiguous memory, with fast random access and efficient `push_back()`.

```cpp
#include <vector>

std::vector<int> numbers;
numbers.push_back(5);   // add at the end
numbers.pop_back();     // remove the last element
numbers.back();         // last element
numbers[0];             // access by index
```

Used in `PmergeMe` as the first container.

</details>

<details>
<summary><b><code>std::deque</code></b></summary>

A **double-ended queue**. It has fast insertion and removal at both ends and supports `operator[]`, but its memory is not guaranteed to be contiguous.

```cpp
#include <deque>

std::deque<int> numbers;
numbers.push_front(5);
numbers.push_back(5);
numbers.pop_front();
numbers.pop_back();
```

Used in `PmergeMe` as the second container.

</details>

<details>
<summary><b><code>vector</code> vs <code>deque</code> vs <code>list</code></b></summary>

| | `vector` | `deque` | `list` |
|---|----------|---------|--------|
| Memory | contiguous | segmented | linked |
| `operator[]` | yes | yes | no |
| `push_front` / `pop_front` | no | yes | yes |
| `push_back` / `pop_back` | yes | yes | yes |

```
vector   [3][5][9][7]                    one block
deque    [3][5]  [9][7]                  several blocks
list     [3] <-> [5] <-> [9] <-> [7]     separate nodes
```

A `deque` keeps elements contiguous **inside** each block, but the blocks can sit at different memory addresses. It keeps an internal index of them.

</details>

## Exercises

<details>
<summary><b>ex00 | Bitcoin Exchange</b></summary>

Calculates the value of Bitcoin on a given date using the rates in `data.csv`, stored in a `std::map`.

| File | Content |
|------|---------|
| `data.csv` | Historical rates: `date,exchange_rate` |
| `input.txt` | Requests: `date \| value` (value between `0` and `1000`) |

```sh
./btc input.txt
```

| `input.txt` | `data.csv` | Calculation | Output |
|-------------|------------|-------------|--------|
| `2011-01-03 \| 3` | `2011-01-03,0.3` | `3 × 0.3` | `2011-01-03 => 3 = 0.9` |

If the date does not exist, the closest earlier date is used. `upper_bound()` returns the first key after the date, and `--it` steps back to the latest date less than or equal to it.

**Logic flow**

```
main
├── validate arguments (argc must be 2)
├── loadDataCsvFile("data.csv")
│   └── skip header, split by ',', validate, store in map
└── processInputTxtFile(argv[1])
    └── for each line:
        ├── parseKeyDate()      split on '|', reject bad separators
        ├── isValidDate()       YYYY-MM-DD, month, day, leap years
        ├── isValidValue()      numeric, not negative, not above 1000
        └── findExchangeRate()  upper_bound, --it, print value * rate
```

</details>

<details>
<summary><b>ex01 | RPN</b></summary>

Evaluates an expression in **Reverse Polish Notation**, where the operator comes after the operands.

- **Operands:** single digits (0–9)
- **Operators:** `+` `-` `*` `/`
- **Errors:** invalid expressions or calculation errors go to `stderr`

```
7 * 7 - 7     becomes     7 7 * 7 -
```

A `std::list<long long>` works as a stack (LIFO), with `back` as the top.

Expression: `7 7 * 7 7 + -`

| Token | List | Operation |
|-------|------|-----------|
| `7` | `[7]` | push |
| `7` | `[7, 7]` | push |
| `*` | `[49]` | `7 * 7` |
| `7` | `[49, 7]` | push |
| `7` | `[49, 7, 7]` | push |
| `+` | `[49, 14]` | `7 + 7` |
| `-` | `[35]` | `49 - 14` |

Result: `35`

</details>

<details>
<summary><b>ex02 | <a href="ex02/README.md">PmergeMe</a></b></summary>

Sorts positive integers with the **Ford-Johnson algorithm** (merge-insertion sort), which uses few comparisons. It runs separately with `std::vector<int>` and `std::deque<int>`.

1. **Pair** the elements. If the count is odd, keep one as the straggler.
2. **Compare** each pair and order it as `(small, big)`.
3. **Recursively sort** the larger elements.
4. **Insert** the small element paired with the smallest big element at the start.
5. **Insert** the remaining small elements in Jacobsthal order, using binary search.

| Concept | Purpose |
|---------|---------|
| Main chain | Sorted elements |
| Pending chain | Smaller elements waiting for insertion |
| Jacobsthal | Decides **which** pending element to insert next |
| Binary search | Decides **where** it belongs |
| Straggler | Leftover element when the input size is odd |

Reference: [Merge-insertion sort (Wikipedia)](https://en.wikipedia.org/wiki/Merge-insertion_sort)

</details>

## Resources

- [Containers in C++ STL](https://www.geeksforgeeks.org/cpp/containers-cpp-stl/)
- [STL algorithms](https://www.geeksforgeeks.org/cpp/c-magicians-stl-algorithms/)
- [Iterators in C++ STL](https://www.geeksforgeeks.org/cpp/iterators-c-stl/)
- [std::stack reference](https://cplusplus.com/reference/stack/stack/)
