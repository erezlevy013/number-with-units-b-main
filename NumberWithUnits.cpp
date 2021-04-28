#include "NumberWithUnits.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>

using namespace std;

namespace ariel
{    
    
    map<string, map<string, double>> Map;


    NumberWithUnits::NumberWithUnits(double x, string s)
    {
        d=double(x);
        str=s;
        if(Map.count(s) == 0)
        {
            throw invalid_argument("invalid argument");
        }
        
    }
   
    void ariel::NumberWithUnits::read_units(ifstream& ifs)
    {
        /*
         if (ifs)
        {
            string line, M_left,M_right,equal;
            double L_num,R_num;
            string save1,save2;
            
            while (getline(ifs, line))
            {
                
                istringstream(line)  >> L_num >> M_left >> equal >> R_num >> M_right; //>> skipws
                
                Map.insert({M_left,map<string,double>{}});
                Map.insert({M_right,map<string,double>{}});
                Map.at(M_left).insert({M_right,R_num});
                Map.at(M_right).insert({M_left,L_num/R_num});

              
              if(save2 == M_left)
                {
                    Map.insert({M_right,map<string,double>{}});
                    Map.at(M_right).insert({save1,L_num/R_num/Map.at(save1).at(save2)});
                    Map.insert({save1,map<string,double>{}});
                    Map.at(save1).insert({M_right,R_num*Map.at(save1).at(save2)});

                    cout<<L_num <<" "<<M_right<<" "<<equal<<" "<<L_num/R_num/Map.at(save1).at(save2)<<" "<<save1<<endl;
                    cout<<L_num <<" "<<save1<<" "<<equal<<" "<<R_num*Map.at(save1).at(save2)<<" "<<M_right<<endl;

                }
                if(save1 == M_right)
                {
                    Map.insert({M_left,map<string,double>{}});
                    Map.at(M_left).insert({save2,R_num*Map.at(save1).at(save2)}); 
                    Map.insert({save2,map<string,double>{}});
                    Map.at(save2).insert({M_left,L_num/R_num/Map.at(save1).at(save2)});

                
                    cout<<"eeee1"<<L_num <<" "<<M_left<<" "<<equal<<" "<<R_num*Map.at(save1).at(save2)<<" "<<save2<<endl;
                    cout<<"eeee"<<L_num <<" "<<save2<<" "<<equal<<" "<<L_num/R_num/Map.at(save1).at(save2)<<" "<<M_left<<endl;

                }
                

                save1=M_left;
                save2=M_right;

                cout<<L_num <<" "<<M_left<<" "<<equal<<" "<<Map.at(M_left).at(M_right)<<" "<<M_right<<endl;
                cout<<L_num <<" "<<M_right<<" "<<equal<<" "<<Map.at(M_right).at(M_left)<<" "<<M_left<<endl;
               
            }
           
        
            map<string, map<string,double>> erez;
            erez.insert({"m",map<string,double>{}});
            erez.insert({"m",map<string,double>{}});
            erez.at("m").insert({"r",5}); 
            erez.at("m").insert({"r",6});


            std::cout<<erez.at("m").at("r")<<endl;
            
        }
        else
        {
            throw string("Error file");
        }*/
        if (ifs)
        {
            string line, M_left,M_right,equal;
            double L_num,R_num;
            while (getline(ifs, line))
            {
                
                istringstream(line)  >> L_num >> M_left >> equal >> R_num >> M_right; 

                if (Map.count(M_left) == 0)
                {
                    Map.insert({M_left, map<string, double>{}});
                }
                if (Map.count(M_right) == 0)
                {
                    Map.insert({M_right, map<string, double>{}});
                }

                for (auto const &temp : Map.at(M_left))
                {
                    Map.at(M_right).insert({temp.first, temp.second / R_num});
                    Map.at(temp.first).insert({M_right, R_num / temp.second});
                }

                for (auto const &temp : Map.at(M_right))
                {
                    Map.at(M_left).insert({temp.first, temp.second * R_num});
                    Map.at(temp.first).insert({M_left, L_num / (R_num * temp.second)});
                }

                Map.at(M_left).insert({M_right, R_num});
                Map.at(M_right).insert({M_left, L_num / R_num});
            }
        }
        else
        {
            throw string("Error file");
        }
    }

    NumberWithUnits NumberWithUnits::operator + (NumberWithUnits& n)
    {
        try
        {
            if(str != n.str)
            {
                NumberWithUnits t{double(d+(n.d/Map.at(str).at(n.str))),str};
                
                return t;
            }
            else
            {
                NumberWithUnits t{double(d+n.d),str};
            
                return t;
            }
        }
        catch(const std::exception& e)
        {
            throw invalid_argument("invalid argument");
        }
        
        //return n;
    }
    NumberWithUnits NumberWithUnits::operator - (NumberWithUnits& n)
    {
        try
        {
            if(str != n.str)
            {
                NumberWithUnits t{d-(n.d/Map.at(str).at(n.str)),str};
                return t;
            }
            else
            {
                NumberWithUnits t{d-n.d,str};
                return t;
            }
        }
        catch(const std::exception& e)
        {
            throw invalid_argument("invalid argument");
        }
        
    }
    NumberWithUnits NumberWithUnits::operator += (const NumberWithUnits& n)
    {
         
        try
        {
         
            if(str != n.str)
            {
                d=d+(n.d/Map.at(str).at(n.str));
                
                
            }
            else
            {
                d=d+n.d;
            }
            

        }
        catch(const std::exception& e)
        {
            throw invalid_argument("invalid argument ");
        }
        return *this;
       
    }
    NumberWithUnits NumberWithUnits::operator -= (const NumberWithUnits& n)
    {
        try
        {
         
            if(str != n.str)
            {
                d=d-(n.d/Map.at(str).at(n.str));
                
                
            }
            else
            {
                d=d-n.d;
            }
            

        }
        catch(const std::exception& e)
        {
            throw invalid_argument("invalid argument ");
        }
        return *this;
       
    }
    NumberWithUnits operator + (const NumberWithUnits& n)//unari
    {
       NumberWithUnits t{+n.d, n.str};
        return t;
    }
    NumberWithUnits operator - (const NumberWithUnits& n)//unari
    {
        NumberWithUnits t{-n.d, n.str};
        return t;
    }       

    bool operator > (const NumberWithUnits& n, const NumberWithUnits& n2)
    {
        try
        {
            //NumberWithUnits t1{d,str};
            if(n.str!=n2.str)
            {
                NumberWithUnits t{Map.at(n2.str).at(n.str)*n2.d,n.str};
                /*cout<<"****************"<<endl;
                cout<<t1<<endl;
                cout<<t2<<endl;
                cout<<"****************"<<endl;*/
                if(n.d>t.d)
                    return true;
                else
                    return false;    
            }
            else if(n.d>n2.d)
            {
                return true;
            }
            else
                return false;

        }
        catch(const std::exception& e)
        {
            throw invalid_argument("invalid argument");
        }
        
    }
    bool operator < (const NumberWithUnits& n, const NumberWithUnits& n2)
    {
        
        try
        {
            if(n.str!=n2.str)
            {
                NumberWithUnits t{Map.at(n2.str).at(n.str)*n2.d,n.str};
                
                if(n.d<t.d)
                    return true;
                else
                    return false;    
            }
            else if(n.d<n2.d)
            {
                return true;
            }
            else
                return false;
           
        }
        catch(const std::exception& e)
        {
            throw invalid_argument("invalid argument");
        }

    }
    bool operator <= (const NumberWithUnits& n, const NumberWithUnits& n2)
    {
        try
        {
            if(n.str!=n2.str)
            {
                NumberWithUnits t{Map.at(n2.str).at(n.str)*n2.d,n.str};
                
                if(n.d-t.d<0.0001)
                    return true;
                else
                    return false;    
            }
            else if(n.d<=n2.d)
            {
                return true;
            }
            else
                return false;
           
        }
        catch(const std::exception& e)
        {
            throw invalid_argument("invalid argument");
        }

    }
    bool operator >= (const NumberWithUnits& n, const NumberWithUnits& n2)
    {
        try
        {
            if(n.str!=n2.str)
            {
                NumberWithUnits t{Map.at(n2.str).at(n.str)*n2.d,n.str};
                
                if(n.d>=t.d)
                    return true;
                else
                    return false;    
            }
            else if(n.d>=n2.d)
            {
                return true;
            }
            else
                return false;
           
        }
        catch(const std::exception& e)
        {
            throw invalid_argument("invalid argument");
        }

    }
    bool operator == (const NumberWithUnits& n, const NumberWithUnits& n2)
    {
        try
        {
            if(n.str!=n2.str)
            {
                
                NumberWithUnits t{Map.at(n2.str).at(n.str)*n2.d,n.str};
                
                if(abs(n.d-t.d)<0.0001)
                    return true;
                else
                    return false;    
            }
            
            else if(abs(n.d-n2.d)<0.0001)
            {
                return true;
            }
            else
                return false;
           
        }
        catch(const std::exception& e)
        {
            throw invalid_argument("invalid argument");
        }

    }
    bool operator != (const NumberWithUnits& n, const NumberWithUnits& n2)
    {
        try
        {
            if(n.str!=n2.str)
            {
                NumberWithUnits t{Map.at(n2.str).at(n.str)*n2.d,n.str};
                
                if(n.d!=t.d)
                    return true;
                else
                    return false;    
            }
            else if(n.d!=n2.d)
            {
                return true;
            }
            else
                return false;
           
        }
        catch(const std::exception& e)
        {
            throw invalid_argument("invalid argument");
        }

    }

    NumberWithUnits NumberWithUnits::operator ++ (int)
    {
        NumberWithUnits b(d, str);
        d++;
        return b;
    }
    NumberWithUnits& NumberWithUnits::operator ++ ()
    {   
        d++;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator -- (int)
    {
         NumberWithUnits b(d, str);
        d--;
        return b;
    }
    NumberWithUnits& NumberWithUnits::operator -- ()
    {
        d--;
        return *this;
    }

    ostream& operator << (ostream& os, const NumberWithUnits& n)
    {
        os<<n.d<<"["<<n.str<<"]";
        return os;
    }
   /* ostream& operator << (ostream& os, const string n)
    {
        os<<n;
        return os;
    }*/
    istream& operator >> (istream& is, NumberWithUnits& n)
    {/*
        char open, close;
        is >> n.d >> open >> n.str >> close;
        
        return is;*/
        char open, close;
        
        is >> n.d >> open >> n.str;
        if (n.str.at(n.str.length() - 1) != ']')
        {
            is >> close;
        }
        else
        {
            n.str = n.str.substr(0, n.str.length() - 1);
        }

        if (Map.count(n.str) == 0)
        {
            throw invalid_argument("invalid argument");
        }

        return is;
    }
           
    NumberWithUnits NumberWithUnits::operator * (const NumberWithUnits& n)
    {
        cout<<"*1";
        return *this;
    }
    NumberWithUnits& NumberWithUnits::operator * (const double x)
    {
        d=d*x;
        return *this ;
    }
    
    NumberWithUnits operator * (const double x, const NumberWithUnits& n)
    {   
        NumberWithUnits t{x*n.d,n.str};
        return t;
    }
}