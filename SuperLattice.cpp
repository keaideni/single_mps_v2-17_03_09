#include "SuperLattice.h"



void SuperLattice::calcuWave(SiteWave& wave2, const Sub& LSub, const SiteWave& wave, const Sub& RSub, 
                const OP_modes& type, const Parameter& para)
{
        wave2.clear();

        int DL(wave.cell().begin()->second.rows());
        int DR(wave.cell().begin()->second.cols());



        OP a(para, type);
        for(auto ita=a.QMat().begin(); ita!=a.QMat().end(); ++ita)
        {
                MatrixXd temp(MatrixXd::Zero(DL, DR));
                for(auto itL=LSub.QMat().begin(); itL!=LSub.QMat().end(); ++itL)
                {
                        for(auto itR=RSub.QMat().begin(); itR!=RSub.QMat().end(); ++itR)
                        {
                                if(ita->first+itL->first+itR->first==para.ParticleNo())
                                {
                                        temp+=ita->second*itL->second*wave.cell().at(ita->first)
                                        *itR->second;
                                }
                        }
                }

                wave2._cell.insert(pair<int, MatrixXd>(a.RLQ().at(ita->first), temp));
        }
}



void SuperLattice::calcuWave(SiteWave& wave2, const SiteWave& wave, const Sub& RSub, 
                const OP_modes& type, const Parameter& para)
{
        wave2.clear();

        int DL(wave.cell().begin()->second.rows());
        int DR(wave.cell().begin()->second.cols());



        OP a(para, type);
        for(auto ita=a.QMat().begin(); ita!=a.QMat().end(); ++ita)
        {
                MatrixXd temp(MatrixXd::Zero(DL, DR));
                
                for(auto itR=RSub.QMat().begin(); itR!=RSub.QMat().end(); ++itR)
                {
                        if(ita->first+itR->first==para.ParticleNo())
                        {
                                temp+=ita->second*wave.cell().at(ita->first)
                                *itR->second;
                        }
                }
                

                wave2._cell.insert(pair<int, MatrixXd>(a.RLQ().at(ita->first), temp));
        }
}