#include<iomanip>
#include <iostream>
#include "reader.h"
char* Reader::getname() { return name; }
int Reader::getnote() { return note; }
int Reader::getnumber() { return number; }
void Reader::setname(char na[]) { strcpy(name, na); }
void Reader::addreader(int n, char* na) {
	note = 0;
	number = n;
	strcpy(name, na);
	for (int i = 0; i < Maxbor; i++)
		borbook[i] = 0;
}
void Reader::delbook() { note = 1; }
void Reader::borrowbook(int bookid)
{
	for (int i = 0; i < Maxbor; i++) {
		if (borbook[i] == 0) { borbook[i] = bookid; return; }
	}
}
int Reader::retbook(int bookid) {
	for (int i = 0; i < Maxbor; i++)
	{
	   if (borbook[i] == bookid) { borbook[i] = 0; return 1; }
	}
	return 0;
}
void Reader::list() {
	int record_borbook = 0;
	cout << setw(5) << number << setw(10) << name<<" " << "�����ţ�[";//����Ϊ��ʾ���߽����ı���Լ�ʣ���������
	for (int i = 0; i < Maxbor; i++)
		if (borbook[i] != 0) { cout << borbook[i] << "      "; 
	record_borbook++;
	}
	cout << "]" << "     "<<"���ɽ�"<<Maxbor-record_borbook<<"����"<<endl;
}