#ifndef LINEAR_EQUATION_H
#define LINEAR_EQUATION_H
#include <bits/stdc++.h>
using namespace std;
class linear_equation
{

    private:
        string TheEquation;
        vector<string> Variables;
        map<string , double > Coefficient;
        string Constant;
        void SortEquation();
    public:
        linear_equation();
        linear_equation(string equation);
        friend  istream& operator>>( istream &input , linear_equation &equ);
        friend  ostream& operator<<( ostream &output , linear_equation &equ) ;
        void operator= (string equ) ;
        linear_equation operator+ (linear_equation equ) ;
        linear_equation operator- (linear_equation equ) ;
        friend linear_equation operator* (linear_equation equ , long double D );
        friend linear_equation operator/ (linear_equation equ , long double D );
        void Clear();
        ~linear_equation();
};

#endif
