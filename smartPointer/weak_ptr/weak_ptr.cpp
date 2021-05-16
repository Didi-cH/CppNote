/* 弱引用智能指针 std::weak_ptr 可以看做是 shared_ptr 的助手，
它不管理 shared_ptr 内部的指针。
std::weak_ptr 没有重载操作符 * 和 ->，
因为它不共享指针，不能操作资源，
所以它的构造不会增加引用计数，析构也不会减少引用计数，
它的主要作用就是作为一个旁观者监视 shared_ptr 中管理的资源是否存在。 */


#include <iostream>
#include <string>
#include <memory>

using namespace std;

//shared_ptr使用注意事项
//1、不能使用一个原始地址初始化多个智能指针对象
//2、函数不能返回管理了this的共享指针对象
//3、共享智能指针不能循环引用

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