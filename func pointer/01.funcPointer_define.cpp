/* ����ָ��Ķ��巽�� */
#include <iostream>
using namespace std;

void func(int a,char b)
{
	cout << "hello func" << endl;
}

// 1���ȶ�������������ͣ���ͨ�����Ͷ��庯��ָ�����
void test01()
{
    typedef void(FUNC_TYPE)(int, char);
    FUNC_TYPE *pFunc = func;
    pFunc(10, 'a');
}

// 2���ȶ��������ָ������ͣ���ͨ�����Ͷ��庯��ָ�����
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
// 3��ֱ�Ӷ��庯��ָ�����
void test03()
{
    void (*p)(int, char) = func;
    p(30, 'c');
}

//4�����庯��ָ������
void func1()
{
	cout << "func1�ĵ���" << endl;
}
void func2()
{
	cout << "func2�ĵ���" << endl;
}
void func3()
{
	cout << "func3�ĵ���" << endl;
}
void test04()
{
	//����ָ�����鶨�巽ʽ
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