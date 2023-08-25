#ifndef _book_h_
#define _book_h_
#include<iostream>
using namespace std;
class Book {//图书类
public:
	char* getname();//获得书名
	int getnote();//获得删除标记
	int getnumber();//获得图书编号
	void setname(char na[]);//设置书名
	void delbook();//删除书名
	void addbook(int n, char* na,char*au,char* pu,int b_price);//添加图书
	int borrowbook();//借书操作
	void retbook();//还书操作
    void list();//输出图书
	void Resetonshelf();//置零
	void return_readerid(int m_readerid);//借书者编号
	int get_readerid();//获得借书编号
	char* getauthor();//获得借阅者编号
	void setauthor(char au[]);
	char* getpublish_house();
	void setpubilsh_house(char pu[]);
private:
	int note;//删除标记（1：已删，0：未删）
	int number;//图书编号
	char name[10];//书名
	char author[10];//作者
	int price;//价格
	char publish_house[10];//出版社
	int onshelf;//上架标志(1:上架)
	int r_number;//新增：借书者编号
};

#endif
