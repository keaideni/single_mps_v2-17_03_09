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
        SiteWave wave_in;
        const edge e;

        int D;
        



        
public:

        int rows(){return D;};
        int cols(){return D;};

        void perform_op(double *x_in, double *y_out)
        {
                vector<double> a;
                for(int i=0; i<D; ++i)a.push_back(x_in[i]);

                
                wave_in.f2Wave(a);//wave_in.show();
                SiteWave wave_out;
                switch(e)
                {
                        case media:
                        {
                                f1tof2a(wave_in, wave_out);wave_in.show();wave_out.show();
                                break;
                        }
                        case Ledge:
                        {
                                f1tof2b(wave_in, wave_out);
                                break;
                        }
                        case Redge:
                        {
                                f1tof2c(wave_in, wave_out);
                                break;
                        }
                }
                wave_out.Wave2f(a);//wave_out.show();
                for(int i=0; i<D; ++i)
                {
                        y_out[i]=a.at(i);
                }

        };

        SuperLattice(const SubLattice& llattice, const SubLattice&rlattice, const Parameter& para,
                const SiteWave& Iniwave):
        Llattice(llattice),
        Rlattice(rlattice),
        Para(para),
        wave_in(Iniwave),
        e(media),
        D(rlattice.SysEye().QMat().begin()->second.rows()*llattice.SysEye().QMat().begin()->second.rows())
        {

                OP a(Para, Eye);
                int dd(a.RLQ().size());
                D*=dd;
                //cout<<D<<endl;
                //cout<<"haha"<<cols()<<endl;

                //f1tof2a(wave, wave2);
        };

        SuperLattice(const SubLattice& rlattice, const Parameter& para, const edge& ee,
                const SiteWave& Iniwave):
        Llattice(rlattice),
        Rlattice(rlattice),
        Para(para),
        wave_in(Iniwave),
        e(ee)
        {
                //cout<<"haha"<<endl;
                switch(ee)
                {
                        case Ledge:
                        {
                                D=rlattice.SysEye().QMat().begin()->second.rows();
                                break;
                        }
                        case Redge:
                        {
                                D=rlattice.SysEye().QMat().begin()->second.cols();
                                break;
                        }
                        case media:
                        {
                                break;
                        }
                }


                OP a(Para, Eye);
                int dd(a.RLQ().size());//cout<<dd<<endl;
                D*=dd;//cout<<D<<endl;
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