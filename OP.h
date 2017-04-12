#ifndef OP_H
#define OP_H

#include "Parameter.h"
#include <unordered_map>
#include <Eigen/Dense>





enum OP_modes{Eye, Creation, Annihilation};
enum Spin{SpinEye, SpinCreation, SpinAnnihilation, SpinZ};//1/2 spin.

using namespace Eigen;

class OP
{
private:
        
        std::unordered_map<int, int> _RLQ;
        std::unordered_map<int, double> _QMat;

        //int _site;

        
public:
        //static int Class_Num;
        //static int Max;//used for the maximum quantum number.
        OP();
        ~OP();

        
        const std::unordered_map<int, int>& RLQ()const{return _RLQ;};
        const std::unordered_map<int, double>& QMat()const{return _QMat;};
        

//=======initialize the boson operator=========================
        OP(const Spin& type);

        OP(const Parameter& para, const OP_modes& type);

        OP(const OP& a);



        void clear();
        void show()const;
};





extern OP operator*(const double& x, const OP& a);


#endif

