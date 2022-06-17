#ifndef PIXEL_H
#define PIXEL_H

#include "!_All_include.h"
#include "muon.h"
#include "point.h"

class pixel
{
public:
    pixel();
    point GetCoor() const;
    point GetSize() const;
    void SetCoor(const point coor);
    void SetSize(const point size);
    bool IsCatch(const muon m) const;
    friend std::istream& operator >> (std::istream&, pixel&);
private:
    point _coor;
    point _size;
};

#endif // PIXEL_H
