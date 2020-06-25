#include <iostream>
#include <vector>
#include "AtomDataSelector.hpp"

class Atom {
private:
    std::string _symbol;
    std::string _name;
    int _atomicMass;
    float _massNumber;
public:
    Atom(std::string symbol, std::string name, int atomicMass, float massNumber)
    : _symbol(symbol), _name(name), _atomicMass(atomicMass), _massNumber(massNumber) {}
};

int main(int argc, const char * argv[]) {
    std::string input;
    std::vector<Atom> reactants, products;
    std::string reactantsString, productsString;
    while(true) {
        std::getline(std::cin, input);
        if (input == "1") {
            std::getline(std::cin, input);
            reactants.emplace_back(Atom(input, GetAtomData(1, input, 2), std::stoi(GetAtomData(1, input, 3)), std::stof(GetAtomData(1, input, 4))));
            if (reactants.size() > 1) {
                reactantsString += " + ";
            }
            reactantsString += input;
        } else if (input == "2") {
            std::getline(std::cin, input);
            products.emplace_back(Atom(input, GetAtomData(1, input, 2), std::stoi(GetAtomData(1, input, 3)), std::stof(GetAtomData(1, input, 4))));
            if (products.size() > 1) {
                productsString += " + ";
            }
            productsString += input;
        }
        std::cout << reactantsString << " -> " << productsString << std::endl;
    }
    return 0;
}
