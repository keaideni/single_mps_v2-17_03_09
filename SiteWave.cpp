#include "SiteWave.h"
#include <Eigen/SVD>
#include <sstream>
#include <fstream>

SiteWave::SiteWave(const int& D, const int& site, const OP& eye):
_site(site)
{
        //MatrixXd tem(MatrixXd::zero(D, D));

        int Sdim(eye.RLQ().size());

        int DL=D<Sdim?D:Sdim;

        MatrixXd tem(MatrixXd::Random(DL, Sdim));

        BDCSVD<MatrixXd> svd(tem, ComputeFullV);

        //cout<<svd.matrixV().transpose()*svd.matrixV()<<endl;
        //cout<<"============================================"<<endl;
        //cout<<svd.matrixV()<<endl;
        //cout<<"============================================"<<endl;

        int i(0);
        for(auto it=eye.QMat().begin(); it!=eye.QMat().end(); ++it)
        {
                _cell.insert(pair<int, MatrixXd>(it->first, svd.matrixV().transpose().block(0, i, DL, 1)));
                ++i;
        }


}




SiteWave::SiteWave(const int& D, const int& site, const OP& eye, const SiteWave& Rsite):
_site(site)
{
        int Sdim(eye.RLQ().size());
        int DR(Rsite._cell.begin()->second.rows());
        int DL(D<DR*Sdim?D:DR*Sdim);

        if(site==1)DL=1;

        MatrixXd tem(MatrixXd::Random(DL, Sdim*DR));

        BDCSVD<MatrixXd> svd(tem, ComputeFullV);

        //cout<<svd.matrixV().transpose()*svd.matrixV()<<endl;
        //cout<<"============================================"<<endl;
        //cout<<svd.matrixV()<<endl;
        //cout<<"============================================"<<endl;

        int i(0);
        for(auto it=eye.QMat().begin(); it!=eye.QMat().end(); ++it)
        {
                _cell.insert(pair<int, MatrixXd>(it->first, svd.matrixV().transpose().block(0, i*DR, DL, DR)));
                ++i;
        }
}








void SiteWave::Wave2f(vector<double>& f)const
{
        f.clear();
        for(auto it=_cell.begin(); it!=_cell.end(); ++it)
        {
                //int D(it->second.rows());//cout<<D<<endl;
                for(int i=0; i<it->second.rows(); ++i)
                {
                        for(int j=0; j<it->second.cols(); ++j)
                        {
                                f.push_back(it->second(i,j));
                        }
                }
        }
}


void SiteWave::f2Wave(const std::vector<double>& f)
{
        //int D(_cell.begin()->second.rows());
        //_cell.clear();

        int fi(0);
        for(auto it=_cell.begin(); it!=_cell.end(); ++it)
        {
                for(int i=0; i<it->second.rows(); ++i)
                {
                        for(int j=0; j<it->second.cols(); ++j)it->second(i, j)=f.at(fi++);
                }
        }
}


void SiteWave::SVD(SiteWave& LWave, const std::vector<double>& f)
{
        int DL(_cell.begin()->second.rows());
        int DR(_cell.begin()->second.cols());

        int num(_cell.size());

        MatrixXd tem(MatrixXd::Zero(DL, num*DR));

        int fi(0);

        for(int i=0; i<num; ++i)
        {
                for(int j=0; j<DL; ++j)
                {
                        for (int k=0; k<DR; ++k)
                        {
                                tem(j, i*DR+k)=f.at(fi++);
                        }
                }
        }


        BDCSVD<MatrixXd> svd(tem, ComputeFullU|ComputeFullV);


        int i(0);
        for(auto it=_cell.begin(); it!=_cell.end(); ++it)
        {
                it->second=svd.matrixV().transpose().block(0, i++*DR, DL<num*DR?DL:num*DR, DR);
                
        }

        MatrixXd temp1=svd.singularValues().asDiagonal();
        if(DL>num*DR)
        {
                MatrixXd temp2=MatrixXd::Zero(DL, temp1.cols());
                for(int i=0; i<num*DR; ++i)
                {
                        temp2.row(i)=temp1.row(i);
                }
                temp1=temp2;
        }



        for(auto it=LWave._cell.begin(); it!=LWave._cell.end(); ++it)
        {
                MatrixXd temp(it->second);//cout<<it->second.rows()<<"x"<<it->second.cols()<<endl;
                //cout<<svd.matrixU().rows()<<"x"<<svd.matrixU().cols()<<endl;

                

                it->second=temp*svd.matrixU()*temp1;
        }

}




void SiteWave::SVD(const std::vector<double>& f, SiteWave& RWave)
{
        int DL(_cell.begin()->second.rows());
        int DR(_cell.begin()->second.cols());


        int num(_cell.size());

        MatrixXd tem(MatrixXd::Zero(num*DL, DR));

        int fi(0);

        for(int i=0; i<num; ++i)
        {
                for(int j=0; j<DL; ++j)
                {
                        for (int k=0; k<DR; ++k)
                        {
                                tem(i*DL+j, k)=f.at(fi++);
                        }
                }
        }


        BDCSVD<MatrixXd> svd(tem, ComputeFullU|ComputeFullV);


        int i(0);
        for(auto it=_cell.begin(); it!=_cell.end(); ++it)
        {
                it->second=svd.matrixU().block(i++*DL, 0, DL, DR<num*DL?DR:num*DL);
                
        }

        MatrixXd temp1=svd.singularValues().asDiagonal();
        if(DR>num*DL)
        {
                MatrixXd temp2=MatrixXd::Zero(temp1.cols(), DR);
                for(int i=0; i<num*DL; ++i)
                        temp2.col(i)=temp1.col(i);

                temp1=temp2;
        }

        for(auto it=RWave._cell.begin(); it!=RWave._cell.end(); ++it)
        {
                MatrixXd temp(it->second);



                it->second=temp1*svd.matrixV().transpose()*temp;
        }

}






const SiteWave& SiteWave::add(const SiteWave& wave)
{
        for(auto it=wave._cell.begin(); it!=wave._cell.end(); ++it)
        {
                auto itt=_cell.find(it->first);
                if(itt!=_cell.end())
                {
                        itt->second+=it->second;
                }else
                {
                        _cell.insert(pair<int, MatrixXd>(it->first, it->second));
                }
        }
}




const SiteWave& SiteWave::operator+=(const SiteWave& wave)
{
        for(auto it=wave._cell.begin(); it!=wave._cell.end(); ++it)
        {
                auto itt=_cell.find(it->first);
                if(itt!=_cell.end())
                {
                        itt->second+=it->second;
                }else
                {
                        _cell.insert(pair<int, MatrixXd>(it->first, it->second));
                }
        }
}


const SiteWave& SiteWave::time(const double& t)
{
        for(auto it=_cell.begin(); it!=_cell.end(); ++it)
        {
                it->second*=t;
        }
}

const SiteWave& SiteWave::operator*=(const double& t)
{
        for(auto it=_cell.begin(); it!=_cell.end(); ++it)
        {
                it->second*=t;
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

        outfile<<_cell.size()<<endl;

        outfile.precision(13);

        for(auto it=_cell.begin(); it!=_cell.end(); ++it)
        {
                outfile<<it->first<<endl;

                int rD(it->second.rows());
                int cD(it->second.cols());
                outfile<<rD<<endl;
                outfile<<cD<<endl;

                for(int i=0; i<rD; ++i)
                {
                        for(int j=0; j<cD; ++j)
                        {
                                outfile<<it->second(i,j)<<"\t";
                        }
                        outfile<<endl;
                }
        }

        outfile.close();



}



void SiteWave::read(const int& site)
{

        _cell.clear();

        _site=site;

        string filename("./data/SiteWave/");

        stringstream sstr;

        sstr<<_site;

        string tem;sstr>>tem;

        filename+=tem;

        ifstream infile(filename);

        int numquan;

        infile>>numquan;

        int size;

        infile>>size;

        int rD, cD;

        for(int i=0; i<size; ++i)
        {
                infile>>numquan;
                infile>>rD;
                infile>>cD;

                MatrixXd tem(rD, cD);

                for(int j=0; j<rD; ++j)
                {
                        for(int k=0; k<cD; ++k)
                        {
                                infile>>tem(j,k);
                        }
                }

                _cell.insert(pair<int, MatrixXd>(numquan, tem));
        }

        infile.close();


}