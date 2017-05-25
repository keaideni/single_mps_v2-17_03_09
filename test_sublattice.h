#include "SubLattice.h"


void test_sublattice(const Parameter& para);

void test_sublattice(const Parameter& para)
{
        OP a(para, Eye);
        //a.show();
        SiteWave haha(3, 100, a);

        SiteWave hehe(3, 99, a, haha);

        //haha.show();

        SubLattice Lside(para, haha, Right);

        Lside.show();


        SubLattice LLside(para, hehe, Right);

        LLside.show();


        //Lside.save();

        //SubLattice LLside;
        //LLside.read(100);

        //LLside.show();
}

