#ifndef RES_H
#define RES_H

#include "!_All_include.h"
#include "equipment.h"
#include "event.h"

class res
{

public:
    res();
    res(const res& r);
    res(const long long count);

    long long GetCount() const;
    event GetEvent(const int index) const;

    void AddEvent(const event e);

    void SetCount(const long long count);
    void SetEvent(const int index, const event e);

    void PrintData(const equipment e, bool print_empty = 0, bool print_full_data = 0, int min_count_l = 0, int min_count_d = 0, int min_count_p = 0) const;

private:
    long long _count;
    std::vector<event> _arr;
};

#endif // RES_H
