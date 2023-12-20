#include<iostream>
#include<cmath>
#include<map>
using namespace std;
//快速积取模
int Quick_Multiply(int a, int b, int mod) {
	int result = 0;
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
int Quick_Power(int a, int n, int mod) {
	int result = 1;
	while (n) {
		if (n & 1) {
			result = Quick_Multiply(a, result, mod);
		}
		a = Quick_Multiply(a, a, mod);
		n >>= 1;
	}
	return result % mod;
}
// 扩展欧几里得算法
int extendedGCD(int a, int b, int& x, int& y) {
	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}

	int x1, y1;
	int gcd = extendedGCD(b % a, a, x1, y1);

	x = y1 - (b / a) * x1;
	y = x1;

	return gcd;
}
// 求逆元
int modInverse(int a, int m) {
	int x, y;
	int gcd = extendedGCD(a, m, x, y);

	if (gcd != 1) {
		std::cerr << "逆元不存在，因为 " << a << " 和 " << m << " 不互质。" << std::endl;
		return -1; // 逆元不存在
	}

	// 确保逆元为正数
	return (x % m + m) % m;
}
//检验签名是否合法
bool is_true(int q, int γ, int δ, int g, int m, int p) {
	int temp1 = Quick_Power(q, γ, p); // 计算 q^γ mod p
	int temp2 = Quick_Power(γ, δ, p); // 计算 γ^δ mod p
	int temp3 = Quick_Power(g, m, p);  // 计算 g^m mod p
	int temp4 = Quick_Multiply(temp1, temp2, p);
	if (((temp4 - temp3) % p) == 0) {
		return true;
	}
	else {
		return false;
	}
}
//// Shanks算法
int Shank(int p, int g, int q, int& a) {
	int m = (int)ceil(sqrt(p - 1));
	map<int, int> L1;
	map<int, int> L2;
	int Inverse = modInverse(g, p);  // g 的逆元
	for (int j = 0; j <= m - 1; j++) {
		int temp1 = Quick_Power(g, m * j, p);
		int temp2 = Quick_Multiply(q, Quick_Power(Inverse, j, p), p);
		L1[temp1] = j;
		L2[temp2] = j;
	}
	map<int, int>::iterator it1;
	map<int, int>::iterator it2;
	for (it1 = L1.begin(); it1 != L1.end(); it1++) {
		for (it2 = L2.begin(); it2 != L2.end(); it2++) {
			int aa = it1->first;
			int bb = it2->first;
			if (it1->first == it2->first) {
				a = (Quick_Multiply(m, it1->second, p - 1) + it2->second) % (p - 1);
				if (a < 0) {
					a += p - 1;
				}
				return 1;
			}
		}
	}
	return -1;
}

int main() {
	int p, g, q;
	cin >> p >> g >> q;
	int m, γ, δ;
	cin >> m >> γ >> δ;
	if (is_true(q, γ, δ, g, m, p)) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}
	int a;
	if (Shank(p, g, q, a) == 1) {
		cout << a << endl;
	}
	int r;
	if (Shank(p, g, γ, r) == 1) {
		cout << r << endl;
	}
	system("pause");
	return 0;
}