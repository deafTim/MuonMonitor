#ifndef KIT_H
#define KIT_H

#include "!_All_include.h"
#include "layer.h"
#include "muon.h"
#include "point.h"
#include "event.h"

class kit
{
public:
    kit();
    kit(const kit& k);
    kit(const point coor, const int count);

    std::string GetName() const;
    point GetCoor() const;
    int GetCount() const;
    layer GetLayer(const int index) const;
    long long GetIndex() const;
    point GetCoorMax() const;
    point GetCoorMid() const;

    void AddLayer(const layer l);
    void UpdateCoor(bool new_coor = 0);
    void UpdateCoor(const layer l, bool new_coor = 0);

    void SetAllCoor(const point coor);
    void SetName(const std::string name);
    void SetCoor(const point coor);
    void SetCount(const int count);
    void SetLayer(const int index, const layer l);
    void SetIndex(const long long index);

    void ReadDetector(std::string detector_config);
    void PrintData();

    void IsCatch(event& e) const;

private:
    std::string _name;
    long long _index;
    point _coor;
    point _coor_max;
    point _coor_mid;
    int _count;
    std::vector<layer> _arr;
};

#endif // KIT_H
