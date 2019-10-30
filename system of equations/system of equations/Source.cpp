#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <iomanip>

void LineSum(double* a, double * b, double n, double mult) {
	for (int i = 0; i < n; i++) {
		a[i] += b[i] * mult;
		if (abs(a[i]) < 0.0000000001) a[i] = 0;
	}
}

void LineSwap(double** a, int t, int h, int n) {
	for (int i = 0; i < n; i++) {
		std::swap(a[t][i], a[h][i]);
	}
}

void Gauss(double** matrix, int n , double** invers) {
	for (int i = 0; i < n; i++) {
		if (matrix[i][i] == 0) {
			for (int j = i + 1; j < n; j++) {
				if (matrix[j][i] != 0) {
					LineSwap(matrix, i, j, n + 1);
					LineSwap(invers, i, j, n);
					break;
				}
			}
		}
		for (int j = i + 1; j < n; j++) {
			double tmp = (matrix[j][i] / matrix[i][i]) * -1;
			LineSum(matrix[j], matrix[i], n + 1, tmp);
			LineSum(invers[j], invers[i], n, tmp);
		}
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
	std::ifstream input("input.txt");
	int n;
	n = 10;
	double** matrix = new double*[n];
	double** A = new double* [n];
	double* X = new double[n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new double[n + 1];
		A[i] = new double[n];
	}
	double** invers = new double* [n];
	for (int i = 0; i < n; i++) {
		invers[i] = new double[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			invers[i][j] = 0;
		}
		invers[i][i] = 1;
	}
	//matrix input
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = (rand()%1001)/100.;
			//matrix[i][j] = (rand() % 10);
		}
	}
	MatCopy(matrix, A, n);
	//X input

	for (int i = 0; i < n; i++) {
		X[i] = (rand()%1001)/100.;
	}
	for (int i = 0; i < n; i++) {
		double temp = 0;
		for (int j = 0; j < n; j++) {
			temp += matrix[i][j] * X[j];
		}
		matrix[i][n] = temp;
	}
	//first matrix output
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << std::setprecision(2) << std::setw(9) << matrix[i][j];
		}
		std::cout << " |" << std::setprecision(2) << std::setw(9) << matrix[i][n];
		std::cout << '\n';
		std::cout << '\n';
	}
	for (int i = 0; i < (n + 1) * 10; i++) {
		std::cout << '-';
	}
	std::cout << '\n';
	std::cout << '\n';
	///////////////////////////////////////////////////////////////////////////////////////////////////

	//Gauss method
	Gauss(matrix, n , invers);
	double* answer = new double[n];

	
	//output after method
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << std::setprecision(2) << std::setw(9) << matrix[i][j];
		}
		answer[i] = matrix[i][n];
		std::cout << " |" << std::setprecision(2) << std::setw(9) << matrix[i][n];
		std::cout << '\n';
		std::cout << '\n';
	}
	for (int i = 0; i < (n+1) * 10; i++) {
		std::cout << '-';
	}
	std::cout << '\n';
	std::cout << '\n';


	///////////////////////////////////////////////////////////////////////////////////////////////////

	
	for (int i = 0; i < n; i++) {
		if (answer[i] != 0) {
			bool good = false;
			for (int j = 0; j < n; j++) {
				if (matrix[i][j] != 0) {
					good = true;
					break;
				}
			}
			if (!good) {
				std::cout << " matrix is not competible \n";
				return 0;
			}
		}

	}

	//get answer
	for (int i = n-1; i >= 0; i--) {
		for (int j = i+1; j < n; j++) {
			answer[i] -= matrix[i][j] * answer[j];
		}
		answer[i] /= matrix[i][i];
		if (matrix[i][i] == 0) {
			std::cout << "variable x" << i + 1 << " is independent (=1 for answer)\n";
			answer[i] = 1;
		}
	}
	//answer output
	double res = 0;

	for (int i = 0; i < n; i++) {
		std::cout << 'x' << i << ':';
		std::cout << std::setprecision(20) << std::setw(24)  << answer[i];
		std::cout << std::setw(5)<< 'X' << i << ':';
		std::cout << std::setprecision(20) << std::setw(24) << X[i] << "\n";
		res = std::max(res, abs(X[i] - answer[i]));
	}

	std::cout << '\n';
	std::cout << '\n';
	std::cout <<"residual :"<< res << "\n\n";
	for (int i = 0; i < (n + 1) * 10; i++) {
		std::cout << '-';
	}
	std::cout << '\n';
	std::cout << '\n';
	///////////////////////////////////////////////////////////////////////////////////////////////////

	//get determinant
	double det = 1;
	for (int i = 0; i < n; i++) {
		det *= matrix[i][i];
	}
	std::cout << "determinant : " << std::setprecision(10) << std::setw(10) << det;

	std::cout << '\n';
	std::cout << '\n';
	for (int i = 0; i < (n + 1) * 10; i++) {
		std::cout << '-';
	}
	std::cout << '\n';
	std::cout << '\n';
	///////////////////////////////////////////////////////////////////////////////////////////////////
	
	double* f = new double[n];
	for (int i = 0; i < n; i++) {
		f[i] = 0;
		for (int j = 0; j < n; j++) {
			f[i] += matrix[i][j] * answer[j];
		}
	}
	res = 0;
	//table for residual
	for (int i = 0; i < n; i++) {
		if (abs(f[i] - matrix[i][n]) > res) {
			res = f[i] - matrix[i][n];
		}
		std::cout << "Ax" << i << ':';
		std::cout << std::setprecision(20) << std::setw(24) << f[i];
		std::cout << std::setw(5)<< 'f' << i << ':';
		std::cout << std::setprecision(20) << std::setw(24) << matrix[i][n] << "\n";
	}
	std::cout << '\n';
	std::cout << '\n';
	//residual output
	std::cout << std::setprecision(7) << std::setw(9) <<"residual : "<< res;
	std::cout << '\n';
	std::cout << '\n';
	for (int i = 0; i < (n + 1) * 10; i++) {
		std::cout << '-';
	}
	std::cout << '\n';
	std::cout << '\n';
	///////////////////////////////////////////////////////////////////////////////////////////////////

	for (int i = 1; i < n; i++) {
		for (int j = i - 1; j >= 0; j--) {
			double tmp = (matrix[j][i] / matrix[i][i]) * -1;
			LineSum(matrix[j], matrix[i], n + 1, (matrix[j][i] / matrix[i][i]) * -1);
			LineSum(invers[j], invers[i], n, tmp);
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			invers[i][j] /= matrix[i][i];
		}
	}
	std::cout << "inverse :\n\n";

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << std::setprecision(2) << std::setw(9) << invers[i][j];
		}
		std::cout << '\n';
		std::cout << '\n';
	}

	for (int i = 0; i < (n + 1) * 10; i++) {
		std::cout << '-';
	}
	std::cout << '\n';
	std::cout << '\n';
	std::cout << "A^(-1) x A :\n\n";

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			double temp = 0;
			for (int h = 0; h < n; h++) {
				temp += invers[i][h] * A[h][j];
			}
			std::cout << std::setprecision(2) << std::setw(9) << temp;
		}
		std::cout << '\n';
		std::cout << '\n';
	}
}