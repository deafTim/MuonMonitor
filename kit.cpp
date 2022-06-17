#include "!_All_include.h"
#include "kit.h"

kit::kit(): _count(0)
{

}

kit::kit(const kit& k): _index(k.GetIndex()), _coor(k.GetCoor()), _count(k.GetCount())
{
    _arr.clear();
    for(int i = 0; i < k.GetCount(); ++i)
        _arr.push_back(k.GetLayer(i));
    UpdateCoor(true);
}

kit::kit(point coor, int count): _coor(coor), _count(count)
{
    _arr.resize(_count);
}

std::string kit::GetName() const
{
    return _name;
}

point kit::GetCoor() const
{
    return _coor;
}

int kit::GetCount() const
{
    return _count;
}

layer kit::GetLayer(const int index) const
{
    if (index < _count)
        return _arr[index];
    return layer();
}

long long kit::GetIndex() const
{
    return _index;
}

point kit::GetCoorMax() const
{
    return _coor_max;
}

point kit::GetCoorMid() const
{
    return _coor_mid;
}

void kit::AddLayer(const layer l)
{
    _arr.push_back(l);
    UpdateCoor(l);
    ++_count;
}

void kit::UpdateCoor(bool new_coor)
{
    for(int i = 0; i < (int)_arr.size(); ++i)
        UpdateCoor(_arr[i], ((i == 0) && new_coor));
}

void kit::UpdateCoor(const layer l, bool new_coor)
{
    if (_count == 0 || new_coor)
    {
        _coor = l.GetCoor();
        _coor_max = l.GetCoorMax();
    }
    if (l.GetCoor().GetX() <= _coor.GetX())
        _coor.SetX(l.GetCoor().GetX());
    if (l.GetCoor().GetY() <= _coor.GetY())
        _coor.SetY(l.GetCoor().GetY());
    if (l.GetCoor().GetZ() <= _coor.GetZ())
        _coor.SetZ(l.GetCoor().GetZ());
    if (l.GetCoorMax().GetX() >= _coor_max.GetX())
        _coor_max.SetX(l.GetCoorMax().GetX());
    if (l.GetCoorMax().GetY() >= _coor_max.GetY())
        _coor_max.SetY(l.GetCoorMax().GetY());
    if (l.GetCoorMax().GetZ() >= _coor_max.GetZ())
        _coor_max.SetZ(l.GetCoorMax().GetZ());
    _coor_mid.SetX((_coor.GetX() + _coor_max.GetX()) / 2);
    _coor_mid.SetY((_coor.GetY() + _coor_max.GetY()) / 2);
    _coor_mid.SetZ((_coor.GetZ() + _coor_max.GetZ()) / 2);
}

void kit::SetAllCoor(const point coor)
{
    for(int i = 0; i < GetCount(); ++i)
    {
        point draft = _arr[i].GetCoor() + coor - GetCoor();
        _arr[i].SetAllCoor(draft);
    }
    UpdateCoor(true);
}

void kit::SetName(const std::string name)
{
    _name = name;
}

void kit::SetCoor(const point coor)
{
    _coor = coor;
}

void kit::SetCount(const int count)
{
    _count = count;
    _arr.resize(_count);
}

void kit::SetLayer(const int index, const layer l)
{
    if (index >= _count)
        return;
    _arr[index] = l;
    UpdateCoor(l);
}

void kit::SetIndex(const long long index)
{
    _index = index;
}

void kit::ReadDetector(std::string detector_config)
{
    std::ifstream fin(detector_config.c_str());

//    if (fin.good())
//        std::cout << "good\n";
//    else
//        std::cout << "bad\n";

    int count_pixels = 16;
    point size(500, 500 ,0);

    layer l;
    detector d;
    point p;
    std::string draft;
    int x, y, z;

    std::getline(fin, draft);
    std::getline(fin, draft);
    while(! fin.eof())
    {
        while(! fin.eof())
        {
            fin >> draft;
            if (draft.compare("###") == 0)
                break;
            if (draft.compare("STOP") == 0)
                break;
            fin >> draft;
            d.SetName(draft);
            fin >> draft;
            fin >> draft;
            fin >> x >> y >> z;
            p.SetCoor(x, y ,z);
            d.SetCoor(p);
            d.SetSize(size);
            fin >> draft;
            fin >> draft;
            d.CreatePixels(count_pixels);
            l.AddDetector(d);
        }
        AddLayer(l);
        l.Clear();
        if (draft.compare("STOP") == 0)
            break;
    }
}

void kit::PrintData()
{
    std::cout << "kit " << GetName() << ":\t\t\t\t\t" <<
                 std::setw(6) << std::setfill(' ') <<
                 GetCoor().GetX() << "\t" <<
                 std::setw(6) << std::setfill(' ') <<
                 GetCoor().GetY() << "\t" <<
                 std::setw(6) << std::setfill(' ') <<
                 GetCoor().GetZ() << "\t" <<
                 std::endl;
    for(int i = 0; i < GetCount(); ++i)
    {
        std::cout << "\t" << "layer " << i << ":\t\t\t" <<
                     std::setw(6) << std::setfill(' ') <<
                     GetLayer(i).GetCoor().GetX() << "\t" <<
                     std::setw(6) << std::setfill(' ') <<
                     GetLayer(i).GetCoor().GetY() << "\t" <<
                     std::setw(6) << std::setfill(' ') <<
                     GetLayer(i).GetCoor().GetZ() << "\t" <<
                     std::endl;
        for(int j = 0; j < GetLayer(i).GetCount(); ++j)
        {
            std::cout << "\t\t" << "detector " << GetLayer(i).GetDetector(j).GetName() << ":\t\t" <<
                         std::setw(6) << std::setfill(' ') <<
                         GetLayer(i).GetDetector(j).GetCoor().GetX() << "\t" <<
                         std::setw(6) << std::setfill(' ') <<
                         GetLayer(i).GetDetector(j).GetCoor().GetY() << "\t" <<
                         std::setw(6) << std::setfill(' ') <<
                         GetLayer(i).GetDetector(j).GetCoor().GetZ() << "\t" <<std::endl;
            for(int g = 0; g < GetLayer(i).GetDetector(j).GetCount(); ++g)
                std::cout << "\t\t\t" << "pixel " << g << ":\t" <<
                             std::setw(6) << std::setfill(' ') <<
                             std::setw(6) << std::setfill(' ') <<
                             GetLayer(i).GetDetector(j).GetPixel(g).GetCoor().GetX() << "\t" <<
                             std::setw(6) << std::setfill(' ') <<
                             GetLayer(i).GetDetector(j).GetPixel(g).GetCoor().GetY() << "\t" <<
                             std::setw(6) << std::setfill(' ') <<
                             GetLayer(i).GetDetector(j).GetPixel(g).GetCoor().GetZ() << std::endl;
        }
        if (i < (GetCount() - 1))
            std::cout << "---------------------------------------------------------------" << std::endl;
    }
}

void kit::IsCatch(event &e) const
{
    std::vector < std::pair < int, std::vector < std::pair < int, std::vector < int > > > > > v;
    v.clear();
    std::vector < std::pair <int, std::vector <int> > > draft;
    for (int i = 0; i < GetCount(); ++i){
        draft = GetLayer(i).IsCatch(e.GetMuon());
        if (draft.size() != 0)
            v.push_back(make_pair(i,draft));
    }
    if (v.size() == 0)
        e.SetFlag(false);
    else
    {
        e.SetFlag(true);
        e.SetArr(v);
    }
}
