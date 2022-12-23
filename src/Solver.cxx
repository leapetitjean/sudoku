#include <Solver.hxx>

bool Solver::DPLL(std::shared_ptr<Formula> formula) {
    formula.get()->unit_clause_propagation();
    formula.get()->pure_literal_propagation();

    if (formula.get()->has_empty_clause()) {
        return false;
    }

    if (formula.get()->empty()) {
        this->formula = formula;
        return true;
    }

    std::string literal = formula.get()->choose_literal();

    std::shared_ptr<Formula> formula1(new Formula(*formula.get()));
    std::shared_ptr<Formula> formula2(new Formula(*formula.get()));

    formula1.get()->assign(literal, true);
    formula2.get()->assign(literal, false);

    return DPLL(formula1) || DPLL(formula2);
}