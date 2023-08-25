#include<iomanip>
#include<cstring>
#include "book.h"
char* Book::getname() { return name; }
int Book::getnote() { return note; }
int Book::getnumber() { return number; }
void Book::setname(char na[]) { strcpy(name, na); }
char* Book::getauthor() { return author; }
void Book::setauthor(char au[])
{
	strcpy(author, au);
}
char* Book::getpublish_house()
{
	return publish_house;
}
void Book::setpubilsh_house(char pu[])
{
	strcpy(publish_house, pu);
}
void Book::addbook(int n, char* na,char* au,char* pu,int b_price)
{
	note = 0;
	number = n;
	strcpy(name, na);
	strcpy(author, au);
	strcpy(publish_house, pu);
	price = b_price;
	onshelf = 1;
}
void Book::delbook()
{
	note = 1;//获得删除标记
}
int Book::borrowbook()
{
	return onshelf;
}
void Book::retbook()
{
	onshelf = 1;
}
void Book::list()
{
	cout << setw(5) << number << setw(10) << name << setw(10)<<author<<setw(15)<<publish_house<<setw(10)<<price<<setw(10) << onshelf; //setw()输出宽度	
}
void Book::Resetonshelf()//新增函数：解决一本书借多次的问题
{
	onshelf = 0;
}
void Book::return_readerid(int m_readerid)//新增函数，得到借书者编号
{
	r_number=m_readerid;
}
int Book::get_readerid()//新增函数，返回借书者编号
{
	return r_number;
}
