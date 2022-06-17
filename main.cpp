#include "!_All_include.h"
#include "equipment.h"
#include "event.h"
#include "surface.h"

void createSurfaces(const equipment e, res& r, int count, double len, double delta_phi, double delta_cos_tet)
{
    point p;
    surface s;
    p.SetX(0);
    p.SetY(0);
    p.SetZ(0);
    s.SetCoor(p);
    s.SetCount(count);
    s.SetLen(len);
    std::cout << std::setw(12) << std::setfill(' ') << delta_phi << "\t" << delta_cos_tet << std::endl;
    std::cout << std::setw(12) << std::setfill(' ') << "phi" << "\t" << "cos_tet" << std::endl;
    for (double phi = 0; phi <= (2 * PI) - delta_phi; phi += delta_phi) //phi in rad
    {
        for (double cos_tet = 1; cos_tet >= 0; cos_tet -= delta_cos_tet) //tet in rad
        {
            if ((cos_tet == 1) && (phi != 0))
                continue;
            std::cout << std::setw(12) << std::setfill(' ') << phi << "\t" << cos_tet << std::endl;
            s.SetPhi(phi);
            s.SetTet(acos(cos_tet));
            s.CreateMuons(count);
            s.RunMuons(r, e);
        }
    }

}

void angleStatistics(std::string outputfile, const res r, double delta_phi, double delta_cos_tet, int min_count_l = 0, int min_count_d = 0, int min_count_p = 0)
{
    std::ofstream fout;
    if (outputfile != "")
        fout.open(outputfile.c_str());
    int count_phi = 2 * PI / delta_phi;
    int count_cos_tet = 1.0 / delta_cos_tet + 1;
//    std::cout << "test " << count_phi << " " << count_cos_tet << std::endl;
    int** arr = new int*[count_phi];
    for(int i = 0; i < count_phi; ++i)
    {
        arr[i] = new int[count_cos_tet];
        for(int j = 0; j < count_cos_tet; ++j)
            arr[i][j] = 0;
    }
    muon draft;
    for(long long i = 0; i < r.GetCount(); ++i)
    {
        if (r.GetEvent(i).GetFlag() &&
                (min_count_l <= r.GetEvent(i).GetCountOfLayers()) &&
                (min_count_d <= r.GetEvent(i).GetCountOfDetectors()) &&
                (min_count_p <= r.GetEvent(i).GetCountOfPixels())
                )
        {
            draft = r.GetEvent(i).GetMuon();
//            std::cout << draft.GetPhi() << "\t" << delta_phi << "\t" << draft.GetPhi() / delta_phi << std::endl << draft.GetTet() << "\t" << cos(draft.GetTet()) << "\t" << delta_cos_tet << "\t" << cos(draft.GetTet()) / delta_cos_tet << std::endl << arr[(int)(draft.GetPhi() / delta_phi)][(int)(cos(draft.GetTet()) / delta_cos_tet)] << std::endl;
            ++(arr[(int)(draft.GetPhi() / delta_phi)][(int)(cos(draft.GetTet()) / delta_cos_tet)]);
//            std::cout << arr[(int)(draft.GetPhi() / delta_phi)][(int)(cos(draft.GetTet()) / delta_cos_tet)] << std::endl;
        }
    }
//    std::cout << "test " << count_phi << " " << count_cos_tet << std::endl;
//    std::cout << std::endl;

    if (outputfile != "")
    {
        fout << std::setw(12) << std::setfill(' ') << "phi\\tet";
        for(int j = 0; j < count_cos_tet; ++j)
            fout << std::setw(12) << std::setfill(' ') << acos(j * delta_cos_tet)<< "\t";
        fout << std::endl;
        for(int i = 0; i < count_phi; ++i)
        {
            fout << std::setw(12) << std::setfill(' ') << i * delta_phi << "\t";
            for(int j = 0; j < count_cos_tet; ++j)
                fout << std::setw(12) << std::setfill(' ') << arr[i][j] << "\t";
            fout << std::endl;
        }
    }
    else
    {
        std::cout << std::setw(12) << std::setfill(' ') << "phi\\tet";
        for(int j = 0; j < count_cos_tet; ++j)
            std::cout << std::setw(12) << std::setfill(' ') << acos(j * delta_cos_tet)<< "\t";
        std::cout << std::endl;
        for(int i = 0; i < count_phi; ++i)
        {
            std::cout << std::setw(12) << std::setfill(' ') << i * delta_phi << "\t";
            for(int j = 0; j < count_cos_tet; ++j)
                std::cout << std::setw(12) << std::setfill(' ') << arr[i][j] << "\t";
            std::cout << std::endl;
        }
    }
    fout.close();
}

void run()
{
    int count = 10000;
    double len = 2000;
    double delta_phi = (15 * PI) / 180;
    double delta_cos_tet = 0.1;
    int min_count_l = 3;
    int min_count_d = 0;
    int min_count_p = 0;
    bool print_empty = 0;
    bool print_full_data = 0;
    std::string outputfile = "testout_1.txt";
//    std::string outputfile = "";
    std::cout << "start." << std::endl;
    equipment e;
    kit k;
    res r;
    std::cout << std::endl;
    std::cout << "start read detector config" << std::endl;
    k.ReadDetector("detector_config.txt");
    std::cout << "end read detector config" << std::endl;
//    check kit set mid coor as 0 0 0
//    k.PrintData();
//    std::cout << std::endl << k.GetCoor().GetX() << "\t" << k.GetCoor().GetY() << "\t" << k.GetCoor().GetZ() << "\t" << k.GetCoorMid().GetX() << "\t" << k.GetCoorMid().GetY() << "\t" << k.GetCoorMid().GetZ() << "\t" << k.GetCoorMax().GetX() << "\t" << k.GetCoorMax().GetY() << "\t" << k.GetCoorMax().GetZ() << std::endl;
    k.SetAllCoor(-k.GetCoorMid());
//    std::cout << std::endl << k.GetCoor().GetX() << "\t" << k.GetCoor().GetY() << "\t" << k.GetCoor().GetZ() << "\t" << k.GetCoorMid().GetX() << "\t" << k.GetCoorMid().GetY() << "\t" << k.GetCoorMid().GetZ() << "\t" << k.GetCoorMax().GetX() << "\t" << k.GetCoorMax().GetY() << "\t" << k.GetCoorMax().GetZ() << std::endl;
//    k.PrintData();
    e.AddKit(k);
    std::cout << "start create surfaces" << std::endl;
    createSurfaces(e, r, count, len, delta_phi, delta_cos_tet);
    std::cout << "end create surfaces" << std::endl;
    std::cout << "press enter to continue" << std::endl;
    std::getchar();
    std::cout << std::endl;
    std::cout << "start print equipment data" << std::endl;
    e.PrintData();
    std::cout << "end print equipment data" << std::endl;
    std::cout << "press enter to continue" << std::endl;
    std::getchar();
    std::cout << "start print result data" << std::endl;
    r.PrintData(e, print_empty, print_full_data, min_count_l, min_count_d, min_count_p);
    std::cout << "Count of all events: " << r.GetCount() << std::endl;
    std::cout << "end print result data" << std::endl;
    std::cout << std::endl;
    std::cout << "press enter to continue" << std::endl;
    std::getchar();
    std::cout << "start angle statistics" << std::endl;
    angleStatistics(outputfile, r, delta_phi, delta_cos_tet, min_count_l, min_count_d, min_count_p);
    std::cout << "end." << std::endl;
}

int main()
{
    run();
    return 0;
}
