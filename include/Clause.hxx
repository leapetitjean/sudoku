#ifndef CLAUSE_HXX
#define CLAUSE_HXX

#include <iostream>
#include <memory>
#include <unordered_map>

class Clause {
   private:
    std::unordered_map<std::string, bool> literals;
    bool is_true = false;

   public:
    Clause() = default;
    Clause(const Clause& clause);
    void add_literal(std::string literal, bool negative);
    void unit_propagate(std::string literal, bool value);

    inline std::string get_literal() { return literals.begin()->first; }
    inline bool value() const { return is_true; }
    inline bool is_unit() { return literals.size() == 1; }
    inline bool empty() const { return literals.empty(); }
    inline bool contains(std::string literal) { return literals.find(literal) != literals.end(); }
    inline bool is_negative(std::string literal) { return literals.find(literal)->second; }
    inline std::unordered_map<std::string, bool>& get_literals() { return literals; }
    friend std::ostream& operator<<(std::ostream& os, const Clause& clause);
};

#endif  // CLAUSE_HXX
