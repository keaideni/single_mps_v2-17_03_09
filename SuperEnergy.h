#ifndef SUPER_ENERGY_H
#define SUPER_ENERGY_H


#include "SuperLattice.h"
#include <Eigen/Core>
#include <SymEigsSolver.h>

using namespace Spectra;

class SuperEnergy
{
private:
        double _energy;
        MatrixXd _ground;
public:
        const double& energy()const{return _energy;};
        const MatrixXd& ground()const{return _ground;};

        SuperEnergy(const SubLattice& Llattice, const SubLattice& Rlattice, const Parameter& para, 
                const SiteWave& IniWave)
        {
                SuperLattice super(Llattice, Rlattice, para, IniWave);//cout<<"haha"<<endl;IniWave.show();
                //Llattice.show(); Rlattice.show();
                SymEigsSolver<double, SMALLEST_ALGE, SuperLattice> eigs(&super, 2, 6);
                vector<double> f;
                IniWave.Wave2f(f);
                double *pt=new double[super.rows()];//cout<<super.rows()<<endl;
                for(int i=0; i<super.rows(); ++i){pt[i]=f.at(i);}
                eigs.init(pt);
                eigs.compute();//cout<<eigs.eigenvectors()<<endl;
                //cout<<eigs.num_iterations()<<endl;
                if(eigs.info()==SUCCESSFUL)
                {
                        _energy=eigs.eigenvalues()(0);
                        _ground=eigs.eigenvectors().col(0);
                }


        };


        SuperEnergy(const SubLattice& lattice, const Parameter& para, const SiteWave& IniWave, edge ee)
        {
                SuperLattice super(lattice, para, ee, IniWave);
                vector<double> f;
                IniWave.Wave2f(f);//cout<<f.size()<<"haha"<<super.rows()<<endl;
                double *pt=new double[super.rows()];//cout<<super.rows()<<endl;
                for(int i=0; i<super.rows(); ++i)pt[i]=f.at(i);

                SymEigsSolver<double, SMALLEST_ALGE, SuperLattice> eigs(&super, 2, 6);

                eigs.init(pt);
                eigs.compute();
                if(eigs.info()==SUCCESSFUL)
                {
                        _energy=eigs.eigenvalues()(0);
                        _ground=eigs.eigenvectors().col(0);
                }


        };
};

#endif // SUPER_ENERGY