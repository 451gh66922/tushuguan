#include"reader.h"
#include"rdatabase.h"
#include"book.h"
#include"bdatabase.h"
#include<iostream>
#include<atltime.h>
using namespace std;
int main(int argc, char* argv[]) {
	CTime time = CTime::GetCurrentTime();//��ʾ��ǰʱ��
	printf("�����Ǳ���ʱ��  %04d/%02d/%02d %02d:%02d:%02d\n", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	int choice = 1, bookid, readerid;
	RDatabase ReaderDB;
	BDatabase BookDB;
	Reader* r;
	Book* b;
	cout << "��ӭ���롰ССͼ��ݡ��������" << endl;
	cout << "----------------------------------------------" << endl;
	while (choice != 0) {
		cout << "----------------------------------------------" << endl;
		cout << "1������ 2 ����  3:ͼ��ά��  4:����ά��   0:�뿪";
		cin >> choice;
		cout << "----------------------------------------------" << endl;
		switch (choice)
		{
		case 1:
			if (time.GetHour() >= 23||time.GetHour()<=5)
			{
				cout << "���ڲ���ͼ�����ʱ�䣬ͼ�����ʱ��Ϊ����6:00������10:59" << endl;//ϵͳά������һ��ʱ�䷶Χ���޷����飬����
			}
			else
			{
				cout << "���������߱��";
				cin >> readerid;
				cout << "����ͼ����";
				cin >> bookid;
				r = ReaderDB.query(readerid);
				if (r == NULL) {
					cout << "�ö��߲�����, ���ܽ��飡" << endl;
					break;
				}
				b = BookDB.query(bookid);
				if (b == NULL) {
					cout << "��ͼ�鲻����, ���ܽ��飡" << endl;
					break;
				}
				if (b->borrowbook() == 0) {
					cout << "��ͼ���ѽ��, ���ܽ��飡" << endl; break;//����һ������ʹ������onshelf=0���Ӷ������һ������Ρ�
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
				cout << "���ڲ���ͼ��黹ʱ�䣬ͼ��黹ʱ��Ϊ����6:00������23:59" << endl;
			}
			else
			{
				cout << "���뻹����߱��";
				cin >> readerid;
				cout << "����ͼ����";
				cin >> bookid;
				r = ReaderDB.query(readerid);
				if (r == NULL) {
					cout << "�ö��߲�����, ���ܻ��飡" << endl; break;
				}
				b = BookDB.query(bookid);
				if (b == NULL) {
					cout << "��ͼ�鲻����, ���ܻ��飡" << endl; break;
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