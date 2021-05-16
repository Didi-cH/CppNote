#include <iostream>
#include <string>
#include <memory>
#include <functional>

using namespace std;

class Test
{
public:
	Test()
	{
		cout << "construct Test..." << endl;
	}
	Test(int x) :m_num(x)
	{
		cout << "construct Test, x = " << x << endl;
	}
	Test(string str)
	{
		cout << "construct Test, str = " << str << endl;
	}
	~Test()
	{
		cout << "destruct Test..." << endl;
	}
	void setValue(int v)
	{
		m_num = v;
	}
	void print()
	{
		cout << "m_num: " << m_num << endl;
	}
private:
	int m_num;
};

int main()
{
	//ͨ�����캯����ʼ��
	unique_ptr<int> ptr1(new int(9));

	//ͨ���ƶ������ʼ��
	unique_ptr<int> ptr2 = move(ptr1);

	//ͨ��reset��ʼ��
	ptr2.reset(new int(7));

	//��ȡԭʼָ��
	unique_ptr<Test> ptr3(new Test(1));
	Test* t = ptr3.get();
	t->setValue(2);
	t->print();

	ptr3->setValue(4);
	ptr3->print();

    // unique_ptr ָ��ɾ������ shared_ptr ָ��ɾ������������ģ�
    // unique_ptr ָ��ɾ������ʱ����Ҫȷ��ɾ���������ͣ�
    // ���Բ����� shared_ptr ����ֱ��ָ��ɾ������
	using ptrFunc = void(*)(Test*);
	unique_ptr<Test,ptrFunc> ptr4(new Test("hello"), [](Test* t) {
		cout << "------" << endl;
		delete t;
	});

	unique_ptr<Test, function<void(Test*)>> ptr5(new Test("hello"), [=](Test* t) {
		cout << "------" << endl;
		delete t;
	});

	//��ռ����ָ����Թ����������͵ĵ�ַ�����Զ��ͷ�
	unique_ptr<Test[]> ptr6(new Test[3]);
	//��C++11��shared_ptr��֧�������д����c++11���֧��
	shared_ptr<Test[]> ptr7(new Test[3]);
	return 0;
}