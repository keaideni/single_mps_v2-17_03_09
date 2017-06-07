#include "SuperLattice.h"
#include "SuperEnergy.h"




void test_superlattice(const Parameter& para);
void test_superlattice(const Parameter& para)
{
        SubLattice Rlattice;

        Rlattice.read(2);

        SiteWave wave1;

        wave1.read(1);

        SiteWave wave2(wave1);

        wave2.show();
        SuperEnergy super(Rlattice, para, wave2, Ledge);
        cout<<super.energy()<<endl<<"haha"<<endl;;
        //cout<<super.ground()<<endl;
}