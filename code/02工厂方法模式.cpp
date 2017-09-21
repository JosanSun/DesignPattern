/*
* ---------------------------------------------------
*  Copyright (c) 2017 josan All rights reserved.
* ---------------------------------------------------
*
*               �����ߣ� Josan
*             ����ʱ�䣺 2017/9/18 16:57:06
*/
#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
#include <memory>
using namespace std;

//����������
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

//�ӷ�����
class OperatorAdd :public Oper
{
public:
	double getResult()
	{
		return getNumberA() + getNumberB();
	}
};

//��������
class OperatorSub :public Oper
{
public:
	double getResult()
	{
		return getNumberA() - getNumberB();
	}
};

//�˷�����
class OperatorMul :public Oper
{
public:
	double getResult()
	{
		return getNumberA() * getNumberB();
	}
};

//��������
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

//�����������      
/* NOTE:
 * ��������ģʽ���ŵ㣺
 * ÿ�μ���һ���µ��������ֻ��Ҫ�̳�OperFactory��Ȼ������µĶ�Ӧ�������У�����Ҫ����OperFactory
 *
 */
class OperFactory
{
public:
	virtual shared_ptr<Oper> createOper() = 0;
};

//ר�������ӷ�������Ĺ���
class OperFactoryAdd :public OperFactory
{
public:
	shared_ptr<Oper> createOper()
	{
		return make_shared<OperatorAdd>();
	}
};

//ר����������������Ĺ���
class OperFactorySub :public OperFactory
{
public:
	shared_ptr<Oper> createOper()
	{
		return make_shared<OperatorSub>();
	}
};

//ר�������˷�������Ĺ���
class OperFactoryMul :public OperFactory
{
public:
	shared_ptr<Oper> createOper()
	{
		return make_shared<OperatorMul>();
	}
};

//ר����������������Ĺ���
class OperFactoryDiv :public OperFactory
{
public:
	shared_ptr<Oper> createOper()
	{
		return make_shared<OperatorDiv>();
	}
};

//���Թ�������ģʽ
void testFactoryMethodMode()
{
	shared_ptr<OperFactory> iFact(new OperFactoryAdd());  //�Ƚϼӷ���˷����ʹ˴��Ĵ�����ڲ�ͬ
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

