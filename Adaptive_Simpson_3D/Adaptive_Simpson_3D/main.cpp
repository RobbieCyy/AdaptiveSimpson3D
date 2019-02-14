#include <iostream>
#include <iomanip>
#include <cmath>

#define FACTOR 15
#define MAX_LEVEL 50

using namespace std;

double Simpson_1D(double(*func)(double), double a, double b) {
	return (b - a) / 6 * (func(a) + 4 * func((a + b) / 2) + func(b));
}

double Adaptive_Simpson_1D(double(*func)(double), double a, double b, double epsilon, int max_level=MAX_LEVEL, int now_level=0) {
	double m = (a + b) / 2;
	double l_result=Simpson_1D(func, a, m), r_result=Simpson_1D(func, m, b), result=Simpson_1D(func, a, b);
	/*if (now_level > max_level) {
		//cout << "Reached maximum depth." << now_level << ' ' << max_level << endl;
		return result;
	}*/
	if (abs(result - l_result - r_result) < FACTOR * epsilon) {
		result = l_result + r_result - (result - l_result - r_result) / FACTOR;
		cout << now_level << endl;
	}
	else {
		result = Adaptive_Simpson_1D(func, a, m, epsilon / 2, max_level, now_level + 1) + Adaptive_Simpson_1D(func, m, b, epsilon / 2, now_level + 1);
	}
	return result;
}

double Myfunc(double x) {
	return cos(1 / x) / x;
	//return 1 + x * sin(10 / (x * x)) * pow(x, 2 * sin(x) / tan(x)) / tan(x);
	//return exp(x);
}

int main() {
	cout << setprecision(10) << Adaptive_Simpson_1D(Myfunc, 0.0001, 2.8, 0.00000001) << endl;
	//system("pause");
	return 0;
}