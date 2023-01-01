#ifndef CLAUSE_HXX
#define CLAUSE_HXX

#include <iostream>
#include <memory>
#include <unordered_map>

/**
 * @brief A Clause is a set of literals to satisfy (logical OR and NOT).
 */
class Clause {
   private:
    /// @brief Stores the literals and the logical NOT of the clause.
    std::unordered_map<std::string, bool> literals;
    /// @brief Stores the value of the clause.
    bool is_true = false;

   public:
    Clause() = default;
    Clause(const Clause& clause);

    /**
     * @brief Add a literal and the corresponding logical NOT.
     *
     * @param literal to add.
     * @param negative true if it is has a logical NOT.
     */
    void add_literal(std::string literal, bool negative);

    /**
     * @brief Remove a literal and changes the value of the clause according to the value of the
     * assigned literal.
     *
     * @param literal to remove.
     * @param value of the literal.
     */
    void unit_propagate(std::string literal, bool value);

    /**
     * @brief Get the literal object.
     *
     * @return std::string
     */
    inline std::string get_literal() { return literals.begin()->first; }

    /**
     * @brief Return the value of the clause.
     *
     * @return true if it is satisfiable.
     * @return false if it is not satisfiable.
     */
    inline bool value() const { return is_true; }

    /**
     * @brief Return if the clause is unit or not.
     *
     * @return true if the clause is unit.
     * @return false if the clause is not unit.
     */
    inline bool is_unit() { return literals.size() == 1; }

    /**
     * @brief Return if the clause is empty or not.
     *
     * @return true if the clause is empty.
     * @return false if the clause is not empty.
     */
    inline bool empty() const { return literals.empty(); }

    /**
     * @brief Check if a literal is a logical NOT or not.
     *
     * @param literal to check.
     * @return true if it is a logical NOT.
     * @return false if it is not a logical NOT.
     */
    inline bool is_negative(std::string literal) { return literals.find(literal)->second; }

    /**
     * @brief Get the literals object.
     *
     * @return std::unordered_map<std::string, bool>&
     */
    inline std::unordered_map<std::string, bool>& get_literals() { return literals; }
    friend std::ostream& operator<<(std::ostream& os, const Clause& clause);
};

#endif  // CLAUSE_HXX
