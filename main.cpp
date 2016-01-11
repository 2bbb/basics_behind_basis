#include <iostream>
#include "include/matrix.hpp"

int main() {
    bbb::matrix<2, 2> a{{{1.0, 2.0}, {0.1, 4.0}}}, b, l, u;
    a.lu_decomposition(l, u);
    b = l * u;
    std::cout << "a" << std::endl;
    std::cout << a[0][0] << ", " << a[0][1] << std::endl
              << a[1][0] << ", " << a[1][1] << std::endl;
    std::cout << "b" << std::endl;
    std::cout << b[0][0] << ", " << b[0][1] << std::endl
              << b[1][0] << ", " << b[1][1] << std::endl;
    std::cout << "l" << std::endl;
    std::cout << l[0][0] << ", " << l[0][1] << std::endl
              << l[1][0] << ", " << l[1][1] << std::endl;
    std::cout << "u" << std::endl;
    std::cout << u[0][0] << ", " << u[0][1] << std::endl
              << u[1][0] << ", " << u[1][1] << std::endl;
    bbb::square_matrix<2> c;
    c = a * b;
    c.lu_decomposition(l, u);
    std::cout << "c" << std::endl;
    std::cout << c[0][0] << ", " << c[0][1] << std::endl
              << c[1][0] << ", " << c[1][1] << std::endl;
    std::cout << "l" << std::endl;
    std::cout << l[0][0] << ", " << l[0][1] << std::endl
              << l[1][0] << ", " << l[1][1] << std::endl;
    std::cout << "u" << std::endl;
    std::cout << u[0][0] << ", " << u[0][1] << std::endl
              << u[1][0] << ", " << u[1][1] << std::endl;
    c = l * u;
    std::cout << "c" << std::endl;
    std::cout << c[0][0] << ", " << c[0][1] << std::endl
    << c[1][0] << ", " << c[1][1] << std::endl;
    return 0;
}