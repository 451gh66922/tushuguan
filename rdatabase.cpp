#include<fstream>
#include<iostream>
#include"rdatabase.h"
using namespace std;
RDatabase::RDatabase() {
	Reader s;
	top = -1;
	ifstream file;//����������file���ļ���
	file.open("reader.dat", ios::in | ios::binary);//���ļ�open("�ļ�·��"���򿪷�ʽ)
	while (1) {                                    //�򿪷�ʽ���ʹ�ã�����|���������ö����Ʒ�ʽ���ļ�
		file.read((char*)&s, sizeof(s));
		if (!file) break;
		top++;
		read[top] = s;
	}
	file.close();//�ر��ļ�
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
void RDatabase::list()//�޸ģ�ɾ�����ߺ�����ʾ
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
		cout << "���޶��߼�¼" << endl;
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
		cout << "����ά����" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "1������ 2������ 3��ɾ�� 4������ 5����ʾ 6��ȫɾ 0���˳�" << endl;
		cin >> choice;
		cout << "----------------------------------------------" << endl;
		switch (choice)
		{
		case 1:cout << "������߱�ţ�";
			cin >> readerid;
			cout << "�������������";
			cin >> readername;
			addreader(readerid, readername); break;
		case 2:cout << "������߱�ţ�";
			cin >> readerid;
			r = query(readerid);
			if (r == NULL) {
				cout << "�ö��߲����ڣ�" << endl;
				break;
			}
			cout << "�����µ�������";
			cin >> readername;
			r->setname(readername); break;
		case 3:cout << "������߱�ţ�";
			cin >> readerid;
			r = query(readerid);
			if (r == NULL) {
				cout << "�ö��߲����ڣ�" << endl;
			}
			else
			{
				r->delbook();
				cout << "�ѽ����Ϊ��" << readerid << "���Ķ���ɾ��" << endl;//���ӵ�������ɾ������
			}
			break;
		case 4:cout << "������߱�ţ�";
			cin >> readerid;
			r = query(readerid);
			if (r == NULL) {
				cout << "�ö��߲����ڣ�" << endl;
				break;
			}
			r->list(); break;
		case 5:list(); break;
		case 6:
			clear();//ȫɾ����
			break;
		}//end switch
	}//end while
}