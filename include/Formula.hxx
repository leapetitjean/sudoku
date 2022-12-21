#ifndef FORMULA_HXX
#define FORMULA_HXX

#include <vector>
#include <unordered_set>
#include <iostream>
#include <Clause.hxx>

class Formula {
    private:
        std::vector<Clause*> clauses;

    public:
        void add_clause(Clause* clause);
        bool value();
        void unit_propagate(std::shared_ptr<Literal> literal);
        bool empty() const;
        void clean();
        Clause* get_unit_clause();
        friend std::ostream& operator<<(std::ostream& os, const Formula& formula);
};

#endif // FORMULA_HXX