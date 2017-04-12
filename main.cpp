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

        VectorXd f(VectorXd::Random(36));

        std::vector<double> v;
        for(int i=0; i<f.rows(); )v.push_back(f(i++));

        SiteWave hehe(3, 0, a);
        cout<<"=======The beautiful parting line=========="<<endl;
        hehe.show();

        haha.SVD(v, hehe);

        cout<<"=======The beautiful parting line=========="<<endl;
        haha.show();

        cout<<"=======The beautiful parting line=========="<<endl;
        hehe.show();

        hehe.save();


}