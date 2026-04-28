#pragma once

#include <stdexcept>
#include <tuple>

template<class T>
class POS
{
    public :
        union
        {
            struct{T x, y;};
            struct{T c, r;};
        };

        template<class P>
        POS(const POS<P>& other)
        {
            static_assert(std::is_arithmetic<T>() && std::is_arithmetic<P>(),"POS explicit type change is impossible");
            this->x = static_cast<T>(other.x);
            this->y = static_cast<T>(other.y);
        }
        POS(T x = static_cast<T>(0), T y = static_cast<T>(0))
        {
            this->x = x;
            this->y = y;
        }
        POS operator+(const POS& other) const { return POS(x + other.x, y + other.y); }
        POS operator-(const POS& other) const { return POS(x - other.x, y - other.y); }
        POS operator*(T num) const { return POS(x * num, y * num); }
        POS operator*(const POS& other) const { return POS(x * other.x, y * other.y); }
        POS operator/(T num) const
        {
            if(num == 0)
                throw std::runtime_error("POS zero division is impossible");
            return POS(x / num, y / num);
        }
        POS operator/(const POS& other) const
        {
            if(other == POS())
                throw std::runtime_error("POS zero division is impossible");
            return POS(x / other.x, y / other.y);
        }
        POS operator+=(const POS& other)
        {
            this->x += other.x;
            this->y += other.y;
            return *this;
        }
        POS operator-=(const POS& other)
        {
            this->x -= other.x;
            this->y == other.y;
            return *this;
        }
        POS operator*=(T num)
        {
            this->x *= num;
            this->y *= num;
            return *this;
        }
        POS operator/=(T num) const
        {
            if(num == 0)
                throw std::runtime_error("POS zero division is impossible");
            this->x /= num;
            this->y /= num;
            return *this;
        }
        bool operator<(const POS& other) const { return other.x < this->x && other.y < this->y; }
        bool operator>(const POS& other) const { return other.x > this->x && other.y > this->y; }
        bool operator<=(const POS& other) const { return other.x <= this->x && other.y <= this->y; }
        bool operator>=(const POS& other) const { return other.x >= this->x && other.y >= this->y; }
};

using POSs = POS<size_t>;
using POSi = POS<int>;
using POSf = POS<float>;

template<std::size_t I, class T>
auto& get(POS<T>& p)
{
    if constexpr (I == 0) return p.x;
    else return p.y;
}

template<std::size_t I, class T>
const auto& get(const POS<T>& p)
{
    if constexpr (I == 0) return p.x;
    else return p.y;
}
namespace std
{
    template<class T>
    struct tuple_size<POS<T>> : std::integral_constant<size_t, 2> {};

    template<class T>
    struct tuple_element<0, POS<T>> { using type = T; };
    template<class T>
    struct tuple_element<1, POS<T>> { using type = T; };
}