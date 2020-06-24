#include <fstream>
#include <iostream>
#include "AtomDataSelector.hpp"

std::string GetAtomData(int keyID, std::string key, int parameterID){
    std::ifstream atomData("AtomData.txt");
    if (!atomData.fail()) {
        std::string line;
        while (atomData >> line) {
            std::size_t beginPos, endPos = 0;
            for (int i = 0; i < keyID; i++) {
                beginPos = endPos + 1;
                endPos = line.find(":", beginPos);
            }
            if (line.substr(beginPos, endPos - beginPos) == key) {
                beginPos, endPos = 0;
                for (int i = 0; i < parameterID; i++) {
                    beginPos = endPos + 1;
                    endPos = line.find(":", beginPos);
                }
                return line.substr(beginPos, endPos - beginPos);
            } else {
                continue;
            }
        }
        return "No atom found";
    } else {
        return "Error with reading AtomData file";
    }
}
