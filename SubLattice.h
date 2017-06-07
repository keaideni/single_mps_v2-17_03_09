#ifndef SUB_LATTICE_H
#define SUB_LATTICE_H

#include "Sub.h"
#include "OP.h"



class SubLattice
{
        private:
                Sub _System;
                Sub _SysEye;
                Sub _SysCreation;
                Sub _SysAnnihilation;

                Part _part;

                int _Site;
        public:
                const Sub& System()const{return _System;};
                const Sub& SysEye()const{return _SysEye;};
                const Sub& SysCreation()const{return _SysCreation;};
                const Sub& SysAnnihilation()const{return _SysAnnihilation;};
                const int& Site(){return _Site;};

                
                SubLattice(){};
                ~SubLattice(){};
                SubLattice(const SubLattice& lattice):
                _System(lattice._System),
                _SysEye(lattice._SysEye),
                _SysCreation(lattice._SysCreation),
                _SysAnnihilation(lattice._SysAnnihilation),
                _Site(lattice._Site)
                {_part=lattice._part;};


                SubLattice(const Parameter& para, const SiteWave& wave, const Part& part):
                _System(para, Onsite, wave, part),
                _SysEye(para, Eye, wave, part),
                _SysCreation(para, Creation, wave, part),
                _SysAnnihilation(para, Annihilation, wave, part),
                _Site(wave.site())
                {_part=part;};

                SubLattice(const Parameter& para, const SiteWave& wave, const SubLattice& lattice, 
                        const int& site):
                _System(para, lattice._System, Eye, wave, lattice._part),
                _SysEye(para, lattice._SysEye, Eye, wave, lattice._part),
                _SysCreation(para, lattice._SysEye, Creation, wave, lattice._part),
                _SysAnnihilation(para, lattice._SysEye, Annihilation, wave, lattice._part),
                _Site(site)
                {
                        _part=lattice._part;
                        Sub temp1(para, lattice._SysCreation, Annihilation, wave, lattice._part);
                        temp1.time(para.t());
                        _System.add(temp1);

                        Sub temp2(para, lattice._SysAnnihilation, Creation, wave, lattice._part);
                        temp2.time(para.t());
                        _System.add(temp2);
                }


                const SubLattice& operator=(const SubLattice& lattice)
                {
                        _Site=lattice._Site;
                        _part=lattice._part;
                        _System=lattice._System;
                        _SysEye=lattice._SysEye;
                        _SysCreation=lattice._SysCreation;
                        _SysAnnihilation=lattice._SysAnnihilation;
                }


                void show()const;

                void save()const;
                void read(const int& site);




};













#endif // SUB_LATTICE_H
