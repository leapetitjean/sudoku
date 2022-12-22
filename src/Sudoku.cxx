#include "Sudoku.hxx"

Sudoku::Sudoku(std::vector<std::vector<int>> grid) {
    std::shared_ptr<Formula> f(new Formula());
    formula = f;

    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            Clause* one_to_n_clause = new Clause();
            for (int z = 0; z < 9; z++) {
                std::string name(std::to_string(x) + std::to_string(y) + std::to_string(z));
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
                    Clause* at_most_one_row_clause = new Clause();
                    std::string name1(std::to_string(x) + std::to_string(y) + std::to_string(z));
                    std::string name2(std::to_string(i) + std::to_string(y) + std::to_string(z));
                    at_most_one_row_clause->add_literal(name1,
                                                        true);
                    at_most_one_row_clause->add_literal(name2,
                                                        true);
                    formula->add_clause(at_most_one_row_clause);
                }
            }
        }
    }

    for (int x = 0; x < 9; x++) {
        for (int z = 0; z < 9; z++) {
            for (int y = 0; y < 8; y++) {
                for (int i = y + 1; i < 9; i++) {
                    Clause* at_most_one_column_clause = new Clause();
                    std::string name1(std::to_string(x) + std::to_string(y) + std::to_string(z));
                    std::string name2(std::to_string(x) + std::to_string(i) + std::to_string(z));
                    at_most_one_column_clause->add_literal(name1,
                                                           true);
                    at_most_one_column_clause->add_literal(name2,
                                                           true);
                    formula->add_clause(at_most_one_column_clause);
                }
            }
        }
    }

    for (int z = 0; z < 9; z++) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int x = 0; x < 3; x++) {
                    for (int y = 0; y < 3; y++) {
                        for (int k = y + 1; k < 3; k++) {
                            Clause* at_most_one_sub_grid_1 = new Clause();
                            std::string name1(std::to_string(3 * i + x) + std::to_string(3 * j + y) + std::to_string(z));
                            std::string name2(std::to_string(3 * i + x) + std::to_string(3 * j + k) + std::to_string(z));
                            at_most_one_sub_grid_1->add_literal(
                                name1, true);
                            at_most_one_sub_grid_1->add_literal(
                                name2, true);
                            formula->add_clause(at_most_one_sub_grid_1);
                        }
                    }
                }
            }
        }
    }

    for (int z = 0; z < 9; z++) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int x = 0; x < 3; x++) {
                    for (int y = 0; y < 3; y++) {
                        for (int k = x + 1; k < 3; k++) {
                            for (int l = 0; l < 3; l++) {
                                Clause* at_most_one_sub_grid_2 = new Clause();
                                std::string name1(std::to_string(3 * i + x) + std::to_string(3 * j + y) + std::to_string(z));
                                std::string name2(std::to_string(3 * i + k) + std::to_string(3 * j + l) + std::to_string(z));
                                at_most_one_sub_grid_2->add_literal(
                                    name1, true);
                                at_most_one_sub_grid_2->add_literal(
                                    name2, true);
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
                std::string name(std::to_string(x) + std::to_string(y) + std::to_string(z));
                if (grid[x][y] - 1 == z) {
                    formula.get()->assign(name, true);
                }
                formula.get()->set_fixed(name);
                formula.get()->unit_propagate(name);
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku) {
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            bool is_fixed = false;
            for (int z = 0; z < 9; z++) {
                std::string name(std::to_string(x) + std::to_string(y) + std::to_string(z));
                 if (sudoku.formula.get()->get_literal_value(name)) {
                    os << z+1 << " ";
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

void Sudoku::solve() {
    Clause* c = formula.get()->get_unit_clause();
    while (c != nullptr) {
        std::string l = c->get_literal();

        if (!c->is_negative(l)) {
            formula.get()->assign(l, true);
        }

        formula.get()->set_fixed(l);
        formula.get()->unit_propagate(l);

        c = formula.get()->get_unit_clause();
    }
}