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
	int countofendings = 0; // количество завершенных на данный момент
	int T1 = 0;
	int timegone = 0; // время на данный момент, при выходе - время моделирования
	long maxtimeofwaiting = -1; // максимальное время ожидания
	int amountofrenovating = 0; // количество всех прохождений через ОА
	unsigned long timeofwaitingOA = 0; // общее время ожидания ОА
	unsigned long timeofrenovating = 0; // общее время ожидания каждого отдельного блока листа
	unsigned long timeofT1 = 0; // общее время ожидания Т1
	Node *maxi = NULL; // ячейка с макс. временем ожидания;
	int numberofoffers = 0; // номер заявки
	int T2 = 100;
	while (countofendings < 1000)
	{
		timegone++;
		if (T1 == 0)  // если счетчик времени подошел к концу
		{
			int temp = rand() % 100;
			list.Add(temp, timegone, numberofoffers);
			numberofoffers++;
			T1 = rand() % 10 + 1; // новый счетчик считывания
			timeofT1 += T1;
		}
		if (T2 == 100) // первое обрабатывание ячейки
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
					cout <<"Кол-во вошедших заявок:"<< numberofoffers << " Длина очереди:" << list.Amount() << " " << endl; // вывод количества заявок в очереди на данный момент
					if (timegone - list.Head->timeofentering > maxtimeofwaiting)
					{
						maxi = list.Head;
						maxtimeofwaiting = timegone - list.Head->timeofentering;
					}
					cout <<"Номер заявки с максимальным временем ожидания:"<< maxi->numberofoffer << " Цикл обслуживания:" << maxi->count <<endl<< " Максимальное время пребывания в очереди:" << maxtimeofwaiting << " Среднее время пребывания:" << timeofrenovating / amountofrenovating << endl;



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
	cout << "Среднее время Т1:"<<timeofT1 / numberofoffers << endl;
	cout << "кол-во всех обработок ОА:"<<amountofrenovating << endl;
	cout <<"Время моделирования:"<< timegone << " Время простоя" << timeofwaitingOA - amountofrenovating << " Кол-во обработанных заявок:" << numberofoffers ;
	cout<< " кол-во вошедших" << list.CountAmount() + 1000 << " кол-во вышедших" << 1000 << endl;

	cout<<endl<<"ПРОВЕРКА ПО ВХОДУ:"<<endl;
	double x=list.CountAmount() + 1000-timegone/(timeofT1 / numberofoffers);
	x/=timegone/(timeofT1 / numberofoffers);
	printf("ПОГРЕШНОСТЬ:%.7lf",100*x);
	cout<<endl<<"ПРОВЕРКА ПО ВЫХОДУ:"<<endl;
	x=-timegone +(amountofrenovating+timeofwaitingOA - amountofrenovating);
	x/=timegone;
	printf("ПОГРЕШНОСТЬ:%.7lf",100*(x));return 0;
}
