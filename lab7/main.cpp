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

double F(double x){
	return pow(x, 5) - 7*pow(x, 2) + 3;
}

double BinSearch(double l, double r, int counter = 0){
	cout.precision(2);
	cout << setw(8) <<  counter << "|" << setw(8) << l << "|" << setw(8) << r << "|" << setw(8) << (l + r)/2 << "|";
	cout << setw(8) << F(l) << "|" << setw(8) << F(r) << "|" << setw(8) << F((l + r)/2) << "|" << setw(8) << (r - l) << "\n";
	double mid = (r + l)/2;
	fprintf(table1, "%d & %.3f & %.3f & %.3f & %.3f & %.3f & %.3f & %.3f \\\\\n", counter, l, r, mid, F(l), F(r), F(mid), r - l);

	if(abs(F(mid)) <  0.01 || counter > 1000) return (r + l)/2;
	if(F(l) * F(mid) < 0) return BinSearch(l, mid, counter + 1);
	else return BinSearch(mid, r, counter + 1);
}

int main(){
	table1 = fopen("table1.txt", "w+");
	if(table1 == NULL) return 1;
	cout << setw(9) << "k" << setw(9) << "a"<< setw(9) << "b"<< setw(9) << "mid"<< setw(9) << "F(a)"<< setw(9) << "F(b)";
	cout << setw(9) << "F(mid)" << setw(10) << "b - a\n\n";

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
