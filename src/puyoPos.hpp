#pragma once

#include <stdexcept>

template<class T>
class POS
{
    public :
        T x, y;
        
        #define c x
        #define r y

        template<class P>
        POS(const POS<P>& other)
        {
            if(!(std::is_same<T,float>() || std::is_same<T,int>()) || !(std::is_same<P,float>() || std::is_same<P,int>()))
                throw std::runtime_error("POS explicit type change is impossible");
            this->x = other.x;
            this->y = other.y;
        }
        POS(T x = 0.0, T y = 0.0)
        {
            this->x = x;
            this->y = y;
        }
        POS operator+(const POS& other) const { return POS(x + other.x, y + other.y); }
        POS operator-(const POS& other) const { return POS(x - other.x, y - other.y); }
        POS operator*(T num) const { return POS(x * num, y * num); }
        POS operator/(T num) const
        {
            if(num == 0)
                throw std::runtime_error("POS zero division is impossible");
            return POS(x / num, y / num);
        }
};
using POSi = POS<int>;
using POSf = POS<float>;