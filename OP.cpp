#include "OP.h"


//struct Eigstruct
//{
        //int q;
        //double lamda;
        //VectorXd state;
//};

//std::string itos(int i);
//std::string itos(int i)
//{
        //std::stringstream s;
        //s << i;
        //return s.str();
//}

//bool comp(const Eigstruct& a, const Eigstruct& b);
//bool comp(const Eigstruct& a, const Eigstruct& b)
//{
        //return (a.lamda > b.lamda);
//}

OP::OP(){}

OP::~OP()
{
        //std::cout<<"the "<<++Class_Num<<"th class destruction!"<<std::endl;
}

OP::OP(const Spin& type)
{



        

        


        switch (type)
        {

                case SpinZ:
                {
                      _RLQ.insert(std::pair<int, int>(0, 0));
                      _RLQ.insert(std::pair<int, int>(1, 1));

                      

                      _QMat.insert(std::pair<int, double>(0, -1));


                      
                      _QMat.insert(std::pair<int, double>(1, 1));


                      break;
                }
                case SpinCreation:
                {
                      _RLQ.insert(std::pair<int, int>(0, 1));

                      

                      _QMat.insert(std::pair<int, double>(0, 1));

                      break;
                }
                case SpinAnnihilation:
                {
                      _RLQ.insert(std::pair<int, int>(1, 0));

                      

                      _QMat.insert(std::pair<int, double>(1, 1));


                      break;
                }
                case SpinEye:
                {
                      _RLQ.insert(std::pair<int, int>(0, 0));
                      _RLQ.insert(std::pair<int, int>(1, 1));

                      

                      _QMat.insert(std::pair<int, double>(0, 1));
                      _QMat.insert(std::pair<int, double>(1, 1));
                      break;
                }
        }

}


OP::OP(const Parameter& para, const OP_modes& type)
{
        int min(para.SiteNo()-para.DeltaQL())
                ,max(para.SiteNo()+para.DeltaQR());

        //for(int i=min; i<=max; ++i)_QDim.insert(std::pair<int, int>(i,1));

        switch(type)
        {
                case Eye:
                {
                        for(int i=min; i<=max; ++i)
                        {
                                _RLQ.insert(std::pair<int, int>(i, i));



                                _QMat.insert(std::pair<int, double>(i, 1));
                        }

                        break;
                }
                case Creation:
                {
                        for(int i=min; i<max; ++i)
                        {
                                _RLQ.insert(std::pair<int, int>(i, i+1));
                                

                                _QMat.insert(std::pair<int, double>(i, sqrt(i+1)));

                        }
                        break;
                }
                case Annihilation:
                {
                        for(int i=min+1; i<=max; ++i)
                        {
                                _RLQ.insert(std::pair<int, int>(i, i-1));
                               

                                _QMat.insert(std::pair<int, double>(i, sqrt(i)));
                        }
                        break;
                }
        }
        
}

OP::OP(const OP& a):
_RLQ(a._RLQ),
_QMat(a._QMat)
{

}



void OP::clear()
{
        //_QDim.clear();
        _QMat.clear();
        _RLQ.clear();
}




void OP::show()const
{
        /*std::cout << "the QDim: " << std::endl;
        for (auto it = _QDim.begin(); it != _QDim.end(); it++)
        {
                std::cout << it->first << " => " << it->second << std::endl;
        }*/
        //std::cout<< "the site: " << std::endl;
        //std::cout<<_site<<std::endl;
        std::cout << "the RLQ: " << std::endl;
        for (auto it = _RLQ.begin(); it != _RLQ.end(); it++)
        {
                std::cout << it->first << " => " << it->second << std::endl;
        }
        std::cout << "the QMat: " << std::endl;
        for (auto it = _QMat.begin(); it != _QMat.end(); it++)
        {
                std::cout << it->first << " => " << it->second<<std::endl;//.rows()<<"x"<<it->second.cols() << std::endl;
        }
}