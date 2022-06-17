#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "!_All_include.h"
#include "kit.h"

class equipment
{
public:
    equipment();
    equipment(const equipment& e);
    equipment(const int count);

    int GetCount() const;
    kit GetKit(const int index) const;

    void AddKit(const kit k);

    void SetCount(const int count);
    void SetKit(const int index, const kit k);

    void PrintData();

private:
    int _count;
    std::vector<kit> _arr;
};

#endif // EQUIPMENT_H
