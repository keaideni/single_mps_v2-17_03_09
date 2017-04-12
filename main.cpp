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

        //haha.show();

        VectorXd f(VectorXd::Random(36));

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
        heha.show();
        MatrixXd aaa(MatrixXd::Zero(3,3));
        for(auto it=heha.cell().begin(); it!=heha.cell().end(); ++it)
        {
                aaa=aaa+it->second.transpose()*it->second;
        }

        cout<<aaa<<endl;

}