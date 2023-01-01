#ifndef FORMULA_HXX
#define FORMULA_HXX

#include <Clause.hxx>
#include <iostream>
#include <unordered_set>
#include <vector>

/**
 * @brief Status of a literal.
 * status is true if we should do something with the value.
 */
struct literal_status {
    bool status = true;
    bool value;
};

/**
 * @brief A Formula is a set of clauses to satisfy (logical AND).
 * It contains all the assignments done as long as the remaining literals (in the different clauses)
 * to assign.
 */
class Formula {
   private:
    /// @brief Set of remaining clauses.
    std::unordered_set<std::shared_ptr<Clause>> clauses;
    /// @brief Set of unit clauses (clauses with a single element).
    std::unordered_set<std::shared_ptr<Clause>> unit_clauses;
    /// @brief Map the literal to the clauses where the literal appears.
    std::unordered_map<std::string, std::unordered_set<std::shared_ptr<Clause>>> literal_in_clauses;
    /// @brief Remaining literals to assign.
    std::unordered_set<std::string> literals_not_fixed;
    /// @brief A map linking a literal to its value.
    std::unordered_map<std::string, bool> assignments;
    /// @brief true if it contains an empty clause (non satifiable).
    bool empty_clause = false;

    /**
     * @brief Get the unit clause object
     *
     * @return std::shared_ptr<Clause>
     */
    std::shared_ptr<Clause> get_unit_clause();

    /**
     * @brief Remove a clause in `clauses` and in `unit_clauses` if it is inside it.
     *
     * @param clause to remove.
     */
    void erase(std::shared_ptr<Clause> clause);

    /**
     * @brief Propagate the value assigned to a literal in all clauses.
     *
     * @param literal to propagate.
     */
    void unit_propagate(std::string literal);

    /**
     * @brief Check if the literal has the same value (always with or always without a logical NOT).
     *
     * @param literal to check if it is a pure literal.
     * @return literal_status with status false if the literal is not pure. If the literal is pure,
     * value takes the value that need to be assigned to the literal.
     */
    literal_status is_pure_literal(std::string literal);

   public:
    Formula() = default;
    Formula(const Formula& formula);

    /**
     * @brief Add a clause to the formula (logical AND).
     *
     * @param clause a clause (logical OR and NOT).
     */
    void add_clause(std::shared_ptr<Clause> clause);

    /**
     * @brief Assign the value to the corresponding literal.
     * The literal is no longer in `literals_not_fixed` but in `assignments`.
     *
     * @param literal name of the literal to assign.
     * @param value value of the literal.
     */
    void assign(std::string literal, bool value);

    /**
     * @brief Do `unit_propagate` until there is not remaining unit clause.
     */
    void unit_clause_propagation();

    /**
     * @brief Do `is_pure_literal` on each not fixed literal and assign them accordingly to the
     * result of the function.
     */
    void pure_literal_propagation();

    /**
     * @brief Add a not fixed literal to the formula.
     * It could be done when adding a new clause to the formula but it could be redondant because a
     * literal can be in multiple clauses.
     *
     * @param literal to add.
     */
    inline void add_literal(std::string literal) { literals_not_fixed.insert(literal); }

    /**
     * @brief Choose a not fixed literal of the formula.
     *
     * @return std::string literal not fixed to assign.
     */
    inline std::string choose_literal() { return *literals_not_fixed.begin(); }

    /**
     * @brief Get the literal value object.
     *
     * @param literal to get.
     * @return true
     * @return false
     */
    inline bool get_literal_value(std::string literal) { return assignments[literal]; }

    /**
     * @brief Check if the formula is empty.
     *
     * @return true if `clauses` is empty.
     * @return false if `clauses` is not empty.
     */
    inline bool empty() const { return clauses.empty(); }

    /**
     * @brief Check if the formula has an empty clause (not satisfiable).
     *
     * @return true if it is not satisfiable.
     * @return false if it is satisfiable.
     */
    inline bool has_empty_clause() { return empty_clause; }
    friend std::ostream& operator<<(std::ostream& os, const Formula& formula);
};

#endif  // FORMULA_HXX