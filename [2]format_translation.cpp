/*
注意(int&)a的含义和*(int*(&a))是一致的
表示的含义是将a原原本本的看成是int
而int(a)是将a转换成int，其中是涉及到格式的转换的

boolalpha将bool数值转换成true或false进行显示
*/
#include <iostream>

using namespace std;

int main()
{
    float a = 1.0f;
    cout<<(int)a<<endl;
    cout<<&a<<endl;
    cout<<(int&)a<<endl;
    cout<<*((int*)&a)<<endl;
    cout<<boolalpha<<((int)a == (int&)a)<<endl;

    cout<<"----------------------\n";

    float b = 0.0f;
    cout<<(int)b<<endl;
    cout<<&b<<endl;
    cout<<(int&)b<<endl;
    cout<<*((int*)&b)<<endl;
    cout<<boolalpha<<((int)b == (int&)b)<<endl;

    cout << "Hello world!" << endl;
    return 0;
}