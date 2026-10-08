void PmergeMe::fordJohnsonVectorThoroughDebug(Vector &values, int depth, bool debug)
{
    std::string indent(depth * 4, ' ');

    // 0. Print current recursion values
    // if (debug)
    // {
    //     std::cout << "\n" << indent
    //               << "[Depth " << depth << "] Values: ";

    //     for (size_t i = 0; i < values.size(); i++)
    //         std::cout << values[i] << " ";

    //     std::cout << std::endl;
    // }

    // Base case
    // if (values.size() <= 1)
    //     return;
    if (values.size() <= 1)
    {
        if (debug)
        {
            std::string indent(depth * 4, ' ');

            std::cout << "\n"
                      << indent
                      << "[Depth " << depth << "] Values: ";

            for (size_t i = 0; i < values.size(); i++)
                std::cout << values[i] << " ";

            std::cout << "\n"
                      << indent
                      << "----- BASE CASE FOR RECURSION REACHED -----\n";
        }

        return;
    }

    // 1. Handle odd element
    bool hasOddLocal = (values.size() % 2 != 0);
    int stragglerLocal = 0;

    if (hasOddLocal)
        stragglerLocal = values.back();

    // 2. Create pairs (small, large)
    VectorPair pairs;

    for (size_t i = 0; i + 1 < values.size(); i += 2)
    {
        int small = values[i];
        int large = values[i + 1];

        if (small > large)
            std::swap(small, large);

        pairs.push_back(std::make_pair(small, large));
    }

    if (debug)
    {
        const int width = 16;
        std::string prefix = std::string(depth * 4, ' ');

        // Values
        std::cout << prefix << "[Depth " << depth << "] "
                  << std::left << std::setw(10) << "Values:";

        for (size_t i = 0; i < values.size(); i += 2)
        {
            std::ostringstream oss;

            if (i + 1 < values.size())
                oss << values[i] << " " << values[i + 1];
            else
                oss << values[i];

            std::cout << std::setw(width) << oss.str();
        }

        std::cout << "\n"
                  << prefix
                  << "          "
                  << std::left << std::setw(10) << "Pairs:";

        for (size_t i = 0; i < pairs.size(); i++)
        {
            std::ostringstream oss;
            oss << "(" << pairs[i].first << ", " << pairs[i].second << ")";

            std::cout << std::setw(width) << oss.str();
        }

        std::cout << "\n"
                  << prefix
                  << "          "
                  << std::left << std::setw(10) << "Index:";

        for (size_t i = 0; i < pairs.size(); i++)
        {
            std::ostringstream oss;
            oss << "(" << "b" << i + 1 << ", a" << i + 1 << ")";

            std::cout << std::setw(width) << oss.str();
        }

        std::cout << "\n\n";
    }

    Vector larger;

    for (size_t i = 0; i < pairs.size(); i++)
        larger.push_back(pairs[i].second);

    fordJohnsonVector(larger, depth + 1, debug);

    VectorPair sortedPairs;
    std::vector<bool> used(pairs.size(), false);

    for (size_t i = 0; i < larger.size(); i++)
    {
        for (size_t j = 0; j < pairs.size(); j++)
        {
            if (!used[j] && pairs[j].second == larger[i])
            {
                sortedPairs.push_back(pairs[j]);
                used[j] = true;
                break;
            }
        }
    }

    if (debug)
    {
        const int width = 14;
        const int labelWidth = 15;

        std::ostringstream depthStream;
        depthStream << "[Depth " << depth << "] ";

        std::string prefix = std::string(depth * 4, ' ') + depthStream.str();

        std::string spaces(prefix.length(), ' ');

        std::cout << "\n"
                  << prefix
                  << std::left << std::setw(labelWidth) << "Sorted pairs:";

        for (size_t i = 0; i < sortedPairs.size(); i++)
        {
            std::ostringstream oss;
            oss << "(" << sortedPairs[i].first
                << ", " << sortedPairs[i].second << ")";

            std::cout << std::setw(width) << oss.str();
        }

        std::cout << "\n"
                  << spaces
                  << std::setw(labelWidth) << "Index:";

        for (size_t i = 0; i < sortedPairs.size(); i++)
        {
            std::ostringstream oss;
            oss << "(b" << i + 1 << ", a" << i + 1 << ")";

            std::cout << std::setw(width) << oss.str();
        }

        std::cout << "\n";
    }

    // 5. Create main chain
    Vector mainChain = larger;

    if (debug)
    {
        printRecursiveChains(mainChain, sortedPairs,
                             depth, "Create chains");
    }

    // 6. Insert first smaller element (b1)
    if (!sortedPairs.empty())
        mainChain.insert(mainChain.begin(), sortedPairs[0].first);

    if (debug)
    {
        VectorPair remainingPending;

        for (size_t i = 1; i < sortedPairs.size(); i++)
            remainingPending.push_back(sortedPairs[i]);

        printRecursiveChains(mainChain, remainingPending,
                             depth, "After inserting b1");
    }

    // 7. Insert remaining smaller elements in Jacobsthal order
    VectorSizeT order = generateInsertionOrder(sortedPairs.size());

    for (size_t i = 0; i < order.size(); i++)
    {
        size_t index = order[i];

        int pending = sortedPairs[index].first;
        int partner = sortedPairs[index].second;

        Vector::iterator partnerPosition =
            std::find(mainChain.begin(), mainChain.end(), partner);

        Vector::iterator position =
            std::lower_bound(mainChain.begin(), partnerPosition, pending);

        // Debug: Show binary search range and insertion position
        if (debug)
        {
            std::string indent(depth * 4, ' ');

            std::cout << "\n"
                      << indent
                      << "[Depth " << depth << "] "
                      << "Insertion " << i + 2
                      << ": b" << index + 1 << " = " << pending
                      << " (partner a" << index + 1
                      << " = " << partner << ")\n\n";

            std::cout << indent << "            !Jacobsthal order decide which pending element to insert next" << std::endl;
            std::cout << indent << "            !std::lower_bound() uses binary search on a sorted range. \n"
                      << std::endl;
            std::cout << indent << "            Search range    : ";

            for (Vector::iterator it = mainChain.begin();
                 it != partnerPosition; ++it)
            {
                std::cout << "[" << *it << "] ";
            }

            std::cout << "\n"
                      << indent
                      << "            lower_bound(" << pending << ") -> ";

            if (position != mainChain.end())
                std::cout << "before " << *position;
            else
                std::cout << "at end";

            std::cout << "\n";
        }

        mainChain.insert(position, pending);

        if (debug)
        {
            std::ostringstream stage;

            stage << "Insertion " << i + 2
                  << ": b" << index + 1
                  << " = " << pending
                  << " (partner a" << index + 1
                  << " = " << partner << ")";

            VectorPair remainingPending;

            for (size_t j = 1; j < sortedPairs.size(); j++)
            {
                bool inserted = false;

                for (size_t k = 0; k <= i; k++)
                {
                    if (order[k] == j)
                    {
                        inserted = true;
                        break;
                    }
                }

                if (!inserted)
                    remainingPending.push_back(sortedPairs[j]);
            }

            printRecursiveChains(mainChain, remainingPending,
                                 depth, stage.str());
        }
    }

    // 8. Insert straggler
    if (hasOddLocal)
    {
        Vector::iterator position =
            std::lower_bound(mainChain.begin(),
                             mainChain.end(),
                             stragglerLocal);

        mainChain.insert(position, stragglerLocal);

        if (debug)
        {
            std::ostringstream stage;
            stage << "Insert straggler = " << stragglerLocal;

            VectorPair emptyPending;

            printRecursiveChains(mainChain, emptyPending,
                                 depth, stage.str());
        }
    }

    // 9. Return sorted values
    values = mainChain;

    if (debug)
    {
        std::cout << "\n"
                  << indent
                  << "[Depth " << depth << "] Return: ";

        for (size_t i = 0; i < values.size(); i++)
            std::cout << values[i] << " ";

        std::cout << "\n";
    }
}

// void PmergeMe::fordJohnsonVector(Vector& values, int depth, bool debug)
// {
//     if (debug)
//     {
//         std::cout << "  [fordJohnsonVector()] "
//                   << std::string(depth * 4, ' ')
//                   << "Depth " << depth << ": ";

//         for (size_t i = 0; i < values.size(); i++)
//             std::cout << values[i] << " ";

//         std::cout << std::endl;
//     }

//     // Base case
//     if (values.size() <= 1)
//         return;

//     // 1. Handle odd element
//     bool hasOddLocal = (values.size() % 2 != 0);
//     int stragglerLocal = 0;

//     if (hasOddLocal)
//         stragglerLocal = values.back();

//     // 2. Create pairs (small, large)
//     VectorPair pairs;

//     for (size_t i = 0; i + 1 < values.size(); i += 2)
//     {
//         int small = values[i];
//         int large = values[i + 1];

//         if (small > large)
//             std::swap(small, large);

//         pairs.push_back(std::make_pair(small, large));
//     }

//     // 3. Extract and recursively sort larger values
//     Vector larger;

//     for (size_t i = 0; i < pairs.size(); i++)
//         larger.push_back(pairs[i].second);

//     fordJohnsonVector(larger, depth + 1, debug);

//     // 4. Reorder pairs according to sorted larger values
//     VectorPair sortedPairs;
//     std::vector<bool> used(pairs.size(), false);

//     for (size_t i = 0; i < larger.size(); i++)
//     {
//         for (size_t j = 0; j < pairs.size(); j++)
//         {
//             if (!used[j] && pairs[j].second == larger[i])
//             {
//                 sortedPairs.push_back(pairs[j]);
//                 used[j] = true;
//                 break;
//             }
//         }
//     }

//     // 5. Create main chain
//     Vector mainChain = larger;

//     // 6. Insert first smaller element (b1)
//     if (!sortedPairs.empty())
//         mainChain.insert(mainChain.begin(), sortedPairs[0].first);

//     // 7. Insert remaining smaller elements in Jacobsthal order
//     VectorSizeT order = generateInsertionOrder(sortedPairs.size());

//     for (size_t i = 0; i < order.size(); i++)
//     {
//         size_t index = order[i];

//         int pending = sortedPairs[index].first;
//         int partner = sortedPairs[index].second;

//         Vector::iterator partnerPosition =
//             std::find(mainChain.begin(), mainChain.end(), partner);

//         Vector::iterator position =
//             std::lower_bound(mainChain.begin(), partnerPosition, pending);

//         mainChain.insert(position, pending);
//     }

//     // 8. Insert straggler
//     if (hasOddLocal)
//     {
//         Vector::iterator position =
//             std::lower_bound(mainChain.begin(),
//                              mainChain.end(),
//                              stragglerLocal);

//         mainChain.insert(position, stragglerLocal);
//     }

//     // 9. Return sorted values
//     values = mainChain;

//     if (debug)
//     {
//         std::cout << "  [fordJohnsonVector()] "
//                   << std::string(depth * 4, ' ')
//                   << "Return " << depth << ": ";

//         for (size_t i = 0; i < values.size(); i++)
//             std::cout << values[i] << " ";
//         std::cout << std::endl;
//     }
// }

// void PmergeMe::fordJohnsonDeque(Deque &values, int depth, bool debug)
// {
//     if (debug)
//     {
//         std::cout << "  [fordJohnsonDeque()] "
//                   << std::string(depth * 4, ' ')
//                   << "Depth " << depth << ": ";

//         for (size_t i = 0; i < values.size(); i++)
//             std::cout << values[i] << " ";

//         std::cout << std::endl;
//     }

//     // Base case
//     if (values.size() <= 1)
//         return;

//     // 1. Handle odd element
//     bool hasOddLocal = (values.size() % 2 != 0);
//     int stragglerLocal = 0;

//     if (hasOddLocal)
//         stragglerLocal = values.back();

//     // 2. Create pairs (small, large)
//     DequePair pairs;

//     for (size_t i = 0; i + 1 < values.size(); i += 2)
//     {
//         int small = values[i];
//         int large = values[i + 1];

//         if (small > large)
//             std::swap(small, large);

//         pairs.push_back(std::make_pair(small, large));
//     }

//     // 3. Extract and recursively sort larger values
//     Deque larger;

//     for (size_t i = 0; i < pairs.size(); i++)
//         larger.push_back(pairs[i].second);

//     fordJohnsonDeque(larger, depth + 1, debug);

//     // 4. Reorder pairs according to sorted larger values
//     DequePair sortedPairs;
//     std::deque<bool> used(pairs.size(), false);

//     for (size_t i = 0; i < larger.size(); i++)
//     {
//         for (size_t j = 0; j < pairs.size(); j++)
//         {
//             if (!used[j] && pairs[j].second == larger[i])
//             {
//                 sortedPairs.push_back(pairs[j]);
//                 used[j] = true;
//                 break;
//             }
//         }
//     }

//     // 5. Create main chain
//     Deque mainChain = larger;

//     // 6. Insert first smaller element (b1)
//     if (!sortedPairs.empty())
//         mainChain.insert(mainChain.begin(), sortedPairs[0].first);

//     // 7. Insert remaining smaller elements in Jacobsthal order
//     VectorSizeT order = generateInsertionOrder(sortedPairs.size());

//     for (size_t i = 0; i < order.size(); i++)
//     {
//         size_t index = order[i];

//         int pending = sortedPairs[index].first;
//         int partner = sortedPairs[index].second;

//         Deque::iterator partnerPosition =
//             std::find(mainChain.begin(), mainChain.end(), partner);

//         Deque::iterator position =
//             std::lower_bound(mainChain.begin(), partnerPosition, pending);

//         mainChain.insert(position, pending);
//     }

//     // 8. Insert straggler
//     if (hasOddLocal)
//     {
//         Deque::iterator position =
//             std::lower_bound(mainChain.begin(),
//                              mainChain.end(),
//                              stragglerLocal);

//         mainChain.insert(position, stragglerLocal);
//     }

//     // 9. Return sorted values
//     values = mainChain;

//     if (debug)
//     {
//         std::cout << "  [fordJohnsonDeque()] "
//                   << std::string(depth * 4, ' ')
//                   << "Return " << depth << ": ";

//         for (size_t i = 0; i < values.size(); i++)
//             std::cout << values[i] << " ";

//         std::cout << std::endl;
//     }
// }

void PmergeMe::sortPairs(Container type)
{
    if (type == VECTOR)
    {
        VectorPair pairs;
        size_t pairCount = vectorValues.size() / 2;

        // 1. Create pairs
        for (size_t i = 0; i < pairCount; i++)
        {
            size_t index = i * 2;
            int small = vectorValues[index];
            int large = vectorValues[index + 1];

            pairs.push_back(std::make_pair(small, large));
        }

        // 2. Extract larger elements
        Vector larger;
        for (size_t i = 0; i < pairs.size(); i++)
            larger.push_back(pairs[i].second);

        // 3. Sort larger elements recursively
        fordJohnson(larger, 0, false); // --- FOR DEBUGGING: TRUE ---

        // 4. Reorder pairs
        VectorPair sortedPairs;
        std::vector<bool> used(pairs.size(), false);

        for (size_t i = 0; i < larger.size(); i++)
        {
            for (size_t j = 0; j < pairs.size(); j++)
            {
                if (!used[j] && pairs[j].second == larger[i])
                {
                    sortedPairs.push_back(pairs[j]);
                    used[j] = true;
                    break;
                }
            }
        }

        // 5. Put pairs back into vector
        for (size_t i = 0; i < sortedPairs.size(); i++)
        {
            vectorValues[i * 2] = sortedPairs[i].first;
            vectorValues[i * 2 + 1] = sortedPairs[i].second;
        }
    }
    else
    {
        DequePair pairs;
        size_t pairCount = dequeValues.size() / 2;

        // 1. Create pairs
        for (size_t i = 0; i < pairCount; i++)
        {
            size_t index = i * 2;
            int small = dequeValues[index];
            int large = dequeValues[index + 1];

            pairs.push_back(std::make_pair(small, large));
        }

        // 2. Extract larger elements
        Deque larger;
        for (size_t i = 0; i < pairs.size(); i++)
            larger.push_back(pairs[i].second);

        // 3. Sort larger elements recursively
        fordJohnson(larger, 0, false);

        // 4. Reorder pairs
        DequePair sortedPairs;
        std::deque<bool> used(pairs.size(), false);

        for (size_t i = 0; i < larger.size(); i++)
        {
            for (size_t j = 0; j < pairs.size(); j++)
            {
                if (!used[j] && pairs[j].second == larger[i])
                {
                    sortedPairs.push_back(pairs[j]);
                    used[j] = true;
                    break;
                }
            }
        }

        // 5. Put pairs back into deque
        for (size_t i = 0; i < sortedPairs.size(); i++)
        {
            dequeValues[i * 2] = sortedPairs[i].first;
            dequeValues[i * 2 + 1] = sortedPairs[i].second;
        }
    }
}


// void PmergeMe::makePairs(Container type)
// {
//     hasOdd = false;

//     if (type == VECTOR)
//     {
//         for (size_t i = 0; i + 1 < vectorValues.size(); i += 2)
//         {
//             if (vectorValues[i] > vectorValues[i + 1])
//                 std::swap(vectorValues[i], vectorValues[i + 1]);
//         }

//         if (vectorValues.size() % 2 != 0)
//         {
//             hasOdd = true;
//             straggler = vectorValues.back();
//         }
//     }
//     else
//     {
//         for (size_t i = 0; i + 1 < dequeValues.size(); i += 2)
//         {
//             if (dequeValues[i] > dequeValues[i + 1])
//                 std::swap(dequeValues[i], dequeValues[i + 1]);
//         }

//         if (dequeValues.size() % 2 != 0)
//         {
//             hasOdd = true;
//             straggler = dequeValues.back();
//         }
//     }
// }


void PmergeMe::createChains(Container type)
{
    if (type == VECTOR)
    {
        vectorMainChain.clear();
        vectorPendingChain.clear();

        size_t pairCount = vectorValues.size() / 2;

        for (size_t i = 0; i < pairCount; i++)
        {
            size_t index = i * 2;
            int small = vectorValues[index];
            int large = vectorValues[index + 1];

            vectorPendingChain.push_back(std::make_pair(small, large));
            vectorMainChain.push_back(large);
        }
    }
    else
    {
        dequeMainChain.clear();
        dequePendingChain.clear();

        size_t pairCount = dequeValues.size() / 2;

        for (size_t i = 0; i < pairCount; i++)
        {
            size_t index = i * 2;
            int small = dequeValues[index];
            int large = dequeValues[index + 1];

            dequePendingChain.push_back(std::make_pair(small, large));
            dequeMainChain.push_back(large);
        }
    }
}

void PmergeMe::insertFirstPending(Container type)
{
    if (type == VECTOR)
    {
        if (vectorPendingChain.empty())
            return;
        vectorMainChain.insert(vectorMainChain.begin(), vectorPendingChain[0].first);
    }
    else
    {
        if (dequePendingChain.empty())
            return;

        dequeMainChain.insert(
            dequeMainChain.begin(),
            dequePendingChain[0].first);
    }
}

void PmergeMe::insertPending(Container type)
{
    size_t insertionCount = 0;
    if (type == VECTOR)
    {
        if (vectorPendingChain.size() <= 1)
            return;

        VectorSizeT order =
            generateInsertionOrder(vectorPendingChain.size());

        for (size_t i = 0; i < order.size(); i++)
        {
            size_t index = order[i];

            int pending = vectorPendingChain[index].first;
            int partner = vectorPendingChain[index].second;

            Vector::iterator partnerPosition =
                std::find(vectorMainChain.begin(),
                          vectorMainChain.end(),
                          partner);

            Vector::iterator position =
                std::lower_bound(vectorMainChain.begin(),
                                 partnerPosition,
                                 pending);

            vectorMainChain.insert(position, pending);

            insertionCount++;

            // printInsertionChains(order, insertionCount);
        }
        vectorPendingChain.clear();
    }
    else
    {
        if (dequePendingChain.size() <= 1)
            return;

        VectorSizeT order =
            generateInsertionOrder(dequePendingChain.size());

        for (size_t i = 0; i < order.size(); i++)
        {
            size_t index = order[i];

            int pending = dequePendingChain[index].first;
            int partner = dequePendingChain[index].second;

            Deque::iterator partnerPosition =
                std::find(dequeMainChain.begin(),
                          dequeMainChain.end(),
                          partner);

            Deque::iterator position =
                std::lower_bound(dequeMainChain.begin(),
                                 partnerPosition,
                                 pending);

            dequeMainChain.insert(position, pending);
        }

        dequePendingChain.clear();
    }
}

void PmergeMe::insertStraggler(Container type)
{
    if (type == VECTOR)
    {
        if (hasOdd)
        {
            Vector::iterator position;

            position = std::lower_bound(vectorMainChain.begin(), vectorMainChain.end(), straggler);
            vectorMainChain.insert(position, straggler);
            hasOdd = false;
        }
        vectorValues = vectorMainChain;
    }
    else
    {
        if (hasOdd)
        {
            Deque::iterator position;

            position = std::lower_bound(dequeMainChain.begin(),
                                        dequeMainChain.end(),
                                        straggler);

            dequeMainChain.insert(position, straggler);
            hasOdd = false;
        }

        dequeValues = dequeMainChain;
    }
}
