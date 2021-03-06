void Superlattice::calcuWave(SiteWave& wave2, const Sub& LSub, const SiteWave& wave, const Sub& RSub, 
                const OP_modes& type, const Parameter& para)
{
        wave2.clear();

        int DL(wave.QMat().begin()->second.rows());
        int DR(wave.QMat().begin()->second.cols());



        OP a(para, type);
        for(auto ita=a.QMat().begin(); ita!=a.QMat().end(); ++ita)
        {
                MatrixXd temp(MatrixXd::Zero(DL, DR));
                for(auto itL=LSub.QMat().begin(); itL!=RSub.QMat().end(); ++itL)
                {
                        for(auto itR=RSub.QMat().begin(); itR!=RSub.QMat().end(); ++itR)
                        {
                                if(ita->first+itL->first+itR->first==para.ParticelNo())
                                {
                                        temp+=it->second*itL->second*wave.QMat().at(it->first)
                                        *itR->second;
                                }
                        }
                }

                wave2._cell.insert(pair<int, MatrixXd>(a.RLQ().at(it->first), temp));
        }
}