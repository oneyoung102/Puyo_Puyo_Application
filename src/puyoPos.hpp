#pragma once

#include <stdexcept>

class POS
{
    public :
        float x, y;

        POS()
        {
            this->x = 0;
            this->y = 0;
        }
        POS(float x, float y)
        {
            this->x = x;
            this->y = y;
        }
        POS operator+(const POS& other) const { return POS(x + other.x, y + other.y); }
        POS operator-(const POS& other) const { return POS(x - other.x, y - other.y); }
        POS operator*(float c) const { return POS(x * c, y * c); }
        POS operator/(float c) const
        {
            if(c == 0)
                throw std::runtime_error("POS zero division is impossible");
            return POS(x / c, y / c);
        }
};