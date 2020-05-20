#include <bits/stdc++.h>

using namespace std;

class polynom{
public:
    vector<double> A;

    polynom();
    polynom(vector<double> c);
    polynom(polynom & b);

    ~polynom();

    void resize(int n);
    int size() const;

    double operator[](int i) const;
    double& operator[](int i);

    double getval(double n) const;

    polynom operator+(const polynom & b);
    polynom operator*(double b);
    polynom operator*(pair<double, int> b);
    polynom operator*(polynom & b);

    friend ostream& operator <<(ostream& out, const polynom& b);
};