#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <iomanip>

double* LineSum(double* a, double * b, double n, double mult) {
	for (int i = 0; i < n; i++) {
		a[i] += b[i] * mult;
		if (abs(a[i]) < 0.0000000001) a[i] = 0;
	}
	return a;
}

int main() {
	srand(time(0));
	std::ifstream input("input.txt");
	int n;
	n = 10;
	double** matrix = new double*[n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new double[n + 1];
	}
	double** obr = new double* [n];
	for (int i = 0; i < n; i++) {
		obr[i] = new double[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			obr[i][j] = 0;
		}
		obr[i][i] = 1;
	}

	//matrix input
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = (rand()%1001)/100.;
		}
	}

	//vector input
	for (int i = 0; i < n; i++) {
		matrix[i][n] = (rand() % 1001) / 100.;;
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
	int z = 0;
	for (int i = 0; i < n, z < n; i++ , z++) {

		bool good = true;
		if (matrix[i][z] == 0) {
			good = false;

			for (int j = i + 1; j < n; j++) {
				if (matrix[j][z] != 0) {
					LineSum(matrix[i], matrix[j], n + 1, 1);
					good = true;
					break;
				}
			}

		}
		if (!good) {
			z++;
			continue;
		}

		for (int j = i + 1; j < n; j++) {
			double tmp = (matrix[j][z] / matrix[i][z]) * -1;
			LineSum(matrix[j], matrix[i], 1 + n, tmp);
			LineSum(obr[j], obr[i], n, tmp);
		}

		/*for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				std::cout << std::setprecision(2) << std::setw(9) << obr[i][j];
			}
			std::cout << '\n';
			std::cout << '\n';
		}
		for (int i = 0; i < (n + 1) * 10; i++) {
			std::cout << '-';
		}
		std::cout << '\n';
		std::cout << '\n';*/
	}
	double* answer = new double[n];
	z--;


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
	for (int i = 0; i < n; i++) {
		std::cout << 'x' << i << ':';
		std::cout << std::setprecision(2) << std::setw(9)  << answer[i]<<"\n";
	}

	std::cout << '\n';
	std::cout << '\n';
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
	std::cout << "determinant : " << std::setprecision(10) << std::setw(10) << det << "\n";

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
	double res = 0;
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
			LineSum(matrix[j], matrix[i], 1 + n, (matrix[j][i] / matrix[i][i]) * -1);
			LineSum(obr[j], obr[i], n, tmp);
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << std::setprecision(2) << std::setw(9) << obr[i][j];
		}
		std::cout << '\n';
		std::cout << '\n';
	}
}