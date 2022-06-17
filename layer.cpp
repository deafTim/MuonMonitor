#include "!_All_include.h"
#include "layer.h"

layer::layer(): _count(0)
{

}

layer::layer(const layer &l): _coor(l.GetCoor()), _count(l.GetCount())
{
    _arr.clear();
    for(int i = 0; i < l.GetCount(); ++i)
        _arr.push_back(l.GetDetector(i));
    UpdateCoor(true);
}

layer::layer(const point coor, const int count): _coor(coor), _count(count)
{
    _arr.resize(_count);
}

point layer::GetCoor() const
{
    return _coor;
}

detector layer::GetDetector(const int index) const
{
    if (index < _count)
        return _arr[index];
    return detector();
}

int layer::GetCount() const
{
    return _count;
}

point layer::GetCoorMax() const
{
    return _coor_max;
}

void layer::AddDetector(const detector d)
{
    _arr.push_back(d);
    UpdateCoor(d);
    ++_count;
}

void layer::UpdateCoor(bool new_coor)
{
    for(int i = 0; i < (int)_arr.size(); ++i)
        UpdateCoor(_arr[i], ((i == 0) && new_coor));
}

void layer::UpdateCoor(const detector d, bool new_coor)
{
    if (_count == 0 || new_coor)
    {
        _coor = d.GetCoor();
        _coor_max = d.GetCoorMax();
    }
    if (d.GetCoor().GetX() <= _coor.GetX())
        _coor.SetX(d.GetCoor().GetX());
    if (d.GetCoor().GetY() <= _coor.GetY())
        _coor.SetY(d.GetCoor().GetY());
    if (d.GetCoor().GetZ() <= _coor.GetZ())
        _coor.SetZ(d.GetCoor().GetZ());
    if (d.GetCoorMax().GetX() >= _coor_max.GetX())
        _coor_max.SetX(d.GetCoorMax().GetX());
    if (d.GetCoorMax().GetY() >= _coor_max.GetY())
        _coor_max.SetY(d.GetCoorMax().GetY());
    if (d.GetCoorMax().GetZ() >= _coor_max.GetZ())
        _coor_max.SetZ(d.GetCoorMax().GetZ());
}

void layer::SetAllCoor(const point coor)
{
    for(int i = 0; i < GetCount(); ++i)
    {
        point draft = _arr[i].GetCoor() + coor - GetCoor();
        _arr[i].SetAllCoor(draft);
    }
    UpdateCoor(true);
}

void layer::SetCoor(const point coor)
{
    _coor = coor;
}

void layer::SetDetector(const int index, const detector d)
{
    if (index >= _count)
        return;
    _arr[index] = d;
    UpdateCoor(d);
}

void layer::SetCount(const int count)
{
    _count = count;
    _arr.resize(_count);
}

std::istream& operator >> (std::istream& in, layer& l)
{
    point coor;
    in >> coor;
    l.SetCoor(coor);
    int count;
    in >> count;
    l.SetCount(count);
    detector d;
    for(int i = 0; i < l.GetCount(); ++i)
    {
        in >> d;
        l.SetDetector(i, d);
    }
    return in;
}

std::vector < std::pair < int, std::vector <int> > >  layer::IsCatch(const muon m) const
{
    std::vector < std::pair <int, std::vector <int> > > v;
    v.clear();
    std::vector <int> draft;
    for (int i = 0; i < (int)_arr.size(); ++i)
    {
        draft = _arr[i].IsCatch(m);
        if (draft.size() != 0)
            v.push_back(make_pair(i,draft));
    }
    return v;
}

void layer::Clear()
{
    _coor = point();
    _count = 0;
    _arr.clear();
}
