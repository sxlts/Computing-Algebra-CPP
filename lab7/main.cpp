#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>

//x^5 - 7x^2 + 3 = 0 
//[-1,0],[0,1],[1,2]
//
//x = (7x^2 - 3)^(1/5)
//[1,2]
//
//x = ((x^5 + 3)/7)^(1/2)
//[-1,0],[0,1]
//
using namespace std;

FILE *table1;
FILE *table2;
FILE *table3;
double eps = 0.0000001;
double x1_0 = -0.5;
double x2_0 = 0.5;
double x3_0 = 1.5;
double n1 = -1.0;
double n2 = 0.5;
double n3 = 2.0;

double F(double x){
	return pow(x, 5.0) - 7.0*pow(x, 2.0) + 3.0;
}
double F1(double x){
	return 5.0*pow(x, 4.0) - 14.0*x;
}
double PHI1(double x){
	return pow((pow(x, 5.0) + 3.0)/7.0, 1.0/2.0);
}
double PHI2(double x){
	return pow(7.0*pow(x, 2.0) - 3.0, 1.0/5.0);
}

double BinSearch(double l, double r, int counter = 0){
	cout.precision(4);
	cout << setw(12) <<  counter << "|" << setw(12) << l << "|" << setw(12) << r << "|" << setw(12) << (l + r)/2 << "|";
	cout << setw(12) << F(l) << "|" << setw(12) << F(r) << "|" << setw(12) << F((l + r)/2) << "|" << setw(12) << (r - l) << "\n";
	double mid = (r + l)/2;
	fprintf(table1, "%d & %.3f & %.3f & %.3f & %.3f & %.3f & %.3f & %.3f \\\\\n", counter, l, r, mid, F(l), F(r), F(mid), r - l);

	if(abs(F(mid)) <  0.01 || counter > 1000) return (r + l)/2;
	if(F(l) * F(mid) < 0) return BinSearch(l, mid, counter + 1);
	else return BinSearch(mid, r, counter + 1);
}

void dechotomy(){
	cout << setw(13) << "k" << setw(13) << "a"<< setw(13) << "b"<< setw(13) << "mid"<< setw(13) << "F(a)"<< setw(13) << "F(b)";
	cout << setw(13) << "F(mid)" << setw(14) << "b - a\n\n";

	fprintf(table1, "[-1,0]\n");

	BinSearch(-1, 0);

	cout << "\n";
	fprintf(table1, "[0,1]\n");

	BinSearch(0, 1);

	cout << "\n";
	fprintf(table1, "[1,2]\n");

	BinSearch(1, 2);

	cout << "\n";
}

void Iteration(){
	cout << setw(13) << "k" << setw(13) << "x(k)" << setw(14) << "x(k + 1)\n\n";
	cout.precision(7);
	int k = 0;
	double x_k, x_k1;

	k = 0;
	x_k = 100;
	x_k1 = x1_0;
	while(abs(x_k1 - x_k) > eps){
		x_k = x_k1;
		x_k1 = PHI1(x_k) * -1.0;
		cout << setw(12) << k << "|" <<  setw(12) << x_k << "|" <<  setw(12) << x_k1 <<"\n";
		k++;
		fprintf(table2, "%d & %.7f & %.7f \\\\\n", k, x_k1, abs(x_k - x_k1));
	}
	fprintf(table2, "\n\n");

	k = 0;
	x_k = 100;
	x_k1 = x2_0;
	cout << "\n\n";
	while(abs(x_k1 - x_k) > eps){
		x_k = x_k1;
		x_k1 = PHI1(x_k);
		cout << setw(12) << k << "|" <<  setw(12) << x_k << "|" <<  setw(12) << x_k1 <<"\n";
		k++;
		fprintf(table2, "%d & %.7f & %.7f \\\\\n", k, x_k1, abs(x_k - x_k1));
	}

	fprintf(table2, "\n\n");
	k = 0;
	x_k = 100;
	x_k1 = x3_0;
	cout << "\n\n";
	while(abs(x_k1 - x_k) > eps){
		x_k = x_k1;
		x_k1 = PHI2(x_k);
		cout << setw(12) << k << "|" <<  setw(12) << x_k << "|" <<  setw(12) << x_k1 <<"\n";
		k++;
		fprintf(table2, "%d & %.7f & %.7f \\\\\n", k, x_k1, abs(x_k - x_k1));
	}
}

void Newton(){
	cout << setw(13) << "k" << setw(13) << "x(k)" << setw(14) << "x(k + 1)\n\n";
	cout.precision(7);

	int k;
	double x_k, x_k1;

	k = 0;
	x_k = 100;
	x_k1 = n1;
	while(abs(x_k1 - x_k) > eps){
		x_k = x_k1;
		x_k1 = x_k - F(x_k)/F1(x_k);
		cout << setw(12) << k << "|" <<  setw(12) << x_k << "|" <<  setw(12) << abs(x_k - x_k1) <<"\n";
		k++;
		fprintf(table3, "%d & %.7f & %.7f \\\\\n", k, x_k1, abs(x_k - x_k1));
	}
	
	fprintf(table3, "\n\n");
	k = 0;
	x_k = 100;
	x_k1 = n2;
	cout << "\n\n";
	while(abs(x_k1 - x_k) > eps){
		x_k = x_k1;
		x_k1 = x_k - F(x_k)/F1(x_k);
		cout << setw(12) << k << "|" <<  setw(12) << x_k << "|" <<  setw(12) << abs(x_k - x_k1) <<"\n";
		k++;
		fprintf(table3, "%d & %.7f & %.7f \\\\\n", k, x_k1, abs(x_k - x_k1));
	}
	
	fprintf(table3, "\n\n");
	k = 0;
	x_k = 100;
	x_k1 = n3;
	cout << "\n\n";
	while(abs(x_k1 - x_k) > eps){
		x_k = x_k1;
		x_k1 = x_k - F(x_k)/F1(x_k);
		cout << setw(12) << k << "|" <<  setw(12) << x_k << "|" <<  setw(12) << abs(x_k - x_k1) <<"\n";
		k++;
		fprintf(table3, "%d & %.7f & %.7f \\\\\n", k, x_k1, abs(x_k - x_k1));
	}
	fprintf(table3, "\n\n");

	
}
int main(){
	table1 = fopen("table1.txt", "w+");
	table2 = fopen("table2.txt", "w+");
	table3 = fopen("table3.txt", "w+");
	if(table1 == NULL) return 1;

	dechotomy();	
	Iteration();
	Newton();

	fclose(table1);
	fclose(table2);
	fclose(table3);
	return 0;
}
