#include<iostream>
using namespace std;
typedef unsigned long long  ull;
//���ٻ�ȡģ
ull Quick_Multiply(ull a, ull b, ull mod) {
	ull result = 0;
	while (b) {
		if (b & 1) {
			result = (result % mod) + (a % mod);
		}
		a = (a * 2) % mod;
		b >>= 1;
	}
	return result % mod;
}
//������ȡģ
ull Quick_Power(ull a, ull n, ull mod) {
	ull result = 1;
	while (n) {
		if (n & 1) {
			result = Quick_Multiply(a, result, mod);//result=(result*a)%mod
		}
		a = Quick_Multiply(a, a, mod);//a=(a*a)%mod
		n >>= 1;
	}
	return result % mod;
}
//ŷ������㷨
ull extendedGCD(ull a, ull b, long long& x, long long& y) {
	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}
	long long x1, y1;
	ull gcd = extendedGCD(b % a, a, x1, y1);

	x = y1  - (b / a) * x1;
	y = x1;

	return gcd;
}
//����Ԫ
ull modInverse(ull a, ull m) {
	long long x, y;
	ull gcd = extendedGCD(a, m, x, y);

	if (gcd != 1) {
		cout << "��Ԫ������" << endl;
		return 0; 
	}
	else {
		ull result = (x % m + m) % m;
		return result;
	}
}
int main() {
	ull g, q, v;
	cin >> g >> q >> v;
	ull r1, y1, r2, y2;
	cin >> r1 >> y1 >> r2 >> y2;
    //����y1-y2
	ull y;
	while (y1 < y2) {
		y1 += q;
	}
	y = (y1  - y2 ) % q;
	//����r1-r2
	ull r;
	while (r1 < r2) {
		r1 += q;
	}
	r = (r1  - r2) % q;
	//���㣨r1-r2)����Ԫ
	ull Inverse = modInverse(r, q);
	//��˽Կ
	ull a = Quick_Multiply(y, Inverse, q);
	cout << a << endl;
	system("pause");
	return 0;
}