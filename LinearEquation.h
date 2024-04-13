#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string> 
#include <stdexcept> 
#include <sstream>
using namespace std;
class LinearEquation
{
	vector<double> elements;
public:
	LinearEquation(vector<double> a);
	LinearEquation(string s);
	LinearEquation(LinearEquation& e);
	LinearEquation& operator =(LinearEquation& e);
	vector<double> GetElements();
	int GetSize();
	LinearEquation& operator -();
	LinearEquation& operator +=(LinearEquation ei);
	LinearEquation& operator -=(LinearEquation ei);
	LinearEquation& operator *=(double a);
	LinearEquation operator +(LinearEquation e);
	LinearEquation operator -(LinearEquation e);
	LinearEquation operator *(double a);
	LinearEquation friend operator *(double a, LinearEquation e);
	bool operator == (LinearEquation e);
	bool operator != (LinearEquation e);
	double operator [](int i) const;
	double& operator [](int i);
	operator vector<double>() const;
	friend istream& operator >> (istream& in, LinearEquation& e) {
		string s;
		getline(in, s);
		LinearEquation e1(s);
		e = e1;
		return in;
	}
	friend ostream& operator << (ostream& out, LinearEquation e) {
		int n = size(e.elements);
		for (int z = 0;z < n - 1;z++) {
			out << e[z] << ' ';
		}
		out << e[n - 1];
		return out;
	}
};

