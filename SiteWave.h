#ifndef SITE_WAVE_H
#define SITE_WAVE_H

#include <unordered_map>
#include <Eigen/Eigenvalues>
#include <Eigen/Dense>
#include "Parameter.h"

using namespace Eigen;

class SiteWave
{
private:
        unordered_map<int, MatrixXd> _cell;
        int _site;
public:
        SiteWave(){};
        ~SiteWave(){};

        
}








#endif // SITE_WAVE_H
