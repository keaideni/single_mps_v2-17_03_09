#ifndef SUPERLATTICE
#define SUPERLATTICE

#include "SubLattice.h"

enum edge
{
        Ledge, Redge, media
};

class SuperLattice
{
private:

        const SubLattice& Llattice;
        const SubLattice& Rlattice;
        const Parameter& Para;
        const edge e;
        



        
public:

        SuperLattice(const SubLattice& llattice, const SubLattice&rlattice, const Parameter& para):
        Llattice(llattice),
        Rlattice(rlattice),
        Para(para),
        e(media)
        {
                //f1tof2a(wave, wave2);
        };

        SuperLattice(const SubLattice& rlattice, const Parameter& para, const edge& ee):
        Llattice(rlattice),
        Rlattice(rlattice),
        Para(para),
        e(ee)
        {
                //f1tof2b(wave, wave2);
        };





        void calcuWave(SiteWave& wave2, const Sub& LSub, const SiteWave& wave, const Sub& RSub, 
                const OP_modes& type, const Parameter& para);

        void calcuWave(SiteWave& wave2, const SiteWave& wave, const Sub& RSub, 
                const OP_modes& type, const Parameter& para);

        void calcuWave(SiteWave& wave2, const Sub& LSub, const SiteWave& wave, 
                const OP_modes& type, const Parameter& para);

        void f1tof2a(const SiteWave& wave, SiteWave& wave2);//for the site on the media.
        void f1tof2b(const SiteWave& wave, SiteWave& wave2);//for the site on the left.
        void f1tof2c(const SiteWave& wave, SiteWave& wave2);//for the site on the right.
};






#endif