#include <iostream>
#include <cmath>
using namespace std;
double dist(Vector P0,Vector P1,Vector P2){
	Vector u1 = P0.VProd(P1);
	u1 = u1.unit();
	Vector u2 = P2.unit();
	double a = u1.DProd(u2);
	a = abs(a);
	return a;
}

double  plan(Vector P0,Vector P1,Vector P2){
	double a = dist(P0,P1,P2);
	double b = dist(P1,P2,P0);
	double c = dist(P2,P0,P1);
	double n = std::min(a,b);
	n = min(n,c);
	return n;
}