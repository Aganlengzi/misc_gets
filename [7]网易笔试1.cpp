/*
http://www.nowcoder.com/test/question/fe6c73cb899c4fe1bdd773f8d3b42c3d?pid=970447&tid=2475394
*/
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <deque>

using namespace std;
/* T3
int main()
{
    int M, N, K, x, y, result = 0;
    int table[21][21] = {0};
    int res[21][21] = {0};
    while(scanf("%d %d %d", &N, &M, &K)!= EOF)
    {
        result = 0;
        for(int i = 0; i < 21; i++)
        {
            for(int j = 0; j < 21; j++)
            {
                table[i][j] = res[i][j] = 0;
            }
        }
        if(N < 3)

        for(int i = 0; i < K; i++)
        {
            scanf("%d %d",&x, &y);
            table[x][y]++;
        }

    //find max
    int max_num = 0, max_x = 0, max_y = 0;
    for(int j = 2; j < N ; j++)
    {
        for(int k = 2; k < M ; k++)
        {
            res[j][k] = table[j][k] + table[j-1][k+1] + table[j-1][k] + table[j-1][k-1] + table[j][k+1] + table[j][k-1] + table[j+1][k+1] + table[j+1][k] + table[j+1][k-1];
            if(max_num < res[j][k])
            {
                max_num = res[j][k];
                max_x = j; max_y = k;
            }
        }
    }
    //result += max_num;


    if(table[max_x][max_y] > 0)
       table[max_x][max_y] -= 1,result++;
    if(table[max_x-1][max_y+1] > 0)
        table[max_x-1][max_y+1] -= 1,result++;
    if(table[max_x-1][max_y] > 0)
        table[max_x-1][max_y] -= 1,result++;
    if(table[max_x-1][max_y-1] > 0)
        table[max_x-1][max_y-1] -= 1,result++;
    if(table[max_x][max_y+1] > 0)
        table[max_x][max_y+1] -= 1,result++;
    if(table[max_x][max_y-1] > 0)
        table[max_x][max_y-1] -= 1,result++;
    if(table[max_x+1][max_y+1] > 0)
        table[max_x+1][max_y+1] -= 1,result++;
    if(table[max_x+1][max_y] > 0)
        table[max_x+1][max_y] -= 1,result++;
    if(table[max_x+1][max_y-1] > 0)
        table[max_x+1][max_y-1] -= 1,result++;

    printf("%d\n",result);
    max_num = 0;
    for(int i = 0; i < 21; i++)
        {
            for(int j = 0; j < 21; j++)
            {
                res[i][j] = 0;
            }
        }

    for(int j = 2; j < N ; j++)
    {
        for(int k = 2; k < M ; k++)
        {
            //res[j][k] = table[j][k] + table[j-1][k+1] + table[j-1][k] + table[j-1][k-1] + table[j][k+1] + table[j][k-1] + table[j+1][k+1] + table[j+1][k] + table[j+1][k-1];
            if(max_num < res[j][k])
            {
                max_num = res[j][k];
                max_x = j; max_y = k;
            }
        }
    }
    if(table[max_x][max_y] > 0)
       table[max_x][max_y] -= 1,result++;
    if(table[max_x-1][max_y+1] > 0)
        table[max_x-1][max_y+1] -= 1,result++;
    if(table[max_x-1][max_y] > 0)
        table[max_x-1][max_y] -= 1,result++;
    if(table[max_x-1][max_y-1] > 0)
        table[max_x-1][max_y-1] -= 1,result++;
    if(table[max_x][max_y+1] > 0)
        table[max_x][max_y+1] -= 1,result++;
    if(table[max_x][max_y-1] > 0)
        table[max_x][max_y-1] -= 1,result++;
    if(table[max_x+1][max_y+1] > 0)
        table[max_x+1][max_y+1] -= 1,result++;
    if(table[max_x+1][max_y] > 0)
        table[max_x+1][max_y] -= 1,result++;
    if(table[max_x+1][max_y-1] > 0)
        table[max_x+1][max_y-1] -= 1,result++;

    printf("%d\n",result);
    }
}
*/


/*T2
double Rdistance(int x0, int y0, int x, int y)
{
    return sqrt((x0 - x)*(x0 - x) + (y0 - y)*(y0 - y));
}


int main()
{
    int R,x1,y1,x2,y2,x3,y3,x0,y0, res = 0;
    while( scanf("%d %d %d %d %d %d %d %d %d", &R, &x1, &y1, &x2, &y2, &x3, &y3, &x0, &y0) != EOF )
    {
        res = 0;
        if(Rdistance(x1,y1,x0,y0) <= R)
            res++;
        if(Rdistance(x2,y2,x0,y0) <= R)
            res++;
        if(Rdistance(x3,y3,x0,y0) <= R)
            res++;
        printf("%dx\n", res);
    }


}
*/
/* T1
int max_common(int m, int n)  //这个辗转相除法是一定要掌握的
{
    int r = n;
    while(r)
    {
        r = m%n;
        m = n;
        n = r;
    }
    return m;

}

int main()
{
    int n, a, next = 0,c = 0;
    while(scanf("%d %d", &n, &a)!= EOF)  // while(scanf("%d %d", &n, &a)!= EOF) 这一句的标准写法
    {
        c = a;
        for(int i = 0; i < n; i++)
        {
            scanf("%d", &next);
            if(next <= c)
            {
                c += next;
            }
            else
            {
                c += max_common(c, next);
            }
        }
        printf("%d\n", c);
    }
}

*/