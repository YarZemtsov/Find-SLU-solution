#include "pch.h"
#include "LinearEquation.h"
LinearEquation::LinearEquation(vector<double> a) {
	if (size(a) < 2) throw logic_error("В уравнении не может быть меньше 2 коэффициентов");
	this->elements = a;
}
LinearEquation::LinearEquation(string s) {
	vector<double> a;
	int n = s.length() + 1, p=0;
	double el = 0.0;
	bool f = 0, m = 0;
	s += " ";
	for (int z = 0;z < n;z++) {
		if (s[z] == '-') {
			if (f) throw invalid_argument("В строке какая-то хрень");
			m = 1;
		}
		else if (s[z] == '.') {
			if(!f || p) throw invalid_argument("В строке какая-то хрень");
			p = 1;
		}
		else if (isdigit(s[z])) {
			if (p) {
				p++;
			}
			f = 1;
			el = el * 10 + (int)s[z] - 48;
		}
		else if (s[z] = ' ' && f) {
			if (m) el = -el;
			if (p) {
				for (int v = 1; v < p; v++) el /= 10.0;
			}
			a.push_back(el);
			el = 0; f = 0; m = 0; p = 0;
		}
		else throw invalid_argument("В строке какая-то хрень");
	}
	if (size(a) < 2) throw logic_error("В уравнении не может быть меньше 2 коэффициентов");
	this->elements = a;
}
LinearEquation::LinearEquation(LinearEquation& e) {
	this->elements = e.elements;
}
LinearEquation& LinearEquation::operator =(LinearEquation& e) {
	this->elements = e.elements;
	return *this;
}
vector<double> LinearEquation::GetElements() {
	return this->elements;
}
int LinearEquation::GetSize() {
	return size(elements);
}
LinearEquation& LinearEquation::operator -() {
	int n = size(elements);
	for (int z = 0;z < n;z++) {
		elements[z] = -elements[z];
	}
	return *this;
}
LinearEquation& LinearEquation::operator +=(LinearEquation ei) {
	int n = size(elements), n1 = ei.GetSize();
	if (n != n1) throw logic_error("Размерности не совпадают");
	for (int z = 0;z < n;z++) {
		elements[z] += ei[z];
	}
	return *this;
}
LinearEquation& LinearEquation::operator -=(LinearEquation ei) {
	int n = size(elements), n1 = ei.GetSize();
	if (n != n1) throw logic_error("Размерности не совпадают");
	for (int z = 0;z < n;z++) {
		elements[z] -= ei[z];
	}
	return *this;
}
LinearEquation& LinearEquation::operator *=(double a) {
	int n = size(elements);
	for (int z = 0;z < n;z++) {
		elements[z] *= a;
	}
	return *this;
}
LinearEquation LinearEquation::operator + (LinearEquation e) {
	int n = size(elements), n1 = e.GetSize();
	if (n != n1) throw logic_error("Размерности не совпадают");
	LinearEquation e1(*this);
	for (int z = 0;z < n;z++) {
		e1[z] += e[z];
	}
	return e1;
}
LinearEquation LinearEquation::operator - (LinearEquation e) {
	int n = size(elements), n1 = e.GetSize();
	if (n != n1) throw logic_error("Размерности не совпадают");
	LinearEquation e1(*this);
	for (int z = 0;z < n;z++) {
		e1[z] -= e[z];
	}
	return e1;
}
LinearEquation LinearEquation::operator * (double a) {
	int n = size(elements);
	LinearEquation e(*this);
	for (int z = 0;z < n;z++) {
		e[z] *= a;
	}
	return e;
}
LinearEquation operator *(double a, LinearEquation e) {
	int n = e.GetSize();
	for (int z = 0;z < n;z++) e[z] *= a;
	return e;
}
bool LinearEquation::operator == (LinearEquation e) {
	return this->elements == e.elements;
}
bool LinearEquation::operator != (LinearEquation e) {
	return this->elements != e.elements;
}
double LinearEquation::operator [](int i) const {
	return elements[i];
}
double& LinearEquation::operator [](int i) {
	return elements[i];
}
LinearEquation::operator vector<double>() const {
	return this->elements;
}