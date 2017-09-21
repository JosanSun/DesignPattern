/*
 * ---------------------------------------------------
 *  Copyright (c) 2017 josan All rights reserved.
 * ---------------------------------------------------
 *
 *               创建者： Josan
 *             创建时间： 2017/9/18 16:57:06
 */
#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
#include <memory>
using namespace std;


class Oper
{
public:
	double getNumberA()
	{
		return x;
	}
	void setNumberA(double xx)
	{
		x = xx;
	}
	double getNumberB()
	{
		return y;
	}
	void setNumberB(double yy)
	{
		y = yy;
	}
	virtual double getResult()
	{
		return 0.0;
	};
private:
	double x;
	double y;
};

class OperatorAdd :public Oper
{
public:
	double getResult()
	{
		return getNumberA() + getNumberB();
	}
};

class OperatorSub :public Oper
{
public:
	double getResult()
	{
		return getNumberA() - getNumberB();
	}
};

class OperatorMul :public Oper
{
public:
	double getResult()
	{
		return getNumberA() * getNumberB();
	}
};

class OperatorDiv :public Oper
{
public:
	double getResult()
	{
		try
		{
			if(fabs(getNumberB()) < 1e-9)
			{
				throw overflow_error("Divide by zero exception");
			}
		}
		catch(overflow_error& e)
		{
			cout << e.what() << " -> " << getNumberB() << endl;
		}
		return getNumberA() / getNumberB();
	}
};

//简答工厂模式  生产出所有的运算符类 
class OperFactory
{
public:
	static Oper* createOper(char operChar)
	{
		Oper* oper = nullptr;
		switch(operChar)
		{
		case '+':
			oper = new OperatorAdd();
			break;
		case '-':
			oper = new OperatorSub();
			break;
		case '*':
			oper = new OperatorMul();
			break;
		case '/':
			oper = new OperatorDiv();
			break;
			//other operation
		default:
			;
		}
		return oper;
	}
};

void testSimpleFactoryMode()
{
	Oper* oper(OperFactory::createOper('+'));
	oper->setNumberA(1);
	oper->setNumberB(2);
	double res = oper->getResult();
	cout << res << endl;
}


int main()
{
	testSimpleFactoryMode();
	return 0;
}

