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

//运算符虚基类
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
	virtual double getResult() = 0;
	virtual ~Oper()
	{

	}
private:
	double x;
	double y;
};

//加法运算
class OperatorAdd :public Oper
{
public:
	double getResult()
	{
		return getNumberA() + getNumberB();
	}
};

//减法运算
class OperatorSub :public Oper
{
public:
	double getResult()
	{
		return getNumberA() - getNumberB();
	}
};

//乘法运算
class OperatorMul :public Oper
{
public:
	double getResult()
	{
		return getNumberA() * getNumberB();
	}
};

//除法运算
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

//工厂的虚基类      
/* NOTE:
 * 工厂方法模式的优点：
 * 每次加入一个新的运算符，只需要继承OperFactory，然后产生新的对应工厂就行，不需要更改OperFactory
 *
 */
class OperFactory
{
public:
	virtual shared_ptr<Oper> createOper() = 0;
};

//专门生产加法运算符的工厂
class OperFactoryAdd :public OperFactory
{
public:
	shared_ptr<Oper> createOper()
	{
		return make_shared<OperatorAdd>();
	}
};

//专门生产减法运算符的工厂
class OperFactorySub :public OperFactory
{
public:
	shared_ptr<Oper> createOper()
	{
		return make_shared<OperatorSub>();
	}
};

//专门生产乘法运算符的工厂
class OperFactoryMul :public OperFactory
{
public:
	shared_ptr<Oper> createOper()
	{
		return make_shared<OperatorMul>();
	}
};

//专门生产除法运算符的工厂
class OperFactoryDiv :public OperFactory
{
public:
	shared_ptr<Oper> createOper()
	{
		return make_shared<OperatorDiv>();
	}
};

//测试工厂方法模式
void testFactoryMethodMode()
{
	shared_ptr<OperFactory> iFact(new OperFactoryAdd());  //比较加法与乘法，就此处的代码存在不同
	shared_ptr<Oper> oper = iFact->createOper();
	oper->setNumberA(1);
	oper->setNumberB(2);
	double res = oper->getResult();
	cout << res << endl;

	shared_ptr<OperFactory> iFact1(new OperFactoryMul());
	shared_ptr<Oper> oper1 = iFact1->createOper();
	oper1->setNumberA(2);
	oper1->setNumberB(5);
	double res1 = oper1->getResult();
	cout << res1 << endl;
}


int main()
{
	testFactoryMethodMode();
	return 0;
}

