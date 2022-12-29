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
    std::unordered_map<std::string, std::unordered_set<std::shared_ptr<Clause>>> literal_in_clauses;
    std::unordered_set<std::string> literals_not_fixed;
    std::unordered_map<std::string, bool> assignments;
    bool empty_clause = false;

    std::shared_ptr<Clause> get_unit_clause();
    void erase(std::shared_ptr<Clause> clause);
    void unit_propagate(std::string literal);
    literal_status is_pure_literal(std::string literal);

   public:
    Formula() = default;
    Formula(const Formula& formula);

    void add_clause(std::shared_ptr<Clause> clause);
    void assign(std::string literal, bool value);
    void unit_clause_propagation();
    void pure_literal_propagation();

    inline void add_literal(std::string literal) { literals_not_fixed.insert(literal); }
    inline std::string choose_literal() { return *literals_not_fixed.begin(); }
    inline bool get_literal_value(std::string literal) { return assignments[literal]; }
    inline bool empty() const { return clauses.empty(); }
    inline bool has_empty_clause() { return empty_clause; }
    friend std::ostream& operator<<(std::ostream& os, const Formula& formula);
};

#endif  // FORMULA_HXX