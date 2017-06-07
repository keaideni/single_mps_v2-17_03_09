#ifndef SITE_WAVE_H
#define SITE_WAVE_H

#include <unordered_map>
#include <map>
#include <Eigen/Eigenvalues>
#include <Eigen/Dense>
#include <vector>
#include <Eigen/SVD>
#include "OP.h"
#include "Parameter.h"

using namespace Eigen;
using namespace std;



class SiteWave
{
private:
        map<int, MatrixXd> _cell;//the integer is for the quantum number while matrix is for MPS.
        int _site;
public:
        SiteWave(){};
        ~SiteWave(){};

        const map<int, MatrixXd>& cell() const{return _cell;};
        const int& site() const{return _site;};

        SiteWave(const int& D, const int& site, const OP& Eye);//right canonical initialization. 
        //For the right edge point.
        SiteWave(const int& D, const int& site, const OP& Eye, const SiteWave& Rsite);
        //right canonical initialization.


        const SiteWave& operator=(const SiteWave&wave)
        {
            _cell.clear();
            _site=wave._site;
            _cell=wave._cell;
        }



        void Wave2f(vector<double>& f)const;
        void f2Wave(const std::vector<double>& f);

        void SVD(SiteWave& LWave, const std::vector<double>& f);

        void SVD(const std::vector<double>& f, SiteWave&RWave);


        const SiteWave& add(const SiteWave& wave);
        const SiteWave& operator+=(const SiteWave& wave);
        const SiteWave& time(const double& t);
        const SiteWave& operator*=(const double& t);



        void save();
        void read(const int& site);



        void show()const
        {
                cout<<"=====the beautiful beginning line of SiteWave======="<<endl;
                cout<<"the site is "<<_site<<endl;
                cout<<"The matrix is"<<endl;

                
                for(auto it=_cell.begin(); it!=_cell.end(); ++it)
                {
                        cout<<it->first<<"=>"<<it->second.rows()<<"X"<<it->second.cols()<<endl;
                }

                cout<<"===========the beautiful ending line=================="<<endl;
        }

        void clear(){_cell.clear();};

        friend class SuperLattice;

        
};








#endif // SITE_WAVE_H
