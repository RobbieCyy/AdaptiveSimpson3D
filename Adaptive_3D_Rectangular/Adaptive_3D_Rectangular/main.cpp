#define FACTOR 15
#define doubel double
#include <iostream>
#include <ctime>

using namespace std;

int Func_count = 0;

double My_func3(double *r) {
	Func_count++;
	return r[0] * r[0] + r[1] * r[1] + r[2] * r[2];
}

double Rectangular_3D(double *a, double *b, double(*f)(double *)) {
	double m[3], V = 1;
	for (int i = 0; i < 3; i++) {
		m[i] = (b[i] + a[i]) / 2;
		V *= (b[i] - a[i]);
	}
	return f(m) * V;
}

double * get_Division(double *a, double *b, int *n) {
	double * result = new double[3];
	for (int i = 0; i < 3; i++) {
		result[i] = a[i] + (b[i] - a[i]) * n[i] / 2;
	}
	return result;
}

double Adaptive_Rectangular_3D(double *a, double *b, double epsilon, double(*f)(double *), int level) {
	double result = Rectangular_3D(a, b, f);
	double sub_result = 0;
	if (level > 20) {
		return result;
	}
	for (int x = 0; x < 1; ++x) {
		for (int y = 0; y < 1; ++y) {
			for (int z = 0; z < 1; ++z) {
				int n1[3] = { 0 };
				int n2[3] = { 0 };
				n1[0] = x, n1[1] = y, n1[2] = z;
				n2[0] = x + 1, n2[1] = y + 1, n2[2] = z + 1;
				sub_result += Rectangular_3D(get_Division(a, b, n1), get_Division(a, b, n2), f);
			}
		}
	}
	if (abs(result - sub_result) < FACTOR * epsilon) {
		cout << "return point 1" << endl;
		return sub_result + (sub_result - result) / FACTOR;
	}
	else {
		result = 0;
		for (int x = 0; x < 1; ++x) {
			for (int y = 0; y < 1; ++y) {
				for (int z = 0; z < 1; ++z) {
					int n1[3] = {0};
					int n2[3] = {0};
					n1[0] = x, n1[1] = y, n1[2] = z;
					n2[0] = x + 1, n2[1] = y + 1, n2[2] = z + 1;
					result += Adaptive_Rectangular_3D(get_Division(a, b, n1), get_Division(a, b, n2), epsilon / 8, f, level + 1);
				}
			}
		}
		cout << "return point 2, level=" << level << " a=[" << a[0] << ' ' << a[1] << ' ' << a[2] << ' ' << "], b=[" << b[0] << ' ' << b[1] << ' ' << b[2] << "]" << endl;
		return result;
	}
	return result;
}

int main() {
	clock_t start, end;
	start = clock();
	
	double a[3] = { -1 , -1, -1}, b[3] = { 1, 1, 1 };

	cout << a[0] << ' ' << a[1] << ' ' << a[2] << ' ' << b[0] << ' ' << b[1] << ' ' << b[2] << endl;
	
	cout << Adaptive_Rectangular_3D(a, b,0.0001, My_func3, 0) << endl;

	end = clock();
	cout << end - start << endl;
	cout << Func_count << endl;
	system("pause");
	return 0;
}