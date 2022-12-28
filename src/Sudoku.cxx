#include <Sudoku.hxx>

std::string get_name(int x, int y, int z) {
    return std::to_string(x) + std::to_string(y) + std::to_string(z);
}

Sudoku::Sudoku(std::vector<std::vector<int>> grid) {
    std::shared_ptr<Formula> f(new Formula());
    formula = f;

    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            std::shared_ptr<Clause> one_to_n_clause(new Clause());
            for (int z = 0; z < 9; z++) {
                std::string name = get_name(x, y, z);
                formula.get()->add_literal(name);
                one_to_n_clause->add_literal(name, false);
            }
            formula.get()->add_clause(one_to_n_clause);
        }
    }

    for (int y = 0; y < 9; y++) {
        for (int z = 0; z < 9; z++) {
            for (int x = 0; x < 8; x++) {
                for (int i = x + 1; i < 9; i++) {
                    std::shared_ptr<Clause> at_most_one_row_clause(new Clause());
                    at_most_one_row_clause->add_literal(get_name(x, y, z), true);
                    at_most_one_row_clause->add_literal(get_name(i, y, z), true);
                    formula->add_clause(at_most_one_row_clause);
                }
            }
        }
    }

    for (int x = 0; x < 9; x++) {
        for (int z = 0; z < 9; z++) {
            for (int y = 0; y < 8; y++) {
                for (int i = y + 1; i < 9; i++) {
                    std::shared_ptr<Clause> at_most_one_column_clause(new Clause());
                    at_most_one_column_clause->add_literal(get_name(x, y, z), true);
                    at_most_one_column_clause->add_literal(get_name(x, i, z), true);
                    formula->add_clause(at_most_one_column_clause);
                }
            }
        }
    }

    for (int z = 0; z < 9; z++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int x = 0; x < 3; x++) {
                    for (int y = 0; y < 3; y++) {
                        for (int k = y + 1; k < 3; k++) {
                            std::shared_ptr<Clause> at_most_one_sub_grid_1(new Clause());
                            at_most_one_sub_grid_1->add_literal(get_name(3 * i + x, 3 * j + y, z),
                                                                true);
                            at_most_one_sub_grid_1->add_literal(get_name(3 * i + x, 3 * j + k, z),
                                                                true);
                            formula->add_clause(at_most_one_sub_grid_1);
                        }
                    }
                }
            }
        }
    }

    for (int z = 0; z < 9; z++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int x = 0; x < 3; x++) {
                    for (int y = 0; y < 3; y++) {
                        for (int k = x + 1; k < 3; k++) {
                            for (int l = 0; l < 3; l++) {
                                std::shared_ptr<Clause> at_most_one_sub_grid_2(new Clause());
                                at_most_one_sub_grid_2->add_literal(
                                    get_name(3 * i + x, 3 * j + y, z), true);
                                at_most_one_sub_grid_2->add_literal(
                                    get_name(3 * i + k, 3 * j + l, z), true);
                                formula->add_clause(at_most_one_sub_grid_2);
                            }
                        }
                    }
                }
            }
        }
    }

    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            if (grid[x][y] == 0) {
                continue;
            }
            for (int z = 0; z < 9; z++) {
                std::string name = get_name(x, y, z);
                if (grid[x][y] - 1 == z) {
                    formula.get()->assign(name, true);
                } else {
                    formula.get()->assign(name, false);
                }
            }
        }
    }
}

void Sudoku::solve() {
    feasible = solver.DPLL(formula);
    formula = solver.get_solution();
}

std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku) {
    if (!sudoku.feasible) {
        os << "No solution" << std::endl;
        return os;
    }
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            bool is_fixed = false;
            for (int z = 0; z < 9; z++) {
                if (sudoku.formula.get()->get_literal_value(get_name(x, y, z))) {
                    os << z + 1 << " ";
                    is_fixed = true;
                }
            }
            if (!is_fixed) {
                os << 0 << " ";
            }
        }
        os << std::endl;
    }
    return os;
}