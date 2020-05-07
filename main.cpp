#include <stdlib.h>
#include <iostream>
#include <time.h>
#include<stdio.h>
#include<string.h>
using namespace std;

struct Node
{
	int x;
	int count;
	int timeofentering;
	int numberofoffer;
	Node *Next, *Prev;
};

class List
{
public: Node *Head, *Tail;
public:
	List() :Head(NULL), Tail(NULL) {};
	~List();
	void Show();
	void Add(int x, int timeofenter, int numberofoffer);
	void HeadToTail(int timeofenter);
	void DeleteHead();
	int Amount();
	long CountAmount();
};

List::~List()
{
	while (Head)
    {  Tail = Head->Next;
		delete Head;
		Head = Tail;
	}
}

void List::Add(int x, int timeofenter, int numberofoffer)
{
	Node *temp = new Node;
	temp->Next = NULL;
	temp->x = x;
	temp->timeofentering = timeofenter;
	temp->count = 0;
	temp->numberofoffer = numberofoffer;

	if (Head != NULL)
	{
		temp->Prev = Tail;
		Tail->Next = temp;
		Tail = temp;
	}
	else
	{
		temp->Prev = NULL;
		Head = Tail = temp;
	}
}

void List::HeadToTail(int timeofenter)
{
	Tail->Next = Head;
	Head = Head->Next;
	Tail = Tail->Next;
	Tail->Next = NULL;
	Tail->count++;
	Tail->timeofentering = timeofenter;
}

void List::DeleteHead()
{
	if(Head->Next != NULL)
		Head = Head->Next;
}

int List::Amount()
{
	int amount = 1;
	Node *temp = Head;
	while (temp != Tail)
	{
		temp = temp->Next;
		amount++;
	}
	return amount;
}

long List::CountAmount()
{
	Node *temp = Head;
	long countamount = Head->count;
	while (temp != Tail)
	{
		temp = temp->Next;
		countamount += temp->count;
	}
	return countamount;
}



void List::Show()
{
	Node *temp = Tail;

	while (temp != NULL)
	{
		cout << temp->x << " ";
		temp = temp->Prev;
	}
	cout << "\n";
	temp = Head;
	while (temp != NULL)
	{
		cout << temp->x << " ";
		temp = temp->Next;
	}
	cout << "\n";
}

int main()
{   setlocale(0, "Russian");
	List list;
	int countofendings = 0; // ���������� ����������� �� ������ ������
	int T1 = 0;
	int timegone = 0; // ����� �� ������ ������, ��� ������ - ����� �������������
	long maxtimeofwaiting = -1; // ������������ ����� ��������
	int amountofrenovating = 0; // ���������� ���� ����������� ����� ��
	unsigned long timeofwaitingOA = 0; // ����� ����� �������� ��
	unsigned long timeofrenovating = 0; // ����� ����� �������� ������� ���������� ����� �����
	unsigned long timeofT1 = 0; // ����� ����� �������� �1
	Node *maxi = NULL; // ������ � ����. �������� ��������;
	int numberofoffers = 0; // ����� ������
	int T2 = 100;
	while (countofendings < 1000)
	{
		timegone++;
		if (T1 == 0)  // ���� ������� ������� ������� � �����
		{
			int temp = rand() % 100;
			list.Add(temp, timegone, numberofoffers);
			numberofoffers++;
			T1 = rand() % 10 + 1; // ����� ������� ����������
			timeofT1 += T1;
		}
		if (T2 == 100) // ������ ������������� ������
		{
			T2 = rand() % 3;
			timeofwaitingOA += T2;
		}
		if (list.CountAmount() == 0)
			timeofwaitingOA++;
		if (T2 == 0)
		{
			if (list.Head->count == 3)
			{
				list.DeleteHead();
				countofendings++;
				amountofrenovating++;
				timeofrenovating += timegone - list.Head->timeofentering;
				T2 = rand() % 3 + 1;
				if (countofendings % 100 == 0)
				{
					cout << countofendings << "!" << endl;
					cout <<"���-�� �������� ������:"<< numberofoffers << " ����� �������:" << list.Amount() << " " << endl; // ����� ���������� ������ � ������� �� ������ ������
					if (timegone - list.Head->timeofentering > maxtimeofwaiting)
					{
						maxi = list.Head;
						maxtimeofwaiting = timegone - list.Head->timeofentering;
					}
					cout <<"����� ������ � ������������ �������� ��������:"<< maxi->numberofoffer << " ���� ������������:" << maxi->count <<endl<< " ������������ ����� ���������� � �������:" << maxtimeofwaiting << " ������� ����� ����������:" << timeofrenovating / amountofrenovating << endl;



				}
			}
			else {
				if (timegone - list.Head->timeofentering > maxtimeofwaiting)
				{
					maxi = list.Head;
					maxtimeofwaiting = timegone - list.Head->timeofentering;
				}
				amountofrenovating++;
				timeofrenovating += timegone - list.Head->timeofentering;
				list.HeadToTail(timegone);
				T2 = rand() % 2 + 1;
			}
			timeofwaitingOA += T2;
		}
		T1--;
		T2--;
	}
	cout << "������� ����� �1:"<<timeofT1 / numberofoffers << endl;
	cout << "���-�� ���� ��������� ��:"<<amountofrenovating << endl;
	cout <<"����� �������������:"<< timegone << " ����� �������" << timeofwaitingOA - amountofrenovating << " ���-�� ������������ ������:" << numberofoffers ;
	cout<< " ���-�� ��������" << list.CountAmount() + 1000 << " ���-�� ��������" << 1000 << endl;

	cout<<endl<<"�������� �� �����:"<<endl;
	double x=list.CountAmount() + 1000-timegone/(timeofT1 / numberofoffers);
	x/=timegone/(timeofT1 / numberofoffers);
	printf("�����������:%.7lf",100*x);
	cout<<endl<<"�������� �� ������:"<<endl;
	x=-timegone +(amountofrenovating+timeofwaitingOA - amountofrenovating);
	x/=timegone;
	printf("�����������:%.7lf",100*(x));return 0;
}
