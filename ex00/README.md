# CPP09 - ex00 | Bitcoin Exchange 🪙

Program that calculates the value of Bitcoin on a given date using historical exchange rates from `data.csv`.

---

## Flow

```text
1️⃣ Get input.txt
        ↓
2️⃣ Load data.csv
        ↓
3️⃣ Read input.txt
        ↓
4️⃣ Validate date + value
        ↓
5️⃣ Find Bitcoin price
        ↓
6️⃣ Calculate and print
```

---

## Structure

```text
              BitcoinExchange btc
                      │
          ┌───────────┴───────────┐
          ↓                       ↓
   loadDataCsv()            processInputTxt()
          ↓                       ↓
      data.csv                 input.txt
          ↓                       ↓
    date,rate                date | value
          ↓
       std::map
          ↓
 "2011-01-03" → 0.3
```

---

## Run

```bash
make
./btc input.txt
```

Input format:

```text
date | value
2011-01-03 | 3
2011-01-09 | 1.2
```

---

## `std::map`

```cpp
std::map<std::string, double> database;
```

Stores:

```text
date → exchange rate

2011-01-03 → 0.3
2012-01-11 → 7.1
```

---

## Main

```text
main
 │
 ├── check argc
 ├── BitcoinExchange btc
 ├── btc.loadDataCsv("data.csv")
 │
 └── btc.processInputTxt(argv[1])
```

---

## Input Processing

```text
processInputTxt()
        ↓
open file
        ↓
skip header
        ↓
getline()
        ↓
processInputLine()
        ↓
check "date | value"
        ↓
validate date
        ↓
validate value
        ↓
find exchange rate
        ↓
value × rate
        ↓
print
```

---

## `std::map::lower_bound()`

Used when the requested date does not exist in the database.

```text
Database:

2011-01-03
2011-01-04
2011-01-10
     ↑
Requested: 2011-01-06
```

`lower_bound("2011-01-06")` finds:

```text
2011-01-10
```

The subject requires the **closest lower date**, so move one iterator back:

```cpp
--it;
```

Result:

```text
2011-01-04
```

---

## Errors

```text
value < 0
→ Error: not a positive number.

value > 1000
→ Error: too large a number.

invalid format/date/value
→ Error: bad input => ...

file cannot open
→ Error: could not open file.
```

---

## Example

```text
data.csv:
2011-01-01,0.3
2011-01-02,0.4
2011-01-03,10
2011-01-04,20
```

```text
input.txt:
date | value
2011-01-03 | 5
2011-01-06 | 40
```

Output:

```text
2011-01-03 => 5 = 50
2011-01-06 => 40 = 800
```