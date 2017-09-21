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
	virtual double getResult() = 0;//使oper可实例化
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

class OperFactory
{
public:
	static shared_ptr<Oper> createOper(char operChar)
	{
		//这边会报错
		shared_ptr<Oper> oper;
		switch(operChar)
		{//这里原先用法不对，应将实例的类名放在模版中，结果显示正确
		case '+':
			////NOTE: make_shared<T>(args);   这个会实例化T(args)对象
			//oper = make_shared<Oper>(OperatorAdd());  //此处会报错。
			//what is make_shared ???
			/*
			 * template <class T, class... Args>
			 * shared_ptr<T> make_shared (Args&&... args);Make shared_ptr
			 * Allocates and constructs an object of type T passing args to its constructor, and returns an object of type shared_ptr<T> that owns and stores a pointer to it (with a use count of 1).
			 */
			oper = make_shared<OperatorAdd>();
			break;
		case '-':
			oper = make_shared<OperatorSub>();
			break;
		case '*':
			oper = make_shared<OperatorMul>();
			break;
		case '/':
			oper = make_shared<OperatorDiv>();
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
	shared_ptr<Oper> oper(OperFactory::createOper('+'));
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