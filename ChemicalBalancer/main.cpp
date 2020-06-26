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
    Atom(std::tuple<std::string, std::string, int, int> atomData)
    : _symbol(std::get<0>(atomData)), _name(std::get<1>(atomData)), _atomicMass(std::get<2>(atomData)), _massNumber(std::get<3>(atomData)) {}
    
    std::string GetSymbol() {
        return _symbol;
    }
};

std::vector<Atom> reactants, products;
std::string reactantsString = "Null", productsString = "Null";

void UpdateEquation(std::vector<Atom> &molecules, std::string &moleculesString) {
    std::string input;
    std::getline(std::cin, input);
    Atom atom = Atom(GetAtomData(input));
    if (atom.GetSymbol() != "Null") {
        molecules.emplace_back(atom);
        if (molecules.size() > 1) {
            moleculesString += " + ";
        } else {
            moleculesString = "";
        }
        moleculesString += input;
    } else {
        std::cout << "Invalid atom symbol" << std::endl;
    }
}

int main(int argc, const char * argv[]) {
    std::string input;
    while(true) {
        std::getline(std::cin, input);
        if (input == "1") {
            UpdateEquation(reactants, reactantsString);
        } else if (input == "2") {
            UpdateEquation(products, productsString);
        }
        std::cout << reactantsString << " -> " << productsString << std::endl;
    }
    return 0;
}
