#include<iostream>
using namespace std;
typedef unsigned long long ull;
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

	x = y1 - (b / a) * x1;
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
		while (x<0) {
			x += m;
		}
		ull result = x % m;
		return result;
	}
}
//���������
ull C(ull n, ull m) {
	if (m < n - m) {
		m = n - m;
	}
	ull ans = 1;
	//������ӵĽ׳�
	for (ull i = m + 1; i <= n; i++) {
		ans = ans * i;
	}

	//���������
	for (ull i = 1; i <= n - m; i++) {
		ans = ans / i;
	}

	return ans;
}
int main() {
	//ģ��
	ull p;
	//����ʽ����
	ull m;
	cin >> p >> m;
	//Z_p�е�m+1����ͬԪ��
	ull* y = new ull[m + 1];
	for (ull i = 0; i <= m; i++) {
		cin >> y[i];
	}
	//����x�Ķ���ʽ
	ull** a = new ull * [m + 1];
	for (ull i = 0; i <= m; i++) {
		a[i] = new ull[m + 1];
	}
	for (ull i = 0; i <= m; i++) {
		for (ull j = 0; j <= m; j++) {
			cin >> a[i][j];
		}
	}
	//�洢A��x��y����ϵ��
	ull** A = new ull * [m + 1];
	for (ull i = 0; i <= m; i++) {
		A[i] = new ull[m + 1];
	}
	//�洢����y����ʽ��ϵ��
	ull** Y = new ull * [m + 1];
	for (int i = 0; i <= m; i++) {
		Y[i] = new ull[m + 1];
	}
	//�洢��y_i - y_j )����Ԫ
	ull* Inverse = new ull[m + 1]; 
	//��y_i - y_j )����Ԫ
	for (ull i = 0; i <= m; i++) {
		ull temp = 1;
		for (ull j = 0; j <= m; j++) {
			if (j == i) {
				continue;
			}
			temp = Quick_Multiply(temp, (y[i] + p - y[j]) % p, p);
		}
		temp;
		Inverse[i] = modInverse(temp, p);
	}
	//�������y����ʽ��ϵ��
	for (ull i = 0; i <= m; i++) {
		//�����i������y�Ķ���ʽ��ϵ��
		for (ull j = 0; j <= m; j++) {
			//����y^j��ϵ��(��ջ��ʵ�֣�
			Y[i][j] = 0;
			if (j == m) {
				Y[i][j] = Quick_Multiply(1, Inverse[i], p);
				continue;
			}
			ull* Stack = new ull[m-j+1];
			ull top = m - j;  //ջ�Ķ���
			ull count = C(m, j);  
			ull index = 1;  //ջ������
			Stack[0] = 0;
			// ����
			ull* increment = new ull[m - j];
			for (ull k = 0; k <= m - j - 1; k++) {
				increment[k] = 1;
			}
			while (count-- > 0) {
				while (index <= top) {
					ull jj = increment[index - 1];
					Stack[index] = Stack[index - 1] + increment[index-1];
					ull ysd = Stack[index];
					if (Stack[index] > m + 1) {
						increment[index - 1] = 1;
						index--;
						increment[index - 1]++;
						continue;
					}
					if (Stack[index] == i+1) {
						increment[index - 1]++;
						Stack[index] += 1;
						if (Stack[index] > m+1) {
							increment[index - 1] = 1;
							index--;
							increment[index-1]++;
							continue;
						}
					}
					index++;
				}
				index--;
				increment[index - 1]++;
				ull temp = 1;
				for (ull k = 1; k <= m - j; k++) {
					temp *= (p - y[Stack[k]-1])%p;
				}
				Y[i][j] += temp;
			}
			ull h = Inverse[i];
			Y[i][j] = Quick_Multiply(Y[i][j], Inverse[i], p);
			ull o = Y[i][j];
			delete[]Stack;
		}
	}
    //����A(x,y)��ϵ��
	for (ull i = 0; i <= m; i++) {
		for (ull j = 0; j <= m; j++) {
			ull sum = 0;
			for (ull k = 0; k <= m; k++) {
				sum += a[k][i] * Y[k][j];
			}
			A[i][j] = sum % p;
		}

	}
	for (ull i = 0; i <= m; i++) {
		for (ull j = 0; j <= m; j++) {
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	//�ͷſռ�
	delete[]Inverse;
	delete[]Y;
	delete[]A;
	delete[]a;
	delete[]y;
	system("pause");
	return 0;
}