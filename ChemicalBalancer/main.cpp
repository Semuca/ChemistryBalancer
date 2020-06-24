#include <iostream>
#include "AtomDataSelector.hpp"

enum atomDetailTypes{Symbol = 1, Name = 2, AtomicNumber = 3, MassNumber = 4};

int main(int argc, const char * argv[]) {
    std::string keyIDinput, keyInput, parameterID;
    while(true) {
        std::getline(std::cin, keyIDinput);
        std::getline(std::cin, keyInput);
        std::getline(std::cin, parameterID);
        std::cout << GetAtomData(std::stoi(keyIDinput), keyInput, std::stoi(parameterID)) << std::endl;
    }
    return 0;
}
