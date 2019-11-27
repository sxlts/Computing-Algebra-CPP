#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;

const int n = 10;
const double Eps = 1e-5;

//square symmetric matrix
vector<vector<double>>  GetSquare(const vector<vector<double>>& matrix){
    vector<vector<double>> squaredMatrix;

    vector<double> temp;
    temp.resize(n , 0);
    squaredMatrix.resize(n, temp);
    temp.clear();

    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n ; j++){
            for(int h = 0; h < n ; h++){
                squaredMatrix[i][j] += matrix[i][h] * matrix[h][j];
            }
        }
    }

    return squaredMatrix;
}

//relaxation method

double scalarMultiply(const vector<double>& x1 , const vector<double>& x2){
    double ret = 0;
    for (int i = 0 ; i < x1.size() ; i++){
        ret += x1[i] * x2[i];
    }
    return ret;
}

vector<double> minus_(const vector<double>& x1 , const vector<double>& x2){
    vector<double> ret = x1;
    for (int i = 0 ; i < x1.size() ; i++){
        ret[i] -= x2[i];
    }
    return ret;
}

vector<double> multiply_(const vector<double>& x1 , double m){
    vector<double> ret = x1;
    for (int i = 0 ; i < x1.size() ; i++){
        ret[i] *= m;
    }
    return ret;
}
vector<double> multMatrixVector(const vector<vector<double>>& matrix , const vector<double>& x){
    vector<double> ret;
    ret.resize(x.size(),0);
    for(int i =0;i<x.size();i++){
        for(int j =0;j<x.size();j++){
            ret[i] += x[j]*matrix[i][j];
        }
    }
    return ret;
}

vector<double> descent(const vector<vector<double>>& matrix , const vector<double>& F){

    int k = 0;
    double max_ = 0;
    vector<double> X;
    X.resize(n,0);
    vector<double> R;
    R.resize(n,0);
    vector<double> newX;
    newX.resize(n,0);

    while(true){
        max_ = 0;
        k++;

        R = minus_(multMatrixVector(matrix,X) , F);

        newX = minus_(X, multiply_(R,scalarMultiply(R,R) / scalarMultiply( multMatrixVector(matrix,R) , R)));

        for(int i =0;i < X.size();i++){
            if(abs(newX[i] - X[i]) > max_){
                max_ = abs(newX[i] - X[i]);
            }
        }

        X = newX;

        if(max_ < Eps) break;
    }

    X.push_back(k);
    X.push_back(max_);

    return X;
}
int main() {
    srand(time(0));

    //ofstream cout("output.txt");

    vector<vector<double>> matrix;
    vector<double> temp;
    temp.resize(n);
    matrix.resize(n, temp);
    temp.clear();

    //create matrix
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            matrix[i][j] = (rand()%1001)/100.;
            if(static_cast<int>((rand()%1001)/100.) % 2 == 0) matrix[i][j] *= -1;
            matrix[j][i] = matrix[i][j];
        }
    }

    //create true X vector
    vector<double> trueX;
    trueX.resize(n);
    for(int i = 0; i < n; i++){
        trueX[i] = (rand()%1001)/100.;
        if(static_cast<int>((rand()%1001)/100.) % 2 == 0) trueX[i] *= -1;
    }

    //create true F vector
    vector<double> trueF;
    trueF.resize(n);
    for(int i = 0; i < n; i++){
        trueF[i] = 0;
        for(int j = 0; j < n; j++){
            trueF[i] += matrix[i][j] * trueX[j];
        }
    }

    //first matrix and trueF output
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setprecision(3) << setw(9) << matrix[i][j];
        }
        cout << " |" << setprecision(3) << setw(9) << trueF[i];
        cout << '\n';
        cout << '\n';
    }

    for (int i = 0; i < (n + 1) * 10; i++) {
        cout << '-';
    }
    cout << '\n';
    cout << '\n';

    //true X output
    cout <<"True X :\n";
    for(int i = 0; i < n; i++){
        cout << setprecision(3) << setw(9) << trueX[i];
        cout << '\n';
    }

    cout << '\n';
    cout << '\n';
    for (int i = 0; i < (n + 1) * 10; i++) {
        cout << '-';
    }
    cout << '\n';
    cout << '\n';

    //create squared matrix
    vector<vector<double>> squaredMatrix;
    temp.resize(n , 0);
    squaredMatrix.resize(n, temp);
    temp.clear();

    squaredMatrix = GetSquare(matrix);

    vector<double> squaredMatrixF;
    squaredMatrixF.resize(n,0);

    for(int i = 0 ; i < n ; i ++){
        for (int j = 0 ; j < n ; j++){
            squaredMatrixF[i] += matrix[i][j] * trueF[j];
        }
    }

    vector<double> newX;
    
    //do method
    newX = descent(squaredMatrix, squaredMatrixF);

    cout << " number of iterations : " << newX[n];
    cout << '\n';
    cout << '\n';
    for (int i = 0; i < (n + 1) * 10; i++) {
        cout << '-';
    }
    cout << '\n';
    cout << '\n';

    //write residual
    double res = 0;
    cout << "compare answers\n\n";
    cout << setw(32)  << "true X" << setw(34)  << "found X\n\n";
    for (int i = 0; i < n; i++) {
        cout << setw(5) << 'x' << i << ':';
        cout << setprecision(20) << setw(25)  << trueX[i];
        cout << setw(5) << 'X' << i << ':';
        cout << setprecision(20) << setw(25) << newX[i] << "\n";
        res = max(res, abs(newX[i] - trueX[i]));
    }

    cout << '\n';
    cout << '\n';
    cout <<"residual :"<< res << "\n\n";
    for (int i = 0; i < (n + 1) * 10; i++) {
        cout << '-';
    }

    return 0;
}