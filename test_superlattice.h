#include "SuperLattice.h"




void test_superlattice(const Parameter& para);
void test_superlattice(const Parameter& para)
{
        SubLattice Rsub;

        Rsub.read(2);

        SiteWave wave1;

        wave1.read(1);

        SiteWave wave2(wave1);

        wave2.show();
        SuperLattice super;
        super.calcuWave(wave2, wave1, Rsub.SysCreation(), Annihilation, para);
        wave2.show();
}