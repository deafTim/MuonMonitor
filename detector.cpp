#include "!_All_include.h"
#include "detector.h"

detector::detector(): _count(0), _arr(0)
{

}

detector::detector(const detector &d): _coor(d.GetCoor()), _count(d.GetCount())
{
    if (this == &d)
        return;
    _name = d.GetName();
    _arr = new pixel[d.GetCount()];
    for (int i = 0; i < d.GetCount(); ++i)
        _arr[i] = d.GetPixel(i);
}

detector::detector(const point coor, const point size, const int count): _coor(coor), _size(size), _count(count)
{
    _arr = new pixel[_count];
}

std::string detector::GetName() const
{
    return _name;
}

point detector::GetCoor() const
{
    return _coor;
}

point detector::GetSize() const
{
    return _size;
}

pixel detector::GetPixel(const int index) const
{
    if (index < _count)
        return _arr[index];
    return pixel();
}

int detector::GetCount() const
{
    return _count;
}

point detector::GetCoorMax() const
{
    return _coor + _size;
}


void detector::SetAllCoor(const point coor)
{
    for(int i = 0; i < GetCount(); ++i)
    {
        point draft = _arr[i].GetCoor() + coor - GetCoor();
        _arr[i].SetCoor(draft);
    }
    SetCoor(coor);
}

void detector::SetName(const std::string name)
{
    _name = name;
}

void detector::SetCoor(const point coor)
{
    _coor = coor;
}

void detector::SetSize(const point size)
{
    _size = size;
}

void detector::SetPixel(const int index, const pixel p)
{
    if (index >= _count)
        return;
    _arr[index] = p;
}

void detector::SetCount(const int count)
{
    _count = count;
    if (_arr != 0)
        delete [] _arr;
    _arr = new pixel[_count];
}

void detector::CreatePixels(const int count)
{
    if (count == 16)
        if ((GetSize().GetX() == 500) && (GetSize().GetY() == 500))
        {
            SetCount(16);
            pixel p;
            p.SetSize(point(122, 122, 0));
            p.SetCoor(point(GetCoor().GetX() + (122 + 4) * 0,
                            GetCoor().GetY() + (122 + 4) * 1,
                            GetCoor().GetZ()));
            _arr[0] = p;
            p.SetCoor(point(GetCoor().GetX() + (122 + 4) * 1,
                            GetCoor().GetY() + (122 + 4) * 1,
                            GetCoor().GetZ()));
            _arr[1] = p;
            p.SetCoor(point(GetCoor().GetX() + (122 + 4) * 1,
                            GetCoor().GetY() + (122 + 4) * 0,
                            GetCoor().GetZ()));
            _arr[2] = p;
            p.SetCoor(point(GetCoor().GetX() + (122 + 4) * 0,
                            GetCoor().GetY() + (122 + 4) * 0,
                            GetCoor().GetZ()));
            _arr[3] = p;
            p.SetCoor(point(GetCoor().GetX() + (122 + 4) * 0,
                            GetCoor().GetY() + (122 + 4) * 2,
                            GetCoor().GetZ()));
            _arr[4] = p;
            p.SetCoor(point(GetCoor().GetX() + (122 + 4) * 1,
                            GetCoor().GetY() + (122 + 4) * 2,
                            GetCoor().GetZ()));
            _arr[5] = p;
            p.SetCoor(point(GetCoor().GetX() + (122 + 4) * 1,
                            GetCoor().GetY() + (122 + 4) * 3,
                            GetCoor().GetZ()));
            _arr[6] = p;
            p.SetCoor(point(GetCoor().GetX() + (122 + 4) * 0,
                            GetCoor().GetY() + (122 + 4) * 3,
                            GetCoor().GetZ()));
            _arr[7] = p;
            p.SetCoor(point(GetCoor().GetX() + (122 + 4) * 3,
                            GetCoor().GetY() + (122 + 4) * 1,
                            GetCoor().GetZ()));
            _arr[8] = p;
            p.SetCoor(point(GetCoor().GetX() + (122 + 4) * 2,
                            GetCoor().GetY() + (122 + 4) * 1,
                            GetCoor().GetZ()));
            _arr[9] = p;
            p.SetCoor(point(GetCoor().GetX() + (122 + 4) * 2,
                            GetCoor().GetY() + (122 + 4) * 0,
                            GetCoor().GetZ()));
            _arr[10] = p;
            p.SetCoor(point(GetCoor().GetX() + (122 + 4) * 3,
                            GetCoor().GetY() + (122 + 4) * 0,
                            GetCoor().GetZ()));
            _arr[11] = p;
            p.SetCoor(point(GetCoor().GetX() + (122 + 4) * 3,
                            GetCoor().GetY() + (122 + 4) * 2,
                            GetCoor().GetZ()));
            _arr[12] = p;
            p.SetCoor(point(GetCoor().GetX() + (122 + 4) * 2,
                            GetCoor().GetY() + (122 + 4) * 2,
                            GetCoor().GetZ()));
            _arr[13] = p;
            p.SetCoor(point(GetCoor().GetX() + (122 + 4) * 2,
                            GetCoor().GetY() + (122 + 4) * 3,
                            GetCoor().GetZ()));
            _arr[14] = p;
            p.SetCoor(point(GetCoor().GetX() + (122 + 4) * 3,
                            GetCoor().GetY() + (122 + 4) * 3,
                            GetCoor().GetZ()));
            _arr[15] = p;
        }

}

detector& detector::operator = (const detector& d)
{
    if (this == &d)
        return *this;
    _name = d.GetName();
    _coor = d.GetCoor();
    _count = d.GetCount();
    if (_arr != 0)
        delete [] _arr;
    _arr = new pixel[d.GetCount()];
    for (int i = 0; i < d.GetCount(); ++i)
        _arr[i] = d.GetPixel(i);
    return *this;
}

std::istream& operator >> (std::istream& in, detector& d)
{
    point coor;
    in >> coor;
    d.SetCoor(coor);
    int count;
    in >> count;
    d.SetCount(count);
    pixel p;
    for(int i = 0; i < d.GetCount(); ++i)
    {
        in >> p;
        d.SetPixel(i, p);
    }
    return in;
}

std::vector <int> detector::IsCatch(const muon m) const
{
    std::vector<int> v;
    v.clear();
    for (int i = 0; i < _count; ++i)
        if (_arr[i].IsCatch(m))
            v.push_back(i);
    return v;
}

detector::~detector()
{
    if (_arr != 0)
        delete [] _arr;
}
