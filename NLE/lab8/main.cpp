#include <bits/stdc++.h>
#include "polynom.h"

using namespace std;

ofstream fout("output.txt");

double a = -1.0, b = 5.0;

double f1(double n){
    return cos(n);
}
double f2(double n){
    return abs(2*n - 3);
}

polynom getP(vector<double>w, vector<double> s, int n){
    polynom P;
    for(int i = 0 ; i <= n ; ++i){
        polynom l(vector<double>{1.});

        for(int j = 0 ; j <= n ; ++j){
            if(i != j) {
                polynom tl(vector<double>{-s[j], 1.});
                l = l * tl;
                l = l * (1./(s[i] - s[j]));
            }
        }
        l = l * w[i];
        P = P + l;
    }
    return P;
}

void inter(int n){
    vector<double> w;
    vector<double> s;
    w.resize(n + 1);
    s.resize(n + 1);
    double step = (b - a)/(double)n;
    polynom P;

    for(int i = 0 ; i <= n ; ++i){
        s[i] = a + (double)i * step;
        w[i] = f1(s[i]);
    }
    P = getP(w, s, n);
    cout << "F1 normal : " << P << "\n";

    for(int i = 0 ; i <= n ; ++i){
        s[i] = 0.5*(a + b) + 0.5*(b - a)*cos((2.*i + 1.)/(2.*n + 2.)*3.1415);
        w[i] = f1(s[i]);
    }
    P = getP(w, s, n);
    cout << "F1 chebyshev : " << P << "\n";

    for(int i = 0 ; i <= n ; ++i){
        s[i] = a + (double)i * step;
        w[i] = f2(s[i]);
    }
    P = getP(w, s, n);
    fout << "{" << P <<"}\n";
    cout << "F2 normal : " << P << "\n";

    for(int i = 0 ; i <= n ; ++i){
        s[i] = 0.5*(a + b) + 0.5*(b - a)*cos((2.*i + 1.)/(2.*n + 2.)*3.1415);
        w[i] = f2(s[i]);
    }
    P = getP(w, s, n);
    cout << "F2 chebyshev : " << P << "\n";
}
int main(){
    inter(3);
    inter(5);
    inter(7);
    inter(10);
    inter(15);
    inter(20);
}