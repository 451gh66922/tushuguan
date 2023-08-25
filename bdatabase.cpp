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
	top = -1;//�����±��0��ʼ����֤����ӵ�һ��Ԫ�ؿ�ʼ��ȡ��Ϣ
	fstream file;
	file.open("book.dat", ios::in | ios::binary);//�ö����Ƶķ�ʽ���ļ����������ָ���ڴ��Ӳ��
	while (1) {
		file.read((char*)&s, sizeof(s));//���ļ��ж�ȡs���ַ���char*ָ��Ļ����У�book�����s�ĵ�ַ��
		if (!file) break;
		top++;
		book[top] = s;
	}
	file.close();
}
void BDatabase::clear() { top = -1; cout << "���������ͼ���¼"<<endl; }
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
void BDatabase::list() {//�����µ�ͼ����Ϣ�����ߣ������磬�۸�
	
	int record_number=0;
		for (int i = 0; i <= top; i++)
		{

			if (book[i].getnote() != 1)      //��ʾ��ɾ����ǲ�Ϊ1������ʾ,�����ɾ������Կ�����ʾ�����Ϣ����һ����
			{
				book[i].list();
				record_number++;
				if (book[i].borrowbook() == 0)
					cout << "          ��ͼ���ѽ���������߱��Ϊ:" << book[i].get_readerid() << endl;//���ӹ���:���Һ���ʾʱ����ͼ��������ʾ�����߱��
				else{cout << endl;}
			}
		}
		if (record_number == 0)
		{
			cout << "����ͼ���¼" << endl;//������ͼ�����ʾ
		}
}
BDatabase::~BDatabase() {
	fstream file;
	file.open("book.dat", ios::out | ios::binary);//����ڴ�->Ӳ��
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
		cout << "ͼ��ά����" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "1: ���� 2: ���� 3: ɾ�� 4: ���� 5: ��ʾ 6: ȫɾ 0: �˳�" << endl;
		cin >> choice;
		cout << "----------------------------------------------" << endl;
		switch (choice)
		{
		case 1:
			cout << "����ͼ���ţ�";
			cin >> bookid;
			cout << "����ͼ����: ";
			cin >> bookname;
			cout << "����ͼ������: ";
			cin >> book_author;
			cout<<"����ͼ�������: ";
			cin >> book_publish_house;
			cout << "����ͼ��۸�: ";
			cin >> book_price;
			addbook(bookid, bookname,book_author,book_publish_house,book_price); break;
		case 2:
			cout << "����ͼ����: ";
			cin >> bookid;
			b = query(bookid);
			if (b == NULL) {
				cout << "��ͼ�鲻���ڣ�" << endl;
				break;
			}
			cout << "�����µ�ͼ������";
			cin >> bookname;
			b->setname(bookname); break;
		case 3:
			cout << "����ͼ���ţ�";
			cin >> bookid;
			b = query(bookid);
			if (b == NULL) {
				cout << "��ͼ�鲻���ڣ��޷�ɾ����" << endl;
				break;
			}
			else
			{
				b->delbook();//���ӵ������ɾ�����ܣ����ɾ����� 
				cout << "�ѽ����Ϊ��"<<" "<< bookid<<" " << "����ͼ��ɾ��" << endl;
				break;
			}

		case 4:
			cout << "����ͼ���ţ�";
			cin >> bookid;
			b = query(bookid);
			if (b == NULL)
			{
				cout << "��ͼ�鲻���ڣ�" << endl;
				break;
			}
			b->list();
			if(b->borrowbook()==0)
				cout << "          ��ͼ���ѽ���������߱��Ϊ:" << book->get_readerid() << endl; break;
		case 5:
			cout << "ͼ����Ϣ����:" << endl;
			list(); 
			break;
		case 6:
				clear();//����ȫɾ����
			    break;
		} //end switch
	}//end while
}