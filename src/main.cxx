#include <fstream>
#include <iostream>
#include <vector>

#include "Sudoku.hxx"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./sudoku <file_name>" << std::endl;
        return EXIT_FAILURE;
    }
    std::string file_name(argv[1]);

    std::string line;
    std::ifstream file(file_name);

    std::vector<std::vector<int>> instance(9, std::vector<int>());
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            getline(file, line, ' ');
            instance[i].push_back(std::stoi(line));
            std::cout << instance[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    Sudoku sudoku(instance);
    sudoku.solve();
    std::cout << sudoku;

    return EXIT_SUCCESS;
}