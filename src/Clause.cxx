#include <Clause.hxx>

Clause::Clause(const Clause& clause) : literals(clause.literals) { is_true = clause.is_true; }

void Clause::add_literal(std::string literal, bool negative) {
    std::unordered_map<std::string, bool>::const_iterator exists = literals.find(literal);
    if (exists != literals.end()) {
        if (exists->second != negative) {
            literals.erase(literal);
        }
    }
    literals.insert(std::make_pair(literal, negative));
}

void Clause::unit_propagate(std::string literal, bool value) {
    std::unordered_map<std::string, bool>::const_iterator exists = literals.find(literal);
    if (exists != literals.end()) {
        literals.erase(literal);
        if (!is_true) {
            is_true = exists->second ? !value : value;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Clause& clause) {
    for (auto pair : clause.literals) {
        os << " OR (";
        if (pair.second) {
            os << "NOT ";
        }
        os << pair.first << ")";
    }
    return os;
}