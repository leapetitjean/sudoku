#include "Clause.hxx"

void Clause::add_literal(std::shared_ptr<Literal> literal, bool negative) {
    std::unordered_map<std::shared_ptr<Literal>, bool>::const_iterator exists =
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
        os << *pair.first.get() << ")";
    }
    return os;
}

void Clause::unit_propagate(std::shared_ptr<Literal> literal) {
    std::unordered_map<std::shared_ptr<Literal>, bool>::const_iterator exists =
        literals.find(literal);
    if (exists != literals.end()) {
        literals.erase(literal);
        if (!is_true) {
            is_true = exists->second ? !literal.get()->value()
                                     : literal.get()->value();
        }
    }
}

bool Clause::empty() const { return literals.empty(); }

bool Clause::is_unit() { return literals.size() == 1; }

std::shared_ptr<Literal> Clause::get_literal() {
    return literals.begin()->first;
}

bool Clause::is_negative(std::shared_ptr<Literal> literal) {
    return literals.find(literal)->second;
}