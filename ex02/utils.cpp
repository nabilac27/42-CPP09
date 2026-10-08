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