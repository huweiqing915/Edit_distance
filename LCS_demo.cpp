#include <iostream>
#include <string>
#include <string.h>

#include <queue>
#include <algorithm>

using namespace std;

inline int MAX(int a, int b) {
	return a > b ? a : b;
}

int memo[100][100]; //暂存结果的集合

int LongestCommonSequence(const string &a, const string &b, int i, int j) {
	if (i == 0 || j == 0) {
		return 0;
	}

	if (memo[i][j] == -1) {	//缓存中没有结果，需要自己计算

		if (a[i - 1] == b[j - 1]) {
			return LongestCommonSequence(a, b, i - 1, j - 1) + 1;
		}

		return MAX(LongestCommonSequence(a, b, i, j - 1),
				LongestCommonSequence(a, b, i - 1, j));
	} else {	//直接返回结果
		return memo[i][j];
	}
}

int LCS(const string &a, const string &b) {
	int memo[100][100];	//暂存结果

	// memo[i][0] = 0
	for (int i = 0; i <= a.size(); ++i) {
		memo[i][0] = 0;
	}
	for (int j = 0; j <= b.size(); ++j) {
		memo[0][j] = 0;
	}

	for (int i = 1; i <= a.size(); ++i) {
		for (int j = 1; j <= b.size(); ++j) {
			if (a[i - 1] == b[j - 1]) {
				memo[i][j] = memo[i - 1][j - 1] + 1;
			} else {
				memo[i][j] = MAX(memo[i - 1][j], memo[i][j - 1]);
			}
		}
	}

	return memo[a.size()][b.size()];

}

struct Student{
	int _id;
	string _name;

//	bool operator<(const Student &other) const{
//		return _id < other._id;
//	}
	Student(int id, const string name):_id(id), _name(name){

	}

};


//这是个函数对象，他实现了Student的比较规则
struct compare{
	bool operator()(const Student &a, const Student &b){
		return a._id < b._id;
	}
};

int main(int argc, char **argv) {
//	memset(memo, 0xff, 100 * 100 * sizeof(int));
//
//	string a = "abcbdab";
//	string b = "bdcaba";
//	int ret = LongestCommonSequence(a, b, a.size(), b.size());
//
//	cout << ret << endl;
//
//	ret = LCS(a, b);
//	cout << ret << endl;


//	priority_queue<int, vector<int>, less<int> > q;
//
//	q.push(13);
//	q.push(23);
//
//	cout << q.top() << endl;



	//建立一个大根堆
	priority_queue<Student, vector<Student>, compare > q;

	q.push(Student(1, "hello"));
	q.push(Student(12, "test"));
	q.push(Student(9, "test"));

	Student tmp = q.top();

	cout << tmp._id << endl;

	//其他方式
	//priority_queue<Student, vector<Student>, less<Student> > q;
	//这种需要重载Student的<操作符

}
