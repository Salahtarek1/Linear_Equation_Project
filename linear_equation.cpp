#include "linear_equation.h"

bool Search(string s , vector<string> v);
string TOString(double d);
bool IsConstant(string s);
void OppositeSign(string &s);

linear_equation::linear_equation()
{
}

linear_equation::linear_equation(string equation)
: TheEquation(equation)
{
   SortEquation();
}
void linear_equation::operator= (string equ)
{
    Clear();
    TheEquation = equ ;
    SortEquation();
}
istream& operator>> ( istream &input , linear_equation &e)
{
     e.Clear();
     input>>e.TheEquation;
     e.SortEquation();
     return input;
}

ostream& operator<< (ostream &output , linear_equation &e)
{
     output<<e.TheEquation;
     return output;
}

void linear_equation::SortEquation()
{
    vector<string> TempVector1 , Vars , Coeff , Const;
    set<string> TempSet;
    string TempString = "";
    double TempNum = 0;
    bool TempTest  = true ;
    if(isalpha(TheEquation[0]))
    {
        TheEquation.insert(0,"1");
    }
    for(unsigned int i=0;i<TheEquation.size();i++)
    {
       if ((TheEquation[i]=='-' || TheEquation[i]=='+') && isalpha(TheEquation[i+1]))
       {
            TheEquation.insert(i+1,"1");
            i++;
       }
    }
    for(unsigned int i=0,j=0;i<TheEquation.size();i++)
    {
            TempString += TheEquation[i];
            if( TheEquation[i+1]=='+' || (TheEquation[i+1]=='-' && TheEquation[i]!='=') || TheEquation[i+1]=='=' || i+1==TheEquation.size())
            {
                TempVector1.push_back(TempString);
                TempString = "" ;
                j++;
            }
    }
    TempString = "";
    TempTest = false ;
    for(unsigned int i=0;i<TempVector1.size();i++){
        if(IsConstant(TempVector1[i]))
        {
            for(unsigned int j=0;j<TempVector1[i].size();j++)
            {
                TempString += TempVector1[i][j];
                if(isalpha(TempVector1[i][j+1]))
                {
                     Vars.push_back(TempVector1[i].substr(j+1));
                     if(TempTest)
                     {
                         OppositeSign(TempString);
                     }
                     Coeff.push_back(TempString);
                     TempString="";
                     break;
                }
            }
        }
        else
        {
            if(TempVector1[i][0]=='=')
            {
                TempTest = true;
            }
            Const.push_back(TempVector1[i]);
        }
    }
    for(unsigned int i=0;i<Vars.size();i++)
    {

        if(TempSet.find(Vars[i]) == TempSet.end() )
        {
            TempSet.insert(Vars[i]);
        }
    }
    for(auto it = TempSet.begin() ; it!=TempSet.end() ; it++)
    {
        Variables.push_back(*it);
    }

    for(unsigned int i=0;i<Vars.size();i++)
    {
        Coefficient[Vars[i]] += atof(Coeff[i].c_str()) ;
    }
    TempNum = 0 ;
    TempTest = true ;
    for(unsigned int i=0;i<Const.size();i++)
    {
         if(Const[i][0]=='='){
                Const[i].erase(0,1);
                TempTest = false;
            }
         if(TempTest){
            if(Const[i][0]!='+' && Const[i][0]!='-' )
            {
                Const[i] = "-" + Const[i] ;
            }
            else if (Const[i][0]=='+')
            {
                Const[i][0]='-';
            }
            else if (Const[i][0]=='-')
            {
                Const[i][0]='+';
            }
        }
        TempNum += atof(Const[i].c_str());
   }
   TheEquation="";
   for(unsigned int i=0;i<Variables.size();i++)
   {
        if(Coeff[i]!="+0")
        {
           TheEquation += TOString(Coefficient[Variables[i]]) + Variables[i] ;
        }
   }
   Constant = TOString(TempNum) ;
   TheEquation += '=' + Constant;
   if(TheEquation[0]=='+')
   {
        TheEquation.erase(0,1);
   }
   if(TheEquation[TheEquation.find("=")+1]=='+')
   {
        TheEquation.erase(TheEquation.find("=")+1,1);
   }
};
linear_equation linear_equation::operator+ (linear_equation equ)
{
   linear_equation newEquation;
   if(equ.TheEquation[0]!='+' && equ.TheEquation[0]!='-' )
   {
       equ.TheEquation.insert(0,"+");
   }
   pair<int,int> IndexOfEqual = {TheEquation.find('='),equ.TheEquation.find('=')};
   newEquation = TheEquation.substr(0,IndexOfEqual.first) + equ.TheEquation.substr(0,IndexOfEqual.second)+"="+ TOString(( atof(equ.Constant.c_str()) )+(atof(Constant.c_str())));
   return newEquation;
}
linear_equation linear_equation::operator- (linear_equation equ)
{
   linear_equation newEquation;
   OppositeSign(equ.TheEquation);
   pair<int,int> IndexOfEqual = {TheEquation.find('='),equ.TheEquation.find('=')};
   newEquation = TheEquation.substr(0,IndexOfEqual.first) + equ.TheEquation.substr(0,IndexOfEqual.second)+"="+ TOString( atof(Constant.c_str()) - (atof(equ.Constant.c_str())) );
   return newEquation;
}
linear_equation operator* (linear_equation equ , long double D )
{
   linear_equation newEquation;
   string TempString;
   for(unsigned int i=0;i<equ.Variables.size();i++)
   {
        if(equ.Coefficient[equ.Variables[i]]!=0)
        {
           TempString += TOString(equ.Coefficient[equ.Variables[i]] * D ) + equ.Variables[i] ;
        }
   }
   TempString += '=' + TOString(atof(equ.Constant.c_str()) * D);
   newEquation = TempString ;
   return newEquation ;
}
linear_equation operator/ (linear_equation equ , long double D )
{
   linear_equation newEquation;
   string TempString;
   for(unsigned int i=0;i<equ.Variables.size();i++)
   {
        if(equ.Coefficient[equ.Variables[i]]!=0)
        {
           TempString += TOString(equ.Coefficient[equ.Variables[i]] / D ) + equ.Variables[i] ;
        }
   }
   TempString += '=' + TOString(atof(equ.Constant.c_str()) / D);
   newEquation = TempString ;
   return newEquation ;
}
linear_equation::~linear_equation()
{
    Clear();
}
void linear_equation::Clear()
{
   TheEquation.clear();
   Variables.clear();
   Coefficient.clear();
   Constant.clear();
}
bool IsConstant(string s){
   for(unsigned int i=0;i<s.size();i++)
   {
        if(isalpha(s[i]))
        {
            return true;
        }
   }
   return false;
}
bool Search(string s , vector<string> v)
{
    for(unsigned int i=0;i<v.size();i++)
    {
       if(v[i]==s)
       {
           return true;
       }
    }
    return false;
}
string TOString(double d)
{
    string s;
    stringstream ss;
    ss << d;
    ss >> s;
    if(s[0]!='+' && s[0]!='-')
    {
        s.insert(0,"+");
    }
    return s;
}
void OppositeSign(string &s)
{
   for(unsigned int i=0;i<s.size();i++)
   {
       if(s[i]=='=' && s[i+1]!='+' && s[i+1]!='-' )
       {
            s.insert(i+1,"-");
            i++;
       }
       else if(s[i]=='-')
       {
            s[i] = '+';
       }
       else if(s[i]=='+')
       {
            s[i] = '-';
       }
   }
   if(s[0]!='+' && s[0]!='-')
   {
       s.insert(0,"-");
   }
}
