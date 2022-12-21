#ifndef SUDOKU_HXX
#define SUDOKU_HXX

#include <vector>
#include <iostream>
#include <Literal.hxx>
#include <Formula.hxx>
#include <Clause.hxx>

class Sudoku {
    private:
        std::vector<std::vector<std::vector<std::shared_ptr<Literal>>>> literals = std::vector<std::vector<std::vector<std::shared_ptr<Literal>>>>(9, std::vector<std::vector<std::shared_ptr<Literal>>>(9, std::vector<std::shared_ptr<Literal>>()));
        Formula formula;

    public:
        Sudoku(std::vector<std::vector<int>> grid);
        void solve();
        friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);
};

#endif // SUDOKU_HXX