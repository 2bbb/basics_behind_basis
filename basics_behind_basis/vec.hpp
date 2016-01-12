//
//  vec.hpp
//
//  Created by ISHII 2bit on 2016/01/08.
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

#include <type_traits>
#include <array>
#include <cmath>

namespace bbb {
    template <std::size_t s, typename value_t = double>
    struct base_vec {
        static_assert(std::is_arithmetic<value_t>::value, "required: value_t is arithmetic type");
        using value_type = value_t;
        
        base_vec()
        : data() {}
        
        base_vec(const base_vec &v)
        : data(v.data) {}
        
        template <typename argument, typename ... arguments, typename std::enable_if<std::is_arithmetic<argument>::value>::type *_ = nullptr>
        base_vec(argument arg, arguments ... args)
        : data({static_cast<value_t>(arg), static_cast<value_t>(args) ...}) {}
        
        template <std::size_t s_, typename value_t_>
        base_vec(const base_vec<s_, value_t_> &v) {
            for(std::size_t i = 0, end = std::min(s, s_); i < end; i++) data[i] = v[i];
        }
        
        constexpr std::size_t size() const { return s; }
        
        value_t &operator[](std::size_t index) { return data[index]; }
        constexpr const value_t &operator[](std::size_t index) const { return data[index]; }
        
        value_t &at(std::size_t index) { return data.at(index); }
        constexpr const value_t &at(std::size_t index) const { return data.at(index); }
        
        base_vec &operator=(const base_vec &v) { data = v.data; }
        base_vec &operator=(const std::array<value_t, s> &v) { data = v; }
        base_vec &operator=(value_type x) {
            for(std::size_t i = 0; i < size(); i++) data[i] = x;
        }
        template <std::size_t s_, typename value_t_>
        base_vec &operator=(const base_vec<s_, value_t_> &v) {
            for(std::size_t i = 0, end = std::min(s, s_); i < end; i++) data[i] = v.data[i];
            return *this;
        }
        
        constexpr const base_vec &operator+() const { return *this; }
        
        constexpr_14 base_vec operator-() const {
            base_vec v0;
            for(std::size_t i = 0; i < size(); i++) v0 = -data[i];
            return v0;
        }
        
        constexpr_14 base_vec operator+(const base_vec &v) const { return base_vec{*this} += v; }
        base_vec &operator+=(const base_vec &v) {
            for(std::size_t i = 0; i < size(); i++) data[i] += v[i];
            return *this;
        }
        
        constexpr_14 base_vec operator-(const base_vec &v) const { return base_vec{*this} -= v; }
        base_vec &operator-=(const base_vec &v) {
            for(std::size_t i = 0; i < size(); i++) data[i] -= v[i];
            return *this;
        }
        
        constexpr_14 value_t dot(const base_vec &v) const {
            value_t sum{0.0};
            for(std::size_t i = 0; i < size(); i++) sum += data[i] * v[i];
            return sum;
        }
        
        constexpr_14 base_vec operator*(value_t scale) const { return base_vec{*this} *= scale; }
        base_vec &operator*=(value_t scale) {
            for(std::size_t i = 0; i < size(); i++) data[i] *= scale;
            return *this;
        }
        
        constexpr_14 base_vec operator/(value_t scale) const { return base_vec{*this} /= scale; }
        base_vec &operator/=(value_t scale) {
            for(std::size_t i = 0; i < size(); i++) data[i] *= 1.0 / scale;
            return *this;
        }
        
        operator std::array<value_t, s> &() { return data; }
        constexpr operator const std::array<value_t, s> &() const { return data; }
        
        constexpr bool operator==(const base_vec &v) const { return data == v.data; }
        constexpr bool operator!=(const base_vec &v) const { return data != v.data; }
        constexpr bool operator<(const base_vec &v)  const { return data <  v.data; }
        constexpr bool operator<=(const base_vec &v) const { return data <= v.data; }
        constexpr bool operator>(const base_vec &v)  const { return data >  v.data; }
        constexpr bool operator>=(const base_vec &v) const { return data >= v.data; }
        void swap(base_vec &v) { std::swap(data, v.data); }
        
        constexpr_14 double distance(const base_vec &rhs) const {
            auto v = *this - rhs;
            return sqrt(v.dot(v));
        }
        
        using iterator = typename std::array<value_t, s>::iterator;
        using const_iterator = typename std::array<value_t, s>::const_iterator;
        using reverse_iterator = typename std::array<value_t, s>::reverse_iterator;
        using const_reverse_iterator = typename std::array<value_t, s>::const_reverse_iterator;
        
        iterator begin() { return data.begin(); }
        iterator end()   { return data.end(); }
        const_iterator begin() const { return data.cbegin(); }
        const_iterator end()   const { return data.cend(); }
        const_iterator cbegin() const { return data.cbegin(); }
        const_iterator cend()   const { return data.cend(); }
        
        reverse_iterator rbegin() { return data.rbegin(); }
        reverse_iterator rend()   { return data.rend(); }
        const_reverse_iterator rbegin() const { return data.crbegin(); }
        const_reverse_iterator rend()   const { return data.crend(); }
        const_reverse_iterator crbegin() const { return data.crbegin(); }
        const_reverse_iterator crend()   const { return data.crend(); }
        
        friend base_vec operator*(value_t scale, const base_vec &v);
    protected:
        std::array<value_t, s> data;
    };
    
    template <std::size_t s, typename value_t = double>
    base_vec<s, value_t> operator*(value_t scale, const base_vec<s, value_t> &v) {
        return v * s;
    }
    
    template <std::size_t s, typename value_t = double>
    struct vec : base_vec<s, value_t> {
        vec() : base_vec<s, value_t>() {};
        template <typename ... arguments>
        vec(arguments ... args) : base_vec<s, value_t>(args ...) {};
    };
    
    template <typename value_t>
    struct vec<2, value_t> : base_vec<2, value_t> {
        value_t &x, &y;
        
        vec(const base_vec<2, value_t> &mom)
        : base_vec<2, value_t>(mom)
        , x(data[0])
        , y(data[1]) {};
        
        vec(value_t x = 0, value_t y = 0)
        : base_vec<2, value_t>(x, y)
        , x(data[0])
        , y(data[1]) {};
        
        template <std::size_t s_, typename value_t_>
        vec(const vec<s_, value_t_> &v)
        : base_vec<2, value_t>(static_cast<base_vec<s_, value_t>>(v))
        , x(data[0])
        , y(data[1]) {};
        
        inline vec &operator=(const vec &v) { data = v.data; };
        
    private:
        using base_vec<2, value_t>::data;
    };
    
    template <typename value_t>
    struct vec<3, value_t> : base_vec<3, value_t> {
        value_t &x, &y, &z;
        
        vec(value_t x = 0, value_t y = 0, value_t z = 0)
        : base_vec<3, value_t>(x, y, z)
        , x(data[0])
        , y(data[1])
        , z(data[2]) {}
        
        operator base_vec<3, value_t> &() { return *this; }
        operator const base_vec<3, value_t> &() const { return *this; }
        
        template <std::size_t s_, typename value_t_>
        vec(const vec<s_, value_t_> &v)
        : base_vec<3, value_t>(static_cast<base_vec<s_, value_t>>(v))
        , x(data[0])
        , y(data[1])
        , z(data[2]) {};
        
        inline vec &operator=(const vec &v) { data = v.data; };
        
    private:
        using base_vec<3, value_t>::data;
    };
    
    template <typename value_t>
    struct vec<4, value_t> : base_vec<4, value_t> {
        value_t &x, &y, &z, &w;
        
        vec(value_t x = 0, value_t y = 0, value_t z = 0, value_t w = 0)
        : base_vec<4, value_t>(x, y, z, w)
        , x(data[0])
        , y(data[1])
        , z(data[2])
        , w(data[3]) {}
        
        template <std::size_t s_, typename value_t_>
        vec(const vec<s_, value_t_> &v)
        : base_vec<4, value_t>(static_cast<base_vec<s_, value_t>>(v))
        , x(data[0])
        , y(data[1])
        , z(data[2])
        , w(data[3]) {};
        
        inline vec &operator=(const vec &v) { data = v.data; };
        
    private:
        using base_vec<4, value_t>::data;
    };
};

#include <iostream>

template <std::size_t s, typename value_t>
std::ostream &operator<<(std::ostream &os, const bbb::base_vec<s, value_t> &v) {
    os << "(";
    for(std::size_t i = 0; i < s - 1; i++) {
        os << v[i] << ", ";
    }
    os << v[s - 1] << ")";
    return os;
}
