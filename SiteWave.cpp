#include "SiteWave.h"
#include <Eigen/SVD>
#include <sstream>
#include <fstream>

SiteWave::SiteWave(const int& D, const int& site, const OP& Eye):
_site(site)
{
        //MatrixXd tem(MatrixXd::zero(D, D));

        int Sdim(Eye.RLQ().size());

        MatrixXd tem(MatrixXd::Random(D, Sdim*D));

        BDCSVD<MatrixXd> svd(tem, ComputeFullV);

        //cout<<svd.matrixV().transpose()*svd.matrixV()<<endl;
        //cout<<"============================================"<<endl;
        //cout<<svd.matrixV()<<endl;
        //cout<<"============================================"<<endl;

        int i(0);
        for(auto it=Eye.QMat().begin(); it!=Eye.QMat().end(); ++it)
        {
                _cell.insert(pair<int, MatrixXd>(it->first, svd.matrixV().transpose().block(0, i*D, D, D)));
                ++i;
        }


}


void SiteWave::Wave2f(vector<double>& f)
{
        for(auto it=_cell.begin(); it!=_cell.end(); ++it)
        {
                int D(it->second.rows());//cout<<D<<endl;
                for(int i=0; i<D; ++i)
                {
                        for(int j=0; j<D; ++j)
                        {
                                f.push_back(it->second(i,j));
                        }
                }
        }
}


void SiteWave::f2Wave(const std::vector<double>& f)
{
        int D(_cell.begin()->second.rows());
        //_cell.clear();

        int fi(0);
        for(auto it=_cell.begin(); it!=_cell.end(); ++it)
        {
                for(int i=0; i<D; ++i)
                {
                        for(int j=0; j<D; ++j)it->second(i, j)=f.at(fi++);
                }
        }
}


void SiteWave::SVD(SiteWave& LWave, const std::vector<double>& f)
{
        int D(_cell.begin()->second.rows());

        int num(_cell.size());

        MatrixXd tem(MatrixXd::Zero(D, num*D));

        int fi(0);

        for(int i=0; i<num; ++i)
        {
                for(int j=0; j<D; ++j)
                {
                        for (int k=0; k<D; ++k)
                        {
                                tem(j, i*D+k)=f.at(fi++);
                        }
                }
        }


        BDCSVD<MatrixXd> svd(tem, ComputeFullU|ComputeFullV);


        int i(0);
        for(auto it=_cell.begin(); it!=_cell.end(); ++it)
        {
                it->second=svd.matrixV().transpose().block(0, i++*D, D, D);
                
        }

        for(auto it=LWave._cell.begin(); it!=LWave._cell.end(); ++it)
        {
                MatrixXd temp(it->second);

                MatrixXd temp1=svd.singularValues().asDiagonal();

                it->second=temp*svd.matrixU()*temp1;
        }

}




void SiteWave::SVD(const std::vector<double>& f, SiteWave& RWave)
{
        int D(_cell.begin()->second.rows());

        int num(_cell.size());

        MatrixXd tem(MatrixXd::Zero(num*D, D));

        int fi(0);

        for(int i=0; i<num; ++i)
        {
                for(int j=0; j<D; ++j)
                {
                        for (int k=0; k<D; ++k)
                        {
                                tem(i*D+j, k)=f.at(fi++);
                        }
                }
        }


        BDCSVD<MatrixXd> svd(tem, ComputeFullU|ComputeFullV);


        int i(0);
        for(auto it=_cell.begin(); it!=_cell.end(); ++it)
        {
                it->second=svd.matrixU().block(i++*D, 0, D, D);
                
        }

        for(auto it=RWave._cell.begin(); it!=RWave._cell.end(); ++it)
        {
                MatrixXd temp(it->second);

                MatrixXd temp1=svd.singularValues().asDiagonal();

                it->second=temp1*svd.matrixV().transpose()*temp;
        }

}



void SiteWave::save()
{
        string filename("./data/SiteWave/");

        stringstream sstr;

        sstr<<_site;

        string tem;sstr>>tem;

        filename+=tem;

        ofstream outfile(filename);

        outfile<<_site<<endl;

        outfile.precision(13);

        for(auto it=_cell.begin(); it!=_cell.end(); ++it)
        {
                outfile<<it->first<<endl;

                int D(it->second.cols());

                outfile<<D<<endl;

                for(int i=0; i<D; ++i)
                {
                        for(int j=0; j<D; ++j)
                        {
                                outfile<<it->second(i,j)<<"\t";
                        }
                        outfile<<endl;
                }
        }



}
