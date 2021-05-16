#include <iostream>
#include <memory>
#include <string>
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
	//一、初始化
	//1、通过构造函数初始化
	// 如果智能指针被初始化了一块有效内存，那么这块内存的引用计数 + 1，
	// 如果智能指针没有被初始化或者被初始化为 nullptr 空指针，引用计数不会 + 1。
	// 另外，不要使用一个原始指针初始化多个 shared_ptr。
	shared_ptr<int> ptr1(new int(3));
	cout << "ptr1 use count: " << ptr1.use_count() << endl;
	cout << endl;

	//2、通过移动构造和拷贝构造初始化
	// 如果使用拷贝的方式初始化共享智能指针对象，这两个对象会同时管理同一块堆内存，堆内存对应的引用计数也会增加；
	// 如果使用移动的方式初始智能指针对象，只是转让了内存的所有权，管理内存的对象并不会增加，因此内存的引用计数不会变化。
	shared_ptr<int> ptr2 = move(ptr1);
	cout << "ptr1 use count: " << ptr1.use_count() << endl;
	cout << "ptr2 use count: " << ptr2.use_count() << endl;

	shared_ptr<int> ptr3 = ptr2;
	cout << "ptr2 use count: " << ptr2.use_count() << endl;
	cout << "ptr3 use count: " << ptr3.use_count() << endl;
	cout << endl;

	//3、通过std::make_shared初始化
	shared_ptr<int> ptr4 = make_shared<int>(8);
	shared_ptr<Test> ptr5 = make_shared<Test>(8);
	shared_ptr<Test> ptr6 = make_shared<Test>("hello world!");
	cout << endl;

	//4、通过reset初始化
	// 对于一个未初始化的共享智能指针，可以通过 reset 方法来初始化，
	// 当智能指针中有值的时候，调用 reset 会使引用计数减 1。
	cout << "ptr6 use count: " << ptr6.use_count() << endl;
	ptr6.reset();
	cout << "ptr6 use count: " << ptr6.use_count() << endl;

	cout << "ptr5 use count: " << ptr5.use_count() << endl;
	ptr5.reset(new Test("hello"));
	cout << "ptr5 use count: " << ptr5.use_count() << endl;
	cout << endl;


	//二、获取原始指针
	//1、get()
	Test* t = ptr5.get();
	t->setValue(1000);
	t->print();
	cout << endl;
	//2、
	ptr5->setValue(99);
	ptr5->print();
	cout << endl;

	//三、指定删除器
	// 当智能指针管理的内存对应的引用计数变为 0 的时候，这块内存就会被智能指针析构掉了。
	// 另外，我们在初始化智能指针的时候也可以自己指定删除动作，这个删除操作对应的函数被称之为删除器，
	// 这个删除器函数本质是一个回调函数，我们只需要进行实现，其调用是由智能指针完成的。
	// 在 C++11 中使用 shared_ptr 管理动态数组时，需要指定删除器


	shared_ptr<Test> ppp(new Test(100), [](Test *t) {
		//释放内存的操作
		cout << "-------------------------" << endl;
		delete t;
	});
	cout << "ppp use count: " << ppp.use_count() << endl;

	shared_ptr<Test> p1(new Test[5], [](Test* t) {
		//释放内存的操作
		cout << "-------------------------" << endl;
		delete []t;
	});

	shared_ptr<Test> p2(new Test[5], default_delete<Test[]>());

	return 0;
}