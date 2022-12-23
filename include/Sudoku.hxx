#ifndef SUDOKU_HXX
#define SUDOKU_HXX

#include <iostream>
#include <vector>

#include <Clause.hxx>
#include <Formula.hxx>
#include <Solver.hxx>

class Sudoku {
   private:
    Solver solver;
    bool feasible = false;
    std::shared_ptr<Formula> formula;

   public:
    Sudoku(std::vector<std::vector<int>> grid);
    void solve();
    friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);
};

#endif  // SUDOKU_HXX