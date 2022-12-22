#include "Clause.hxx"

Clause::Clause(const Clause& clause) {
    for (std::unordered_map<std::string, bool>::const_iterator literal = clause.literals.begin(); literal != clause.literals.end(); literal++) {
        add_literal(literal->first, literal->second);
    }
    is_true = clause.is_true;
}

void Clause::add_literal(std::string literal, bool negative) {
    std::unordered_map<std::string, bool>::const_iterator exists =
        literals.find(literal);
    if (exists != literals.end()) {
        if (exists->second != negative) {
            literals.erase(literal);
        }
    }
    literals.insert(std::make_pair(literal, negative));
}

bool Clause::value() const { return is_true; }

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

void Clause::unit_propagate(std::string literal, bool value) {
    std::unordered_map<std::string, bool>::const_iterator exists =
        literals.find(literal);
    if (exists != literals.end()) {
        literals.erase(literal);
        if (!is_true) {
            is_true = exists->second ? !value : value;
        }
    }
}

bool Clause::empty() const { return literals.empty(); }

bool Clause::is_unit() { return literals.size() == 1; }

std::string Clause::get_literal() {
    return literals.begin()->first;
}

bool Clause::is_negative(std::string literal) {
    return literals.find(literal)->second;
}

bool Clause::contains(std::string literal) {
    return literals.find(literal) != literals.end();
}