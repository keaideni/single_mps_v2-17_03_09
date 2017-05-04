#include "Parameter.h"
#include "SiteWave.h"


using namespace  std;
int main()
{
        ifstream infile("./data/QNosave");
        Parameter para(infile);
        //para.show();

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