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
	//通过构造函数初始化
	unique_ptr<int> ptr1(new int(9));

	//通过移动构造初始化
	unique_ptr<int> ptr2 = move(ptr1);

	//通过reset初始化
	ptr2.reset(new int(7));

	//获取原始指针
	unique_ptr<Test> ptr3(new Test(1));
	Test* t = ptr3.get();
	t->setValue(2);
	t->print();

	ptr3->setValue(4);
	ptr3->print();

    // unique_ptr 指定删除器和 shared_ptr 指定删除器是有区别的，
    // unique_ptr 指定删除器的时候需要确定删除器的类型，
    // 所以不能像 shared_ptr 那样直接指定删除器。
	using ptrFunc = void(*)(Test*);
	unique_ptr<Test,ptrFunc> ptr4(new Test("hello"), [](Test* t) {
		cout << "------" << endl;
		delete t;
	});

	unique_ptr<Test, function<void(Test*)>> ptr5(new Test("hello"), [=](Test* t) {
		cout << "------" << endl;
		delete t;
	});

	//独占智能指针可以管理数组类型的地址，能自动释放
	unique_ptr<Test[]> ptr6(new Test[3]);
	//在C++11中shared_ptr不支持下面的写法，c++11后才支持
	shared_ptr<Test[]> ptr7(new Test[3]);
	return 0;
}