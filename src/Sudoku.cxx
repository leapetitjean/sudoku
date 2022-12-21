#include "Sudoku.hxx"

Sudoku::Sudoku(std::vector<std::vector<int>> grid) {
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            Clause* one_to_n_clause = new Clause();
            for (int z = 0; z < 9; z++) {
                std::shared_ptr<Literal> literal(new Literal(x, y, z));
                literals[x][y].push_back(literal);
                one_to_n_clause->add_literal(literal, false);
            }
            formula.add_clause(one_to_n_clause);
        }
    }

    for (int y = 0; y < 9; y++) {
        for (int z = 0; z < 9; z++) {
            for (int x = 0; x < 8; x++) {
                for (int i = x + 1; i < 9; i++) {
                    Clause* at_most_one_row_clause = new Clause();
                    at_most_one_row_clause->add_literal(literals[x][y][z],
                                                        true);
                    at_most_one_row_clause->add_literal(literals[i][y][z],
                                                        true);
                    formula.add_clause(at_most_one_row_clause);
                }
            }
        }
    }

    for (int x = 0; x < 9; x++) {
        for (int z = 0; z < 9; z++) {
            for (int y = 0; y < 8; y++) {
                for (int i = y + 1; i < 9; i++) {
                    Clause* at_most_one_column_clause = new Clause();
                    at_most_one_column_clause->add_literal(literals[x][y][z],
                                                           true);
                    at_most_one_column_clause->add_literal(literals[x][i][z],
                                                           true);
                    formula.add_clause(at_most_one_column_clause);
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
                            at_most_one_sub_grid_1->add_literal(
                                literals[3 * i + x][3 * j + y][z], true);
                            at_most_one_sub_grid_1->add_literal(
                                literals[3 * i + x][3 * j + k][z], true);
                            formula.add_clause(at_most_one_sub_grid_1);
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
                                at_most_one_sub_grid_2->add_literal(
                                    literals[3 * i + x][3 * j + y][z], true);
                                at_most_one_sub_grid_2->add_literal(
                                    literals[3 * i + k][3 * j + l][z], true);
                                formula.add_clause(at_most_one_sub_grid_2);
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
                if (grid[x][y] - 1 == z) {
                    literals[x][y][z].get()->negate();
                }
                literals[x][y][z].get()->set_fixed();
                formula.unit_propagate(literals[x][y][z]);
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku) {
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            bool is_fixed = false;
            os << "(" << x << ", " << y << ")" << std::endl;
            for (int z = 0; z < 9; z++) {
                if (sudoku.literals[x][y][z].get()->is_fixed()) {
                    os << sudoku.literals[x][y][z].get()->value() << " ";
                } else {
                    os << "? ";
                }
                // if (sudoku.literals[x][y][z].get()->value()) {
                //    os << z+1 << " ";
                //    is_fixed = true;
                //}
            }
            os << std::endl;
            // if (!is_fixed) {
            //    os << 0 << " ";
            //}
        }
        os << "---" << std::endl;
    }
    return os;
}

void Sudoku::solve() {
    Clause* c = formula.get_unit_clause();
    while (c != nullptr) {
        std::shared_ptr<Literal> l = c->get_literal();

        int x = l.get()->get_x();
        int y = l.get()->get_y();
        int z = l.get()->get_z();

        if (!c->is_negative(l)) {
            l.get()->negate();
        }

        l.get()->set_fixed();
        formula.unit_propagate(l);

        c = formula.get_unit_clause();
    }
}