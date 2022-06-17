#include "!_All_include.h"
#include "point.h"

point::point()
{
    _x = 0;
    _y = 0;
    _z = 0;
}

point::point(double x, double y, double z): _x(x), _y(y), _z(z)
{

}

double point::GetX() const
{
    return _x;
}

double point::GetY() const
{
    return _y;
}

double point::GetZ() const
{
    return _z;
}

bool point::operator <=(const point& b) const
{
    if (GetZ() < b.GetZ())
        return true;
    if (GetZ() == b.GetZ())
    {
        if (GetX() < b.GetX())
            return true;
        if (GetX() == b.GetX())
            if (GetY() <= b.GetY())
                return true;
    }
    return false;
}

const point point::operator +(const point b) const
{
    point c;
    c.SetX(GetX() + b.GetX());
    c.SetY(GetY() + b.GetY());
    c.SetZ(GetZ() + b.GetZ());
    return c;
}

const point point::operator -(const point b) const
{
    point c;
    c.SetX(GetX() - b.GetX());
    c.SetY(GetY() - b.GetY());
    c.SetZ(GetZ() - b.GetZ());
    return c;
}

const point point::operator -() const
{
    point b;
    b.SetX(-GetX());
    b.SetY(-GetY());
    b.SetZ(-GetZ());
    return b;
}

void point::SetX(double x)
{
    _x = x;
}

void point::SetY(double y)
{
    _y = y;
}

void point::SetZ(double z)
{
    _z = z;
}

void point::SetCoor(double x, double y, double z){
    SetX(x);
    SetY(y);
    SetZ(z);
}

std::istream& operator >> (std::istream& in, point& p)
{
    int draft;
    in >> draft;
    p.SetX(draft);
    in >> draft;
    p.SetY(draft);
    in >> draft;
    p.SetZ(draft);
    return in;
}
