#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;
#define MAX_LEN 20;
class Test
{
public :
	int a;
	int b;
	Test()
	{
	}
	~Test()
	{
	}
	Test(int a, int b)
	{
		this->a=a;
		this->b=b;
	}
	//int operator + (const Test& t) const;
	Test operator + (const Test& t) const;
	Test operator - (const Test& t) const;
	int operator * (const Test& t) const;
	bool operator == (const Test& t) const;
	//Test operator = (Test& t) const;
private:
};
Test Test::operator + (const Test& t) const
{
	Test test;
	test.a=this->a+t.a;
	test.b=this->b+t.b;
	return test;
}
Test Test::operator - (const Test& t) const
{
	Test test;
	test.a=this->a-t.a;
	test.b=this->b-t.b;
	return test;
}
bool Test::operator == (const Test& t) const
{
	return this->a==t.a&&this->b==t.b;
}
int Test::operator * (const Test& t) const
{
	return this->a*t.a+this->b*t.b;
}
int main()
{

	Test t1(1,2),t2(3,4),t3;
	t3=t2 + t1;
	cout<<t3.a<<" "<<t3.b<<endl;
	t3=t2 - t1;
	cout<<t3.a<<" "<<t3.b<<endl;
	t3=t1 - t2;
	cout<<t3.a<<" "<<t3.b<<endl;
	string result = (t2 == t1) ? "TRUE" : "FALSE";
	cout<<result<<endl;
	int k = t2*t1;
	cout<<k<<endl;
	return 0;
}