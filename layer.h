#ifndef LAYER_H
#define LAYER_H

#include "!_All_include.h"
#include "detector.h"
#include "muon.h"
#include "point.h"

class layer
{
public:
    layer();
    layer(const layer& l);
    layer(const point coor, const int count);

    point GetCoor() const;
    detector GetDetector(const int index) const;
    int GetCount() const;
    point GetCoorMax() const;

    void AddDetector(const detector d);
    void UpdateCoor(bool new_coor = 0);
    void UpdateCoor(const detector d, bool new_coor = 0);

    void SetAllCoor(const point coor);
    void SetCoor(const point coor);
    void SetDetector(const int index, const detector d);
    void SetCount(const int count);

    friend std::istream& operator >> (std::istream&, layer&);

    std::vector < std::pair <int, std::vector <int> > >  IsCatch(const muon m) const;

    void Clear();

private:
    point _coor;
    point _coor_max;
    int _count;
    std::vector<detector> _arr;
};

#endif // LAYER_H
