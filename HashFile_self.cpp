#pragma warning(disable:4996);
#include<iostream>
using namespace std;
const int N = 13;
typedef int keyType;
struct elemType {
	keyType key;
	char value[20];
};
struct Node {
	struct elemType data;
	int next;
};
const char Hash[] = "Hash";
const char Index[] = "HashIndex";
const int keySize = sizeof(keyType);
const int elemSize = sizeof(Node);
int haveData(int);
/*
if (mod == 1) {
	初始化
}
else {
	新建文件
}
*/

int getHash(int key) {
	return key % N;
}

bool reWrite(int mod) {//初始化散列文件
	if (mod == 1) {
		cout << "--- 确定要初始化散列文件(y/n)? ---\n";
		char a;
		cin >> a;
		if (a != 'y' && a != 'Y') {
			cout << "--- 未执行初始化操作！ ---\n";
			return false;
		}
	}
	FILE* fp, * fp2;
	fp = fopen(Hash, "wb+");
	fp2 = fopen(Index, "wb+");
	if (fp == NULL || fp2 == NULL) {
		cout << "--- 文件打开失败！---\n";
		return false;
	}
	int* arr = (int*)calloc(N, keySize);
	//初始化链表，-1代表空
	for (int i = 0; i < N; i++) {
		arr[i] = -1;
	}
	fwrite((char*)arr, N * keySize, 1, fp2);
	fclose(fp);
	fclose(fp2);
	cout << "--- 执行成功！ ---\n";
	return true;
}

//检测是否有散列文件
bool create() {
	FILE* fp, * fp2;
	fp = fopen(Hash, "rb");
	fp2 = fopen(Index, "rb");
	//文件未打开
	if (fp == NULL || fp2 == NULL) {
		cout << "--- 文件不存在，是否要新建Hash文件(y/n)? ---\n";
		char a;
		cin >> a;
		if (a == 'y' || a == 'Y') {
			cout << "--- 正在新建Hash文件！ ---\n";
		}
		else {
			cout << "--- 未执行新建操作! ---\n";
			return false;
		}
		reWrite(0);
	}
	return true;
}

bool insertOne() {
	FILE* fp, * fp2;
	fp = fopen(Hash, "rb+");
	fp2 = fopen(Index, "rb+");
	if (fp == NULL || fp2 == NULL) {
		cout << "--- 文件打开失败！ ---\n";
		return false;
	}
	cout << "请输入待插入元素x的值(一个整数(关键字)和一个字符串(附加信息，长度小于20)):\n";
	struct Node x;
	int* arr = (int*)calloc(N, keySize);
	cin >> x.data.key;
	cin >> x.data.value;
	if (haveData(x.data.key)) {
		cout << "--- 该关键值已存在，不能重复录入! ---\n";
		return false;
	}
	//获取链表头
	fread((char*)arr, (N)*keySize, 1, fp2);
	int hash = getHash(x.data.key);
	x.next = arr[hash];
	//文件内指针移至文件尾
	fseek(fp, 0L, SEEK_END);
	//计算出结点位置序号
	int len = ftell(fp) / elemSize;
	fwrite((char*)&x, elemSize, 1, fp);
	arr[hash] = len;
	//指针移到文件头
	fseek(fp2, 0L, SEEK_SET);
	fwrite((char*)arr, N * keySize, 1, fp2);
	fclose(fp);
	fclose(fp2);
	return true;
}

//b==true 手动输入关键字
//b=false 不需要输入关键字
void searchOne() {
	int key;
	cout << "请输入关键值\n";
	cin >> key;
	int hash = getHash(key);
	FILE* fp, * fp2;
	fp = fopen(Hash, "rb+");
	fp2 = fopen(Index, "rb+");
	int* arr = (int*)calloc(N, keySize);
	fread((char*)arr, N * keySize, 1, fp2);
	int p = arr[hash];
	if (p == -1) {
		cout << "不存在此元素！\n";
		return;
	}
	while (p != -1) {
		Node x;
		fseek(fp, p * elemSize, SEEK_SET);
		fread((char*)&x, elemSize, 1, fp);
		if (x.data.key == key) {
			cout << "value= " << x.data.value << endl;
		}
		p = x.next;
	}
}

int haveData(int key) {
	int hash = getHash(key);
	FILE* fp, * fp2;
	fp = fopen(Hash, "rb+");
	fp2 = fopen(Index, "rb+");
	int* arr = (int*)calloc(N, keySize);
	fread((char*)arr, N * keySize, 1, fp2);
	int p = arr[hash];
	if (p == -1) {
		return false;
	}
	while (p != -1) {
		Node x;
		fseek(fp, p * elemSize, SEEK_SET);
		fread((char*)&x, elemSize, 1, fp);
		if (x.data.key == key) {
			return true;
		}
		p = x.next;
	}
	return false;
}

void display() {
	FILE* fp, * fp2;
	fp = fopen(Hash, "rb+");
	fp2 = fopen(Index, "rb+");
	if (fp == NULL || fp2 == NULL) {
		cout << "文件打开失败！\n";
		return;
	}
	int* arr = (int*)calloc(N, keySize);
	if (arr == NULL) {
		cout << "数组空间申请失败！\n";
		return;
	}
	fread((char*)arr, keySize, N, fp2);

	for (int i = 0; i < N; i++) {
		int p = arr[i];
		cout << i;
		while (p != -1) {
			Node x;
			fseek(fp, p * elemSize, SEEK_SET);
			fread((char*)&x, elemSize, 1, fp);
			cout << " ->" << x.data.key << "(" << x.data.value << ") ";
			p = x.next;
		}
		cout << endl;
	}
	fclose(fp);
	fclose(fp2);
}

void start() {
	cout << "--- 1.初始化散列文件 ---\n";
	cout << "--- 2.插入新值 ---\n";
	cout << "--- 3.输出全部数据 ---\n";
	cout << "--- 4.查找元素 ---\n";
	cout << "--- 0.退出程序 ---\n";
	int a;
	cin >> a;
	switch (a)
	{
	case 1: {
		reWrite(1);
		break;
	}
	case 2: {
		insertOne();
		break;
	}
	case 3: {
		display();
		break;
	}
	case 4: {
		searchOne();
		break;
	}
	case 0: {
		exit(0);
	}
	default:
		cout << "输入错误！请重新输入！\n";
		return;
	}
}

int main() {
	create();
	while (1) {
		start();
	}
	return 0;
}