#include "!_All_include.h"
#include "pixel.h"

pixel::pixel()
{
}

point pixel::GetCoor() const
{
    return _coor;
}

point pixel::GetSize() const
{
    return _size;
}

void pixel::SetCoor(const point coor)
{
    _coor = coor;
}

void pixel::SetSize(const point size)
{
    _size = size;
}

bool pixel::IsCatch(const muon m) const
{
    if (GetSize().GetZ() == 0)
    {
        double draft_z = GetCoor().GetZ() - m.GetCoor().GetZ();
        double draft_x = m.GetCoor().GetX() +
                (draft_z) * sin(m.GetTet()) * cos(m.GetPhi()) /
                cos(m.GetTet());
        double draft_y = m.GetCoor().GetY() +
                (draft_z) * sin(m.GetTet()) * sin(m.GetPhi()) /
                cos(m.GetTet());
        int draft_x_low = GetCoor().GetX();
        int draft_x_big = GetCoor().GetX() + _size.GetX();
        int draft_y_low = GetCoor().GetY();
        int draft_y_big = GetCoor().GetY() + _size.GetY();

        if ((draft_x >= draft_x_low) && (draft_x < draft_x_big)
             && (draft_y >= draft_y_low) && (draft_y < draft_y_big))
            return true;
    }
    return false;
}

std::istream& operator >> (std::istream& in, pixel& p)
{
    point draft;
    in >> draft;
    p.SetCoor(draft);
    in >> draft;
    p.SetSize(draft);
    return in;
}
