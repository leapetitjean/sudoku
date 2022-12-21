#ifndef SUDOKU_HXX
#define SUDOKU_HXX

#include <Clause.hxx>
#include <Formula.hxx>
#include <Literal.hxx>
#include <iostream>
#include <vector>

class Sudoku {
   private:
    std::vector<std::vector<std::vector<std::shared_ptr<Literal>>>> literals =
        std::vector<std::vector<std::vector<std::shared_ptr<Literal>>>>(
            9, std::vector<std::vector<std::shared_ptr<Literal>>>(
                   9, std::vector<std::shared_ptr<Literal>>()));
    std::unordered_set<std::shared_ptr<Literal>> not_fixed_literals;
    Formula formula;

   public:
    Sudoku(std::vector<std::vector<int>> grid);
    void solve();
    friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);
};

#endif  // SUDOKU_HXX