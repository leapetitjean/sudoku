#ifndef SUDOKU_HXX
#define SUDOKU_HXX

#include <Clause.hxx>
#include <Formula.hxx>
#include <iostream>
#include <vector>

class Sudoku {
   private:
    bool feasible = false;
    std::shared_ptr<Formula> formula;

   public:
    Sudoku(std::vector<std::vector<int>> grid);
    void solve();
    bool dpll(std::shared_ptr<Formula> f);
    friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);
};

#endif  // SUDOKU_HXX