#ifndef SOLVER_HXX
#define SOLVER_HXX

#include <Formula.hxx>
#include <memory>

class Solver {
   private:
    /// @brief Result formula.
    std::shared_ptr<Formula> formula;

   public:
    /**
     * @brief Davis-Putnam-Logemann-Loveland algorithm
     *
     * Algorithm based on the [wikipedia](https://en.wikipedia.org/wiki/DPLL_algorithm) pseudocode.
     *
     * @param formula pointer to a formula to satisfy.
     * @return true if the formula is satisfiable.
     * @return false if the formula is not satisfiable.
     */
    bool DPLL(std::shared_ptr<Formula> formula);

    /**
     * @brief Get the solution object.
     *
     * @return std::shared_ptr<Formula> formula obtained by the solver.
     */
    inline std::shared_ptr<Formula> get_solution() { return formula; }
};

#endif  // SOLVER_HXX