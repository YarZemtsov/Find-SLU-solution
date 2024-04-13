// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
//
// JYJ HF<JNFTN!!!!

#include <iostream>
#include "../OOP L5t1/LinearEquation.h"
#include "../OOP L5t1/SystemOfLinearEquation.h"
int main()
{
	vector<double> b0 = { 2,3,4,5 }, b1 = { 0,0,1,5 }, b2 = { 0,0,1 };
	SystemOfLinearEquation s({ b0,b1 });
	bool c = 1;

	SystemOfLinearEquation w = s;
	vector<vector<double>> ans = w.find_solution(c);
	int n = size(ans),n1=1;
	if (n) n1 = size(ans[0]);
	else cout << "Invalid System";
	for (int z = 0; z < n; z++) {
		cout << "x" << z + 1 << " = ";
		for (int v = 0; v < n1-1; v++) {
			if (ans[z][v]) {
				cout << "+ (" << ans[z][v] << ")x" << v + 1 << " ";
			}
		}
		cout << "+ (" << ans[z][n1 - 1] << ") ";
		cout << "\n";
	}
	return 0;
}
