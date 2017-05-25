#include "Parameter.h"
#include "Sub.h"



using namespace std;
void test_Sub(const Parameter& para);
void test_Sub(const Parameter& para)
{


        
        OP a(para, Eye);
        //a.show();
        SiteWave haha(3, 0, a);



        SiteWave a1(3, 1, a, haha);
        //haha.show();
        //a1.show();
        OP b(para, Creation);
        //b.show();

        OP c(para, Annihilation);

        Sub test(para, Creation, haha, Right);test.show();

        test.time(2); test.show();


        /*ofstream outfile("haha");
        test.save(outfile);
        outfile.close();

        ifstream infile("haha");
        if(!infile.good())
        {
                cout<<"error!!!!!!the file doesn't open!"<<endl;
                exit(true);
        }

        Sub test1;
        test1.read(infile);test1.show();
        //Sub test1(test, b, a1, Right);

        //Sub test2(test1);


        //(test1+=(test2)).show();*/
}