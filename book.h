#ifndef _book_h_
#define _book_h_
#include<iostream>
using namespace std;
class Book {//ͼ����
public:
	char* getname();//�������
	int getnote();//���ɾ�����
	int getnumber();//���ͼ����
	void setname(char na[]);//��������
	void delbook();//ɾ������
	void addbook(int n, char* na,char*au,char* pu,int b_price);//���ͼ��
	int borrowbook();//�������
	void retbook();//�������
    void list();//���ͼ��
	void Resetonshelf();//����
	void return_readerid(int m_readerid);//�����߱��
	int get_readerid();//��ý�����
	char* getauthor();//��ý����߱��
	void setauthor(char au[]);
	char* getpublish_house();
	void setpubilsh_house(char pu[]);
private:
	int note;//ɾ����ǣ�1����ɾ��0��δɾ��
	int number;//ͼ����
	char name[10];//����
	char author[10];//����
	int price;//�۸�
	char publish_house[10];//������
	int onshelf;//�ϼܱ�־(1:�ϼ�)
	int r_number;//�����������߱��
};

#endif
