#ifndef EVENT_H
#define EVENT_H

#include "!_All_include.h"
#include "muon.h"

class event
{
public:
    event();
    event(const muon m, const int index_k, const int index_m);

    std::vector < std::pair < int , std::vector < std::pair < int, std::vector < int > > > > > GetArr() const;
    long long GetKitIndex() const;
    long long GetMuonIndex() const;
    muon GetMuon() const;
    bool GetFlag() const;
    int GetCountOfDetectors() const;
    int GetCountOfLayers() const;
    int GetCountOfPixels() const;

    void SetArr(std::vector < std::pair < int , std::vector < std::pair < int, std::vector < int > > > > > _arr);
    void SetMuon(const muon m);
    void SetKitIndex(const long long index_k);
    void SetMuonIndex(const long long index_m);
    void SetFlag(const bool flag);

    void UpdateCounts();

private:
    long long _index_k;
    long long _index_m;
    int _count_l;
    int _count_d;
    int _count_p;
    muon _m;
    bool _flag;
    std::vector < std::pair < int , std::vector < std::pair < int, std::vector < int > > > > > _arr;
};

#endif // EVENT_H
