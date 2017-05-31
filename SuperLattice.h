#ifndef SUPERLATTICE
#define SUPERLATTICE

#include "SubLattice.h"


class SuperLattice
{



        
public:
        void calcuWave(SiteWave& wave2, const Sub& LSub, const SiteWave& wave, const Sub& RSub, 
                const OP_modes& type, const Parameter& para);

        void calcuWave(SiteWave& wave2, const SiteWave& wave, const Sub& RSub, 
                const OP_modes& type, const Parameter& para);
};






#endif