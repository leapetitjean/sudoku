#ifndef LITERAL_HXX
#define LITERAL_HXX

#include <iostream>
#include <string>

class Literal {
   private:
    std::string name;
    bool assignment = false;
    bool fixed = false;
    int x;
    int y;
    int z;

   public:
    Literal(int x, int y, int z);
    bool value() const;
    void negate();
    void set_fixed();
    bool is_fixed();
    inline int get_x() { return x; };
    inline int get_y() { return y; };
    inline int get_z() { return z; };
    friend std::ostream& operator<<(std::ostream& os, const Literal& literal);
};

#endif  // LITERAL_HXX