#include "pch.h"
#include "SystemOfLinearEquation.h"

SystemOfLinearEquation::SystemOfLinearEquation(vector<vector<double>> a) {
	int m = size(a);
	if (m < 1) throw logic_error("Система пуста");
	int n = size(a[0]);
	for (int z = 1;z < m;z++) if (size(a[z]) != n) throw invalid_argument("Размеры уравнений не совпадают");
	n--;
	vector<LinearEquation> s;
	for (int z = 0;z < m;z++) {
		LinearEquation e(a[z]);
		s.push_back(e);
	}
	this->system = s;
	this->m = m;
	this->n = n;
}
SystemOfLinearEquation::SystemOfLinearEquation(SystemOfLinearEquation& s) {
	this->system = s.system;
	this->m = s.m;
	this->n = s.n;
}
SystemOfLinearEquation& SystemOfLinearEquation::operator = (const SystemOfLinearEquation& s) {
	this->system = s.system;
	this->m = s.m;
	this->n = s.n;
	return *this;
}
LinearEquation SystemOfLinearEquation::operator [] (int i) const {
	return this->system[i];
}
LinearEquation& SystemOfLinearEquation::operator [] (int i) {
	return this->system[i];
}
SystemOfLinearEquation SystemOfLinearEquation::to_stairs() {
	SystemOfLinearEquation s = *this;
	vector<double> d = { 1.1, 2.2, 3.3 };
	LinearEquation e(d);
	int used_eq = 0;
	int x = 0, eq = 0;
	while (x<n) {
		while (eq<m && s[eq][x] == 0) eq++;
		if (eq < m) {
			e = s[used_eq];
			s[used_eq] = s[eq];
			s[eq] = e;
			s[used_eq] *= 1.0 / s[eq][x];
			for (int z = used_eq+1;z < m;z++) {
				s[z] -= s[used_eq] * s[z][x];
			}
			used_eq++;
		}
		x++;eq = used_eq;
	}
	return s;
}
vector<vector<double>> SystemOfLinearEquation::find_solution(bool& is_val) {
	SystemOfLinearEquation s = *this;
	s = s.to_stairs();
	vector<double> d (s.n+1,0);
	LinearEquation teta(d);
	vector<vector<double>> sol;
	is_val = 1;
	int p = m - 1,n1=n-1;
	for (int z = m-1;z >= 0;z--) {
		teta[n] = s[z][n];
		if (s[z] == teta) {
			if (teta[n] == 0) {
				s.del_line(z);
			}
			else {
				is_val = 0;
				return sol;
			}
		}
		teta[n] = 0;
	}
	for (int z = 0;z < s.n;z++) {
		sol.push_back(d);
		sol[z][z] = 1;
	}
	vector<int> subordinates;
	vector<vector<double>> matrix;
	vector<double> d1;
	for (int z = 0;z < s.n;z++) {
		d1.clear();
		for (int v = 0;v < s.m;v++) {
			d1.push_back(s[v][z]);
		}
		matrix.push_back(d1);
	}
	subordinates = chose_subordinates(matrix,s.m,subordinates,s.n);
	int sub = s.m,a;
	for (int z = 0;z < sub;z++) {
		a = subordinates[z];
		for (int x = 0;x < s.n;x++) {
			for (int v = 0;v < s.n+1;v++) {
				if (a != x) {
					sol[a][v] += -sol[x][v] * s[sub - 1 - z][x] / s[sub - 1 - z][a];
				}
			}
			
		}
		sol[a][n] += s[sub - 1 - z][n] / s[sub - 1 - z][a];
		sol[a][a] = 0;
	}
	return sol;
}
double det(vector<vector<double>> v) {
	int n = size(v);
	if (n == 1) return v[0][0];
	vector<vector<double>> v1;
	vector<double> a;
	double ans = 0;
	int f;
	for (int z = 0;z < n;z++) {
		v1.clear();
		
		for (int x = 0;x < n;x++) {
			if (x != z) {
				a.clear();
				for (int x1 = 1;x1 < n;x1++) {
					a.push_back(v[x][x1]);
				}
				v1.push_back(a);
			}
		}
		f = (1 + (-2 * (z % 2 != 0)));
		ans += v[z][0] * f * det(v1);
	}
	return ans;
}
void SystemOfLinearEquation::del_line(int i) {
	SystemOfLinearEquation s(*this);
	vector<LinearEquation> newsys;
	for (int z = 0;z < m;z++) {
		if (z != i) newsys.push_back(s[z]);
	}
	this->system = newsys;
	this->m--;
}
vector<int> chose_subordinates(vector<vector<double>> matr,int m, vector<int> ans,int last) {
	vector<int> ans1 = { -1 };
	if (size(ans) == m) {
		vector<vector<double>> ds;
		for (int z = 0;z < m;z++) {
			ds.push_back(matr[ans[z]]);
		}
		double d = det(ds);
		if (d) {
			return ans;
		}
	}
	else {
		int n1 = size(ans);
		ans.push_back(-1);
		for (int z = last - 1;z >= 0;z--) {
			ans[n1] = z;
			ans1 = chose_subordinates(matr, m, ans,z);
			if (ans1[0] != -1) return ans1;
		}
	}
	return ans1;
}