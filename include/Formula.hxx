#ifndef FORMULA_HXX
#define FORMULA_HXX

#include <Clause.hxx>
#include <iostream>
#include <unordered_set>
#include <vector>

class Formula {
   private:
    std::vector<std::shared_ptr<Clause>> clauses;
    std::vector<std::shared_ptr<Clause>> unit_clauses;
    std::unordered_map<std::string, bool> assignments_not_fixed;
    std::unordered_map<std::string, bool> assignments_fixed;
    bool empty_clause = false;

   public:
    Formula() = default;
    Formula(const Formula& formula);
    void add_clause(std::shared_ptr<Clause> clause);
    void add_literal(std::string literal);
    void assign(std::string literal, bool value);
    bool get_literal_value(std::string literal);
    std::string choose_literal();
    bool value();
    void unit_propagate(std::string literal);
    void unit_clause_propagation();
    bool empty() const;
    void clean();
    std::shared_ptr<Clause> get_unit_clause();
    void pure_literal_propagation();
    bool is_pure_literal(std::string literal);
    inline bool has_empty_clause() { return empty_clause; };
    friend std::ostream& operator<<(std::ostream& os, const Formula& formula);
};

#endif  // FORMULA_HXX