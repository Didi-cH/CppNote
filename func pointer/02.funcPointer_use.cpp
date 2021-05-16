//函数指针做函数参数，回调函数
#include <iostream>
#include <string.h>
using namespace std;

struct Person
{
	char name[64];
	int age;
};

//案例一：打印任意类型数据
void myPrint(void *data,void(*mp)(void*))
{
    mp(data);
}
void printInt(void *data)
{
    int *num = (int *)data;
    cout << *num << endl;
}
void callback(void *data)
{
    Person *p = (Person *)data;
    cout << p->name << ";" << p->age << endl;
}
void test01()
{
    int a = 10;
    myPrint(&a, printInt);

    Person p{"abc", 18};
    myPrint(&p, callback);
}

//案例二：打印任意类型数组
void printAllArray(void *arr,int eleSize, int len,void(*myPrint)(void*))
{
	char* p = (char*)arr;
	for (int i = 0; i < len; i++)
	{
		char* pArr = p + eleSize * i;
		//cout << *(int*)pArr << endl;
		myPrint(pArr);
	}
}

void printPerson(void* data)
{
	Person* p = (Person*)data;
	cout << p->name << " " << p->age << endl;
}
void test02()
{
	Person personArr[] = {
		{"a",16},
		{"b",17},
		{"c",18},
		{"d",19},
	};
	int len = sizeof(personArr) / sizeof(Person);
	printAllArray(personArr, sizeof(Person), len, printPerson);
}

//案例三：查找数组中是否有指定类型的元素，如果有返回1，如果没有返回0
int findArrEle(void* array, int eleSize, int len, void* data,bool(*myCompare)(void *,void *))
{
	char* p = (char*)array;
	for (int i = 0; i < len; i++)
	{
		char* pArr = p + eleSize * i;

		if (myCompare(data, pArr))
		{
			return 1;
		}
	}

	return 0;
}

bool callback3(void* data1, void* data2)
{
	Person* p1 = (Person*)data1;
	Person* p2 = (Person*)data2;

	if (strcmp(p1->name,p2->name)==0 && p1->age == p2->age)
	{
		return true;
	}
	return false;
}

void test03()
{
	Person personArr[] = {
	{"a",16},
	{"b",17},
	{"c",18},
	{"d",19},
	};

	int len = sizeof(personArr) / sizeof(Person);
	Person p1 = { "c",18 };
	int ret = findArrEle(personArr, sizeof(Person), len, &p1, callback3);

	if (ret)
	{
		cout << "找到这个元素" << endl;
	}
	else
	{
		cout << "没有找到" << endl;
	}
}

int main()
{
    test01();
    test02();
    test03();
    return 0;
}