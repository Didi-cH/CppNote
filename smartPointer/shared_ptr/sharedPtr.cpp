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
	//һ����ʼ��
	//1��ͨ�����캯����ʼ��
	// �������ָ�뱻��ʼ����һ����Ч�ڴ棬��ô����ڴ�����ü��� + 1��
	// �������ָ��û�б���ʼ�����߱���ʼ��Ϊ nullptr ��ָ�룬���ü������� + 1��
	// ���⣬��Ҫʹ��һ��ԭʼָ���ʼ����� shared_ptr��
	shared_ptr<int> ptr1(new int(3));
	cout << "ptr1 use count: " << ptr1.use_count() << endl;
	cout << endl;

	//2��ͨ���ƶ�����Ϳ��������ʼ��
	// ���ʹ�ÿ����ķ�ʽ��ʼ����������ָ����������������ͬʱ����ͬһ����ڴ棬���ڴ��Ӧ�����ü���Ҳ�����ӣ�
	// ���ʹ���ƶ��ķ�ʽ��ʼ����ָ�����ֻ��ת�����ڴ������Ȩ�������ڴ�Ķ��󲢲������ӣ�����ڴ�����ü�������仯��
	shared_ptr<int> ptr2 = move(ptr1);
	cout << "ptr1 use count: " << ptr1.use_count() << endl;
	cout << "ptr2 use count: " << ptr2.use_count() << endl;

	shared_ptr<int> ptr3 = ptr2;
	cout << "ptr2 use count: " << ptr2.use_count() << endl;
	cout << "ptr3 use count: " << ptr3.use_count() << endl;
	cout << endl;

	//3��ͨ��std::make_shared��ʼ��
	shared_ptr<int> ptr4 = make_shared<int>(8);
	shared_ptr<Test> ptr5 = make_shared<Test>(8);
	shared_ptr<Test> ptr6 = make_shared<Test>("hello world!");
	cout << endl;

	//4��ͨ��reset��ʼ��
	// ����һ��δ��ʼ���Ĺ�������ָ�룬����ͨ�� reset ��������ʼ����
	// ������ָ������ֵ��ʱ�򣬵��� reset ��ʹ���ü����� 1��
	cout << "ptr6 use count: " << ptr6.use_count() << endl;
	ptr6.reset();
	cout << "ptr6 use count: " << ptr6.use_count() << endl;

	cout << "ptr5 use count: " << ptr5.use_count() << endl;
	ptr5.reset(new Test("hello"));
	cout << "ptr5 use count: " << ptr5.use_count() << endl;
	cout << endl;


	//������ȡԭʼָ��
	//1��get()
	Test* t = ptr5.get();
	t->setValue(1000);
	t->print();
	cout << endl;
	//2��
	ptr5->setValue(99);
	ptr5->print();
	cout << endl;

	//����ָ��ɾ����
	// ������ָ�������ڴ��Ӧ�����ü�����Ϊ 0 ��ʱ������ڴ�ͻᱻ����ָ���������ˡ�
	// ���⣬�����ڳ�ʼ������ָ���ʱ��Ҳ�����Լ�ָ��ɾ�����������ɾ��������Ӧ�ĺ�������֮Ϊɾ������
	// ���ɾ��������������һ���ص�����������ֻ��Ҫ����ʵ�֣��������������ָ����ɵġ�
	// �� C++11 ��ʹ�� shared_ptr ����̬����ʱ����Ҫָ��ɾ����


	shared_ptr<Test> ppp(new Test(100), [](Test *t) {
		//�ͷ��ڴ�Ĳ���
		cout << "-------------------------" << endl;
		delete t;
	});
	cout << "ppp use count: " << ppp.use_count() << endl;

	shared_ptr<Test> p1(new Test[5], [](Test* t) {
		//�ͷ��ڴ�Ĳ���
		cout << "-------------------------" << endl;
		delete []t;
	});

	shared_ptr<Test> p2(new Test[5], default_delete<Test[]>());

	return 0;
}