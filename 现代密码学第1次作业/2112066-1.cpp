#include<iostream>
using namespace std;
//���ٻ�ȡģ
unsigned long long Quick_Multiply(unsigned long long a, unsigned long long b, unsigned long long mod) {
	unsigned long long result = 0;
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
unsigned long long Quick_Power(unsigned long long a, unsigned long long n, unsigned long long mod) {
	unsigned long long result = 1;
	while (n) {
		if (n & 1) {
			result = Quick_Multiply(a, result, mod);//result=(result*a)%mod
		}
		a = Quick_Multiply(a, a, mod);//a=(a*a)%mod
		n >>= 1;
	}
	return result % mod;
}
void RSA_Generator(unsigned long long N, unsigned long long p, unsigned long long q, unsigned long long e, unsigned long long s0, int i) {
	unsigned long long T=1; // ����
	unsigned long long s1 = Quick_Power(s0, e, N);
	bool first = true;
	unsigned long long s; // �м����
	while (true) {
		//��һ��ѭ��
		if (first) {
			s = s1;
			first = false;
		}
		else {
			s = Quick_Power(s, e, N);
			if (s != s1) {
				T++;
			}
			else {
				cout << T << endl;
				break;
			}
		}
	}
	int  count = 0; // ���������������ǰi������
	first = true;
	while (true) {
		count++;
		if (count > i) {
			cout << endl;
			break;
		}
		//��һ��ѭ��
		if (first) {
			s = s1;
			first = false;
			
		}
		else {
			s = Quick_Power(s, e, N);
		}	
		cout << s % 2;
	}
}
int main() {
	unsigned long long N, p, q;
	cin >> N >> p >> q;
	unsigned long long e, s0;
	int i;
	cin >> e >> s0 >> i;
	RSA_Generator(N, p, q, e, s0, i);
	system("pause");
	return 0;
}