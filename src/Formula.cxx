#include <Formula.hxx>

Formula::Formula(const Formula& formula)
    : assignments_fixed(formula.assignments_fixed),
      assignments_not_fixed(formula.assignments_not_fixed) {
    for (std::unordered_set<std::shared_ptr<Clause>>::const_iterator c =
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
    std::unordered_map<std::string, bool> literals = clause->get_literals();
    for (std::unordered_map<std::string, bool>::const_iterator literal =
             literals.begin();
         literal != literals.end(); literal++) {
        if (literal_in_clauses.find(literal->first) !=
            literal_in_clauses.end()) {
            literal_in_clauses[literal->first].insert(clause);
        } else {
            literal_in_clauses.insert(std::make_pair(
                literal->first,
                std::unordered_set<std::shared_ptr<Clause>>{clause}));
        }
    }
    clauses.insert(clause);
}

void Formula::add_literal(std::string literal) {
    assignments_not_fixed.insert(std::make_pair(literal, false));
}

void Formula::unit_propagate(std::string literal) {
    std::vector<std::shared_ptr<Clause>> to_erase;
    for (std::unordered_set<std::shared_ptr<Clause>>::const_iterator clause =
             clauses.begin();
         clause != clauses.end(); clause++) {
        (*clause)->unit_propagate(literal, assignments_fixed.at(literal));
        bool value = (*clause)->value();
        if ((*clause)->empty() && !value) {
            empty_clause = true;
            to_erase.push_back(*clause);
        } else if (value) {
            to_erase.push_back(*clause);
        }
    }
    for (std::vector<std::shared_ptr<Clause>>::const_iterator clause =
             to_erase.begin();
         clause != to_erase.end(); clause++) {
        clauses.erase(*clause);
    }
}

bool Formula::empty() const { return clauses.empty(); }

std::shared_ptr<Clause> Formula::get_unit_clause() {
    for (std::unordered_set<std::shared_ptr<Clause>>::const_iterator clause =
             clauses.begin();
         clause != clauses.end(); clause++) {
        if ((*clause)->is_unit()) {
            return *clause;
        }
    }
    return nullptr;
}

void Formula::pure_literal_propagation() {
    std::vector<std::string> to_propagate;

    for (std::unordered_map<std::string, bool>::const_iterator assigment =
             assignments_not_fixed.begin();
         assigment != assignments_not_fixed.end(); assigment++) {
        if (is_pure_literal(assigment->first)) {
            to_propagate.push_back(assigment->first);
        }
    }

    for (std::vector<std::string>::const_iterator literal =
             to_propagate.begin();
         literal != to_propagate.end(); literal++) {
        assign(*literal, assignments_not_fixed[*literal]);
    }
}

bool Formula::is_pure_literal(std::string literal) {
    std::unordered_set<std::shared_ptr<Clause>>::const_iterator clause =
        literal_in_clauses[literal].begin();
    bool negative = (*clause)->is_negative(literal);
    clause++;
    for (clause; clause != literal_in_clauses[literal].end(); clause++) {
        if (negative != (*clause)->is_negative(literal)) {
            return false;
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
    std::shared_ptr<Clause> clause = get_unit_clause();
    while (clause != nullptr) {
        std::string literal = clause->get_literal();
        assign(literal, !clause->is_negative(literal));
        clause = get_unit_clause();
    }
}
