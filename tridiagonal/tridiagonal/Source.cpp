#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <iomanip>

using namespace std;

double* ans;
void LineSum(double* a, double* b, double n, double mult) {
	for (int i = 0; i < n; i++) {
		a[i] += b[i] * mult;
		if (abs(a[i]) < 0.0000000001) a[i] = 0;
	}
}

void LineSwap(double** a, int t, int h, int n) {
	for (int i = 0; i < n; i++) {
		swap(a[t][i], a[h][i]);
	}
}

void MatCopy(double** a, double** b, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			b[i][j] = a[i][j];
		}
	}
}

int main() {
	srand(time(0));
	ofstream cout("output.txt");
	int n;
	n = 10;
	double** matrix = new double* [n];
	double** A = new double* [n];
	ans = new double[n];
	double* X = new double[n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new double[n + 1];
		A[i] = new double[n];
	}
	//matrix input
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i - 1; j++) {
			matrix[i][j] = 0;
		}
		for (int j = i - 1; j < i + 2, j < n; j++) {
			matrix[i][j] = (rand() % 1001) / 100.;
			if (rand() % 2 == 1) matrix[i][j] *= -1;
		}
		for (int j = i + 2; j < n; j++) {
			matrix[i][j] = 0;
		}
		
	}
	MatCopy(matrix, A, n);
	//X input

	for (int i = 0; i < n; i++) {
		X[i] = (rand() % 1001) / 100.;
		if (rand() % 2 == 1) X[i] *= -1;
	}

	for (int i = 0; i < n; i++) {
		double temp = 0;
		for (int j = max(0, i - 1); j <= min(n - 1, i + 1); j++) {
			temp += matrix[i][j] * X[j];
		}
		matrix[i][n] = temp;
	}
	//first matrix output
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << setprecision(5) << setw(9) << matrix[i][j];
		}
		cout << " |" << setprecision(5) << setw(9) << matrix[i][n];
		cout << '\n';
		cout << '\n';
	}
	for (int i = 0; i < (n + 1) * 10; i++) {
		cout << '-';
	}
	cout << '\n';
	cout << '\n';
	///////////////////////////////////////////////////////////////////////////////////////////////////

	double* P = new double[n];
	double* Q = new double[n];

	P[1] = -1 * matrix[0][1] / matrix[0][0];
	Q[1] = matrix[0][n] / matrix[0][0];
	for (int i = 1; i < n - 1; i++) {
		P[i + 1] = -1 * matrix[i][i + 1] / (matrix[i][i] + (matrix[i][i - 1] * P[i]));
		Q[i + 1] = ((-1 * Q[i] * matrix[i][i-1]) + matrix[i][n]) / (matrix[i][i] + matrix[i][i - 1] * P[i]);
	}
	ans[n - 1] = ((-1 * matrix[n - 1][n - 2]* Q[n - 1]) + matrix[n - 1][n]) / (matrix[n-1][n - 1] + (matrix[n - 1][n - 2] * P[n - 1]));
	for (int i = n - 2; i >= 0; i--) {
		ans[i] = (ans[i + 1] * P[i + 1]) + Q[i + 1];
	}

	double res = 0;
	for (int i = 0; i < n; i++) {
		res = max(res, abs(ans[i] - X[i]));
		cout <<"x"<<i<<":"<< setprecision(20) << setw(24) << ans[i] <<"  X" << i << ":" << setprecision(20) << setw(24) << X[i] << "\n";
	}
	cout << setprecision(3)<< "\nresidual : " << res;
	cout << '\n';
	cout << '\n';
	for (int i = 0; i < (n + 1) * 10; i++) {
		cout << '-';
	}
	cout << '\n';
	cout << '\n';
	///////////////////////////////////////////////////////////////////////////////////////////////////
	res = 0;
	for (int i = 0; i < n; i++) {
		double temp = 0;
		for (int j = max(0,i-1); j <= min(n-1,i+1); j++) {
			temp += matrix[i][j] * ans[j];
		}
		res = max(res, abs(temp - matrix[i][n]));
		cout << "f" << i << ":" << setprecision(20) << setw(24) << temp << "  F" << i << ":" << setprecision(20) << setw(24) << matrix[i][n] << "\n";
	}
	cout << setprecision(3) << "\nresidual : " << res;
	cout << '\n';
	cout << '\n';
	for (int i = 0; i < (n + 1) * 10; i++) {
		cout << '-';
	}
	cout << '\n';
	cout << '\n';
}