/* 函数指针的定义方法 */
#include <iostream>
using namespace std;

void func(int a,char b)
{
	cout << "hello func" << endl;
}

// 1、先定义出函数的类型，再通过类型定义函数指针变量
void test01()
{
    typedef void(FUNC_TYPE)(int, char);
    FUNC_TYPE *pFunc = func;
    pFunc(10, 'a');
}

// 2、先定义出函数指针的类型，再通过类型定义函数指针变量
void test02()
{
    typedef void (*FUNC_TYPE)(int, char);
    FUNC_TYPE pFunc = func;
    pFunc(20, 'b');

    //c++
    using FUNC_TYPE2 = void (*)(int, char);
    FUNC_TYPE2 pFunc2 = func;
    pFunc2(21, 'b');
}
// 3、直接定义函数指针变量
void test03()
{
    void (*p)(int, char) = func;
    p(30, 'c');
}

//4、定义函数指针数组
void func1()
{
	cout << "func1的调用" << endl;
}
void func2()
{
	cout << "func2的调用" << endl;
}
void func3()
{
	cout << "func3的调用" << endl;
}
void test04()
{
	//函数指针数组定义方式
    void (*func_array[3])();
    func_array[0] = func1;
    func_array[1] = func2;
    func_array[2] = func3;

    for (int i = 0; i < 3;i++)
    {
        func_array[i]();
    }
}

int main()
{
        test01();
        test02();
        test03();
        test04();
        return 0;
}