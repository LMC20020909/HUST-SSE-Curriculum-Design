#include <stdio.h>
#include <string.h>
#include <algorithm>
int dp[1000][1000];
char a[1000], b[1000];
int EditDis(char* a,char* b,int dp[][1000])
{
    int len1 = strlen(a);
    int len2 = strlen(b);
  
    for (int i = 1; i <= len1; i++)
        dp[i][0] = i;       //a长度为i,b为空时，a转换成b的最小编辑距离为i
    for (int j = 0; j <= len2; j++)
        dp[0][j] = j;       //a为空，b长度为j时，a转换成b的最小编辑距离为j
    dp[0][0] = 0;           //a和b都为空时，最小编辑距离为0
    for (int i = 1; i <= len1; i++)
    {
        for (int j = 1; j <= len2; j++)
        {
            int flag;
            if (a[i-1] == b[j-1])
                flag = 0;
            else
                flag = 1;
            dp[i][j] = fmin(dp[i - 1][j] + 1, fmin(dp[i][j - 1] + 1, dp[i - 1][j - 1] + flag));
            //dp[i-1][j]+1表示删掉字符串a最后一个字符a[i]
            //dp[i][j-1]+1表示给字符串添加b最后一个字符
            //dp[i-1][j-1]+flag表示改变,相同则不需操作次数,不同则需要,用flag记录
        }
    }
    return dp[len1][len2];
}
int main(void) {
    gets_s(a);
    gets_s(b);
    int dis=EditDis(a, b, dp);
    printf("%d\n", dis);
}
