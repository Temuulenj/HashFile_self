#pragma warning(disable: 4996)
#include<iostream>
#include<fstream>
using namespace std;

//结点结构体
typedef struct Node{
	string value="";
	int key=0;
	struct Node* next=NULL;
}*List;

//hash桶
static List a[13];

//hash函数
int getHash(int key) {
	return key % 13;
}

//初始化
bool initList() {
	for (int i = 0; i < 13; i++) {
		a[i] = new Node;
		a[i]->next = NULL;
	}
	return true;
}

//尾插法
void addElem(List list, List n) {
	List p = list;
	while (p->next != NULL) {
		p = p->next;
	}
	p->next = n;
}

//输入一个元素
void InsertOne() {
	cout << "key value" << endl;
	List n = new Node;
	cin >> n->key;
	cin >> n->value;
	n->next = NULL;
	int f = getHash(n->key);
	addElem(a[f], n);
}

//输出List
void disList() {
	//system("cls");
	for (int i = 0; i < 13; i++) {
		List q = a[i];
		cout << i;
		while (q->next != NULL)
		{
			q = q->next;
			cout << " -> " << q->key << "(" << q->value << ")";
		}
		cout << endl;
	}
}

//按Key查找
string SearchOfKey() {
	int key;
	cout << "请输入要查找的Key"<<endl;
	cin >> key;
	int hashKey = getHash(key);
	List p = a[hashKey];
	while (p->next!=NULL){
		p = p->next;
		if (p->key == key) {
			return p->value;
		}
	}
	return "不存在此元素";
}

void write() {
	ofstream file("hash");
	file << a;
}
void read() {
	ifstream file("hash");
	//file >> a;
}

int main() {
	if (!initList()) {
		cout << "初始化失败！";
		return -1;
	};
	InsertOne();
	cout<<SearchOfKey()<<endl<<endl;
	disList();
	return 0;
}