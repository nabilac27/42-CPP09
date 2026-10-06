/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 15:33:22 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/06 16:42:20 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
    try
    {
        PmergeMe pmerge;

        // Parse input
        pmerge.parseValue(argc, argv);
        pmerge.printState("Initial");

        // 1. Make pairs
        pmerge.makePairs();
        pmerge.printPairs();

        // 2. Compare each pairs, and sort
        pmerge.sortPairs();
        pmerge.printPairs();

        // 3. Recursively, sort, big elements, Create main chain + pending
        pmerge.createChains();
        pmerge.printChains(false);

        // // 4. Insert first pending
        pmerge.insertFirstPending();
        pmerge.printChains(true);

        // // 5. Insert remaining pending
        // pmerge.insertPending();
        // pmerge.printChains();

        // pmerge.insertOdd();
        // pmerge.printChains();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

// int main(int argc, char *argv[])
// {
//     try
//     {
//         PmergeMe value;
        
//         value.parseValue(argc, argv);

//         value.makePairs();
//         value.sortPairs();

//         value.createChains();
//         value.printChains();

//         value.insertFirstPending();
//         value.printChains();

//         value.insertPending();
//         value.printChains();

//         value.insertOdd();
//         value.printChains();
//         // PmergeMe value;

//         // // 1. Parse
//         // value.parseValue(argc, argv);
//         // value.printValue("Initial");

//         // // 2. Make pairs
//         // value.makePairs();
//         // value.printPairs();

//         // // 3. Sort pairs
//         // value.sortPairs();
//         // value.printPairs();

//         // // 4. Create main + pending chains
//         // value.createChains();
//         // value.printChains();

//         // // 5. Insert first pending value
//         // value.insertFirstPending();
//         // value.printChains();

//         // // 6 + 7. Insert remaining pending values
//         // value.insertPending();
//         // value.printChains();

//         // // 8. Insert odd leftover
//         // value.insertOdd();
//         // value.printChains();
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << e.what() << std::endl;
//         return 1;
//     }

//     return 0;
// }

/*
    createChains()

    Main:    3 5 5 7 8
    Pending: 2 4 3 6 1
            b1 b2 b3 b4 b5

            ↓

    insertFirstPending()

    Main:
    2 3 5 5 7 8

            ↓

    generateInsertionOrder(5)

    2 1 4 3
    │ │ │ │
    │ │ │ └─ b4
    │ │ └─── b5
    │ └───── b2
    └─────── b3

            ↓

    insertPending()

    b3 = 3
    b2 = 4
    b5 = 1
    b4 = 6

            ↓

    1 2 3 3 4 5 5 6 7 8
*/
/*
	TO-DO

	sortPairs()
		❌ currently bubble sort
		→ needs recursive Ford-Johnson

	insertPending()
		❌ currently normal left-to-right insertion
		→ needs Jacobsthal order
		→ needs partner-bounded binary search

	----
    5 4 3 2 1 8 7 6 5 3
                ↓
            make pairs
                ↓
    (4,5) (2,3) (1,8) (6,7) (3,5)
                ↓
        recursively sort pairs
        based on larger elements
                ↓
    (2,3) (4,5) (3,5) (6,7) (1,8)
                ↓
            create chains
                ↓
    main:    3 5 5 7 8
    pending: 2 4 3 6 1
                ↓
            insert b1
                ↓
        Jacobsthal insertion order
                ↓
        partner-bounded binary search

    ---
	main()
	↓
	parseValue()
	↓
	check each argv[i]
	↓
	convert to int
	↓
	┌────────────┬────────────┐
	↓            ↓
	_vector      _deque

	./PmergeMe 3 5 9 7 4

	vector = [3, 5, 9, 7, 4]
	deque  = [3, 5, 9, 7, 4]


    ----

    parseValue()
      ↓
    makePairs()
        ↓
    sortPairs()
        ↓
    createChains()
        ↓
    insertFirstPending()
        ↓
    insertPending()
        ↓
    SORTED

    Current:
    pending → normal order → lower_bound entire chain

    Final Ford-Johnson:
    pending → Jacobsthal order → binary search limited by partner

    ---

    After sortPairs()

    1. parseValue()      ✓
    2. makePairs()       ✓
    3. sortPairs()       ✓
    4. createChains()    ← NEXT
    5. insert first small value
    6. Jacobsthal insertion
    7. binary search insertion
    8. handle odd leftover
    9. deque version
    10. timing

    Suppose after sortPairs():
        (3, 4) (1, 7) (8, 9)

    Each pair is:
        small  big
        3     4
        1     7
        8     9

    Now createChains() separates them:
        Main chain: 4 7 9
        Pending:    3 1 8

*/
