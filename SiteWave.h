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

enum edge
{
        leftedge, rightedge
};

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

        SiteWave(const int& D, const int& site, const OP& Eye);
        SiteWave(const int& D, const int& site, const OP& Eye, const edge& edgestate);


        void Wave2f(vector<double>& f);
        void f2Wave(const std::vector<double>& f);

        void SVD(SiteWave& LWave, const std::vector<double>& f);

        void SVD(const std::vector<double>& f, SiteWave&RWave);


        void save();
        void read(const int& site);


        void show()const
        {
                cout<<"the site is "<<_site<<endl;
                cout<<"The matrix is"<<endl;

                
                for(auto it=_cell.begin(); it!=_cell.end(); ++it)
                {
                        cout<<it->first<<"=>"<<endl;
                        cout<<it->second<<endl;
                }
        }

        
};








#endif // SITE_WAVE_H
