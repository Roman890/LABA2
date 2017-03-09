
#include <iostream>
#include <cstring>
#include <math.h>
#include <cstdlib>

using namespace std;
const int MAX = 10;     


class Stack
{
private:
	char action[MAX];         // ������ ��� �������� ��������
	int top1;                 // ������� ��� ����������� �������
	int number[MAX];          // ������ ��� �����
	int top2;                 // ������� ��� ��������� �������
public:
	Stack()              // �����������
	{
		top1 = 0;
		top2 = 0;
	}
	void pushAction(char var) // ��������� � ���������� ������ c�����
	{
		action[top1] = var;
		top1++;
	}
	char popAction()           // ����� �� ����������� ������� ������
	{
		top1--;
		return action[top1];
	}
	int gettopAction()         // ������ ���������� ��������� � ������� ��������
	{
		return top1;
	}
	int gettopNumber()         // ������ ���������� ��������� � ������� ��������
	{
		return top2;
	}
	void pushNumber(int var)  // ��������� � ���������� ������ c�����
	{
		number[top2] = var;
		top2++;
	}
	int popNumber()           // ����� �� ����������� ������� ������
	{
		top2--;
		return number[top2];
	}
	int sum()
	{
		return number[top2-2] = number[top2 - 2] + number[top2-1];
	}
	int minus()
	{
		return number[top2-2] = number[top2 - 2] - number[top2-1];
	}
	int divid()
	{
		return number[top2-2] = number[top2 - 2] / number[top2-1];
	}
	int multy()
	{
		return number[top2-2] = number[top2 - 2] * number[top2 - 1];
	}
	int stepen()
	{
		return number[top2-2] = pow(number[top2 - 2], number[top2-1]); 
	}
	char popActionTop1_1()          
	{
		return action[top1-1];
	}
};


class CALCULATOR
{
private:
	Stack s;                 
	char* pStr;                // ������ ��� �����
	int len;                   // ����� ������
public:
	CALCULATOR(char* ptr)      // �����������
	{
		pStr = ptr;            // ���������� ��������� �� ������
		len = strlen(pStr);    // ������������� �����
	}
	int calc(char* str, int status);  // �������� ���������� ��������
	void action(char act);             // ���������� ��������
	int prioritet(char act);           // ����������� ���������� ��������
};



void CALCULATOR::action(char act) {
	switch (act)
	{
	case '+': s.pushNumber(s.sum()); break;
	case '-': s.pushNumber(s.minus()); break;
	case '*': s.pushNumber(s.multy()); break;
	case '/': s.pushNumber(s.divid()); break;
	case '^': s.pushNumber(s.stepen()); break;
	default: cout << "\n����������� ��������"; exit(1);
	}
	return;
}

int CALCULATOR::prioritet(char act)
{
	switch (act)
	{
	case '+': return 1; break;
	case '-': return 1; break;
	case '*': return 2; break;
	case '/': return 2; break;
	case '^': return 3; break;
	}
}

int CALCULATOR::calc(char* string, int status)
{
	int l = strlen(string);
	char n;
	int k;

	// ���������� ���� ������: ��� �������� � ��� ����� 
	for (int i = 0; i < l; ++i)
	{
		// ���� �����, �� ��������� ���� ��� �����
		if ((string[i] <= '9') && (string[i] >= '0'))
		{
			s.pushNumber(atof(string + i));
		}
		// ���� ��������� �������� ���� ��� ����� ��������, ����������� �� �������, ��  
		else if (prioritet(s.popActionTop1_1()) >= prioritet(string[i]))
		{
			n = s.popAction();   //����������� �������� �� �����
			action(n);           //��������� �������� �� ������ �� ����� 
			s.pushAction(string[i]);//������ ����� �������� �� ����  ��������
		}
		// ���� ��������� �������� ����, �� ��������� ���� ��� �������� 
		else
		{
		 s.pushAction(string[i]);
		}
	}
	while (1)
	{

		if (s.gettopAction() == 0) { break; }
		n = s.popAction();
		cout << n << endl;
		action(n);
	}
	return s.popNumber();
}


int main()
{
	setlocale(LC_ALL, "Russian");
	char string[MAX]; 

	cout << "\n������� �������������� ���������:  ";
	cin >> string;
	CALCULATOR* task = new CALCULATOR(string);					// ������� ������ ��� �������
	cout << "\n���������: " << task->calc(string,1) << endl;    // ������
	delete task;												// ������� ������
	
	return 0;
}


