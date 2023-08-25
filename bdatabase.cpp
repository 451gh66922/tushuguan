#include<fstream>
#include<string>
#include<iostream>
#include"bdatabase.h"
#include"reader.h"
#include"rdatabase.h"
using namespace std;
BDatabase::BDatabase()
{
	Book s;
	top = -1;//数组下标从0开始，保证数组从第一个元素开始读取信息
	fstream file;
	file.open("book.dat", ios::in | ios::binary);//用二进制的方式读文件。输入输出指：内存和硬盘
	while (1) {
		file.read((char*)&s, sizeof(s));//从文件中读取s个字符到char*指向的缓存中（book类对象s的地址）
		if (!file) break;
		top++;
		book[top] = s;
	}
	file.close();
}
void BDatabase::clear() { top = -1; cout << "已清空所有图书记录"<<endl; }
Book* BDatabase::query(int bookid) {
	for (int i = 0; i <= top; i++)
		if (book[i].getnumber() == bookid && book[i].getnote() == 0)
			return &book[i];
	return NULL;
}
int BDatabase::addbook(int n, char* na,char* au,char* pu,int b_price) {
	Book* p = query(n);
	if (p == NULL)
	{
		top++;
		book[top].addbook(n, na,au,pu,b_price);
		return 1;
	}
	return 0;
}
void BDatabase::list() {//增加新的图书信息，作者，出版社，价格。
	
	int record_number=0;
		for (int i = 0; i <= top; i++)
		{

			if (book[i].getnote() != 1)      //显示中删除标记不为1才能显示,解决“删除书后仍可以显示书的信息”这一问题
			{
				book[i].list();
				record_number++;
				if (book[i].borrowbook() == 0)
					cout << "          该图书已借出，借阅者编号为:" << book[i].get_readerid() << endl;//增加功能:查找和显示时，若图书借出，显示借阅者编号
				else{cout << endl;}
			}
		}
		if (record_number == 0)
		{
			cout << "暂无图书记录" << endl;//增加无图书的显示
		}
}
BDatabase::~BDatabase() {
	fstream file;
	file.open("book.dat", ios::out | ios::binary);//输出内存->硬盘
	for (int i = 0; i <= top; i++)
		if (book[i].getnote() == 0)
			file.write((char*)&book[i], sizeof(book[i]));
	file.close();
}
void BDatabase::bookdata() {
	int choice = 1;
	char bookname[20];
	char book_author[10];
	char book_publish_house[10];
	int book_price;
	int bookid;
	Book* b;
	while (choice != 0) {
		cout << "图书维护：" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "1: 新增 2: 更改 3: 删除 4: 查找 5: 显示 6: 全删 0: 退出" << endl;
		cin >> choice;
		cout << "----------------------------------------------" << endl;
		switch (choice)
		{
		case 1:
			cout << "输入图书编号：";
			cin >> bookid;
			cout << "输入图书名: ";
			cin >> bookname;
			cout << "输入图书作者: ";
			cin >> book_author;
			cout<<"输入图书出版社: ";
			cin >> book_publish_house;
			cout << "输入图书价格: ";
			cin >> book_price;
			addbook(bookid, bookname,book_author,book_publish_house,book_price); break;
		case 2:
			cout << "输入图书编号: ";
			cin >> bookid;
			b = query(bookid);
			if (b == NULL) {
				cout << "该图书不存在！" << endl;
				break;
			}
			cout << "输入新的图书名：";
			cin >> bookname;
			b->setname(bookname); break;
		case 3:
			cout << "输入图书编号：";
			cin >> bookid;
			b = query(bookid);
			if (b == NULL) {
				cout << "该图书不存在，无法删除！" << endl;
				break;
			}
			else
			{
				b->delbook();//增加单本书的删除功能，获得删除标记 
				cout << "已将编号为“"<<" "<< bookid<<" " << "”的图书删除" << endl;
				break;
			}

		case 4:
			cout << "输入图书编号：";
			cin >> bookid;
			b = query(bookid);
			if (b == NULL)
			{
				cout << "该图书不存在！" << endl;
				break;
			}
			b->list();
			if(b->borrowbook()==0)
				cout << "          该图书已借出，借阅者编号为:" << book->get_readerid() << endl; break;
		case 5:
			cout << "图书信息如下:" << endl;
			list(); 
			break;
		case 6:
				clear();//增加全删功能
			    break;
		} //end switch
	}//end while
}