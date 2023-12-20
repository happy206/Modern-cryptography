#include<iostream>
#include<string>
#include<sstream>
#include<set>
#include<vector>
#include <algorithm>
using namespace std;
//是否属于访问结构
bool inclue(set<int>a, vector<set<int>>clue) {
	for (int i = 0; i < clue.size(); i++) {
		//第一个集合是否包含第二个集合
		if (includes(a.begin(), a.end(), clue[i].begin(), clue[i].end())) {
			return true;		  
		}
	}
	return false;
}
//找{WXY}
void find_WYZ(int w, int x, int y, vector<int>&W, vector<int>&X, vector<int>&Y, vector<int>&Z, vector<set<int>>clue2, vector<set<int>>clue3, set<int>number) {
	set<int>WYZ = { w,y };
	for (auto it = number.begin(); it != number.end(); ++it) {
		if (*it == w || *it == y) {
			continue;
		}
		else {
			int z = *it;
			WYZ.insert(z);
			if (inclue(WYZ, clue2) || inclue(WYZ, clue3)) {
				set<int>WY = { w,y };
				set<int>WZ = { w,z };
				if (!inclue(WY, clue2) && !inclue(WZ, clue2)) {
					W.push_back(w);
					X.push_back(x);
					Y.push_back(y);
					Z.push_back(z);
				}
			}
			else {
				WYZ.erase(z);
			}
		}
	}
}
int main() {
	/*
	思路如下:
	想满足定理13.9的条件，需根据最小非授权子集来构造{W,X}、{X,Y}和{W,Y,Z}。而如果
	{W}、{X}、{Y}、{Z}任意一个是最小非授权子集，则不可能满足{W,Y}、{X}、{W,Z}不属于
	访问结构这一条件，所以{W，X}和{X，Y}一定是最小非授权子集。

	而{W,Y,Z}要么是最小授权子集，要么是由包含两个元素的最小非授权子集任加一个元素构成的

	基于上，我们只需提取包含两个元素和三个元素的最小非授权子集来找证据即可。
	*/
	cout << "Input.in" << endl;
	//参与者数量
	int n;
	cin >> n;
	//授权子集个数
	int m;
	cin >> m;
	//跳过回车
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//可选的用户序号（即元素数量等于2或3的最小非授权子集中的用户）
	//这样选的{X}一定不属于访问结构
	set<int>number;
	//最小授权子集集合
	set<int>* Authorized_subsets = new set<int>[m];
	//线索2(即元素数量等于2的最小非授权子集的集合）
	vector<set<int>>clue2;
	//线索3(即元素数量等于3的最小非授权子集的集合）
	vector<set<int>>clue3;
	//处理不规则输入
	for (int i = 0; i < m; i++) {
		string line;
		getline(cin, line);
		stringstream ss(line);
		//获得用空格分隔的数字
		while (ss >> line) {
			Authorized_subsets[i].insert(stoi(line));//将字符串转化为整数
		}
		if (Authorized_subsets[i].size() == 2) {
			clue2.push_back(Authorized_subsets[i]);
			number.insert(Authorized_subsets[i].begin(), Authorized_subsets[i].end());
		}
		if (Authorized_subsets[i].size() == 3) {
			clue3.push_back(Authorized_subsets[i]);
			number.insert(Authorized_subsets[i].begin(), Authorized_subsets[i].end());
		}
	}
	cout << "Output.out" << endl;
	//W,X,Y,Z
	vector<int>W;
	vector<int>X;
	vector<int>Y;
	vector<int>Z;
	int w, x, y, z;
	for (int i = 0; i < clue2.size(); i++) {
		//两个只有两个元素的最小非授权子集共有的那个元素，即X
		set<int> commonElement;
		//两个只有两个元素的最小非授权子集不相交的两个元素，即W,Y
		set<int> disjointElements;
		for (int j = i+1; j < clue2.size(); j++) {
	        //获取两个set的交集
			set_intersection(clue2[i].begin(), clue2[i].end(), clue2[j].begin(), clue2[j].end(), inserter(commonElement, commonElement.begin()));
			if (commonElement.size() == 1) {
				x = *commonElement.begin();
				// 获取两个set的对称差集
				set_symmetric_difference(clue2[i].begin(), clue2[i].end(), clue2[j].begin(), clue2[j].end(), inserter(disjointElements, disjointElements.begin()));
				w = *disjointElements.begin();
				y = *next(disjointElements.begin());
				find_WYZ(w, x, y, W, X, Y, Z, clue2, clue3, number);
				find_WYZ(y, x, w, W, X, Y, Z, clue2, clue3, number);
			}
		}
	}
	// 创建一个索引数组
	vector<int> indices(W.size());
	for (int i = 0; i < indices.size(); ++i) {
		indices[i] = i;
	}
	// 使用 lambda 表达式作为排序谓词,排序规则是按照W中对应的元素大小排序
	sort(indices.begin(), indices.end(), [&W](int a, int b) {
		return W[a] < W[b];
	});
	for (int i = 0; i < indices.size(); i++) {
		cout << W[indices[i]] << " " << X[indices[i]] << " " << Y[indices[i]] << " " << Z[indices[i]] << endl;
	}
	cout << "#" << endl;
	system("pause");
	return 0;
}