#define FACTOR 10
#define doubel double
#include <iostream>
#include <ctime>

using namespace std;

long long Func_count = 0;

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
	//cout << "level=" << level << " a=[" << a[0] << ' ' << a[1] << ' ' << a[2] << ' ' << "], b=[" << b[0] << ' ' << b[1] << ' ' << b[2] << "]" << endl;
	double result = Rectangular_3D(a, b, f);
	double sub_result = 0;
	if (level > 20) {
		return result;
	}
	for (int x = 0; x < 2; ++x) {
		for (int y = 0; y < 2; ++y) {
			for (int z = 0; z < 2; ++z) {
				int n1[3] = { 0 };
				int n2[3] = { 0 };
				n1[0] = x, n1[1] = y, n1[2] = z;
				n2[0] = x + 1, n2[1] = y + 1, n2[2] = z + 1;
				double * aa, *bb;
				aa = get_Division(a, b, n1);
				bb = get_Division(a, b, n2);
				sub_result += Rectangular_3D(aa, bb, f);
				delete aa;
				delete bb;
			}
		}
	}
	if (abs(result - sub_result) < FACTOR * epsilon) {
		//cout << "return point 1" << endl;
		return sub_result + (sub_result - result) / FACTOR;
	}
	else {
		result = 0;
		for (int x = 0; x < 2; ++x) {
			for (int y = 0; y < 2; ++y) {
				for (int z = 0; z < 2; ++z) {
					int n1[3] = {0};
					int n2[3] = {0};
					n1[0] = x, n1[1] = y, n1[2] = z;
					n2[0] = x + 1, n2[1] = y + 1, n2[2] = z + 1;
					double * aa, *bb;
					aa = get_Division(a, b, n1);
					bb = get_Division(a, b, n2);
					result += Adaptive_Rectangular_3D(aa, bb, epsilon / 8, f, level + 1);
					delete aa;
					delete bb;
				}
			}
		}
		//cout << "return point 2, level=" << level << " a=[" << a[0] << ' ' << a[1] << ' ' << a[2] << ' ' << "], b=[" << b[0] << ' ' << b[1] << ' ' << b[2] << "]" << endl;
		return result;
	}
	return result;
}

int main() {
	clock_t start, end;
	start = clock();
	
	double a[3] = { -1 , -1, -1}, b[3] = { 1, 1, 1 };

	cout << Adaptive_Rectangular_3D(a, b,0.0001, My_func3, 0) << endl;

	end = clock();
	cout << (end - start)/1000.0 << endl;
	cout << Func_count << endl;
	system("pause");
	return 0;
}