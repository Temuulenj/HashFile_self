#pragma warning(disable: 4996)
#include<iostream>
#include<fstream>
using namespace std;
#define BucketSize 13

//结点结构体
typedef struct Node{
	string value="";
	int key=0;
	struct Node* next=NULL;
}*List;

//hash桶
static List a[BucketSize];

//hash函数
int getHash(int key) {
	return key % BucketSize;
}

//初始化
bool initList() {
	for (int i = 0; i < BucketSize; i++) {
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

//插入一个元素
void InsertOne() {
	cout << "key value" << endl;
	List n = new Node;
	cin >> n->key;
	cin >> n->value;
	n->next = NULL;
	int f = getHash(n->key);
	addElem(a[f], n);
	cout << "插入成功！" << endl;
}

//输出List
void disList() {
	//system("cls");
	cout << "--------------------------------------------------" << endl;
	for (int i = 0; i < BucketSize; i++) {
		List q = a[i];
		cout << i;
		while (q->next != NULL)
		{
			q = q->next;
			cout << " -> " << q->key << "(" << q->value << ")";
		}
		cout << endl;
	}
	cout << "--------------------------------------------------" << endl;
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


//按值查找
void SearchOfValue() {
	string value;
	cout << "请输入要查找的值" << endl;
	cin >> value;
	bool b = false;
	for (int i = 0; i < BucketSize; i++){
		List p = a[i];
		while (p->next!=NULL){
			p = p->next;
			if (!p->value.compare(value))
			{
				cout << "KEY = " << p->key << endl;
				b = true;
			}
		}
	}
	if(!b)
		cout << "未找到此元素" << endl;
	return;
}

void menu() {
	system("cls");
	cout << " 1.初始化数组"<<endl;
	cout << " 2.插入数据"<<endl;
	cout << " 3.查看所有数据" << endl;
	cout << " 4.按关键字查找值" << endl;
	cout << " 5.按值查找关键字" << endl;
	cout << " 0.退出系统" << endl;
	int choise;
	cin >> choise;
	switch (choise){
		case 1: {
			cout << ((initList()==true) ? "初始化成功！\n" : "初始化失败！\n");
			break;
		}
		case 2: {
			InsertOne();
			break;
		}
		case 3: {
			disList();
			break;
		}
		case 4: {
			cout<<SearchOfKey()<<endl;
			break;
		}
		case 5: {
			SearchOfValue();
			break;
		}
		case 0: {
			exit(0);
		}
		default:{
			cout << "输入错误！请重新输入！" << endl;
			break;
		}
	}
}

int main() {
	initList();
	while (1)
	{
		menu();
		system("pause");
	}
	return 0;
}