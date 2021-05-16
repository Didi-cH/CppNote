/* ����������ָ�� std::weak_ptr ���Կ����� shared_ptr �����֣�
�������� shared_ptr �ڲ���ָ�롣
std::weak_ptr û�����ز����� * �� ->��
��Ϊ��������ָ�룬���ܲ�����Դ��
�������Ĺ��첻���������ü���������Ҳ����������ü�����
������Ҫ���þ�����Ϊһ���Թ��߼��� shared_ptr �й������Դ�Ƿ���ڡ� */


#include <iostream>
#include <string>
#include <memory>

using namespace std;

//shared_ptrʹ��ע������
//1������ʹ��һ��ԭʼ��ַ��ʼ���������ָ�����
//2���������ܷ��ع�����this�Ĺ���ָ�����
//3����������ָ�벻��ѭ������

struct Test:public enable_shared_from_this<Test>
{
	shared_ptr<Test> getSharedPtr()
	{
		return shared_from_this();
	}
	~Test()
	{
		cout << "class Test is disstruct ... " << endl;
	}
};
struct TA;
struct TB;

struct TA
{
	weak_ptr<TB> bptr;
	~TA()
	{
		cout << "class TA is disstruct ... " << endl;
	}
};

struct TB
{
	shared_ptr<TA> bptr;
	~TB()
	{
		cout << "class TB is disstruct ... " << endl;
	}
};

void testPtr()
{
	shared_ptr<TA> ap(new TA);
	shared_ptr<TB> bp(new TB);
	cout << "TA object use count: " << ap.use_count() << endl;
	cout << "TB object use count: " << bp.use_count() << endl;

	ap->bptr = bp;
	bp->bptr = ap;
	cout << "TA object use count: " << ap.use_count() << endl;
	cout << "TB object use count: " << bp.use_count() << endl;
}

int main()
{
	Test* t = new Test;
	shared_ptr<Test> ptr1(t);
	shared_ptr<Test> ptr2 = ptr1;

	shared_ptr<Test> sp1(new Test);
	cout << "use_count: " << sp1.use_count() << endl;
	shared_ptr<Test> sp2 = sp1->getSharedPtr();
	cout << "use_count: " << sp1.use_count() << endl;

	testPtr();

	return 0;
}