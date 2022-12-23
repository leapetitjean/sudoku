#include <Formula.hxx>

Formula::Formula(const Formula& formula)
    : assignments_fixed(formula.assignments_fixed),
      assignments_not_fixed(formula.assignments_not_fixed) {
    for (std::vector<std::shared_ptr<Clause>>::const_iterator c =
             formula.clauses.begin();
         c != formula.clauses.end(); c++) {
        std::shared_ptr<Clause> clause(new Clause(**c));
        add_clause(clause);
    }
    empty_clause = formula.empty_clause;
}

std::ostream& operator<<(std::ostream& os, const Formula& formula) {
    os << "Formula( " << formula.clauses.size() << " ):" << std::endl;
    for (auto c : formula.clauses) {
        os << "AND (" << *c << ")" << std::endl;
    }
    return os;
}

void Formula::add_clause(std::shared_ptr<Clause> clause) {
    clauses.push_back(clause);
}

void Formula::add_literal(std::string literal) {
    assignments_not_fixed.insert(std::make_pair(literal, false));
}

void Formula::unit_propagate(std::string literal) {
    for (std::vector<std::shared_ptr<Clause>>::const_iterator c =
             clauses.begin();
         c != clauses.end(); c++) {
        (*c)->unit_propagate(literal, assignments_fixed.at(literal));
    }
    clean();
}

void Formula::clean() {
    std::vector<std::shared_ptr<Clause>>::const_iterator it = clauses.begin();
    while (it != clauses.end()) {
        if ((*it)->empty()) {
            if (!(*it)->value()) {
                empty_clause = true;
            }
            clauses.erase(it);
        } else if ((*it)->value()) {
            clauses.erase(it);
        } else {
            it++;
        }
    }
}

bool Formula::empty() const { return clauses.empty(); }

std::shared_ptr<Clause> Formula::get_unit_clause() {
    for (std::vector<std::shared_ptr<Clause>>::const_iterator c =
             clauses.begin();
         c != clauses.end(); c++) {
        if ((*c)->is_unit()) {
            return *c;
        }
    }
    return nullptr;
}

void Formula::pure_literal_propagation() {
    std::vector<std::string> to_propagate;

    for (std::unordered_map<std::string, bool>::const_iterator l =
             assignments_not_fixed.begin();
         l != assignments_not_fixed.end(); l++) {
        if (is_pure_literal(l->first)) {
            to_propagate.push_back(l->first);
        }
    }

    for (std::vector<std::string>::const_iterator l = to_propagate.begin();
         l != to_propagate.end(); l++) {
        assign(*l, assignments_not_fixed[*l]);
    }
}

bool Formula::is_pure_literal(std::string literal) {
    bool first = true;
    bool negative = false;
    for (std::vector<std::shared_ptr<Clause>>::const_iterator c =
             clauses.begin();
         c != clauses.end(); c++) {
        if ((*c)->contains(literal)) {
            if (first) {
                negative = (*c)->is_negative(literal);
                first = false;
            }
            if (negative != (*c)->is_negative(literal)) {
                return false;
            }
        }
    }
    assignments_not_fixed[literal] = !negative;
    return true;
}

void Formula::assign(std::string literal, bool value) {
    assignments_not_fixed[literal] = value;
    assignments_not_fixed.erase(literal);
    assignments_fixed.insert(std::make_pair(literal, value));
    unit_propagate(literal);
}

bool Formula::get_literal_value(std::string literal) {
    if (assignments_not_fixed.find(literal) != assignments_not_fixed.end()) {
        return assignments_not_fixed[literal];
    }
    return assignments_fixed[literal];
}

std::string Formula::choose_literal() {
    return assignments_not_fixed.begin()->first;
}

void Formula::unit_clause_propagation() {
    std::shared_ptr<Clause> c = get_unit_clause();
    while (c != nullptr) {
        std::string l = c->get_literal();
        assign(l, !c->is_negative(l));
        c = get_unit_clause();
    }
}
