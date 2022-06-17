#ifndef POINT_H
#define POINT_H

#include "!_All_include.h"

class point
{
public:
    point();
    point(double x, double y, double z);
    double GetX() const;
    double GetY() const;
    double GetZ() const;

    bool operator <= (const point& b) const;
    const point operator +(const point b) const;
    const point operator -(const point b) const;
    const point operator -() const;

    void SetX(double x);
    void SetY(double y);
    void SetZ(double z);
    void SetCoor(double x, double y, double z);

    friend std::istream& operator >> (std::istream&, point&);

private:
    double _x;
    double _y;
    double _z;
};

#endif // POINT_H
