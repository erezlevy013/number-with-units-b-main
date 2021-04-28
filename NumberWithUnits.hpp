#ifndef NUMBERWITHUNIT_H
#define NUMBERWITHUNIT_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <map>
using namespace std;

namespace ariel
{
    class NumberWithUnits
    {
        public:

        double d;
        string str;
        

        
        
        
        NumberWithUnits(double x, string s);
        static void read_units(ifstream& ifs);

        NumberWithUnits operator + (NumberWithUnits& n);
        NumberWithUnits operator - (NumberWithUnits& n);
        NumberWithUnits operator += (const NumberWithUnits& n);
        NumberWithUnits operator -= (const NumberWithUnits& n);
        friend NumberWithUnits operator + (const NumberWithUnits& n);//unari
        friend NumberWithUnits operator - (const NumberWithUnits& n);//unari

        friend bool operator > (const NumberWithUnits& n, const NumberWithUnits& n2);
        friend bool operator < (const NumberWithUnits& n,const NumberWithUnits& n2);
        friend bool operator <= (const NumberWithUnits& n,const NumberWithUnits& n2);
        friend bool operator >= (const NumberWithUnits& n,const NumberWithUnits& n2);
        friend bool operator == (const NumberWithUnits& n,const NumberWithUnits& n2);
        friend bool operator != (const NumberWithUnits& n,const NumberWithUnits& n2);

        NumberWithUnits operator ++ (int);
        NumberWithUnits& operator ++ ();
        NumberWithUnits operator -- (int);
        NumberWithUnits& operator -- ();

        friend ostream& operator << (ostream& os, const NumberWithUnits& n);
        //friend ostream& operator << (ostream& os, const string n);
        friend istream& operator >> (istream& is, NumberWithUnits& n);
           
        NumberWithUnits operator * (const NumberWithUnits& n);
        NumberWithUnits& operator * (const double x) ;
        friend NumberWithUnits operator * (const double x, const NumberWithUnits& n);

        
    };



}
#endif