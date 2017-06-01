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


void SuperLattice::calcuWave(SiteWave& wave2, const Sub& LSub, const SiteWave& wave, 
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
                        if(ita->first+itL->first==para.ParticleNo())
                        {
                                temp+=ita->second*itL->second*wave.cell().at(ita->first);
                        }
                }
                

                wave2._cell.insert(pair<int, MatrixXd>(a.RLQ().at(ita->first), temp));
        }
}

void SuperLattice::f1tof2a(const SiteWave& wave, SiteWave& wave2)
{
        SiteWave wavetem;

        calcuWave(wave2, Llattice.System(), wave, Rlattice.SysEye(), Eye, Para);

        calcuWave(wavetem, Llattice.SysEye(), wave, Rlattice.SysEye(), Onsite, Para);
        wave2.add(wavetem);

        calcuWave(wavetem, Llattice.SysEye(), wave, Rlattice.System(), Eye, Para);
        wave2.add(wavetem);

        calcuWave(wavetem, Llattice.SysCreation(), wave, Rlattice.SysEye(), Annihilation, Para);
        wavetem.time(-1*Para.t());
        wave2.add(wavetem);

        calcuWave(wavetem, Llattice.SysAnnihilation(), wave, Rlattice.SysEye(), Creation, Para);
        wavetem.time(-1*Para.t());
        wave2.add(wavetem);


        calcuWave(wavetem, Llattice.SysEye(), wave, Rlattice.SysAnnihilation(), Creation, Para);
        wavetem.time(-1*Para.t());
        wave2.add(wavetem);

        calcuWave(wavetem, Llattice.SysEye(), wave, Rlattice.SysCreation(), Annihilation, Para);
        wavetem.time(-1*Para.t());
        wave2.add(wavetem);


        
}

void SuperLattice::f1tof2b(const SiteWave& wave, SiteWave& wave2)
{
        SiteWave wavetem;

        calcuWave(wave2, wave, Rlattice.System(), Eye, Para);

        calcuWave(wavetem, wave, Rlattice.SysCreation(), Annihilation, Para);
        wavetem.time(-1*Para.t());
        wave2.add(wavetem);

        calcuWave(wavetem, wave, Rlattice.SysAnnihilation(), Creation, Para);
        wavetem.time(-1*Para.t());
        wave2.add(wavetem);

        calcuWave(wavetem, wave, Rlattice.SysEye(), Onsite, Para);
        wave2.add(wavetem);


}

void SuperLattice::f1tof2c(const SiteWave& wave, SiteWave& wave2)
{
        SiteWave wavetem;

        calcuWave(wave2, Llattice.System(), wave, Eye, Para);

        calcuWave(wavetem, Llattice.SysCreation(), wave, Annihilation, Para);
        wavetem.time(-1*Para.t());
        wave2.add(wavetem);

        calcuWave(wavetem, Llattice.SysAnnihilation(), wave, Creation, Para);
        wavetem.time(-1*Para.t());
        wave2.add(wavetem);

        calcuWave(wavetem, Llattice.SysEye(), wave, Onsite, Para);
        wave2.add(wavetem);
}

