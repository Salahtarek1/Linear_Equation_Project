#include<bits/stdc++.h>
#include <linear_equation.h>
using namespace std;

int main()
{
  linear_equation E1,E2,E3,E4("2x1+3x2+4x3=16");

  cin>>E1;    /// 3x2+4x1+4x3+x1-2x3-11+x4=16
  cout<<E1<<endl;   /// E1 = 5x1+3x2+2x23+1x4=27

  cout<<E4<<endl;

  E1 = "4x1+2x2+9x3+8x4+4x5+2x6+3x7+6x8+8x9=2";
  E2 = "2x1+4x2+1x3+1x4+2x5-3x6+5x7+6x8+6x9=6 ";
  E3 = E1+E2;
  cout<<E3<<endl;

  E1 = "5x1+9x2+8x3+7x4-6x5+4x6+2x7-3x8+4x9=8";
  E2 = "2x1+4x2+1x3+1x4+2x5-3x6+5x7+6x8+6x9=6";
  E3 = E1 - E2;
  cout<<E3<<endl;

  E1 = "2x1+4x2+1x3+1x4+2x5-3x6+5x7+6x8+6x9=7";
  E2 = E1*3;
  E3 = E1/2;
  cout<<E2<<endl;
  cout<<E3<<endl;
}


