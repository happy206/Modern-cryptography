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
int main() {
	ull g, q;
	cin >> g >> q;
	ull a, k, r;
	cin >> a >> k >> r;
	//��ģ��
	ull p = 2 * q + 1;
	//��Կv
	ull v = Quick_Power(g, q - a, p);
	//��������֤����Ϣ
	ull �� = Quick_Power(g, k, p);
	//��Alice����Ӧy
	ull y = (k + Quick_Multiply(a, r, q)) % q;
	cout << v << endl << �� << endl << y << endl;

	system("pause");
	return 0;
}