#include<bits/stdc++.h>
#include "Matrix.h"
using namespace std;
int main()
{
    Matrix A(5, 5), B(5, 5), C(5, 5);
    A.set(1);
    cout<<A;
    B.set(1);
    A-=B;
    cout<<A;
    C.set(1);
    A+=B;
    cout<<A;
    A*=C;
    cout<<A;
    B=B^3;
    cout<<B;
}