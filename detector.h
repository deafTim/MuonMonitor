#ifndef DETECTOR_H
#define DETECTOR_H

#include "!_All_include.h"
#include "muon.h"
#include "pixel.h"
#include "point.h"

class detector
{
public:
    detector();
    detector(const detector& d);//copy constructor
    detector(const point coor, const point size, const int count);

    std::string GetName() const;
    point GetCoor() const;
    point GetSize() const;
    pixel GetPixel(const int index) const;
    int GetCount() const;
    point GetCoorMax() const;

    void SetAllCoor(const point coor);
    void SetName(const std::string name);
    void SetCoor(const point coor);
    void SetSize(const point size);
    void SetPixel(const int index, const pixel p);
    void SetCount(const int count);

    void CreatePixels(const int count);

    detector& operator = (const detector& d);

    friend std::istream& operator >> (std::istream&, detector&);

    std::vector <int> IsCatch(const muon m) const;

    ~detector();
private:
    std::string _name;
    point _coor;
    point _size;
    int _count;
    pixel* _arr;
};

#endif // DETECTOR_H
