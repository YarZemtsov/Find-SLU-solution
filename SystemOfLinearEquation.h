#pragma once
#include "LinearEquation.h"
class SystemOfLinearEquation
{
	vector<LinearEquation> system;
	int n;
	int m;
public:
	SystemOfLinearEquation(vector<vector<double>> a);
	SystemOfLinearEquation(SystemOfLinearEquation& s);
	SystemOfLinearEquation& operator = (const SystemOfLinearEquation& s);
	LinearEquation operator [] (int i) const;
	LinearEquation& operator [] (int i);
	SystemOfLinearEquation to_stairs();
	vector<vector<double>> find_solution(bool& is_val);
	void del_line(int i);
	friend ostream& operator << (ostream& out, SystemOfLinearEquation s) {
		int n = size(s.system);
		for (int z = 0;z < n;z++) out << s[z] << "\n";
		return out;
	}
};
double det(vector<vector<double>> v);
vector<int> chose_subordinates(vector<vector<double>> matr, int m, vector<int> ans, int last);