#include "Kwic.hpp"
#include "Word.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace text
{

    using Line = std::vector<Word>;

    void kwic(std::istream &in, std::ostream &out)
    {
        // Use a set to automatically sort and eliminate duplicates
        auto comparator = [](Line const &lhs, Line const &rhs)
        {
            return std::lexicographical_compare(
                lhs.begin(), lhs.end(),
                rhs.begin(), rhs.end());
        };

        std::set<Line, decltype(comparator)> allRotations(comparator);

        // Read all lines from input
        std::string inputLine;
        while (std::getline(in, inputLine))
        {
            if (inputLine.empty())
            {
                continue; // Skip empty lines
            }

            // Parse words from the line
            Line words;
            std::istringstream lineStream(inputLine);
            Word w;
            while (lineStream >> w)
            {
                words.push_back(w);
            }

            if (words.empty())
            {
                continue; // Skip lines with no valid words
            }

            // Generate all rotations of this line
            for (size_t i = 0; i < words.size(); ++i)
            {
                Line rotation = words;
                std::rotate(rotation.begin(), rotation.begin() + i, rotation.end());
                allRotations.insert(rotation);
            }
        }

        // Output all rotations in sorted order
        for (auto const &line : allRotations)
        {
            auto it = line.begin();
            if (it != line.end())
            {
                out << *it;
                ++it;
            }
            for (; it != line.end(); ++it)
            {
                out << ' ' << *it;
            }
            out << '\n';
        }
    }

}
