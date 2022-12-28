#ifndef SUDOKU_HXX
#define SUDOKU_HXX

#include <Clause.hxx>
#include <Formula.hxx>
#include <Solver.hxx>
#include <iostream>
#include <vector>

class Sudoku {
   private:
    Solver solver;
    bool feasible = false;
    std::shared_ptr<Formula> formula;

   public:
    Sudoku(std::vector<std::vector<int>> grid);
    void solve();
    friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);
    friend std::string get_name(int x, int y, int z);
};

#endif  // SUDOKU_HXX