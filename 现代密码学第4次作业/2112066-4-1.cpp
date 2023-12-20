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
		while (x<0) {
			x += m;
		}
		ull result = x % m;
		return result;
	}
}
//计算组合数
ull C(ull n, ull m) {
	if (m < n - m) {
		m = n - m;
	}
	ull ans = 1;
	//计算分子的阶乘
	for (ull i = m + 1; i <= n; i++) {
		ans = ans * i;
	}

	//计算组合数
	for (ull i = 1; i <= n - m; i++) {
		ans = ans / i;
	}

	return ans;
}
int main() {
	//模数
	ull p;
	//多项式次数
	ull m;
	cin >> p >> m;
	//Z_p中的m+1个不同元素
	ull* y = new ull[m + 1];
	for (ull i = 0; i <= m; i++) {
		cin >> y[i];
	}
	//关于x的多项式
	ull** a = new ull * [m + 1];
	for (ull i = 0; i <= m; i++) {
		a[i] = new ull[m + 1];
	}
	for (ull i = 0; i <= m; i++) {
		for (ull j = 0; j <= m; j++) {
			cin >> a[i][j];
		}
	}
	//存储A（x，y）的系数
	ull** A = new ull * [m + 1];
	for (ull i = 0; i <= m; i++) {
		A[i] = new ull[m + 1];
	}
	//存储关于y多项式的系数
	ull** Y = new ull * [m + 1];
	for (int i = 0; i <= m; i++) {
		Y[i] = new ull[m + 1];
	}
	//存储（y_i - y_j )的逆元
	ull* Inverse = new ull[m + 1]; 
	//求（y_i - y_j )的逆元
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
	//计算关于y多项式的系数
	for (ull i = 0; i <= m; i++) {
		//计算第i个关于y的多项式的系数
		for (ull j = 0; j <= m; j++) {
			//计算y^j的系数(用栈来实现）
			Y[i][j] = 0;
			if (j == m) {
				Y[i][j] = Quick_Multiply(1, Inverse[i], p);
				continue;
			}
			ull* Stack = new ull[m-j+1];
			ull top = m - j;  //栈的顶部
			ull count = C(m, j);  
			ull index = 1;  //栈的索引
			Stack[0] = 0;
			// 增量
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
    //计算A(x,y)的系数
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
	//释放空间
	delete[]Inverse;
	delete[]Y;
	delete[]A;
	delete[]a;
	delete[]y;
	system("pause");
	return 0;
}