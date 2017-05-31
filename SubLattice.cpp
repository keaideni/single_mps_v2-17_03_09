#include "SubLattice.h"


void SubLattice::show()const
{

        cout<<"================the beginning of the SubLattice==================="<<endl;

        if(_part==Left)
        {
                cout<<"This is the left SubLattice:"<<endl;
        }else
        {
                cout<<"This is the right SubLattice:"<<endl;
        }

        cout<<"This SubLattice describes the "<<_Site<<" site."<<endl;

        cout<<"The system term of this SubLattice is"<<endl;
        _System.show();
        cout<<"The Eye term of this SubLattice is"<<endl;
        _SysEye.show();
        cout<<"The Creation of this SubLattice is"<<endl;
        _SysCreation.show();
        cout<<"The annihilation of this SubLattice is"<<endl;
        _SysAnnihilation.show();


        cout<<"==================the ending of the SubLattice===================="<<endl;

}

void SubLattice::save()const
{
        string filename("./data/SubLattice/");

        stringstream sstr;

        sstr<<_Site;

        string tem;sstr>>tem;

        filename+=tem;

        ofstream outfile(filename);

        outfile<<_Site<<endl;

        if(_part==Left)
        {
                outfile<<0<<endl;
        }else outfile<<1<<endl;

        _System.save(outfile);
        _SysEye.save(outfile);
        _SysCreation.save(outfile);
        _SysAnnihilation.save(outfile);

        outfile.close();
}


void SubLattice::read(const int& site)
{
        string filename("./data/SubLattice/");

        stringstream sstr;

        sstr<<site;

        string tem;sstr>>tem;

        filename+=tem;

        ifstream infile(filename);

        infile>>_Site;

        int temp;

        infile>>temp;

        if(temp==0)
        {
                _part=Left;
        }else
        {
                _part=Right;
        }

        _System.read(infile);
        _SysEye.read(infile);
        _SysCreation.read(infile);
        _SysAnnihilation.read(infile);

        infile.close();
}