#ifndef FORMULA_HXX
#define FORMULA_HXX

#include <Clause.hxx>
#include <iostream>
#include <unordered_set>
#include <vector>

struct literal_status {
    bool status = true;
    bool value;
};

class Formula {
   private:
    std::unordered_set<std::shared_ptr<Clause>> clauses;
    std::unordered_set<std::shared_ptr<Clause>> unit_clauses;
    std::unordered_map<std::string, std::unordered_set<std::shared_ptr<Clause>>>
        literal_in_clauses;
    std::unordered_set<std::string> literals_not_fixed;
    std::unordered_map<std::string, bool> assignments;
    bool empty_clause = false;
    std::shared_ptr<Clause> get_unit_clause();
    literal_status is_pure_literal(std::string literal);

   public:
    Formula() = default;
    Formula(const Formula& formula);
    void add_clause(std::shared_ptr<Clause> clause);
    void add_literal(std::string literal);
    void assign(std::string literal, bool value);
    bool get_literal_value(std::string literal);
    std::string choose_literal();
    void unit_propagate(std::string literal);
    void unit_clause_propagation();
    void pure_literal_propagation();
    inline bool empty() const { return clauses.empty(); }
    inline bool has_empty_clause() { return empty_clause; }
    friend std::ostream& operator<<(std::ostream& os, const Formula& formula);
};

#endif  // FORMULA_HXX