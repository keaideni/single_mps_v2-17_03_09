#ifndef ITERATOR_H
#define ITERATOR_H

#include "SuperEnergy.h"



void calcu(const SuperEnergy& super, SiteWave& wave1, SiteWave& wave2, int& dir, 
        int& iterL, int& iterR, int& iterM, const Parameter& para);

void Iterator(const Parameter& para);
void Iterator(const Parameter& para)
{
        SubLattice Rlattice, Llattice;

        int iterL(0), iterR(2), iterM(1);//to label the left lattice, right lattice and media point.

        int dir(1);//1 for right direction and -1 for left direction.

        SiteWave wave1, wave2;

        for(int i=0; i<para.SweepNo(); ++i)
        {

                while(true)
                {

                        

                        wave1.read(iterM);

                        if(iterL==0)
                        {
                                Rlattice.read(iterR);
                                SuperEnergy super(Rlattice, para, wave1, Ledge);
                                calcu(super, wave1, wave2, dir, iterL, iterR, iterM, para);
                                cout<<super.energy()<<endl;
                                SubLattice lattice(para, wave1, Left);lattice.save();
                        }else if(iterR==para.LatticeSize()+1)
                        {
                                Llattice.read(iterL);
                                SuperEnergy super(Llattice, para, wave1, Redge);
                                calcu(super, wave1, wave2, dir, iterL, iterR, iterM, para);
                                cout<<super.energy()<<endl;
                                SubLattice lattice(para, wave1, Right);lattice.save();

                        }else
                        {
                                Llattice.read(iterL);//wave1.show();
                                Rlattice.read(iterR);//Llattice.SysEye().show();Rlattice.SysEye().show();
                                SuperEnergy super(Llattice, Rlattice, para, wave1);
                                //cout<<super.ground().rows()<<endl;
                                calcu(super, wave1, wave2, dir, iterL, iterR, iterM, para);
                                cout<<super.energy()<<endl;
                                if(dir==1)
                                {
                                        SubLattice lattice(para, wave1, Llattice, iterL);
                                        lattice.save();
                                }else
                                {
                                        SubLattice lattice(para, wave1, Rlattice, iterR);
                                        lattice.save();
                                }

                        }


                        wave1.save(); wave2.save();//wave1.show();//wave2.show();

                        if(iterL==0|iterR==para.LatticeSize()+1)break;

                }

                dir=-1*dir;
        }

        
}



void calcu(const SuperEnergy& super, SiteWave& wave1, SiteWave& wave2, int& dir,
        int& iterL, int& iterR, int& iterM, const Parameter& para)
{
        vector<double> f;
        for(int i=0; i<super.ground().rows(); ++i)f.push_back(super.ground()(i));
        //cout<<f.size()<<endl;

                        
        switch(dir)
        {
                case 1:
                {
                        wave2.read(iterR);

                        wave1.SVD(f, wave2);

                                        
                        iterL+=1; iterR+=1; iterM+=1;

                        break;

                }
                case -1:
                {
                        wave2.read(iterL);

                        wave1.SVD(wave2, f);

                        iterL-=1; iterR-=1; iterM-=1;

                        break;
                        }
                }
                        

                
}











#endif // ITERATOR_H





