#include<iostream>
#include<string>
#include<sstream>
#include<set>
#include<vector>
#include <algorithm>
using namespace std;
//�Ƿ����ڷ��ʽṹ
bool inclue(set<int>a, vector<set<int>>clue) {
	for (int i = 0; i < clue.size(); i++) {
		//��һ�������Ƿ�����ڶ�������
		if (includes(a.begin(), a.end(), clue[i].begin(), clue[i].end())) {
			return true;		  
		}
	}
	return false;
}
//��{WXY}
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
	˼·����:
	�����㶨��13.9���������������С����Ȩ�Ӽ�������{W,X}��{X,Y}��{W,Y,Z}�������
	{W}��{X}��{Y}��{Z}����һ������С����Ȩ�Ӽ����򲻿�������{W,Y}��{X}��{W,Z}������
	���ʽṹ��һ����������{W��X}��{X��Y}һ������С����Ȩ�Ӽ���

	��{W,Y,Z}Ҫô����С��Ȩ�Ӽ���Ҫô���ɰ�������Ԫ�ص���С����Ȩ�Ӽ��μ�һ��Ԫ�ع��ɵ�

	�����ϣ�����ֻ����ȡ��������Ԫ�غ�����Ԫ�ص���С����Ȩ�Ӽ�����֤�ݼ��ɡ�
	*/
	cout << "Input.in" << endl;
	//����������
	int n;
	cin >> n;
	//��Ȩ�Ӽ�����
	int m;
	cin >> m;
	//�����س�
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//��ѡ���û���ţ���Ԫ����������2��3����С����Ȩ�Ӽ��е��û���
	//����ѡ��{X}һ�������ڷ��ʽṹ
	set<int>number;
	//��С��Ȩ�Ӽ�����
	set<int>* Authorized_subsets = new set<int>[m];
	//����2(��Ԫ����������2����С����Ȩ�Ӽ��ļ��ϣ�
	vector<set<int>>clue2;
	//����3(��Ԫ����������3����С����Ȩ�Ӽ��ļ��ϣ�
	vector<set<int>>clue3;
	//������������
	for (int i = 0; i < m; i++) {
		string line;
		getline(cin, line);
		stringstream ss(line);
		//����ÿո�ָ�������
		while (ss >> line) {
			Authorized_subsets[i].insert(stoi(line));//���ַ���ת��Ϊ����
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
		//����ֻ������Ԫ�ص���С����Ȩ�Ӽ����е��Ǹ�Ԫ�أ���X
		set<int> commonElement;
		//����ֻ������Ԫ�ص���С����Ȩ�Ӽ����ཻ������Ԫ�أ���W,Y
		set<int> disjointElements;
		for (int j = i+1; j < clue2.size(); j++) {
	        //��ȡ����set�Ľ���
			set_intersection(clue2[i].begin(), clue2[i].end(), clue2[j].begin(), clue2[j].end(), inserter(commonElement, commonElement.begin()));
			if (commonElement.size() == 1) {
				x = *commonElement.begin();
				// ��ȡ����set�ĶԳƲ
				set_symmetric_difference(clue2[i].begin(), clue2[i].end(), clue2[j].begin(), clue2[j].end(), inserter(disjointElements, disjointElements.begin()));
				w = *disjointElements.begin();
				y = *next(disjointElements.begin());
				find_WYZ(w, x, y, W, X, Y, Z, clue2, clue3, number);
				find_WYZ(y, x, w, W, X, Y, Z, clue2, clue3, number);
			}
		}
	}
	// ����һ����������
	vector<int> indices(W.size());
	for (int i = 0; i < indices.size(); ++i) {
		indices[i] = i;
	}
	// ʹ�� lambda ���ʽ��Ϊ����ν��,��������ǰ���W�ж�Ӧ��Ԫ�ش�С����
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