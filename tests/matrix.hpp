//
// Created by ISHII 2bit on 2016/01/12.
//

#pragma once

#include <matrix.hpp>

namespace bbb_test {
    namespace matrix {
        void test() {
            bbb::matrix<2, 2> a{{{1.0, 2.0}, {0.1, 4.0}}}, b, l, u;
            a.lu_decomposition(l, u);
            b = l * u;
            std::cout << "a" << std::endl << a;
            std::cout << "b" << std::endl << b;
            std::cout << "l" << std::endl << l;
            std::cout << "u" << std::endl << u;
            bbb::square_matrix<2> c;
            std::cout << (a == b ? "a == b" : "a != b") << std::endl;
            c = a * b;
            c.lu_decomposition(l, u);
            std::cout << "c" << std::endl << c;
            std::cout << "l" << std::endl << l;
            std::cout << "u" << std::endl << u;
            c = l * u;
            std::cout << "c" << std::endl << c;
            std::cout << (c == a * b ? "c == a * b" : "c != a * b") << std::endl;
        }
    };
}