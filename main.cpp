#include "Parameter.h"
#include "OP.h"


using namespace  std;
int main()
{
        ifstream infile("./data/QNosave");
        Parameter para(infile);
        para.show();

        OP a(para, Annihilation);
        a.show();
}