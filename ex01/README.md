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

- In this implementation, a **`std::list`** is used to store the operands.

   ```cpp
       std::list<long long> numbers;
   ```

- The **back of the list** acts like the top of a stack:

   ```text
       [7] ↔ [3]
              ↑
             back
   ```

### General Logic

```text
expression
    │
    ▼
stringstream → read token
    │
    ├── digit
    │     ↓
    │   convert to int
    │     ↓
    │   push_back()
    │
    ├── operator
    │     ↓
    │   need 2 operands
    │     ↓
    │   back() → right
    │   pop_back()
    │
    │   back() → left
    │   pop_back()
    │     ↓
    │   calculate(left, right, op)
    │     ↓
    │   push_back(result)
    │
    └── invalid
          ↓
        Error
    │
    ▼
end of expression
    │
    ▼
list size == 1?
   ┌────┴────┐
   ▼         ▼
  YES        NO
   │          │
print back() Error
```

```text
NUMBER   → PUSH_BACK

OPERATOR → GET + REMOVE 2
           CALCULATE
           PUSH_BACK 1

END      → exactly 1 value must remain
```

### Program Flow

```text
                Read token
                    │
      ┌─────────────┼─────────────┐
      │             │             │
      ▼             ▼             ▼
   Number        Operator       Invalid
      │             │             │
      ▼             ▼             ▼
Convert to int   Need 2 values   Error
      │             │
      ▼             ▼
 push_back()    back() → right
                    │
                    ▼
                pop_back()
                    │
                    ▼
                back() → left
                    │
                    ▼
                pop_back()
                    │
                    ▼
                calculate()
                    │
                    ▼
            push_back(result)
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
 list.size() == 1?
   ┌────┴────┐
   ▼         ▼
  YES        NO
   │          │
   ▼          ▼
 Print       Error
 result
```

### Why right first, then left?

For:

```text
7 3 -
```

the list contains:

```text
[7] ↔ [3]
 ↑      ↑
left   right
       back
```

We first take the last value:

```cpp
int right = numbers.back();
numbers.pop_back();
```

Then:

```cpp
int left = numbers.back();
numbers.pop_back();
```

Then calculate:

```cpp
calculate(left, right, '-');
```

So:

```text
7 - 3 = 4
```

and **not**:

```text
3 - 7 = -4
```

This order is especially important for `-` and `/`.

### Example 1

```text
Expression: 7 7 * 7 -

Token           List
──────────────────────
7               [7]

7               [7, 7]

*               [49]

7               [49, 7]

-               [42]

Result: 42
```

### Example 2

```text
Expression: 7 7 * 7 7 + -

Token           List                Operation
─────────────────────────────────────────────────────────
7               [7]                 push_back(7)

7               [7, 7]              push_back(7)

*               [49]                right = back() → 7
                                     pop_back()
                                     left = back()  → 7
                                     pop_back()
                                     7 * 7 = 49
                                     push_back(49)

7               [49, 7]             push_back(7)

7               [49, 7, 7]          push_back(7)

+               [49, 14]            right = back() → 7
                                     pop_back()
                                     left = back()  → 7
                                     pop_back()
                                     7 + 7 = 14
                                     push_back(14)

-               [35]                right = back() → 14
                                     pop_back()
                                     left = back()  → 49
                                     pop_back()
                                     49 - 14 = 35
                                     push_back(35)

Result: 35
```

### Summary

```text
std::list<long long> numbers

NUMBER
   ↓
push_back()

OPERATOR
   ↓
size() >= 2
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