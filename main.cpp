#include <iostream>
#include <cstring>
#include <math.h>
#include <cstdlib>

using namespace std;
const int MAX = 50;


class Stack
{
private:
    char action[MAX];         // массив для символов действий
    int top1;                 // вершина для символьного массива
    double number[MAX];       // массив для чисел
    int top2;                 // вершина для числового массива
public:
    Stack()              // конструктор
    {
        top1 = 0;
        top2 = 0;
    }
    void pushAction(char var) // поместить в символьный массив cимвол
    {
        action[top1] = var;
        top1++;
    }
    char popAction()           // взять из символьного массива символ
    {
        top1--;
        return action[top1];
    }
    int gettopAction()         // узнать количество элементов в массиве символов
    {
        return top1;
    }
    int gettopNumber()         // узнать количество элементов в массиве символов
    {
        return top2;
    }
    void pushNumber(double var)  // поместить в символьный массив cимвол
    {
        number[top2] = var;
        top2++;
    }
    double popNumber()           // взять из символьного массива символ
    {
        top2--;
        return number[top2];
    }
    double sum()
    {
        return number[top2-2] = number[top2 - 2] + number[top2-1];
    }
    double minus()
    {
        return number[top2-2] = number[top2 - 2] - number[top2-1];
    }
    double divid()
    {
        return number[top2-2] = number[top2 - 2] / number[top2-1];
    }
    double multy()
    {
        return number[top2-2] = number[top2 - 2] * number[top2 - 1];
    }
    double stepen()
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
    char* pStr;                // строка для ввода
    int len;                   // длина строки
public:
    CALCULATOR(char* ptr)      // конструктор
    {
        pStr = ptr;            // запоминаем указатель на строку
        len = strlen(pStr);    // устанавливаем длину
    }
    double calc(char* str, int status);  // алгоритм выполнения действий
    void action(char act);             // выполнение действий
    int prioritet(char act);           // определение приоритета действия
};



void CALCULATOR::action(char act) {
    switch (act)
    {
    case '+': s.sum(); break;
    case '-': s.minus(); break;
    case '*': s.multy(); break;
    case '/': s.divid(); break;
    case '^': s.stepen(); break;
    default: cout << "\nНеизвестный оператор"; exit(1);
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


double CALCULATOR::calc(char* string, int status)
{
    char n;
    double k;
    char* p;

    // заполнение двух стеков: для действий и для чисел
    for (int i = 0; i < len; i++)
    {

        // если число, то заполняем стек для чисел
        if ((string[i] >= '0') && (string[i] <= '9'))
        {
            double temp = atof(string + i);
            s.pushNumber(temp);
            p = strpbrk(string + i, "+-*/^()");
            if (p == NULL) break;
            i = p - string - 1;
        }
        // если встретилась закрывающаяся скобка, то выталкиваем все действия из стека и выполняем их
        else if (string[i] == ')')
        {
            while (1)
            {
                n = s.popAction();
                if (n == '(') { break; }
                action(n);
                k = s.popNumber();
            }
        }
        // если встретилась открывающаяся скобка или предыдущее действие - открывающаяся скобка, то заполняем действием стек для действий
        else if ((string[i] == '(') || (s.popActionTop1_1() == '(')) {
            s.pushAction(string[i]);
        }
        // если приоритет операции ниже или равен операции, находящейся на вершине, то
        else if (prioritet(s.popActionTop1_1()) >= prioritet(string[i]))
        {
            n = s.popAction();   //выталкиваем операцию из стека
            action(n);           //выполняем действие со стеком из чисел
            k = s.popNumber();
            --i;
        }
        // если приоритет операции выше, то заполняем стек для действий
        else
        {
         s.pushAction(string[i]);
        }
    }
    while (1)
    {
        if (s.gettopAction() == 0) { break; }
        n = s.popAction();
        action(n);
        k = s.popNumber();
    }
    return s.popNumber();
}


int main()
{
    setlocale(LC_ALL, "Russian");
    char string[MAX];

    cout << "\nВведите арифметическое выражение:  ";
    cin >> string;
    CALCULATOR* task = new CALCULATOR(string);					// создаем объект для разбора
    cout << "\nРезультат: " << task->calc(string,1) << endl;    // решаем
    delete task;												// удаляем объект

    return 0;
}

