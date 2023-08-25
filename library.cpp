#include"reader.h"
#include"rdatabase.h"
#include"book.h"
#include"bdatabase.h"
#include<iostream>
#include<atltime.h>
using namespace std;
int main(int argc, char* argv[]) {
	CTime time = CTime::GetCurrentTime();//显示当前时间
	printf("现在是北京时间  %04d/%02d/%02d %02d:%02d:%02d\n", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	int choice = 1, bookid, readerid;
	RDatabase ReaderDB;
	BDatabase BookDB;
	Reader* r;
	Book* b;
	cout << "欢迎进入“小小图书馆”管理软件" << endl;
	cout << "----------------------------------------------" << endl;
	while (choice != 0) {
		cout << "----------------------------------------------" << endl;
		cout << "1：借书 2 还书  3:图书维护  4:读者维护   0:离开";
		cin >> choice;
		cout << "----------------------------------------------" << endl;
		switch (choice)
		{
		case 1:
			if (time.GetHour() >= 23||time.GetHour()<=5)
			{
				cout << "现在不是图书借阅时间，图书借阅时间为早上6:00至晚上10:59" << endl;//系统维护，在一定时间范围内无法借书，还书
			}
			else
			{
				cout << "输入借书读者编号";
				cin >> readerid;
				cout << "输入图书编号";
				cin >> bookid;
				r = ReaderDB.query(readerid);
				if (r == NULL) {
					cout << "该读者不存在, 不能借书！" << endl;
					break;
				}
				b = BookDB.query(bookid);
				if (b == NULL) {
					cout << "该图书不存在, 不能借书！" << endl;
					break;
				}
				if (b->borrowbook() == 0) {
					cout << "该图书已借出, 不能借书！" << endl; break;//增加一个函数使借书后的onshelf=0，从而解决了一本书借多次。
				}
				else
				{
					r->borrowbook(b->getnumber());
					b->Resetonshelf();
					b->return_readerid(r->getnumber());
				}
			}
			break;
		case 2:
			if (time.GetHour() >= 0 && time.GetHour() <= 5)
			{
				cout << "现在不是图书归还时间，图书归还时间为早上6:00至晚上23:59" << endl;
			}
			else
			{
				cout << "输入还书读者编号";
				cin >> readerid;
				cout << "输入图书编号";
				cin >> bookid;
				r = ReaderDB.query(readerid);
				if (r == NULL) {
					cout << "该读者不存在, 不能还书！" << endl; break;
				}
				b = BookDB.query(bookid);
				if (b == NULL) {
					cout << "该图书不存在, 不能还书！" << endl; break;
				}
				b->retbook();
				r->retbook(b->getnumber());
			}
			break;
		case 3:
			BookDB.bookdata(); break;
		case 4:
			ReaderDB.readerdata(); break;
		}//end switch
	}//end while
	return 0;
}