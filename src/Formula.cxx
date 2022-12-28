#include <Formula.hxx>

Formula::Formula(const Formula& formula)
    : literals_not_fixed(formula.literals_not_fixed),
      assignments(formula.assignments) {
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
    if (clause->is_unit()) {
        unit_clauses.insert(clause);
    }
}

void Formula::add_literal(std::string literal) {
    literals_not_fixed.insert(literal);
}

void Formula::unit_propagate(std::string literal) {
    std::vector<std::shared_ptr<Clause>> to_erase;
    for (std::unordered_set<std::shared_ptr<Clause>>::const_iterator clause =
             literal_in_clauses[literal].begin();
         clause != literal_in_clauses[literal].end(); clause++) {
        (*clause)->unit_propagate(literal, assignments.at(literal));
        bool value = (*clause)->value();
        if ((*clause)->empty() && !value) {
            empty_clause = true;
            to_erase.push_back(*clause);
        } else if (value) {
            to_erase.push_back(*clause);
        } else if ((*clause)->is_unit()) {
            unit_clauses.insert(*clause);
        }
    }
    for (std::vector<std::shared_ptr<Clause>>::const_iterator clause =
             to_erase.begin();
         clause != to_erase.end(); clause++) {
        clauses.erase(*clause);
        if (unit_clauses.find(*clause) != unit_clauses.end()) {
            unit_clauses.erase(*clause);
        }
    }
}

std::shared_ptr<Clause> Formula::get_unit_clause() {
    if (unit_clauses.empty()) {
        return nullptr;
    }
    return *unit_clauses.begin();
}

void Formula::pure_literal_propagation() {
    std::vector<std::pair<std::string, bool>> to_propagate;

    for (std::unordered_set<std::string>::const_iterator assigment =
             literals_not_fixed.begin();
         assigment != literals_not_fixed.end(); assigment++) {
        literal_status status = is_pure_literal(*assigment);
        if (status.status) {
            to_propagate.push_back(std::make_pair(*assigment, status.value));
        }
    }

    for (std::vector<std::pair<std::string, bool>>::const_iterator literal =
             to_propagate.begin();
         literal != to_propagate.end(); literal++) {
        assign(literal->first, literal->second);
    }
}

literal_status Formula::is_pure_literal(std::string literal) {
    literal_status status;
    std::unordered_set<std::shared_ptr<Clause>>::const_iterator clause =
        literal_in_clauses[literal].begin();
    bool negative = (*clause)->is_negative(literal);
    clause++;
    while (clause != literal_in_clauses[literal].end()) {
        if (negative != (*clause)->is_negative(literal)) {
            status.status = false;
            return status;
        }
        clause++;
    }
    status.value = !negative;
    return status;
}

void Formula::assign(std::string literal, bool value) {
    literals_not_fixed.erase(literal);
    assignments.insert(std::make_pair(literal, value));
    unit_propagate(literal);
}

bool Formula::get_literal_value(std::string literal) {
    // TODO status if not found
    return assignments[literal];
}

std::string Formula::choose_literal() { return *literals_not_fixed.begin(); }

void Formula::unit_clause_propagation() {
    std::shared_ptr<Clause> clause = get_unit_clause();
    while (clause != nullptr) {
        std::string literal = clause->get_literal();
        assign(literal, !clause->is_negative(literal));
        clause = get_unit_clause();
    }
}
