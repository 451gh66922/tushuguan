#include<fstream>
#include<iostream>
#include"rdatabase.h"
using namespace std;
RDatabase::RDatabase() {
	Reader s;
	top = -1;
	ifstream file;//创建流对象file（文件）
	file.open("reader.dat", ios::in | ios::binary);//打开文件open("文件路径"，打开方式)
	while (1) {                                    //打开方式配合使用，利用|操作符：用二进制方式读文件
		file.read((char*)&s, sizeof(s));
		if (!file) break;
		top++;
		read[top] = s;
	}
	file.close();//关闭文件
}
void RDatabase::clear()
{
	top = -1;
}
Reader* RDatabase::query(int readerid) {
	for (int i = 0; i <= top; i++)
		if (read[i].getnumber() == readerid && read[i].getnote() == 0)
			return &read[i];
	return NULL;
}
int RDatabase::addreader(int n, char* na) {
	Reader* p = query(n);
	if (p == NULL) {
		top++;
		read[top].addreader(n, na);
		return 1;
	}
	return 0;
}
void RDatabase::list()//修改：删除读者后不再显示
{
	int record_read=0;

	for (int i = 0; i <= top; i++)
	{
		if (read[i].getnote()!=1)
		{
			read[i].list();
			record_read++;
		}
	}
	if (record_read == 0)
		cout << "暂无读者记录" << endl;
}
RDatabase::~RDatabase() {
	fstream file;
	file.open("reader.dat", ios::out | ios::binary);
	for (int i = 0; i <= top; i++)
		if (read[i].getnote() == 0)
			file.write((char*)&read[i], sizeof(read[i]));
	file.close();
}
void RDatabase::readerdata() {
	int choice = 1;
	char readername[20];
	int readerid;
	Reader* r;
	while (choice != 0) {
		cout << "读者维护：" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "1：新增 2：更改 3：删除 4：查找 5：显示 6：全删 0：退出" << endl;
		cin >> choice;
		cout << "----------------------------------------------" << endl;
		switch (choice)
		{
		case 1:cout << "输入读者编号：";
			cin >> readerid;
			cout << "输入读者姓名：";
			cin >> readername;
			addreader(readerid, readername); break;
		case 2:cout << "输入读者编号：";
			cin >> readerid;
			r = query(readerid);
			if (r == NULL) {
				cout << "该读者不存在！" << endl;
				break;
			}
			cout << "输入新的姓名：";
			cin >> readername;
			r->setname(readername); break;
		case 3:cout << "输入读者编号：";
			cin >> readerid;
			r = query(readerid);
			if (r == NULL) {
				cout << "该读者不存在！" << endl;
			}
			else
			{
				r->delbook();
				cout << "已将编号为“" << readerid << "”的读者删除" << endl;//增加单个读者删除功能
			}
			break;
		case 4:cout << "输入读者编号：";
			cin >> readerid;
			r = query(readerid);
			if (r == NULL) {
				cout << "该读者不存在！" << endl;
				break;
			}
			r->list(); break;
		case 5:list(); break;
		case 6:
			clear();//全删函数
			break;
		}//end switch
	}//end while
}