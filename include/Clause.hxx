#ifndef CLAUSE_HXX
#define CLAUSE_HXX

#include <Literal.hxx>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>

class Clause {
   private:
    std::unordered_map<std::shared_ptr<Literal>, bool> literals;
    bool is_true = false;

   public:
    void add_literal(std::shared_ptr<Literal> literal, bool negative);
    bool value() const;
    void unit_propagate(std::shared_ptr<Literal> literal);
    bool empty() const;
    bool is_unit();
    bool is_negative(std::shared_ptr<Literal> literal);
    std::shared_ptr<Literal> get_literal();
    friend std::ostream& operator<<(std::ostream& os, const Clause& clause);
};

#endif  // CLAUSE_HXX
