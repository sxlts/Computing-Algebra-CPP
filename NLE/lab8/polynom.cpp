#include "polynom.h"

polynom::polynom(){}
polynom::polynom(vector<double> c){
    A = c;
}
polynom::polynom(polynom & b){
    A = b.A;
}
polynom::~polynom(){ }

void polynom::resize(int n){
    while(A.size() < n){
        this->A.push_back(0);
    }
}
int polynom::size() const{
    return A.size();
}

double polynom::operator[](int i) const{
    return this->A[i];
}
double& polynom::operator[](int i){
    return this->A[i];
}

polynom polynom::operator+(const polynom & b){
    polynom a(*this);
    a.resize(max(a.size(), b.size()));

    for(int i = 0 ; i < b.size() ; ++i){
        a[i] += b[i];
    }
    return a;
}

polynom polynom::operator*(double b){
    polynom a(*this);
    for(int i = 0 ; i < a.size() ; ++i){
        a[i]*= b;
    }
    return a;
}
polynom polynom::operator*(pair<double, int> b){
    polynom a(*this);
    double c = b.first;
    int p = b.second;

    a = a*c;
    a.resize(a.size() + p);

    for(int i = 1 ; i <= a.size() - p ; ++i){
        a[a.size() - i] = a[a.size() - i - p];
    }
    for(int i = 0 ; i < p ; ++i) a[i] = 0;

    return a;
}
polynom polynom::operator*(polynom & b){
    polynom a;

    for(int i = 0 ; i < b.size() ; ++i){
        pair<double, int> mult = {b[i], i};
        a = a + *this*mult;
    }

    return a;
}

ostream& operator <<(ostream& out, const polynom& b){
    for(int i = 0 ; i < b.size() - 1; ++i){
        out << b[i] << " * x^" << i << " + ";
    }
    out << b[b.size() - 1] << "*x^" << b.size() - 1;
    return out;
}

double polynom::getval(double n) const{
    double sum = 0;
    double x = 1;

    for(int i = 0 ; i < this->size() ; ++i){
        sum += (*this)[i]*x;
        x*=n;
    }

    return sum;
}








