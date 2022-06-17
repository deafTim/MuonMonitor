#ifndef MUON_H
#define MUON_H

#include "!_All_include.h"
#include "point.h"

class muon
{
public:
    muon();
    muon(const point p, const double tet, const double phi);
    point GetCoor() const;
    double GetPhi() const;
    double GetTet() const;
    double GetPhiCrazy() const;
    double GetTetCrazy() const;

    void SetCoor(const double a, const double b, const double c);
    void SetCoor(const point p);
    void SetTet (double tet);
    void SetPhi (double phi);
    void SetTetCrazy (double tet);
    void SetPhiCrazy (double phi);
    friend std::istream& operator >> (std::istream&, muon&);
private:
    point _point;
    double _phi;
    double _tet;
    double _phi_crazy;
    double _tet_crazy;
};

#endif // MUON_H
