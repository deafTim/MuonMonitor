#include "res.h"

res::res(): _count(0)
{

}

res::res(const res& r): _count(r.GetCount())
{
    _arr.clear();
    for (int i = 0; i < r.GetCount(); ++i)
        _arr.push_back(r.GetEvent(i));
}

res::res(const long long count): _count(count)
{
    _arr.resize(count);
}

long long res::GetCount() const
{
    return _count;
}

event res::GetEvent(const int index) const
{
    if (index < _count)
        return _arr[index];
    return event();
}

void res::AddEvent(const event e)
{
    _arr.push_back(e);
    ++_count;
}

void res::SetCount(const long long count)
{
    _count = count;
    _arr.resize(_count);
}

void res::SetEvent(const int index, const event e)
{
    if (index >= _count)
        return;
    _arr[index] = e;
}

void res::PrintData(const equipment e, bool print_empty, bool print_full_data, int min_count_l, int min_count_d, int min_count_p) const
{
    long long count_events = 0;
    int ind_k, ind_l, ind_d, ind_p;
    std::cout << "res data" << std::endl;
    for (long long i = 0; i < GetCount(); ++i)
    {
        if (print_empty ||
                (GetEvent(i).GetFlag() &&
                 (min_count_l <= GetEvent(i).GetCountOfLayers()) &&
                 (min_count_d <= GetEvent(i).GetCountOfDetectors()) &&
                 (min_count_p <= GetEvent(i).GetCountOfPixels())
                 ) )
        {
            if ((int)GetEvent(i).GetArr().size() > 1)
                ++count_events;
            if (print_full_data)
            {
                ind_k = GetEvent(i).GetKitIndex();
                std::cout << "\t" << "event " << i <<
                             std::setw(12) << std::setfill(' ') <<
                             ":\t\t\t\tphi\t\ttet\t\tx\t\ty\t\tz\t\t" <<
                             GetEvent(i).GetFlag() << std::endl;
                std::cout << "\t" << "muon" <<
                             ":\t\t\t\t\t" <<
                             std::setw(12) << std::setfill(' ') <<
                             GetEvent(i).GetMuon().GetPhi() << "\t" <<
                             std::setw(12) << std::setfill(' ') <<
                             GetEvent(i).GetMuon().GetTet() << "\t" <<
                             std::setw(12) << std::setfill(' ') <<
                             GetEvent(i).GetMuon().GetCoor().GetX() << "\t" <<
                             std::setw(12) << std::setfill(' ') <<
                             GetEvent(i).GetMuon().GetCoor().GetY() << "\t" <<
                             std::setw(12) << std::setfill(' ') <<
                             GetEvent(i).GetMuon().GetCoor().GetZ() << "\t" <<
                             std::endl;
                std::cout << "\t" << "kit " << ind_k << ":\t\t\t\t\t\t\t\t\t" <<
                             std::setw(12) << std::setfill(' ') <<
                             e.GetKit(ind_k).GetCoor().GetX() << "\t" <<
                             std::setw(12) << std::setfill(' ') <<
                             e.GetKit(ind_k).GetCoor().GetY() << "\t" <<
                             std::setw(12) << std::setfill(' ') <<
                             e.GetKit(ind_k).GetCoor().GetZ() << "\t" <<
                             std::endl;
                for (int j = 0; j < (int)GetEvent(i).GetArr().size(); ++j)
                {
                    ind_l = GetEvent(i).GetArr()[j].first;
                    std::cout << "\t\t" << "layer " <<
                                 GetEvent(i).GetArr()[j].first << ":\t\t\t\t\t\t\t" <<
                                 std::setw(12) << std::setfill(' ') <<
                                 e.GetKit(ind_k).GetLayer(ind_l).GetCoor().GetX() << "\t" <<
                                 std::setw(12) << std::setfill(' ') <<
                                 e.GetKit(ind_k).GetLayer(ind_l).GetCoor().GetY() << "\t" <<
                                 std::setw(12) << std::setfill(' ') <<
                                 e.GetKit(ind_k).GetLayer(ind_l).GetCoor().GetZ() << "\t" <<
                                 std::endl;
                    for (int k = 0; k < (int)GetEvent(i).GetArr()[j].second.size(); ++k)
                    {
                        ind_d = GetEvent(i).GetArr()[j].second[k].first;
                        std::cout << "\t\t\t" << "detector " <<
                                     GetEvent(i).GetArr()[j].second[k].first << ":\t\t\t\t\t\t" <<
                                     std::setw(12) << std::setfill(' ') <<
                                     e.GetKit(ind_k).GetLayer(ind_l).GetDetector(ind_d).GetCoor().GetX() << "\t" <<
                                     std::setw(12) << std::setfill(' ') <<
                                     e.GetKit(ind_k).GetLayer(ind_l).GetDetector(ind_d).GetCoor().GetY() << "\t" <<
                                     std::setw(12) << std::setfill(' ') <<
                                     e.GetKit(ind_k).GetLayer(ind_l).GetDetector(ind_d).GetCoor().GetZ() << "\t" <<
                                     std::endl;
                        for (int l = 0; l < (int)GetEvent(i).GetArr()[j].second[k].second.size(); ++l)
                        {
                            ind_p = GetEvent(i).GetArr()[j].second[k].second[l];
                            std::cout << "\t\t\t\t" << "pixel " <<
                                         GetEvent(i).GetArr()[j].second[k].second[l] << ":\t\t\t\t\t" <<
                                         std::setw(12) << std::setfill(' ') <<
                                         e.GetKit(ind_k).GetLayer(ind_l).GetDetector(ind_d).GetPixel(ind_p).GetCoor().GetX() << "\t" <<
                                         std::setw(12) << std::setfill(' ') <<
                                         e.GetKit(ind_k).GetLayer(ind_l).GetDetector(ind_d).GetPixel(ind_p).GetCoor().GetY() << "\t" <<
                                         std::setw(12) << std::setfill(' ') <<
                                         e.GetKit(ind_k).GetLayer(ind_l).GetDetector(ind_d).GetPixel(ind_p).GetCoor().GetZ() << "\t" <<
                                         std::endl;
                        }
                    }
                }
                std::cout << "---------------------------------------------------------------------------------------------------------------------------------" << std::endl;
            }
        }
    }
    std::cout << "Count of necessary events: " << count_events << std::endl;
}



