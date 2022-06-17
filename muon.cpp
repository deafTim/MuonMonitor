#include "!_All_include.h"
#include "muon.h"

muon::muon()
{
}

muon::muon(const point p, const double tet, const double phi): _point(p), _phi(phi), _tet(tet)
{

}

point muon::GetCoor() const
{
    return _point;
}

double muon::GetPhi() const
{
    return _phi;
}

double muon::GetTet() const
{
    return _tet;
}

double muon::GetPhiCrazy() const
{
    return _phi_crazy;
}

double muon::GetTetCrazy() const
{
    return _tet_crazy;
}

void muon::SetCoor(const double x, const double y, const double z)
{
    _point.SetCoor(x, y, z);
    return;
}

void muon::SetCoor(const point p)
{
    _point = p;
}

void muon::SetPhi(double phi)
{
    _phi = phi;
    return;
}

void muon::SetTet(double tet)
{
    _tet = tet;
    return;
}

void muon::SetPhiCrazy(double phi)
{
    _phi_crazy = phi;
    return;
}

void muon::SetTetCrazy(double tet)
{
    _tet_crazy = tet;
    return;
}

std::istream& operator >> (std::istream& in, muon& m)
{
    point p;
    in >> p;
    m.SetCoor(p);
    int angle;
    in >> angle;
    m.SetPhi(angle);
    in >> angle;
    m.SetTet(angle);
    return in;
}
