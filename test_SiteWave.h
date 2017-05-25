#include "Parameter.h"
#include "SiteWave.h"
#include "SubLattice.h"


using namespace  std;




void test_SiteWave(const Parameter& para);
void test_SiteWave(const Parameter& para)
{
        

        OP a(para, Eye);
        //a.show();
        SiteWave haha(3, 0, a);

        haha.show();

        SiteWave hehe(1,1,a,haha);

        cout<<"=======The beautiful parting line=========="<<endl;

        hehe.show();

        /*VectorXd f(VectorXd::Random(36));

        std::vector<double> v;
        for(int i=0; i<f.rows(); )v.push_back(f(i++));

        SiteWave hehe(3, 0, a);
        cout<<"=======The beautiful parting line=========="<<endl;


        haha.SVD(v, hehe);
        hehe.show();
        cout<<"=======The beautiful parting line=========="<<endl;


        haha.save();

        SiteWave heha;
        heha.read(0);
        heha.show();*/



        MatrixXd aaa(MatrixXd::Zero(1,1));
        for(auto it=hehe.cell().begin(); it!=hehe.cell().end(); ++it)
        {
                aaa=aaa+it->second*it->second.transpose();
        }


        cout<<"=======The beautiful parting line=========="<<endl;

        cout<<aaa<<endl;
}


void Ini(const Parameter& para);
void Ini(const Parameter& para)
{
        OP a(para, Eye);

        SiteWave wave1(para.D(), para.LatticeSize(), a);
        wave1.save();

        SubLattice lattice1(para, wave1, Right);
        lattice1.save();

        for(int i=para.LatticeSize()-1; i>0; i=i-1)
        {

                SiteWave wave2(para.D(), i, a, wave1);

                SubLattice lattice2(para, wave2, lattice1, Right);
                lattice2.save();

                //cout<<wave2.site()<<endl;
                wave2.save();

                wave1=wave2;
                lattice1=lattice2;
        }
        wave1.show();
        lattice1.read(1);
        lattice1.show();
}