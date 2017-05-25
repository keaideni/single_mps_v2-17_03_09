#include "test_SiteWave.h"
#include "test_Sub.h"
#include "test_sublattice.h"

int Sub::QMax;

int main()
{
        //test_SiteWave();

        ifstream infile("./data/QNosave");
        Parameter para(infile);
        //para.show();
        Sub::QMax=para.ParticleNo();
        //test_Sub(para);
        Ini(para);
        //para.show();
        //test_sublattice(para);

}