#include "Sub.h"

Sub::Sub(const OP& a, const SiteWave& wave, const Part& part):
_RLQ(a.RLQ())
{
        switch(part)
        {
                case Left:
        
                for(auto it=a.RLQ().begin(); it!=a.RLQ().end(); ++it)
                {
                        MatrixXd temp(wave.cell().at(it->second).adjoint()*wave.cell().at(it->first));
                        _QMat.insert(pair<int, MatrixXd>(it->first, temp));
                }
                break;

                case Right:
                for(auto it=a.RLQ().begin(); it!=a.RLQ().end(); ++it)
                {
                        MatrixXd temp(wave.cell().at(it->first)*wave.cell().at(it->second).adjoint());
                        _QMat.insert(pair<int, MatrixXd>(it->first, temp));
                }
                break;

        }
}



Sub::Sub(const Parameter& para, const OP_modes& type, const SiteWave& wave, const Part& part)
{
        OP a(para, type);
        _RLQ=a.RLQ();


        switch(part)
        {
                case Left:
        
                for(auto it=a.RLQ().begin(); it!=a.RLQ().end(); ++it)
                {
                        MatrixXd temp(wave.cell().at(it->second).adjoint()*wave.cell().at(it->first));
                        _QMat.insert(pair<int, MatrixXd>(it->first, temp));
                }
                break;

                case Right:
                for(auto it=a.RLQ().begin(); it!=a.RLQ().end(); ++it)
                {
                        MatrixXd temp(wave.cell().at(it->first)*wave.cell().at(it->second).adjoint());
                        _QMat.insert(pair<int, MatrixXd>(it->first, temp));
                }
                break;

        }
}




Sub::Sub(const Sub& sub, const OP& a, const SiteWave& wave, const Part& part)
{
        for(auto it=sub._RLQ.begin(); it!=sub._RLQ.end(); ++it)
        {
                for(auto itt=a.RLQ().begin(); itt!=a.RLQ().end(); ++itt)
                {
                        int RQ(it->first+itt->first);
                        int LQ(it->second+itt->second);

                        if(RQ<=QMax&&LQ<=QMax)
                        {
                                auto ittt=_RLQ.find(RQ);
                                if(ittt==_RLQ.end())
                                        _RLQ.insert(pair<int, int>(RQ, LQ));
                                //cout<<"haha"<<endl;
                        }
                }
        }

        switch(part)
        {
                case Left:
                for(auto it=sub._QMat.begin(); it!=sub._QMat.end(); ++it)
                {
                        for(auto itt=a.RLQ().begin(); itt!=a.RLQ().end(); ++itt)
                        {
                                int RQ(it->first+itt->first);
                                auto ittt=_RLQ.find(RQ);
                                if(ittt!=_RLQ.end())
                                {

                                        MatrixXd temp(wave.cell().at(itt->second).adjoint()
                                                *it->second*wave.cell().at(itt->first)*a.QMat().at(itt->first));

                                        auto matit=_QMat.find(RQ);
                                        if(matit==_QMat.end())
                                        {
                                                _QMat.insert(pair<int, MatrixXd>(RQ, temp));
                                        }else
                                        {
                                                _QMat.at(RQ)+=temp;
                                        }


                                }
                        }
                }
                break;

                case Right:
                for(auto it=sub._QMat.begin(); it!=sub._QMat.end(); ++it)
                {
                        for(auto itt=a.RLQ().begin(); itt!=a.RLQ().end(); ++itt)
                        {
                                int RQ(it->first+itt->first);
                                auto ittt=_RLQ.find(RQ);
                                if(ittt!=_RLQ.end())
                                {

                                        MatrixXd temp(wave.cell().at(itt->first)
                                                *it->second*wave.cell().at(itt->second).adjoint()
                                                *a.QMat().at(itt->first));

                                        auto matit=_QMat.find(RQ);
                                        if(matit==_QMat.end())
                                        {
                                                _QMat.insert(pair<int, MatrixXd>(RQ, temp));
                                        }else
                                        {
                                                _QMat.at(RQ)+=temp;
                                        }


                                }
                        }
                }
                break;

        }
}


Sub::Sub(const Parameter& para, const Sub& sub, const OP_modes& type, const SiteWave& wave, const Part& part)
{
        OP a(para, type);


        for(auto it=sub._RLQ.begin(); it!=sub._RLQ.end(); ++it)
        {
                for(auto itt=a.RLQ().begin(); itt!=a.RLQ().end(); ++itt)
                {
                        int RQ(it->first+itt->first);
                        int LQ(it->second+itt->second);

                        if(RQ<=QMax&&LQ<=QMax)
                        {
                                auto ittt=_RLQ.find(RQ);
                                if(ittt==_RLQ.end())
                                        _RLQ.insert(pair<int, int>(RQ, LQ));
                                //cout<<"haha"<<endl;
                        }
                }
        }

        switch(part)
        {
                case Left:
                for(auto it=sub._QMat.begin(); it!=sub._QMat.end(); ++it)
                {
                        for(auto itt=a.RLQ().begin(); itt!=a.RLQ().end(); ++itt)
                        {
                                int RQ(it->first+itt->first);
                                auto ittt=_RLQ.find(RQ);
                                if(ittt!=_RLQ.end())
                                {

                                        MatrixXd temp(wave.cell().at(itt->second).adjoint()
                                                *it->second*wave.cell().at(itt->first)*a.QMat().at(itt->first));

                                        auto matit=_QMat.find(RQ);
                                        if(matit==_QMat.end())
                                        {
                                                _QMat.insert(pair<int, MatrixXd>(RQ, temp));
                                        }else
                                        {
                                                _QMat.at(RQ)+=temp;
                                        }


                                }
                        }
                }
                break;

                case Right:
                for(auto it=sub._QMat.begin(); it!=sub._QMat.end(); ++it)
                {
                        for(auto itt=a.RLQ().begin(); itt!=a.RLQ().end(); ++itt)
                        {
                                int RQ(it->first+itt->first);
                                auto ittt=_RLQ.find(RQ);
                                if(ittt!=_RLQ.end())
                                {

                                        MatrixXd temp(wave.cell().at(itt->first)
                                                *it->second*wave.cell().at(itt->second).adjoint()
                                                *a.QMat().at(itt->first));

                                        auto matit=_QMat.find(RQ);
                                        if(matit==_QMat.end())
                                        {
                                                _QMat.insert(pair<int, MatrixXd>(RQ, temp));
                                        }else
                                        {
                                                _QMat.at(RQ)+=temp;
                                        }


                                }
                        }
                }
                break;

        }
}






const Sub& Sub::add(const Sub& sub)
{
        //show(); sub.show();

        for(auto it=sub._RLQ.begin(); it!=sub._RLQ.end(); ++it)
        {
                auto itt=_RLQ.find(it->first);
                if(itt==_RLQ.end())
                {
                        _RLQ.insert(pair<int, int>(it->first, it->second));
                }
        }
        for(auto it=_RLQ.begin(); it!=_RLQ.end(); ++it)
        {
                auto itt=sub._RLQ.find(it->first);
                if(itt!=sub._RLQ.end())
                {
                        
                        if(it->second!=itt->second)
                        {
                                cout<<"The upper quantum didn't match each other"<<endl;
                                exit(true);
                        }
                }
        }

        for(auto it=sub._QMat.begin(); it!=sub._QMat.end(); ++it)
        {
                auto itt=_QMat.find(it->first);
                if(itt!=_QMat.end())
                        itt->second+=it->second;
                else
                        _QMat.insert(pair<int, MatrixXd>(it->first, it->second));
        }

        return *this;

}



const Sub& Sub::time(const double& t)
{
        for(auto it=_QMat.begin(); it!=_QMat.end(); ++it)
        {
                it->second*=t;
        }

        return *this;
}




const Sub& Sub::operator+=(const Sub& sub)
{

        //show(); sub.show();

        if(_RLQ.size()!=sub._RLQ.size())
        {
                cout<<"The RLQ dimension of the sub didn't equal"<<endl;
                exit(true);
        }
        for(auto it=_RLQ.begin(); it!=_RLQ.end(); ++it)
        {
                auto itt=sub._RLQ.find(it->first);
                if(itt==sub._RLQ.end())
                {
                        cout<<"The RLQ of two sub didn't match each other"<<endl;
                        exit(true);
                }

                if(it->second!=itt->second)
                {
                        cout<<"The upper quantum didn't match each other"<<endl;
                        exit(true);
                }
        }

        for(auto it=_QMat.begin(); it!=_QMat.end(); ++it)
        {
                it->second+=sub._QMat.at(it->first);
        }

        return *this;
}




void Sub::show()const
{
        cout<<"==========the beautiful beginning line of Sub============="<<endl;
        cout<<"The RLQ of this sub:"<<endl;
        for(auto it=_RLQ.begin(); it!=_RLQ.end(); ++it)cout<<it->first<<" => "<<it->second<<endl;

        cout<<"The QMat of this sub:"<<endl;
        for(auto it=_QMat.begin(); it!=_QMat.end(); ++it)cout<<it->first<<" =>"<<endl<<it->second.rows()
                <<"x"<<it->second.cols()<<endl;
                cout<<"==========the beautiful ending line============="<<endl;
}


void Sub::save(ofstream& outfile)const
{
        outfile<<_RLQ.size()<<endl;
        for(auto it=_RLQ.begin(); it!=_RLQ.end(); ++it)
        {
                outfile<<it->first<<"\t"<<it->second<<endl;
        }

        for(auto it=_QMat.begin(); it!=_QMat.end(); ++it)
        {
                int DL(it->second.rows());
                int DR(it->second.cols());

                outfile<<DL<<"\t"<<DR<<endl;

                outfile<<it->first<<endl;

                for(int i=0; i<DL; ++i)
                {
                        for(int j=0; j<DR; ++j)
                        {
                                outfile<<it->second(i,j)<<endl;
                        }
                }
        }
}

void Sub::read(ifstream& infile)
{
        _RLQ.clear();
        _QMat.clear();

        int Dim;
        infile>>Dim;

        int QL, QR;

        int DL, DR;


        for(int i=0; i<Dim; ++i)
        {
                infile>>DR>>DL;

                _RLQ.insert(pair<int, int>(DR, DL));
        }


        for(int i=0; i<Dim; ++i)
        {
                infile>>DL>>DR;

                MatrixXd temp(MatrixXd::Zero(DL, DR));

                infile>>QR;

                for(int j=0; j<DL; ++j)
                {
                        for(int k=0; k<DR; ++k)
                        {
                        infile>>temp(j,k);

                        }
                }

                _QMat.insert(pair<int, MatrixXd>(QR, temp));
        }


}
