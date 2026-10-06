# PmergeMe

`PmergeMe` sorts a sequence of positive integers using the **Ford-Johnson algorithm**, also known as **merge-insertion sort**.

## How the Algorithm Works

1. **Create pairs**  
   Group the elements into pairs. If the number of elements is odd, one element is left unpaired.

2. **Compare each pair**  
   Compare the two elements in every pair to determine the smaller and larger element.

   ```text
   Input:  3 5 9 7 4 2

   Pairs:
   (3, 5) (9, 7) (4, 2)

   Ordered pairs:
   (3, 5) (7, 9) (2, 4)
   ```

3. **Recursively sort the larger elements**  
   Take the larger element from each pair and recursively sort them using the same merge-insertion algorithm.

   ```text
   Larger elements:
   5 9 4

   Sorted:
   4 5 9
   ```

   These elements form the basis of the **main chain**.

4. **Insert the first smaller element**  
   Insert the element paired with the smallest element of the sorted main chain at the beginning.

5. **Insert the remaining elements**  
   Insert the remaining smaller elements into the main chain using a specially chosen insertion order.

   **Binary search** is used to determine where each element should be inserted, reducing the number of comparisons.

## General Flow

- 
    ```text
        Input sequence
            |
            v
        Create pairs
            |
            v
        Order each pair
            |
            v
        Recursively sort larger elements
            |
            v
        Build the main chain
            |
            v
        Insert smaller elements
        using binary search
            |
            v
        Sorted sequence
    ```

- The special insertion order used by Ford-Johnson is based on the **Jacobsthal sequence**, which helps minimize the number of comparisons required during insertion.