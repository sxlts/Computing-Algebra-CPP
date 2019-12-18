#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

const int n = 6;
double k = 0;
const double Eps = 5e-7;

int main() {
    ifstream getData("data.txt");
    ofstream out("output.txt");
    if(!getData.is_open()) return 1;

    vector<double> temp;
    temp.resize(n,0);

    vector<vector<double>> B;
    B.resize(n,temp);
    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n ; j++){
            getData >> B[i][j];
        }
    }

    vector<vector<double>> C;
    C.resize(n,temp);
    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n ; j++){
            getData >> C[i][j];
        }
    }

    getData >> k;
    getData.close();

    vector<vector<double>> A;
    A.resize(n,temp);
    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n ; j++){
            A[i][j] = B[i][j] + C[i][j]*k;
        }
    }
    out << "MATRIX :\n\n";
    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n ; j++){
            out << setprecision(4) << setw(9) << A[i][j] << " ";
        }
        out << "\n";
    }
    out <<"\n";
    vector<double> z;
    z.resize(n,1);
    int k = 0;
    double L = 0;
    while(true){

        vector<double> z_next;
        z_next.resize(n , 0);
        double norm = 0;
        double L_new;

        for(int i = 0 ; i < n; i++){
            for(int j = 0; j < n ; j++){
                z_next[i]+= A[i][j]*z[j];
            }
            norm += z_next[i]*z_next[i];
        }

        norm = sqrt(norm);

        double rkArk = 0, rkrk= 0;
        for(int i = 0 ; i < n; i++){
            rkArk += z[i]*z_next[i];
            rkrk += z[i]*z[i];
        }

        L_new = rkArk / rkrk;
        if(abs(L_new - L) < Eps)
        break;

        for(int i = 0 ; i < n; i++){
            z_next[i] = z_next[i]/norm;
        }
        L = L_new;
        z = z_next;
        k++;
    }

    out<<"FOUND " << setprecision(7) << L << " WITH " << k << " ITERATIONS\n";
    out<<"EIGEN VECTOR : (";
    for(int i =0;i<n;i++){
        out << " " << setprecision(4) << z[i] << " ";
        if(i + 1 < n) out << ',';
        else out << ")\n";
    }
}
