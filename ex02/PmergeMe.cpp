/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*      PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 22:02:54 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/06 23:18:59 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/* ************************************************************************** */
/*  ORTHODOX CANONICAL FORM                                                   */
/* ************************************************************************** */
PmergeMe::PmergeMe() : hasOdd(false), straggler(0)
{
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    *this = other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        vectorValues = other.vectorValues;
        vectorMainChain = other.vectorMainChain;
        vectorPendingChain = other.vectorPendingChain;

        dequeValues = other.dequeValues;
        dequeMainChain = other.dequeMainChain;
        dequePendingChain = other.dequePendingChain;

        hasOdd = other.hasOdd;
        straggler = other.straggler;
    }
    return (*this);
}

PmergeMe::~PmergeMe()
{
}

/* ************************************************************************** */
/*  PARSE                                                                     */
/* ************************************************************************** */
void PmergeMe::parseValue(int argc, char *argv[])
{
    if (argc < 2)
        throw(std::runtime_error("Error"));

    for (int i = 1; i < argc; i++)
    {
        for (int j = 0; argv[i][j]; j++)
        {
            if (!std::isdigit(argv[i][j]))
                throw(std::runtime_error("Error"));
        }
        int value = std::atoi(argv[i]);

        if (value <= 0)
            throw(std::runtime_error("Error"));

        vectorValues.push_back(value);
        dequeValues.push_back(value);
    }
}

double PmergeMe::sort(Container type)
{
    double start = getTime();

    makePairs(type);
    sortPairs(type);
    createChains(type);
    insertFirstPending(type);
    insertPending(type);
    insertStraggler(type);

    return (getTime() - start); // in s = (end - start) / 1000000.0;
}

/* ************************************************************************** */
/*  FORD-JOHNSON -- 1. MAKE PAIRS                                             */
/* ************************************************************************** */
void PmergeMe::makePairs(Container type)
{
    hasOdd = false;

    if (type == VECTOR)
    {
        for (size_t i = 0; i + 1 < vectorValues.size(); i += 2)
        {
            if (vectorValues[i] > vectorValues[i + 1])
                std::swap(vectorValues[i], vectorValues[i + 1]);
        }

        if (vectorValues.size() % 2 != 0)
        {
            hasOdd = true;
            straggler = vectorValues.back();
        }
    }
    else
    {
        for (size_t i = 0; i + 1 < dequeValues.size(); i += 2)
        {
            if (dequeValues[i] > dequeValues[i + 1])
                std::swap(dequeValues[i], dequeValues[i + 1]);
        }

        if (dequeValues.size() % 2 != 0)
        {
            hasOdd = true;
            straggler = dequeValues.back();
        }
    }
}
/* ************************************************************************** */
/*  FORD-JOHNSON -- 2. SORT PAIRS into (smaller, larger)                      */
/* ************************************************************************** */
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
        fordJohnsonVector(larger, 0, false); // --- FOR DEBUGGING: TRUE ---

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

        for (size_t i = 0; i < pairCount; i++)
        {
            size_t index = i * 2;
            int small = dequeValues[index];
            int large = dequeValues[index + 1];

            pairs.push_back(std::make_pair(small, large));
        }

        Deque larger;

        for (size_t i = 0; i < pairs.size(); i++)
            larger.push_back(pairs[i].second);

        fordJohnsonDeque(larger, 0, false);

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

        for (size_t i = 0; i < sortedPairs.size(); i++)
        {
            dequeValues[i * 2] = sortedPairs[i].first;
            dequeValues[i * 2 + 1] = sortedPairs[i].second;
        }
    }
}

/* ************************************************************************** */
/*  FORD-JOHNSON -- 3. RECURSIVELY SORT BIG ELEMENTS                          */
/* ************************************************************************** */
void PmergeMe::fordJohnsonVector(Vector& values, int depth, bool debug)
{
    if (debug)
    {
        std::cout << "  [fordJohnsonVector()] "
                  << std::string(depth * 4, ' ')
                  << "Depth " << depth << ": ";

        for (size_t i = 0; i < values.size(); i++)
            std::cout << values[i] << " ";

        std::cout << std::endl;
    }

    // Base case
    if (values.size() <= 1)
        return;

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

    // 3. Extract and recursively sort larger values
    Vector larger;

    for (size_t i = 0; i < pairs.size(); i++)
        larger.push_back(pairs[i].second);

    fordJohnsonVector(larger, depth + 1, debug);

    // 4. Reorder pairs according to sorted larger values
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

    // 5. Create main chain
    Vector mainChain = larger;

    // 6. Insert first smaller element (b1)
    if (!sortedPairs.empty())
        mainChain.insert(mainChain.begin(), sortedPairs[0].first);

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

        mainChain.insert(position, pending);
    }

    // 8. Insert straggler
    if (hasOddLocal)
    {
        Vector::iterator position =
            std::lower_bound(mainChain.begin(),
                             mainChain.end(),
                             stragglerLocal);

        mainChain.insert(position, stragglerLocal);
    }

    // 9. Return sorted values
    values = mainChain;

    if (debug)
    {
        std::cout << "  [fordJohnsonVector()] "
                  << std::string(depth * 4, ' ')
                  << "Return " << depth << ": ";

        for (size_t i = 0; i < values.size(); i++)
            std::cout << values[i] << " ";
        std::cout << std::endl;
    }
}

void PmergeMe::fordJohnsonDeque(Deque &values, int depth, bool debug)
{
    if (debug)
    {
        std::cout << "  [fordJohnsonDeque()] "
                  << std::string(depth * 4, ' ')
                  << "Depth " << depth << ": ";

        for (size_t i = 0; i < values.size(); i++)
            std::cout << values[i] << " ";

        std::cout << std::endl;
    }

    // Base case
    if (values.size() <= 1)
        return;

    // 1. Handle odd element
    bool hasOddLocal = (values.size() % 2 != 0);
    int stragglerLocal = 0;

    if (hasOddLocal)
        stragglerLocal = values.back();

    // 2. Create pairs (small, large)
    DequePair pairs;

    for (size_t i = 0; i + 1 < values.size(); i += 2)
    {
        int small = values[i];
        int large = values[i + 1];

        if (small > large)
            std::swap(small, large);

        pairs.push_back(std::make_pair(small, large));
    }

    // 3. Extract and recursively sort larger values
    Deque larger;

    for (size_t i = 0; i < pairs.size(); i++)
        larger.push_back(pairs[i].second);

    fordJohnsonDeque(larger, depth + 1, debug);

    // 4. Reorder pairs according to sorted larger values
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

    // 5. Create main chain
    Deque mainChain = larger;

    // 6. Insert first smaller element (b1)
    if (!sortedPairs.empty())
        mainChain.insert(mainChain.begin(), sortedPairs[0].first);

    // 7. Insert remaining smaller elements in Jacobsthal order
    VectorSizeT order = generateInsertionOrder(sortedPairs.size());

    for (size_t i = 0; i < order.size(); i++)
    {
        size_t index = order[i];

        int pending = sortedPairs[index].first;
        int partner = sortedPairs[index].second;

        Deque::iterator partnerPosition =
            std::find(mainChain.begin(), mainChain.end(), partner);

        Deque::iterator position =
            std::lower_bound(mainChain.begin(), partnerPosition, pending);

        mainChain.insert(position, pending);
    }

    // 8. Insert straggler
    if (hasOddLocal)
    {
        Deque::iterator position =
            std::lower_bound(mainChain.begin(),
                             mainChain.end(),
                             stragglerLocal);

        mainChain.insert(position, stragglerLocal);
    }

    // 9. Return sorted values
    values = mainChain;

    if (debug)
    {
        std::cout << "  [fordJohnsonDeque()] "
                  << std::string(depth * 4, ' ')
                  << "Return " << depth << ": ";

        for (size_t i = 0; i < values.size(); i++)
            std::cout << values[i] << " ";

        std::cout << std::endl;
    }
}

/* ************************************************************************** */
/*  FORD-JOHNSON -- 4. Insert the partner of the smallest big element         */
/* ************************************************************************** */
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

/* ************************************************************************** */
/*  FORD-JOHNSON -- 5. Insert the remaining small elements                    */
/* ************************************************************************** */
/*
    generateJacobsthal
    previous = 1
    current  = 3

    next = 3 + 2×1 = 5
    next = 5 + 2×3 = 11
    next = 11 + 2×5 = 21

    3, 5, 11, 21, 43...

    For :   generateJacobsthal(10)  --> [3, 5]
    11 isn't included because we only have 10 pending elements.
*/
VectorSizeT PmergeMe::generateJacobsthal(size_t size)
{
    VectorSizeT jacobsthal;
    size_t previous = 1;
    size_t current = 3;
    size_t next = 0;

    while (current <= size)
    {
        jacobsthal.push_back(current);

        next = current + (2 * previous);
        previous = current;
        current = next;
    }

    return (jacobsthal);
}

VectorSizeT PmergeMe::generateInsertionOrder(size_t size)
{
    VectorSizeT order;
    VectorSizeT jacobsthal = generateJacobsthal(size);
    size_t previous = 1;

    for (size_t i = 0; i < jacobsthal.size(); i++)
    {
        size_t current = jacobsthal[i];

        for (size_t j = current; j > previous; j--)
            order.push_back(j - 1);
        previous = current;
    }
    for (size_t j = size; j > previous; j--)
        order.push_back(j - 1);

    return (order);
}

/* ************************************************************************** */
/*  INSERT PENDING                                                            */
/* ************************************************************************** */
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

            printInsertionChains(order, insertionCount);
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

/* ************************************************************************** */
/*  INSERT STRAGGLER                                                          */
/* ************************************************************************** */
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

/* ************************************************************************** */
/*  TIME																	  */
/* ************************************************************************** */
size_t PmergeMe::getSize(Container type) const
{
    if (type == VECTOR)
        return (vectorValues.size());
    else
        return (dequeValues.size());
}

double PmergeMe::getTime()
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000000.0 + time.tv_usec);
}

/* ************************************************************************** */
/*  PRINT																	  */
/* ************************************************************************** */
void PmergeMe::printState(const char *msg, Container type, bool debug)
{
    if (type == VECTOR)
    {
        if (debug)
            std::cout << "\n[" << msg << "]   Vector: ";
        else
            std::cout << msg << ": ";

        for (size_t i = 0; i < vectorValues.size(); i++)
            std::cout << vectorValues[i] << " ";
        std::cout << std::endl;
    }
}

void PmergeMe::printTime(double time, Container type) const
{
    std::string container;

    if (type == VECTOR)
        container = "std::vector";
    else
        container = "std::deque";

    std::cout << "Time to process a range of "
              << getSize(type)
              << " elements with " << container << " : "
              << std::fixed << std::setprecision(5)
              << time
              << " us"
              << std::endl;
}

void PmergeMe::printDebugging(Debug type)
{
    if (type == PAIRS)
    {
        std::cout << "\n[Pairs  ]   " << "Vector: ";
        for (size_t i = 0; i < vectorValues.size(); i += 2)
        {
            if (i + 1 < vectorValues.size())
                std::cout << "(" << vectorValues[i] << ", " << vectorValues[i + 1] << ") ";
            else
                std::cout << vectorValues[i];
        }

        std::cout << std::endl;
    }

    if (type == PAIRS_INDEX)
    {
        const int width = 11;

        // 1. Print pair values
        std::cout << "\n[Pairs  ]   Vector: ";

        for (size_t i = 0; i < vectorValues.size(); i += 2)
        {
            std::ostringstream oss;

            if (i + 1 < vectorValues.size())
                oss << "(" << vectorValues[i] << ", "
                    << vectorValues[i + 1] << ")";
            else
                oss << vectorValues[i];

            std::cout << std::left << std::setw(width) << oss.str();
        }

        std::cout << std::endl;

        // 2. Print pair labels
        std::cout << "[Index  ]   Vector: ";

        for (size_t i = 0; i < vectorValues.size(); i += 2)
        {
            std::ostringstream oss;

            if (i + 1 < vectorValues.size())
            {
                size_t index = (i / 2) + 1;

                oss << "(b" << index << ", a" << index << ")";
            }
            else
                oss << "Straggler";

            std::cout << std::left << std::setw(width) << oss.str();
        }

        std::cout << std::endl;
    }

    else if (type == CHAINS || type == CHAINS_FIRST_INSERTED)
    {
        std::cout << "\n[Chains ]" << std::endl;

        std::cout << "  "
                  << std::left << std::setw(15) << "Main chain"
                  << std::setw(20) << "Pending chain"
                  << "Straggler"
                  << std::endl;

        size_t mainIndex = 0;
        size_t pendingIndex = (type == CHAINS_FIRST_INSERTED) ? 1 : 0;

        while (mainIndex < vectorMainChain.size() || pendingIndex < vectorPendingChain.size())
        {
            std::string mainText;
            std::string pendingText;

            if (mainIndex < vectorMainChain.size())
            {
                std::ostringstream oss;
                oss << "[" << vectorMainChain[mainIndex] << "]";
                mainText = oss.str();
            }

            if (pendingIndex < vectorPendingChain.size())
            {
                std::ostringstream oss;
                oss << "[" << vectorPendingChain[pendingIndex].first
                    << "] -> "
                    << vectorPendingChain[pendingIndex].second;
                pendingText = oss.str();

                pendingIndex++;
            }

            std::cout << "  "
                      << std::left << std::setw(15) << mainText
                      << std::setw(20) << pendingText;

            if (mainIndex == 0 && hasOdd)
                std::cout << "[" << straggler << "]";

            std::cout << std::endl;

            mainIndex++;
        }

        std::cout << std::endl;
    }
}

void PmergeMe::printInsertionChains(const VectorSizeT &order, size_t insertionCount)
{
    // 1. Print current insertion information
    size_t index = order[insertionCount - 1];

    int pending = vectorPendingChain[index].first;
    int partner = vectorPendingChain[index].second;

    std::cout << "\n  [Insertion " << insertionCount + 1 << "] "
              << "b" << index + 1
              << " = " << pending
              << " (partner a" << index + 1
              << " = " << partner << ")"
              << std::endl;

    // 2. Build remaining pending chain
    VectorPair remainingPending;

    // b1 was already inserted in insertFirstPending().
    for (size_t j = 1; j < vectorPendingChain.size(); j++)
    {
        bool inserted = false;

        for (size_t k = 0; k < insertionCount; k++)
        {
            if (order[k] == j)
            {
                inserted = true;
                break;
            }
        }

        if (!inserted)
            remainingPending.push_back(vectorPendingChain[j]);
    }

    // 3. Print chains
    std::cout << "\n[Chains ]\n";
    std::cout << "  " << std::left
              << std::setw(15) << "Main chain"
              << std::setw(20) << "Pending chain"
              << "Straggler\n";

    size_t rows = std::max(vectorMainChain.size(),
                           remainingPending.size());

    for (size_t j = 0; j < rows; j++)
    {
        std::ostringstream mainText;
        std::ostringstream pendingText;
        std::ostringstream stragglerText;

        if (j < vectorMainChain.size())
            mainText << "[" << vectorMainChain[j] << "]";

        if (j < remainingPending.size())
        {
            pendingText << "[" << remainingPending[j].first
                        << "] -> " << remainingPending[j].second;
        }

        if (j == 0 && hasOdd)
            stragglerText << "[" << straggler << "]";

        std::cout << "  " << std::left
                  << std::setw(15) << mainText.str()
                  << std::setw(20) << pendingText.str()
                  << stragglerText.str()
                  << "\n";
    }
}

void PmergeMe::printRecursiveChains(const Vector &mainChain,
                                    const VectorPair &pendingChain,
                                    int depth,
                                    const std::string &stage)
{
    std::string indent(depth * 4, ' ');

    std::ostringstream prefix;
    prefix << "[Depth " << depth << "] " << stage << " -> ";

    const int mainWidth = 15;
    const int prefixWidth = std::max(
        static_cast<size_t>(36),
        prefix.str().length() + 1);

    std::cout << "\n"
              << indent
              << std::left
              << std::setw(prefixWidth) << prefix.str()
              << std::setw(mainWidth) << "Main chain"
              << "Pending chain\n";

    size_t rows = std::max(mainChain.size(), pendingChain.size());

    for (size_t i = 0; i < rows; i++)
    {
        std::ostringstream mainText;
        std::ostringstream pendingText;

        if (i < mainChain.size())
            mainText << "[" << mainChain[i] << "]";

        if (i < pendingChain.size())
        {
            pendingText << "[" << pendingChain[i].first
                        << "] -> " << pendingChain[i].second;
        }

        std::cout << indent
                  << std::setw(prefixWidth) << ""
                  << std::setw(mainWidth) << mainText.str()
                  << pendingText.str()
                  << "\n";
    }
}

/*
    ford-johnson, ford-johnson deque, insertPending
    Next priority: Update your outer insertPending() to use partner-bounded binary search too,
                    so the recursive and outer implementations follow the same insertion rules.

    ⚠️ fordJohnsonDeque() still needs the same recursive correction
    ⚠️ Pair identity for duplicate values is not handled robustly
    ⚠️ Straggler insertion still needs review for strict Ford-Johnson comparison behavior

    ---

    Jacobsthal order decides which pending value to insert next (b3 = 7).
    Binary search (lower_bound) decides where to insert it (between 6 and 9).
    Partner-bounded insertion decides how far the binary search is allowed to go (before 300).
*/