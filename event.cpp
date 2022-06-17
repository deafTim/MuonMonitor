#include "!_All_include.h"
#include "event.h"

event::event()
{
    _arr.clear();
}

event::event(const muon m, const int index_k, const int index_m): _index_k(index_k), _index_m(index_m),  _m(m)
{
    _arr.clear();
}

std::vector < std::pair < int , std::vector < std::pair < int, std::vector < int > > > > > event::GetArr() const
{
    return _arr;
}

muon event::GetMuon() const
{
    return _m;
}

long long event::GetKitIndex() const
{
    return _index_k;
}

long long event::GetMuonIndex() const
{
    return _index_m;
}

bool event::GetFlag() const
{
    return _flag;
}

int event::GetCountOfDetectors() const
{
    return _count_d;
}

int event::GetCountOfLayers() const
{
    return _count_l;
}

int event::GetCountOfPixels() const
{
    return _count_p;
}

void event::SetMuon(const muon m)
{
    _m = m;
}

void event::SetKitIndex(const long long index_k)
{
    if (index_k != 0)
        std::cout << "errrrrr " << index_k << std::endl;
    _index_k = index_k;
    _arr.clear();
}

void event::SetMuonIndex(const long long index_m)
{
    _index_m = index_m;
}

void event::SetArr(std::vector < std::pair < int, std::vector < std::pair < int, std::vector < int > > > > > arr)
{
    if (GetFlag())
        _arr = arr;
    else
        _arr.clear();
    UpdateCounts();
}

void event::SetFlag(const bool flag)
{
    _flag = flag;
    _arr.clear();
}

void event::UpdateCounts()
{
    _count_d = 0;
    _count_l = _arr.size();
    _count_p = 0;
    for (int i = 0; i < (int)_arr.size(); ++i)
    {
        _count_d += _arr[i].second.size();
        for (int j = 0; j < (int)_arr[i].second.size(); ++j)
            _count_p += _arr[i].second[j].second.size();
    }
}
