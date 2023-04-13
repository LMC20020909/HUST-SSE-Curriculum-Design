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
        dp[i][0] = i;       //a����Ϊi,bΪ��ʱ��aת����b����С�༭����Ϊi
    for (int j = 0; j <= len2; j++)
        dp[0][j] = j;       //aΪ�գ�b����Ϊjʱ��aת����b����С�༭����Ϊj
    dp[0][0] = 0;           //a��b��Ϊ��ʱ����С�༭����Ϊ0
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
            //dp[i-1][j]+1��ʾɾ���ַ���a���һ���ַ�a[i]
            //dp[i][j-1]+1��ʾ���ַ������b���һ���ַ�
            //dp[i-1][j-1]+flag��ʾ�ı�,��ͬ�����������,��ͬ����Ҫ,��flag��¼
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
