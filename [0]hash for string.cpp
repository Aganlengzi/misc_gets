/**
拉链法字符串hash表
原文： http://blog.csdn.net/hzhsan/article/details/25567679
Hash方法主要用于快速访问
需要解决两个问题:
1) 溢出：这个例子没有给出方法
2) 冲突：开放寻址法  拉链法

存储<key,value>时，hash函数并不会考虑有相同的两个key的情况
它做的处理只是将原来的具有相同的key值的那个数据段更新
而对于具有不同的key值而其计算出的hash值相同的情况才会做冲突处理，
——拉链法采用的方法是在相同的hash值对应项后面挂链表
**/
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;
#define BUFF_COUNT 1000

/*各种字符串hash函数实现一遍看看*/
unsigned int BKDRHash(char *str);   // BKDR Hash Function 【这个方法对不同情况都具有较好效果】
unsigned int SDBMHash(char *str);
unsigned int ELFHash(char *str);    // ELF Hash Function
unsigned int DJBHash(char *str);    // DJB Hash Function
unsigned int APHash(char *str);     // AP Hash Function
unsigned int BCZJhash(char *str);   // 编程珠玑
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
hash表的建立，主要是确定hash值，然后将要存储的元素加入到对应下标的链表中
不过好像链表头是浪费掉的：也就是数组中并没有放数据，而只是一个pNext指针
而且只要key相同的就是后面的覆盖前面的，明显不对啊
<并不是，这样的话实际上是对的，因为后面过来的<key, value>对正好应该是更新前面的
而hash的冲突主要是指不同的key计算出相同的hash值而采取的处理方法
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

/*******************************字符串hash函数**********************************/

/*
实际就是将字符串中所有的字母都计算在内形成一个值，作为其hash值
最后的按位与操作是控制这个hash值的取值范围
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
实际上思路是差不多的，只是这里采用较大素数进行计算
*/
unsigned int SDBMHash(char *str)
{
    unsigned int hash1 = 0;

    while(*str)
    {
        //equivalent to: hash = 65599 * hash + (*str++);
        hash1 = (*str++) + (hash1 << 6) + (hash1 << 16) - hash1;//增加计算的效率，移位比较快
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
编程珠玑中的一个hash函数
用跟元素个数最接近的质数作为散列表的大小
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

