/*
http://www.patest.cn/contests/pat-b-practise/1049
1049. ���е�Ƭ�κ�(20)

����һ���������У����ǿ��Դ��н�ȡ����������ļ���������ΪƬ�Ρ����磬��������{0.1, 0.2, 0.3, 0.4}��������(0.1) (0.1, 0.2) (0.1, 0.2, 0.3) (0.1, 0.2, 0.3, 0.4) (0.2) (0.2, 0.3) (0.2, 0.3, 0.4) (0.3) (0.3, 0.4) (0.4) ��10��Ƭ�Ρ�

�������������У����ȫ��Ƭ�ΰ��������е���֮�͡��籾����10��Ƭ���ܺ���0.1 + 0.3 + 0.6 + 1.0 + 0.2 + 0.5 + 0.9 + 0.3 + 0.7 + 0.4 = 5.0��

�����ʽ��

�����һ�и���һ��������105��������N����ʾ���������ĸ������ڶ��и���N��������1.0���������������е���������Կո�ָ���

�����ʽ��

��һ�����������������Ƭ�ΰ�������֮�ͣ���ȷ��С�����2λ��

����������
4
0.1 0.2 0.3 0.4 
���������
5.00
*/
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int n = 0;
    double result = 0.0;
    double the_num = 0.0;
    scanf("%d",&n);

    for( int i = 0; i < n; i++)
    {
        scanf("%lf",&the_num);
        //result += (i+1)*(n-i)*the_num; //�������˵�˳����ͨ��ȫ��������������Ϊ(i+1)*(n-i)�Ľ������Խ��
        result += the_num*(i+1)*(n-i);   //�����ǶԵ�  Խ�磡����
    }
    printf("%.2f\n",result);
    return 0;
}