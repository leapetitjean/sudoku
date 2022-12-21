#include "Literal.hxx"

Literal::Literal(int x, int y, int z) {
    std::string name = "x" + std::to_string(x) + std::to_string(y) + std::to_string(z);
    this->name = name; 
    this->x = x;
    this->y = y;
    this->z = z;
}

bool Literal::value() const {
    return assignment;
}

void Literal::negate() {
    if (!fixed) {
        assignment = !assignment;
    }
}

std::ostream& operator<<(std::ostream& os, const Literal& literal) {
    os << literal.name << ": " << literal.assignment;
    return os;
}

void Literal::set_fixed() {
    fixed = true;
}

bool Literal::is_fixed() {
    return fixed;
}