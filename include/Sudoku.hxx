#ifndef SUDOKU_HXX
#define SUDOKU_HXX

#include <Clause.hxx>
#include <Formula.hxx>
#include <Solver.hxx>
#include <iostream>
#include <vector>

class Sudoku {
   private:
    /// @brief Solver to solve the sudoku.
    Solver solver;
    /// @brief Value of satisfiabilty of the instance.
    bool feasible = false;
    /// @brief SAT formula of the sudoku.
    std::shared_ptr<Formula> formula;

   public:
    /**
     * @brief Construct a new Sudoku object.
     *
     * @param grid of already assigned values.
     */
    Sudoku(std::vector<std::vector<int>> grid);

    /**
     * @brief Call the solver to solve the formula.
     */
    void solve();
    friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);
};

#endif  // SUDOKU_HXX