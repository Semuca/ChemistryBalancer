#include <iostream>
#include <vector>
#include "AtomDataSelector.hpp"

class Molecule;
Molecule compileMolecule(std::string input);

std::vector<Molecule> reactants, products;
std::string reactantsString = "Null", productsString = "Null";

class Atom {
private:
    std::string _symbol;
    std::string _name;
    int _atomicMass;
    float _massNumber;
public:
    Atom(std::tuple<std::string, std::string, int, int> atomData)
    : _symbol(std::get<0>(atomData)), _name(std::get<1>(atomData)), _atomicMass(std::get<2>(atomData)), _massNumber(std::get<3>(atomData)) {}
    
    std::string getSymbol() {
        return _symbol;
    }
};

class Molecule {
private:
    std::vector<Atom> _components;
public:
    Molecule(std::vector<std::string> components) {
        for (int i = 0; i < components.size(); i++) {
            if (components[i][0] == '<') {
                Molecule mol = compileMolecule(components[i].substr(1, components[i].size()));
                if (!mol.isEmpty()) {
                    std::vector<Atom> molComponents = mol.getComponents();
                    for (int j = 0; j < molComponents.size(); j++) {
                        _components.emplace_back(molComponents[j]);
                    }
                }
            } else {
                _components.emplace_back(Atom(GetAtomData(components[i])));
                if (_components.back().getSymbol() == "Null") {
                    _components.pop_back();
                }
            }
        }
    }
    
    std::vector<Atom> getComponents() {
        return _components;
    }
    
    bool isEmpty() {
        if (_components.size() == 0) {
            return true;
        }
        return false;
    }
};

std::vector<std::string> splitMolecule(std::string input) {
    std::vector<std::string> components;
    std::size_t beginPos = 0, endPos = 0;
    int bracketLevel = 0;
    for (int i = 1; i < input.size(); i++) {
        if (bracketLevel > 0) {
            if (input[i] == '>') {
                bracketLevel--;
            }
        } else {
            if (input[i] == '<') {
                bracketLevel++;
                endPos = i;
                components.emplace_back(input.substr(beginPos, endPos - beginPos));
                beginPos = i;
            } else if (isupper(input[i])) {
                endPos = i;
                components.emplace_back(input.substr(beginPos, endPos - beginPos));
                beginPos = i;
            }
        }
    }
    if (beginPos != input.size()) {
        components.emplace_back(input.substr(beginPos, input.size() - beginPos));
    }
    return components;
}

Molecule compileMolecule(std::string input) {
    std::vector<std::string> splitComponents = splitMolecule(input);
    std::vector<std::string> components;
    int buffer = 0;
    int bracketLevel = 0;
    for (int i = 0; i < splitComponents.size(); i++) {
        for (int j = 0; j < splitComponents[i].size(); j++) {
            if (splitComponents[i][j] == '<') {
                buffer = 1;
                bracketLevel++;
            } else if (splitComponents[i][j] == '>') {
                bracketLevel--;
            }
            if (bracketLevel == 0) {
                if (isnumber(splitComponents[i][j])) {
                    std::string number = splitComponents[i].substr(j, splitComponents[i].size() - j);
                    std::string item = splitComponents[i].substr(0, j - buffer);
                    for (int k = 0; k < std::stoi(number); k++) {
                        components.emplace_back(item);
                    }
                    break;
                } else if (j == splitComponents[i].size() - 1) {
                    components.emplace_back(splitComponents[i]);
                }
            }
        }
    }
    return Molecule(components);
}

void updateEquation(std::vector<Molecule> &molecules, std::string &moleculesString) {
    std::string input;
    std::getline(std::cin, input);
    Molecule molecule = compileMolecule(input);
    std::vector<Atom> _comp = molecule.getComponents();
    for (int i = 0; i < _comp.size(); i++) {
        std::cout << _comp[i].getSymbol() << std::endl;
    }
    if (!molecule.isEmpty()) {
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
            updateEquation(reactants, reactantsString);
        } else if (input == "2") {
            updateEquation(products, productsString);
        }
        std::cout << reactantsString << " -> " << productsString << std::endl;
    }
    return 0;
}
