#include "surface.h"
#include "point.h"
#include "muon.h"
#include "!_All_include.h"

surface::surface(): _count(0), _index(0)
{
    _arr.clear();
}

surface::surface(const point coor, const double tet, const double phi, const double len, const int count):_coor(coor), _tet(tet), _phi(phi), _len(len),_count(count)
{
    _arr.resize(_count);
}

point surface::GetCoor() const
{
    return _coor;
}

double surface::GetTet() const
{
    return _tet;
}

double surface::GetPhi() const
{
    return _phi;
}

double surface::GetLen() const
{
    return _len;
}

int surface::GetCount() const
{
    return _count;
}

muon surface::GetMuon(const int index) const
{
    if (index < _count)
        return _arr[index];
    return muon();
}

int surface::GetIndex() const
{
    return _index;
}

void surface::SetCoor(const point coor)
{
    _coor = coor;
}

void surface::SetTet(const double tet)
{
    _tet = tet;

}

void surface::SetPhi(const double phi)
{
    _phi = phi;
}

void surface::SetLen(const double len)
{
    _len = len;
}

void surface::SetCount(const int count)
{
    int i;
    for(i = 0; i < sqrt(count); ++i);
    if (i * i != count)
    {
        std::cout << "error: surf " << GetIndex() << "try set count " << count << ", but it not a ^2 of int " << i << std::endl;
        return;
    }
    _count = count;
    _arr.resize(_count);
}

void surface::SetMuon(const int index, const muon m)
{
    if (index >= _count)
        return;
    _arr[index] = m;
}

void surface::SetIndex(const int index)
{
    _index = index;
}

std::istream& operator >> (std::istream& in, surface& s)
{
    point draft;
    in >> draft;
    s.SetCoor(draft);
    int draft_int;
    in >> draft_int;
    s.SetTet(draft_int);
    in >> draft_int;
    s.SetPhi(draft_int);
    in >> draft_int;
    s.SetLen(draft_int);
    return in;
}

void surface::CreateMuons(const int count)
{
    SetCount(count);
    int count_x = sqrt(count);
    double draft_x, draft_y, draft_z;
    int count_m = 0;
    double delta_edge = GetLen() * (1 - 1.0 / count_x) / 2;
    double delta_step = GetLen() / count_x;

    double phi_crazy = atan(GetTet() / (sin(GetTet()) * cos(GetPhi())));
    double tet_crazy = atan(GetTet() / (sin(GetTet()) * sin(GetPhi())));

    muon draft;
    draft.SetPhi(GetPhi());
    draft.SetTet(GetTet());
    draft.SetPhiCrazy(phi_crazy);
    draft.SetTetCrazy(tet_crazy);

    for(double i = -delta_edge; i <= delta_edge; i+=delta_step)
        for(double j = -delta_edge; j <= delta_edge; j+=delta_step)
        {
            draft_x = (GetCoor().GetX() + i) * cos(GetPhi()) -
                    ((GetCoor().GetY() + j) * cos(GetTet()) -
                     GetCoor().GetZ() * sin(GetTet())) * sin(GetPhi());
            draft_y = (GetCoor().GetX() + i) * sin(GetPhi()) +
                    ((GetCoor().GetY() + j) * cos(GetTet()) -
                     GetCoor().GetZ() * sin(GetTet())) * cos(GetPhi());
            draft_z = (GetCoor().GetY() + j) * sin(GetTet()) +
                    GetCoor().GetZ() * cos(GetTet());
            draft.SetCoor(draft_x, draft_y, draft_z);
//            std::cout << std::setw(6) << std::setfill(' ') << "create_muons\t" << i << "\t" << j << "\t" << draft_x << "\t" << draft_y << "\t" << draft_z << std::endl;
            SetMuon(count_m, draft);
            ++count_m;
        }
}

void surface::RunMuons(res &r, const equipment e) const
{
    for (int i = 0; i < e.GetCount(); ++i)
        RunMuons(r, e.GetKit(i));
}

void surface::RunMuons(res &r, const kit k) const
{
    for (int i = 0; i < GetCount(); ++i)
    {
        event draft;
        draft.SetMuon(GetMuon(i));
        draft.SetMuonIndex((long long) GetIndex() * GetCount() + i);
        draft.SetKitIndex(k.GetIndex());
        k.IsCatch(draft);
        r.AddEvent(draft);
    }
}
