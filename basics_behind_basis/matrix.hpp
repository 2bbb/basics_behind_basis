//
//  matrix.hpp
//
//  Created by ISHII 2bit on 2016/01/11.
//
//

#pragma once

#ifndef constexpr_14
#   if 201402L <= __cplusplus
#       define constexpr_14 constexpr
#   else
#       define constexpr_14
#   endif
#endif

#include <iostream>
#include <type_traits>
#include <array>
#include <cmath>
#include <algorithm>

namespace bbb {
    using default_value_t = double;

    template <std::size_t row_num, std::size_t col_num, typename value_t = default_value_t>
    struct matrix {
        using value_type = value_t;
        using column_type = std::array<value_t, col_num>;
        using inner_container_type = std::array<column_type, row_num>;
        inner_container_type data;
        
        constexpr std::size_t row_size() const { return row_num; }
        constexpr std::size_t column_size() const { return col_num; }

        matrix() = default;
        matrix(const value_type (&data)[col_num][row_num]) {
            for(std::size_t j = 0; j < col_num; j++) {
                for(std::size_t i = 0; i < row_num; i++) {
                    this->data[j][i] = data[j][i];
                }
            }
        }
        inline column_type &operator[](std::size_t index) { return data[index]; }
        inline const column_type &operator[](std::size_t index) const { return data[index]; }
        
        inline matrix operator+(const matrix &rhs) const { return matrix{*this} += rhs; }
        matrix &operator+=(const matrix &rhs) {
            for(std::size_t j = 0; j < data.size(); j++) {
                for(std::size_t i = 0; i < data[j].size(); i++) {
                    data[j][i] += rhs.data[j][i];
                }
            }
            return *this;
        }
        
        inline constexpr matrix operator-(const matrix &rhs) const { return matrix{*this} -= rhs; }
        matrix &operator-=(const matrix &rhs) {
            for(std::size_t j = 0; j < data.size(); j++) {
                for(std::size_t i = 0; i < data[j].size(); i++) {
                    data[j][i] -= rhs[j][i];
                }
            }
            return *this;
        }
        
        template <std::size_t col_num_, typename value_t_>
        matrix<row_num, col_num_, value_t> operator*(const matrix<col_num, col_num_, value_t_> &rhs) const {
            matrix<row_num, col_num_, value_t> res;
            for(std::size_t i = 0; i < row_num; i++) {
                for(std::size_t j = 0; j < col_num_; j++) {
                    res[i][j] = 0;
                    for(std::size_t k = 0; k < col_num; k++) {
                        res[i][j] += data[i][k] * rhs[k][j];
                    }
                }
            }
            return res;
        }
        
        inline constexpr matrix operator*(value_t scale) const { return matrix{*this} *= scale; }
        matrix &operator*=(value_t scale) {
            for(std::size_t j = 0; j < data.size(); j++) {
                for(std::size_t i = 0; i < data[j].size(); i++) {
                    data[j][i] *= scale;
                }
            }
            return *this;
        }
        
        inline constexpr matrix operator/(value_t scale) const { return matrix{*this} /= scale; }
        matrix &operator/=(value_t scale) {
            return *this *= (1.0 / scale);
        }
        
        inline constexpr matrix operator+() const { return matrix{*this}; }
        inline constexpr matrix operator-() const { return matrix{*this} *= -1.0; }
        
        inline constexpr bool operator==(const matrix &rhs) const { return data == rhs.data; };
        inline constexpr bool operator!=(const matrix &rhs) const { return data != rhs.data; };
        inline void swap(matrix &rhs) { std::swap(data, rhs.data); }
        
        constexpr_14 matrix<col_num, row_num, value_t> transpose() const {
            matrix<col_num, row_num, value_t> res;
            for(std::size_t j = 0; j < data.size(); j++) {
                for(std::size_t i = 0; i < data[j].size(); i++) {
                    res[i][j] = data[j][i];
                }
            }
            return res;
        }

        inline constexpr_14 auto trace() const
        -> typename std::enable_if<row_num == col_num, value_type>::type
        {
            std::size_t size = row_num;
            value_type sum{0};
            for(std::size_t i = 0; i < size; i++) sum += (*this)[i][i];
            return sum;
        }

        typename std::enable_if<row_num == col_num>::type lu_decomposition(matrix &l, matrix &u) {
            std::size_t size = row_num;
            l *= 0;
            u *= 0;
            for(std::size_t i = 0; i < size; i++) l[i][i] = 1;

            for(std::size_t j = 0; j < size; j++) {
                u[0][j] = (*this)[0][j];
                for(std::size_t i = 1; i < j + 1; i++) {
                    value_t sum{0.0};
                    for(std::size_t k = 0; k < i; k++) sum += l[i][k] * u[k][j];
                    u[i][j] = (*this)[i][j] - sum;
                }
                for(std::size_t i = j + 1; i < size; i++) {
                    value_t sum{0.0};
                    for(std::size_t k = 0; k < i; k++) sum += l[i][k] * u[k][j];
                    l[i][j] = ((*this)[i][j] - sum) / u[j][j];
                }
            }
        }
    };
    
    template <std::size_t size, typename value_t = default_value_t>
    struct square_matrix : matrix<size, size, value_t> {
        using typename matrix<size, size, value_t>::value_type;
        using typename matrix<size, size, value_t>::column_type;
        using matrix<size, size, value_t>::data;
        using matrix<size, size, value_t>::operator*=;

        square_matrix() = default;
        template <typename value_t_>
        square_matrix(const matrix<size, size, value_t_> &m)
        : matrix<size, size, value_t>(m) {}
        
        inline square_matrix &operator*=(const square_matrix &rhs) {
            return (*this = (*this) * rhs);
        }
    };
    
    template <std::size_t size, typename value_t = default_value_t>
    struct column_vector;
    
    template <std::size_t size, typename value_t = default_value_t>
    struct row_vector : matrix<size, 1, value_t> {
        using typename matrix<size, 1, value_t>::value_type;
        using matrix<size, 1, value_t>::data;
        
        value_type &operator[](std::size_t index) { return data[index][0]; }
        constexpr value_type &operator[](std::size_t index) const { return data[index][0]; }
        
        constexpr_14 double dot(const row_vector &rhs) const {
            value_type sum{0.0};
            for(std::size_t i = 0; i < size; i++) sum += (*this)[i] * rhs[i];
            return sum;
        }
        
        inline constexpr_14 double distance(const row_vector &rhs) const {
            return ((*this) - rhs).norm();
        }
        
        constexpr_14 double norm() const {
            double sum{0.0};
            for(std::size_t i = 0; i < size; i++) sum += (*this)[i] * (*this)[i];
            return std::sqrt(sum);
        }
        
        inline constexpr double p_distance(const row_vector &rhs, std::size_t p) const {
            return ((*this) - rhs).p_norm(p);
        }
        
        constexpr_14 double p_norm(std::size_t p) const {
            double sum{0.0};
            for(std::size_t i = 0; i < size; i++) sum += std::pow(std::fabs((*this)[i]), p);
            return std::pow(sum, 1.0 / p);
        }
        
        constexpr_14 double inf_norm() const {
            double max{fabs((*this)[0])};
            for(std::size_t i = 1; i < size; i++) max = std::max(std::fabs((*this)[i]), max);
            return max;
        }
        
        inline constexpr column_vector<size, value_type> convert_to_column() const {
            return this->transpose();
        }
    };
    
    template <std::size_t size, typename value_t>
    struct column_vector : matrix<1, size, value_t> {
        using typename matrix<1, size, value_t>::value_type;
        using matrix<1, size, value_t>::data;
        
        value_type &operator[](std::size_t index) { return data[0][index]; }
        constexpr value_type &operator[](std::size_t index) const { return data[0][index]; }
        
        constexpr_14 value_type dot(const column_vector &rhs) const {
            value_type sum{0.0};
            for(std::size_t i = 0; i < size; i++) sum += (*this)[i] * rhs[i];
            return sum;
        }
        
        inline constexpr double distance(const column_vector &rhs) const {
            return ((*this) - rhs).norm();
        }
        
        constexpr_14 double norm() const {
            double sum{0.0};
            for(std::size_t i = 0; i < size; i++) sum += (*this)[i] * (*this)[i];
            return std::sqrt(sum);
        }
        
        inline constexpr double p_distance(const column_vector &rhs, std::size_t p) const {
            return ((*this) - rhs).p_norm(p);
        }
        
        constexpr_14 double p_norm(std::size_t p) const {
            double sum{0.0};
            for(std::size_t i = 0; i < size; i++) sum += std::pow(std::fabs((*this)[i]), p);
            return std::pow(sum, 1.0 / p);
        }
        
        constexpr_14 double inf_norm() const {
            double max{fabs((*this)[0])};
            for(std::size_t i = 1; i < size; i++) max = std::max(std::fabs((*this)[i]), max);
            return max;
        }
        
        inline constexpr row_vector<size, value_type> convert_to_row_vector() const {
            return this->transpose();
        }
    };
    
    template <std::size_t size, typename value_t = default_value_t>
    using vector = column_vector<size, value_t>;
};

#include <iostream>

template <std::size_t row_num, std::size_t col_num, typename value_t>
std::ostream &operator<<(std::ostream &os, const bbb::matrix<row_num, col_num, value_t> &mat) {
    for(std::size_t j = 0; j < col_num; j++) {
        for(std::size_t i = 0; i < row_num - 1; i++) {
            os << mat[j][i] << ", ";
        }
        os << mat[j][row_num - 1] << std::endl;
    }
    return os;
}
