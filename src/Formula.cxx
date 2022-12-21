#include "Formula.hxx"

std::ostream& operator<<(std::ostream& os, const Formula& formula) {
    os << "Formula( " << formula.clauses.size() << " ):" << std::endl;
    for (auto c : formula.clauses) {
        os << "AND (" << *c << ")" << std::endl;
    }
    return os;
}

void Formula::add_clause(Clause* clause) { clauses.push_back(clause); }

bool Formula::value() {
    bool value = true;
    for (std::vector<Clause*>::const_iterator clause = clauses.begin();
         clause != clauses.end(); clause++) {
        value = value && (*clause)->value();
    }
    return value;
}

void Formula::unit_propagate(std::shared_ptr<Literal> literal) {
    for (std::vector<Clause*>::const_iterator c = clauses.begin();
         c != clauses.end(); c++) {
        if (!(*c)->value()) {
            (*c)->unit_propagate(literal);
        }
    }
    clean();
}

void Formula::clean() {
    std::vector<Clause*>::const_iterator it = clauses.begin();
    while (it != clauses.end()) {
        if ((*it)->empty()) {
            clauses.erase(it);
        } else if ((*it)->value()) {
            clauses.erase(it);
        } else {
            it++;
        }
    }
}

bool Formula::empty() const { return clauses.empty(); }

Clause* Formula::get_unit_clause() {
    for (std::vector<Clause*>::const_iterator c = clauses.begin();
         c != clauses.end(); c++) {
        if ((*c)->is_unit()) {
            return *c;
        }
    }
    return nullptr;
}