#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
//Ѱ�һ�
vector<set<int>> find_basis(set<int>* sets , int x) {
    // �������м��ϣ��ҵ��������������Ӽ��ļ���
    vector<set<int>> basis;
    for (int i = 0; i < x; i++) {
        bool isInclude = false;
        for (int j = 0; j < x; j++) {
            if (j == i) {
                continue;
            }
            //��һ�������Ƿ�����ڶ�������
            if (includes(sets[i].begin(), sets[i].end(), sets[j].begin(), sets[j].end())) {
                isInclude = true;
                break;
            }
        }
        if (!isInclude) {
            basis.push_back(sets[i]);
        }
    }
    return basis;
}
//ɾ����ͬ������������ϵļ���
void removeDuplicateSets(vector<set<int>>& v) {
    for (int i = 0; i <= v.size() - 1; i++) {
        for (int j = 0; j <= v.size() - 1; j++) {
            if (i == j) {
                continue;
            }
            if (includes(v[i].begin(), v[i].end(), v[j].begin(), v[j].end())) {
                v.erase(v.begin() + i);
                i--;
                break;
            }
        }
    }
}
//�����ȡ��ʽ֮��Ĳ����㣨������Ǻ�ȡ��ʽ��
vector<set<int>>AND(vector<set<int>>CNF1, vector<set<int>>CNF2) {
    vector<set<int>>result;
    for (const auto& set1 : CNF1) {
        for (const auto& set2 : CNF2) {
            set<int>temp;
            set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(temp, temp.begin()));
            result.push_back(temp);
        }
    }
    removeDuplicateSets(result);
    return result;
}
//����ȡ��ʽת��Ϊ��ȡ��ʽ
vector<set<int>>DNF_TO_CNF(vector<set<int>> DNF) {
    if (DNF.size() == 1) {
        return DNF;
    }
    //��ȡ��ʽ
    vector<set<int>>CNF;
    for (const auto& p0 : DNF[0]) {
        set<int>temp1;
        temp1.insert(p0);
        CNF.push_back(temp1);
    }
    DNF.erase(DNF.begin());
    while (true) {
        if (DNF.size() == 0) {
            return CNF;
        }
        vector<set<int>>temp_CNF;
        for (const auto& p0 : DNF[0]) {
            set<int>temp1;
            temp1.insert(p0);
            temp_CNF.push_back(temp1);
        }
        CNF = AND(CNF, temp_CNF);
        DNF.erase(DNF.begin());
    }
}
int main() {
    cout << "Input.in" << endl;
	//����������
	int n;
	cin >> n;
	//��Ȩ�Ӽ�����
	int x;
	cin >> x;
    //�����س�
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//��Ȩ�Ӽ�����
	set<int>* Authorized_subsets = new set<int>[x];
	//������������
    for (int i = 0; i < x; i++) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        //����ÿո�ָ�������
        while (ss >> line) {
            Authorized_subsets[i].insert(stoi(line));//���ַ���ת��Ϊ����
        }
    }
    cout << "Output.out" << endl;
    //�õ���
    vector<set<int>>basis = find_basis(Authorized_subsets, x);
    //<algorithm>��sort()���������ǰ���ҵҪ��������������
    sort(basis.begin(), basis.end());
    // ��������Ľ��  
    for (const auto& set : basis) {
        for (const auto& number : set) {
            cout << number << " ";
        }
        cout << endl;
    }
    cout << "#" << endl;
    //����ȡ��ʽ��ɺ�ȡ��ʽ
    vector<set<int>>CNF = DNF_TO_CNF(basis);
    sort(CNF.begin(), CNF.end());
     // ��������Ľ��  
    for (const auto& set : CNF) {
        for (const auto& number : set) {
            cout << number << " ";
        }
        cout << endl;
    }
    cout << "#" << endl;
    //�ַ�����
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= CNF.size() - 1; j++) {
            if (CNF[j].find(i) != CNF[j].end()) {
                cout << j + 1 << " ";
            }
        }
        cout << endl;
    }
    cout << "#" << endl;
	system("pause");
	return 0;
}
