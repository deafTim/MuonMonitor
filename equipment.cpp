#include "equipment.h"

equipment::equipment(): _count(0)
{
    _arr.clear();
}

equipment::equipment(const equipment &e): _count(e.GetCount())
{
    _arr.clear();
    for (int i = 0; i < e.GetCount(); ++i)
        _arr.push_back(e.GetKit(i));
}

equipment::equipment(const int count): _count(count)
{
    _arr.resize(count);
}

int equipment::GetCount() const
{
    return _count;
}

kit equipment::GetKit(const int index) const
{
    if (index < _count)
        return _arr[index];
    return kit();
}

void equipment::AddKit(const kit k)
{
    _arr.push_back(k);
    _arr[_count].SetIndex(_count);
    ++_count;
}

void equipment::SetCount(const int count)
{
    _count = count;
    _arr.resize(_count);
}

void equipment::SetKit(const int index, const kit k)
{
    if (index >= _count)
        return;
    _arr[index] = k;
}

void equipment::PrintData()
{
    std::cout << "equipment" << std::endl;
    for (int h = 0; h < GetCount(); ++h)
    {
        std::cout << "\t" << "kit " << h << ":\t\t\t\t\t" <<
                     std::setw(6) << std::setfill(' ') <<
                     GetKit(h).GetCoor().GetX() << "\t" <<
                     std::setw(6) << std::setfill(' ') <<
                     GetKit(h).GetCoor().GetY() << "\t" <<
                     std::setw(6) << std::setfill(' ') <<
                     GetKit(h).GetCoor().GetZ() << "\t" <<
                     std::endl;
        for(int i = 0; i < GetKit(h).GetCount(); ++i)
        {
            std::cout << "\t\t" << "layer " << i << ":\t\t\t" <<
                         std::setw(6) << std::setfill(' ') <<
                         GetKit(h).GetLayer(i).GetCoor().GetX() << "\t" <<
                         std::setw(6) << std::setfill(' ') <<
                         GetKit(h).GetLayer(i).GetCoor().GetY() << "\t" <<
                         std::setw(6) << std::setfill(' ') <<
                         GetKit(h).GetLayer(i).GetCoor().GetZ() << "\t" <<
                         std::endl;
            for(int j = 0; j < GetKit(h).GetLayer(i).GetCount(); ++j)
            {
                std::cout << "\t\t\t" << "detector " <<
                             GetKit(h).GetLayer(i).GetDetector(j).GetName() << ":\t\t" <<
                             std::setw(6) << std::setfill(' ') <<
                             GetKit(h).GetLayer(i).GetDetector(j).GetCoor().GetX() << "\t" <<
                             std::setw(6) << std::setfill(' ') <<
                             GetKit(h).GetLayer(i).GetDetector(j).GetCoor().GetY() << "\t" <<
                             std::setw(6) << std::setfill(' ') <<
                             GetKit(h).GetLayer(i).GetDetector(j).GetCoor().GetZ() << "\t" <<std::endl;
                for(int g = 0; g < GetKit(h).GetLayer(i).GetDetector(j).GetCount(); ++g)
                    std::cout << "\t\t\t\t" << "pixel " << g << ":\t" <<
                                 std::setw(6) << std::setfill(' ') <<
                                 GetKit(h).GetLayer(i).GetDetector(j).GetPixel(g).GetCoor().GetX() << "\t" <<
                                 std::setw(6) << std::setfill(' ') <<
                                 GetKit(h).GetLayer(i).GetDetector(j).GetPixel(g).GetCoor().GetY() << "\t" <<
                                 std::setw(6) << std::setfill(' ') <<
                                 GetKit(h).GetLayer(i).GetDetector(j).GetPixel(g).GetCoor().GetZ() << std::endl;
            }
            if (i < (GetKit(h).GetCount() - 1))
                std::cout << "-----------------------------------------------------------------------" << std::endl;
        }
    }
}
