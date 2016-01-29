/**
�������ַ���hash��
ԭ�ģ� http://blog.csdn.net/hzhsan/article/details/25567679
Hash������Ҫ���ڿ��ٷ���
��Ҫ�����������:
1) ������������û�и�������
2) ��ͻ������Ѱַ��  ������

�洢<key,value>ʱ��hash���������ῼ������ͬ������key�����
�����Ĵ���ֻ�ǽ�ԭ���ľ�����ͬ��keyֵ���Ǹ����ݶθ���
�����ھ��в�ͬ��keyֵ����������hashֵ��ͬ������Ż�����ͻ����
�������������õķ���������ͬ��hashֵ��Ӧ����������
**/
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;
#define BUFF_COUNT 1000

/*�����ַ���hash����ʵ��һ�鿴��*/
unsigned int BKDRHash(char *str);   // BKDR Hash Function ����������Բ�ͬ��������нϺ�Ч����
unsigned int SDBMHash(char *str);
unsigned int ELFHash(char *str);    // ELF Hash Function
unsigned int DJBHash(char *str);    // DJB Hash Function
unsigned int APHash(char *str);     // AP Hash Function
unsigned int BCZJhash(char *str);   // �������
unsigned int PJWHash(char *str);    // P. J. Weinberger Hash Function
unsigned int JSHash(char *str);     // JS Hash Function
unsigned int RSHash(char *str);     // RS Hash Function


struct Student_info
{
    string name;
    int age;
};

struct Store_info
{
    string key;
    Student_info stu;
    Store_info *pNext;
    Store_info():pNext(NULL){}
};

Store_info *buff;

/*
hash��Ľ�������Ҫ��ȷ��hashֵ��Ȼ��Ҫ�洢��Ԫ�ؼ��뵽��Ӧ�±��������
������������ͷ���˷ѵ��ģ�Ҳ���������в�û�з����ݣ���ֻ��һ��pNextָ��
����ֻҪkey��ͬ�ľ��Ǻ���ĸ���ǰ��ģ����Բ��԰�
<�����ǣ������Ļ�ʵ�����ǶԵģ���Ϊ���������<key, value>������Ӧ���Ǹ���ǰ���
��hash�ĳ�ͻ��Ҫ��ָ��ͬ��key�������ͬ��hashֵ����ȡ�Ĵ�����
>

*/
bool Hash_set(string key, const Student_info& student)
{
    unsigned int hash_index = BKDRHash((char*)key.c_str())%BUFF_COUNT;

    Store_info *pStore = &buff[hash_index];
    while((pStore->key != key) && (pStore->pNext != NULL))
    {
        pStore = pStore->pNext;
    }
    if(pStore->key == key)
    {
        pStore->stu = student;
        return true;
    }

    Store_info *pNewStore = new Store_info();
    pNewStore->key = key;
    pNewStore->stu = student;

    pStore->pNext = pNewStore;
    return true;
}


Student_info* Hash_get(string key)
{
    unsigned int hash_index = BKDRHash((char*)key.c_str())%BUFF_COUNT;
    Store_info *pStore = &buff[hash_index];

    while((pStore->key != key) && (pStore->pNext != NULL))
    {
        pStore = pStore->pNext;
    }
    if(pStore->key == key)
    {
        return &pStore->stu;
    }
    return NULL;
}

int main()
{
    //cout << "Hello world!" << endl;
    buff = new Store_info[BUFF_COUNT];
    Student_info stu1;
    stu1.name = "hu";
    stu1.age = 11;
    Hash_set("key1",stu1);

    Student_info stu2;
    stu2.name = "ha";
    stu2.age = 22;
    Hash_set("key1",stu2);

    Student_info stu3;
    stu3.name = "hW";
    stu3.age = 33;
    Hash_set("key3",stu3);

    Student_info *pstu = Hash_get("key1");
    if(pstu == NULL)
    {
        printf("ERROR: GET NULL\n");
    }
    else
    {
        printf("name: %s\nage:%d\n", pstu->name.c_str(),pstu->age);
    }

    printf("END\n");
    delete[] buff;
    return 0;
}

/*******************************�ַ���hash����**********************************/

/*
ʵ�ʾ��ǽ��ַ��������е���ĸ�����������γ�һ��ֵ����Ϊ��hashֵ
���İ�λ������ǿ������hashֵ��ȡֵ��Χ
*/
unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131;
    unsigned int hash1 = 0;
    while(*str)
    {
        hash1 = hash1 *seed + (*str++);
    }

    return (hash1 & 0x7FFFFFFF);
}
/*
ʵ����˼·�ǲ��ģ�ֻ��������ýϴ��������м���
*/
unsigned int SDBMHash(char *str)
{
    unsigned int hash1 = 0;

    while(*str)
    {
        //equivalent to: hash = 65599 * hash + (*str++);
        hash1 = (*str++) + (hash1 << 6) + (hash1 << 16) - hash1;//���Ӽ����Ч�ʣ���λ�ȽϿ�
    }
    return (hash1 & 0x7FFFFFFF);
}
/*

*/
unsigned int RSHash(char* str)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash1 = 0;

    while(*str)
    {
        hash1 = hash1 * a + (*str++);
        a *= b;
    }
    return (hash1 & 0x7FFFFFFF);
}

unsigned int ISHash(char* str)
{
    unsigned int hash1 = 1315423911;

    while(*str)
    {
        hash1 ^= ((hash1 << 5) + (*str++) + (hash1 >> 2));
    }
    return (hash1 & 0x7FFFFFFF);
}

// P. J. Weinberger Hash Function
unsigned int PJWHash(char *str)
{
    unsigned int BitsInUnignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    unsigned int ThreeQuarters    = (unsigned int)((BitsInUnignedInt  * 3) / 4);
    unsigned int OneEighth        = (unsigned int)(BitsInUnignedInt / 8);
    unsigned int HighBits         = (unsigned int)(0xFFFFFFFF) << (BitsInUnignedInt - OneEighth);
    unsigned int hash             = 0;
    unsigned int test             = 0;

    while (*str)
    {
        hash = (hash << OneEighth) + (*str++);
        if ((test = hash & HighBits) != 0)
        {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return (hash & 0x7FFFFFFF);
}

// ELF Hash Function
unsigned int ELFHash(char *str)
{
    unsigned int hash = 0;
    unsigned int x    = 0;

    while (*str)
    {
        hash = (hash << 4) + (*str++);
        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
            hash &= ~x;
        }
    }

    return (hash & 0x7FFFFFFF);
}

// DJB Hash Function
unsigned int DJBHash(char *str)
{
    unsigned int hash = 5381;

    while (*str)
    {
        hash += (hash << 5) + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

// AP Hash Function
unsigned int APHash(char *str)
{
    unsigned int hash = 0;
    int i;

    for (i=0; *str; i++)
    {
        if ((i & 1) == 0)
        {
            hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
        }
        else
        {
            hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
        }
    }

    return (hash & 0x7FFFFFFF);
}
/*
��������е�һ��hash����
�ø�Ԫ�ظ�����ӽ���������Ϊɢ�б�Ĵ�С
*/
#define NHASH 29989
#define MULT 31
unsigned int BCZJhash(char *str)
{
    unsigned int h = 0;
    for (; *str; str++)
        h = MULT *h + *str;
    return h % NHASH;
}

