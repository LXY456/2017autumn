#pragma once
#include <iostream>
#include <cctype>
#include <string>
using namespace std;
enum StatusCode {SUCCESS,FAIL,UNDER_FLOW,OVER_FLOW,RANGE_ERROR,DUPLICATE_ERROR,NOT_PRESENT,ENTRY_INSERTED,ENTRY_FOUND,VISITED,UNVISITED};
template<class ElemType>
struct Node
{
	ElemType data;
	Node<ElemType>*next;
	Node();
	Node(ElemType item, Node<ElemType>*link = NULL);
};
template<class ElemType>
Node<ElemType>::Node()
{
	next = NULL;
}
template<class ElemType>
Node<ElemType>::Node(ElemType item, Node<ElemType>*link)
{
	data = item;
	next = link;
}
template<class ElemType>
class LinkStack
{
protected:
	Node<ElemType> *top;
	void Init();
public:
	LinkStack();
	virtual ~LinkStack();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void(*visit)(const ElemType &))const;
	StatusCode Push(const ElemType &e);
	StatusCode Top(ElemType &e) const;
	StatusCode Pop(ElemType &e);
	LinkStack(const LinkStack<ElemType>&copy);
	LinkStack<ElemType>&operator=(const LinkStack<ElemType>&copy);
};
template<class ElemType>
void LinkStack<ElemType>::Init()
{
	top = NULL;
}
template<class ElemType>
LinkStack<ElemType>::LinkStack()
{
	Init();
}
template<class ElemType>
LinkStack<ElemType>::~LinkStack()
{
	Clear();
}
template<class ElemType>
int LinkStack<ElemType>::Length() const
{
	int count = 0;
	for (Node<ElemType>*tmpPtr = top; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{
		count++;
	}
	return count;
}
template<class ElemType>
bool LinkStack<ElemType>::Empty() const
{
	return top == NULL;
}
template<class ElemType>
void LinkStack<ElemType>::Clear()
{
	ElemType tmpElem;
	while (!Empty())
		Pop(tmpElem);
}
template<class ElemType>
void LinkStack<ElemType>::Traverse(void(*visit)(const ElemType &))const
{
	Node<ElemType>*tmpPtr;
	LinkStack<ElemType>tmps;
	for (tmpPtr = top; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{
		tmps.Push(tmpPtr->data);
	}
	for (tmpPtr = tmps.top; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{
		(*visit)(tmpPtr->data);
	}
}
template<class ElemType>
StatusCode LinkStack<ElemType>::Push(const ElemType &e)
{
	Node<ElemType> *new_top = new Node<ElemType>(e, top);
	if (new_top == NULL)
	{
		return OVER_FLOW;
	}
	else
	{
		top = new_top;
		return SUCCESS;
	}
}
template<class ElemType>
StatusCode LinkStack<ElemType>::Top(ElemType &e)const
{
	if (Empty())
	{
		return UNDER_FLOW;
	}
	else
	{
		e = top->data;
		return SUCCESS;
	}
}
template<class ElemType>
StatusCode LinkStack<ElemType>::Pop(ElemType &e)
{
	if (Empty())
	{
		return UNDER_FLOW;
	}
	else
	{
		Node<ElemType> *old_top = top;
		e = old_top->data;
		top = old_top->next;
		delete old_top;
		return SUCCESS;
	}
}
template<class ElemType>
LinkStack<ElemType>::LinkStack(const LinkStack<ElemType>&copy)
{
	if (copy.Empty())
	{
		Init();
	}
	else
	{
		top = new Node<ElemType>(copy.top->data);
		Node<ElemType>*buttomPtr = top;
		for (Node<ElemType>*tmpPtr = copy.top->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
		{
			buttomPtr->next = new Node<ElemType>(tmpPtr->data);
			buttomPtr = buttomPtr->next;
		}
	}
}
template<class ElemType>
LinkStack<ElemType>&LinkStack<ElemType>::operator=(const LinkStack<ElemType>&copy)
{
	if (&copy != this)
	{
		if (copy.Empty())
		{
			Init();
		}
		else
		{
			Clear();
			top = new Node<ElemType>(copy.top->data);
			Node<ElemType>*buttomPtr = top;
			for (Node<ElemType>*tmpPtr = copy.top->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
			{
				buttomPtr->next = new Node<ElemType>(tmpPtr->data);
				buttomPtr = buttomPtr->next;
			}
		}
	}
	return *this;
}
class Calculator {
public:
	void Run()                              //执行表达式
	{
		cout << "请输入表达式：";
		optr.Push('=');
		char ch;
		char optrTop;
		double operand;
		char theta;
		//cin >> ch;

		GetChar(ch);
        //cout << ch << endl;
		//cin >> ch;
		/*while (ch!='q') 
		{
			if (!IsOperator(ch))
			{*/
				/*operand = ch - '0';
				opnd.Push(operand);
				GetChar(ch);*/

				//cin >> ch;
				//cout << operand << endl;
				//GetChar(ch);
				/*cout << "不是操作符" << endl;
				system("PAUSE");*/
			/*}
			else
			{*/
				//optr.Push(ch);
				//cin >> ch;
				//GetChar(ch);

					/*double left, right;
                    //optr.Pop(theta);
					opnd.Pop(left);
					opnd.Pop(right);
					opnd.Push(DoOperator(right, ch, left));
					GetChar(ch);*/

					//cin >> ch;
					/*cout << "是操作符" << endl;
					system("PAUSE");*/
			//}
		//}

		while ((optr.Top(optrTop), optrTop != '=') || ch != '=')
		{
			if (!IsOperator(ch))
			{
				cin.putback(ch);
				cin >> operand;
				opnd.Push(operand);
				//cin >> ch;
				GetChar(ch);
			}
			else
			{
				switch (Precede(optrTop,ch))
				{
				case '<':
					optr.Push(ch);
					GetChar(ch);
					//cin >> ch;
					break;
				case '=':
					optr.Pop(optrTop);
					GetChar(ch);
					//cin >> ch;
					break;
				case '>':
					double left, right;
					opnd.Pop(right);
					opnd.Pop(left);
					optr.Pop(theta);
					opnd.Push(DoOperator(left, theta, right));
					break;
				case 'e':
					cout << "操作符匹配错" << endl;
					exit(2);
				}
			}
		}
		opnd.Top(operand);
		cout<<"表达式值为：" << operand << endl;
    }
	void GetChar(char &ch)         //从输入流获取一字符ch,并跳过空格及回车
	{
		char a;
		cin >> a;
		while (a == '\n' || a == ' ')
		{
			cin >> a;
		}
		ch=a;
		/*if (!cin.eof())
		{
			ch = 'q';
		}*/
		/*char a;
		cin.get(a);
		if(a == '\n')
		{
			cout << "回车" << endl;
		}
		else if (a == ' ')
		{
			cout << "空格" << endl;
		}
		else
		{
			cin >> ch;
		}*/
	}
	char Precede(char theta1, char theta2)
	{
		switch (theta1)
		{
		case '+':
			if (theta2 == '+' || theta2 == '-' || theta2 == ')' || theta2 == '=')
			{
				return '>';
			}
			else
			{
				return '<';
			}
			break;
		case'-':
			if (theta2 == '+' || theta2 == '-' || theta2 == ')' || theta2 == '=')
			{
				return '>';
			}
			else
			{
				return '<';
			}
			break;
		case '*':
			if (theta2 == '+' || theta2 == '-' || theta2 == ')' || theta2 == '=' || theta2 == '*' || theta2 == '/')
			{
				return '>';
			}
			else
			{
				return '<';
			}
			break;
		case '/':
			if (theta2 == '+' || theta2 == '-' || theta2 == ')' || theta2 == '=' || theta2 == '*' || theta2 == '/')
			{
				return '>';
			}
			else
			{
				return '<';
			}
			break;
		case '(':
			if (theta2 == '+' || theta2 == '-' || theta2 == '*' || theta2 == '/' || theta2 == '(')
			{
				return '<';
			}
			else
			{
				if (theta2 == ')')
				{
					return '=';
				}
				else
				{
					return 'e';
				}
			}
			break;
		case ')':
			if (theta2 == '+' || theta2 == '-' || theta2 == '*' || theta2 == '/' || theta2 == ')' || theta2 == '=')
			{
				return '>';
			}
			else if (theta2 == '(')
			{
				return 'e';
			}
			break;
		case '=':
			if (theta2 == '+' || theta2 == '-' || theta2 == '*' || theta2 == '/' || theta2 == '(')
			{
				return '<';
			}
			else
			{
				if (theta2 == ')')
				{
					return 'e';
				}
				else
				{
					return '=';
				}
			}
			break;
		}
	}
private:
	LinkStack<double> opnd;     //操作数栈 
	LinkStack<char> optr;         //操作符栈      
	//int isp(char op);                        //栈内优先数
	//int icp(char op);                        //栈外优先数
	bool IsOperator(char ch)
	{
		bool flag = false;
		if (ch=='('||ch==')'||ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='=')
		{
			flag = true;
		}
		return flag;
	}
	double DoOperator(double x, char op, double y)
	{
		switch (op)
		{
		case '+':
		{
			double result;
			result = x + y;
			//cout << "+" << endl;
			return result;
			break;
		}
		case '-':
		{
			double result;
			result = x - y;
			return result;
			break;
		}
		case '*':
		{
			double result;
			result = x * y;
			return result;
			break;
		}
		case '/':
		{
			double result;
			result = x / y;
			return result;
			break;
		}
		}
		//形成运算指令，进行运算
	}
};
int UserSaysYes()
{
	int c;
	char a;
	cin >> a;
	if (a == 'y')
	{
		c = 1;
	}
	if (a == 'n')
	{
		c = 2;
	}
	else
	{
		c = 3;
	}
	return c;
}