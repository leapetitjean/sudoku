#ifndef CLAUSE_HXX
#define CLAUSE_HXX

#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>

class Clause {
   private:
    std::unordered_map<std::string, bool> literals;
    bool is_true = false;

   public:
    Clause() = default;
    Clause(const Clause& clause);
    void add_literal(std::string literal, bool negative);
    bool value() const;
    void unit_propagate(std::string literal, bool value);
    bool empty() const;
    bool is_unit();
    bool is_negative(std::string literal);
    bool contains(std::string literal);
    std::string get_literal();
    friend std::ostream& operator<<(std::ostream& os, const Clause& clause);
};

#endif  // CLAUSE_HXX
