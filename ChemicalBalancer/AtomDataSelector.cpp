#include <fstream>
#include <string>
#include <tuple>
#include "AtomDataSelector.hpp"

std::tuple<std::string, std::string, int, int> GetAtomData(std::string symbol) {
    std::ifstream atomData("AtomData.txt");
    if (!atomData.fail()) {
        std::string line;
        while (atomData >> line) {
            std::string symbolTest = line.substr(0, symbol.size());
            if (symbolTest == symbol) {
                std::size_t beginPos, endPos = symbol.size();
                std::string data[4];
                data[0] = symbol;
                for (int i = 1; i < 4; i++) {
                    beginPos = endPos + 1;
                    endPos = line.find(":", beginPos);
                    data[i] = line.substr(beginPos, endPos - beginPos);
                }
                return std::make_tuple(data[0], data[1], std::stoi(data[2]), std::stoi(data[3]));
            }
        }
        return std::make_tuple("Null", "Null", 0, 0);
    }
    throw std::logic_error("Cannot find AtomData.txt file");
}
