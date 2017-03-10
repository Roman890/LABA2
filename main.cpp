

#ifdef __cplusplus
extern "C" {
#endif
        double calc(const char * str, int * status);
#ifdef __cplusplus
}
#endif


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
                for (int i = 0; i < MAX; i++) {
                        action[i] = 0;
                        number[i] = 0;
                }
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
public:
        void action(char act);             // выполнение действий
        int prioritet(char act);           // определение приоритета действия
        Stack stack()
        {
                return s;
        }
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


double calc(const char* string, int* status)
{
        const char *p = string;
        CALCULATOR task;					// создаем объект для разбора
        char n;
        double k;

        // заполнение двух стеков: для действий и для чисел
        for (int i = 0; i < strlen(string); i++)
        {

                // если число, то заполняем стек для чисел
                if ((string[i] >= '0') && (string[i] <= '9'))
                {
                        double temp = atof(string + i);
                        task.stack.pushNumber(temp);
                        p = strpbrk(string + i, "+-*/^()");
                        if (p == NULL) break;
                        i = p - string - 1;
                }
                // если встретилась закрывающаяся скобка, то выталкиваем все действия из стека и выполняем их
                else if (string[i] == ')')
                {
                        while (1)
                        {
                                n = task.stack.popAction();
                                if (n == '(') { break; }
                                task.action(n);
                                k = task.stack.popNumber();
                        }
                }
                // если встретилась открывающаяся скобка или предыдущее действие - открывающаяся скобка, то заполняем действием стек для действий
                else if ((string[i] == '(') || (task.stack.popActionTop1_1() == '(')) {
                        task.stack.pushAction(string[i]);
                }
                // если приоритет операции ниже или равен операции, находящейся на вершине, то
                else if (task.prioritet(task.stack.popActionTop1_1()) >= task.prioritet(string[i]))
                {
                        n = task.stack.popAction();   //выталкиваем операцию из стека
                        task.action(n);           //выполняем действие со стеком из чисел
                        k = task.stack.popNumber();
                        --i;
                }
                // если приоритет операции выше, то заполняем стек для действий
                else
                {
                 task.stack.pushAction(string[i]);
                }
        }
        while (1)
        {
                if (task.stack.gettopAction() == 0) { break; }
                n = task.stack.popAction();
                task.action(n);
                k = task.stack.popNumber();
        }
        return task.stack.popNumber();
}
