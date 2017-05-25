#ifndef SUB_H
#define SUB_H
#include <fstream>
#include "SiteWave.h"
#include "OP.h"

enum Part
{
        Left, Right
};


class Sub
{
private:
        unordered_map<int, int> _RLQ;
        unordered_map<int, MatrixXd> _QMat;
        

public:
        static int QMax;
        const unordered_map<int, int>& RLQ() const {return _RLQ;};
        const unordered_map<int, MatrixXd>& QMat() const {return _QMat;};


        Sub(){};
        ~Sub(){};
        Sub(const OP& a, const SiteWave& wave, const Part& part);
        Sub(const Parameter& para, const OP_modes& type, const SiteWave& wave, const Part& part);


        Sub(const Parameter& para, const Sub& sub, const OP_modes& type, const SiteWave& wave, const Part& part);
        Sub(const Sub& sub, const OP& a, const SiteWave& wave, const Part& part);
        Sub(const Sub& sub):
        _RLQ(sub._RLQ),
        _QMat(sub._QMat)
        {};


        const Sub& add(const Sub& sub);
        const Sub& time(const double& t);
        const Sub& operator+=(const Sub& sub);

        const Sub& operator=(const Sub& sub)
        {
                _QMat=sub._QMat;
                _RLQ=sub._RLQ;
        }

        void save(ofstream& outfile)const;
        void read(ifstream& infile);



        void show()const;
};













#endif