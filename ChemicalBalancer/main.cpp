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

class Molecule {
private:
    std::vector<Atom> _components;
public:
    Molecule(std::vector<std::string> components) {
        for (int i = 0; i < components.size(); i++) {
            _components.emplace_back(Atom(GetAtomData(components[i])));
            if (_components.back().GetSymbol() == "Null") {
                _components.pop_back();
            }
        }
    }
    
    bool IsEmpty() {
        if (_components.size() == 0) {
            return true;
        }
        return false;
    }
};

std::vector<Molecule> reactants, products;
std::string reactantsString = "Null", productsString = "Null";

Molecule readMolecule(std::string input) {
    std::vector<std::string> components;
    std::size_t beginPos = 0, endPos = 0;
    for (int i = 1; i < input.size(); i++) {
        if(isupper(input[i])) {
            endPos = i;
            components.emplace_back(input.substr(beginPos, endPos - beginPos));
            beginPos = i;
        } else if (isnumber(input[i])) {
            endPos = i;
            for (int j = 0; j < input[i] - 48; j++) {
                components.emplace_back(input.substr(beginPos, endPos - beginPos));
            }
            beginPos = i + 1;
        }
    }
    if (beginPos != input.size()) {
        components.emplace_back(input.substr(beginPos, input.size() - beginPos));
    }
    return Molecule(components);
}

void UpdateEquation(std::vector<Molecule> &molecules, std::string &moleculesString) {
    std::string input;
    std::getline(std::cin, input);
    Molecule molecule = readMolecule(input);
    if (!molecule.IsEmpty()) {
        molecules.emplace_back(molecule);
        if (molecules.size() > 1) {
            moleculesString += " + ";
        } else {
            moleculesString = "";
        }
        moleculesString += input;
    } else {
        std::cout << "Invalid molecule" << std::endl;
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
