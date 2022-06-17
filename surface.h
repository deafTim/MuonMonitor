#ifndef SURFACE_H
#define SURFACE_H

#include "!_All_include.h"
#include "equipment.h"
#include "muon.h"
#include "point.h"
#include "res.h"

class surface
{
public:
    surface();
    surface(const point coor, const double tet,
            const double phi, const double len, const int count);
    
    point GetCoor() const;
    double GetTet() const;
    double GetPhi() const;
    double GetLen() const;
    int GetCount() const;
    muon GetMuon(const int index) const;
    int GetIndex() const;

    void SetCoor(const point coor);
    void SetTet(const double tet);
    void SetPhi(const double phi);
    void SetLen(const double len);
    void SetCount(const int count);
    void SetMuon(const int index, const muon m);
    void SetIndex(const int index);

    friend std::istream& operator >> (std::istream&, surface&);

    void CreateMuons(const int count);
    void RunMuons(res& r, const equipment e) const;
    void RunMuons(res& r, const kit k) const;

private:
    point _coor;
    double _tet;
    double _phi;
    double _len;
    int _count;
    int _index;
    std::vector<muon> _arr;
};

#endif // SURFACE_H
