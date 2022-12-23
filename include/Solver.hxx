#ifndef SOLVER_HXX
#define SOLVER_HXX

#include <memory>
#include <Formula.hxx>

class Solver {
    private:
        std::shared_ptr<Formula> formula;
    public:
        bool DPLL(std::shared_ptr<Formula> formula);
        inline std::shared_ptr<Formula> get_solution() { return formula; }
};

#endif // SOLVER_HXX