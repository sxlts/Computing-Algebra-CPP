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
vector<double> Relax(const vector<vector<double>>& matrix , const vector<double>& F , double w){

    int k = 0;
    double tempSum = 0;
    double max_ = 0;
    vector<double> X;
    X.resize(n,0);

    while (true) {
        k++;
        max_ = 0;

        for (int i = 0; i < n; i++) {
            tempSum = 0;

            for (int j = 0; j < n; j++) {
                tempSum += matrix[i][j] * X[j];
            }

            double tempX = X[i] + (F[i] - tempSum) * w / matrix[i][i];

            if(abs(tempX - X[i]) > max_){
                max_ = abs(tempX - X[i]);
            }

            X[i] = tempX;
        }

        if (max_ < Eps) {
            break;
        }
    }

    X.push_back(k);
    X.push_back(max_);

    return X;
}
int main() {
    srand(time(0));

//    ofstream cout("output.txt");
    
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
    double w;


    //draw table
    cout << setw(5) <<  "w" << setw(30) <<  "number of iterations" << setw(25) <<  "||x(k+1) - x(k)||" << "\n\n";

    w = 0.2;
    newX = Relax(squaredMatrix, squaredMatrixF, w);
    cout << setprecision(3) << setw(5) << w << setw(30) <<  newX[n] << setw(25) <<  newX[n+1] << "\n\n";

    w = 0.5;
    newX = Relax(squaredMatrix, squaredMatrixF, w);
    cout << setprecision(3) << setw(5) << w << setw(30) <<  newX[n] << setw(25) <<  newX[n+1] << "\n\n";

    w = 0.8;
    newX = Relax(squaredMatrix, squaredMatrixF, w);
    cout << setprecision(3) << setw(5) << w << setw(30) <<  newX[n] << setw(25) <<  newX[n+1] << "\n\n";

    w = 1.0;
    newX = Relax(squaredMatrix, squaredMatrixF, w);
    cout << setprecision(3) << setw(5) << w << setw(30) <<  newX[n] << setw(25) <<  newX[n+1] << "\n\n";

    w = 1.3;
    newX = Relax(squaredMatrix, squaredMatrixF, w);
    cout << setprecision(3) << setw(5) << w << setw(30) <<  newX[n] << setw(25) <<  newX[n+1] << "\n\n";

    w = 1.5;
    newX = Relax(squaredMatrix, squaredMatrixF, w);
    cout << setprecision(3) << setw(5) << w << setw(30) <<  newX[n] << setw(25) <<  newX[n+1] << "\n\n";

    w = 1.8;
    newX = Relax(squaredMatrix, squaredMatrixF, w);
    cout << setprecision(3) << setw(5) << w << setw(30) <<  newX[n] << setw(25) <<  newX[n+1] << "\n\n";

    cout << '\n';
    cout << '\n';
    for (int i = 0; i < (n + 1) * 10; i++) {
        cout << '-';
    }
    cout << '\n';
    cout << '\n';

    double res = 0;
    cout << "compare asnweras for w = 1.8 \n\n";
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