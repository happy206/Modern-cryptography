#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
//寻找基
vector<set<int>> find_basis(set<int>* sets , int x) {
    // 遍历所有集合，找到不是其他集合子集的集合
    vector<set<int>> basis;
    for (int i = 0; i < x; i++) {
        bool isInclude = false;
        for (int j = 0; j < x; j++) {
            if (j == i) {
                continue;
            }
            //第一个集合是否包含第二个集合
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
//删除相同或包含其他集合的集合
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
//计算合取范式之间的并运算（结果还是合取范式）
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
//将析取范式转化为合取范式
vector<set<int>>DNF_TO_CNF(vector<set<int>> DNF) {
    if (DNF.size() == 1) {
        return DNF;
    }
    //合取范式
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
	//参与者数量
	int n;
	cin >> n;
	//授权子集个数
	int x;
	cin >> x;
    //跳过回车
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//授权子集集合
	set<int>* Authorized_subsets = new set<int>[x];
	//处理不规则输入
    for (int i = 0; i < x; i++) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        //获得用空格分隔的数字
        while (ss >> line) {
            Authorized_subsets[i].insert(stoi(line));//将字符串转化为整数
        }
    }
    cout << "Output.out" << endl;
    //得到基
    vector<set<int>>basis = find_basis(Authorized_subsets, x);
    //<algorithm>中sort()函数正好是按作业要求那样进行排序
    sort(basis.begin(), basis.end());
    // 输出排序后的结果  
    for (const auto& set : basis) {
        for (const auto& number : set) {
            cout << number << " ";
        }
        cout << endl;
    }
    cout << "#" << endl;
    //将析取范式变成合取范式
    vector<set<int>>CNF = DNF_TO_CNF(basis);
    sort(CNF.begin(), CNF.end());
     // 输出排序后的结果  
    for (const auto& set : CNF) {
        for (const auto& number : set) {
            cout << number << " ";
        }
        cout << endl;
    }
    cout << "#" << endl;
    //分发规则
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
