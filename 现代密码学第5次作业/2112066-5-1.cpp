#include<iostream>
using namespace std;
typedef unsigned long long ull;
//快速积取模
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
//快速幂取模
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
//欧几里得算法
ull extendedGCD(ull a, ull b, long long& x, long long& y) {
	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}
	long long x1, y1;
	ull gcd = extendedGCD(b % a, a, x1, y1);

	x = y1 - (b / a) * x1;
	y = x1;

	return gcd;
}
//求逆元
ull modInverse(ull a, ull m) {
	long long x, y;
	ull gcd = extendedGCD(a, m, x, y);

	if (gcd != 1) {
		cout << "逆元不存在" << endl;
		return 0;
	}
	else {
		while (x < 0) {
			x += m;
		}
		ull result = x % m;
		return result;
	}
}
int main() {
	ull t, w, p;
	cin >> t >> w >> p;
	ull* x = new ull[t + 1];
	ull* y = new ull[t + 1];
	for (ull i = 1; i <= t; i++) {
		cin >> x[i] >> y[i];
	}
	ull xx;
	cin >> xx;
	//计算K
	ull K = 0;
	for (ull j = 1; j <= t; j++) {
		ull temp = y[j];
		for (ull k = 1; k <= t; k++) {
			if (k == j)continue;
			//求分母逆元
			ull Inverse = modInverse((x[k] + p - x[j]) % p, p);
			temp = Quick_Multiply(temp, Quick_Multiply(x[k], Inverse, p), p);
		}
		K += temp;
		K %= p;
	}
	cout << K << endl;
	//计算y'
	ull yy = 0;
	for (ull j = 1; j <= t; j++) {
		ull temp = y[j];
		for (ull k = 1; k <= t; k++) {
			if (k == j)continue;
			//求分子
			ull molecule = (xx + p - x[k]) % p;
			//求分母逆元
			ull Inverse = modInverse((x[j] + p - x[k]) % p, p);
			temp = Quick_Multiply(temp, Quick_Multiply(molecule, Inverse, p), p);
		}
		yy += temp;
		yy %= p;
	}
	cout << yy << endl;
	delete[]x;
	delete[]y;
	system("pause");
	return 0;
}