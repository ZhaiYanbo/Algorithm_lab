/*
    实验名称：01背包问题
    使用算法技术：蛮力法、动态规划、贪心法
    问题描述：一个旅行者有一个最多能装 M 公斤的背包，现在有 n 件物品，
             它们的重量分别是W1，W2，...,Wn,它们的价值分别为C1,C2,...,Cn，求旅行者能获得最大总价值。
    
    例：当weights={2,3,4,7}，values={1,3,5,9}时，M=10,n=4时，
        结果应为12.
        解释，选取第二件和第四件物品。
    
    使用说明：在主函数中先实例化一个Solution类的对象，再通过该对象调用bruteSolution、dpSolution、greedySolution函数，
             传入的参数为物品重量数组、物品价值数组、背包容量、物品个数，返回值是背包可容纳的最大价值，打印验证即可。
    创建时间：2022.5.17
    最后修改时间:2022.5.23
    作者：计算机2006班翟衍博 8207200203
*/
#include<iostream>
#include<time.h>
#include<vector>
#include<algorithm>
using namespace std;
class Solution
{
public:
    //蛮力法的辅助函数，用于深度优先遍历
    /*
        res:记录结果
        i：处理到第几个物品
        n:总共有多少个物品
        m：当前背包的剩余容量
        weights:表示物品重量的数组
        values:表示物品价值的数组
        val:记录当前价值
    */
    void dfs(int& res,int i,const int n,int m,const vector<int>weights,const vector<int>values, int val)
    {
        if(m<0)     return ;    //背包容量小于零，答案无效，直接返回
        if(i == n || m == 0)    //物品处理完或者背包容量占用完，更新res的值
        {
            res = max(res, val);
            return;
        }

        dfs(res, i+1, n, m - weights[i], weights, values, val + values[i]); //选
        dfs(res, i+1, n, m, weights, values, val);                          //不选
    }

    //1.蛮力法
    int bruteSolution(const vector<int>weights,const vector<int>values,const int M,const int n)
    {
        int res=0;
        dfs(res,0,n,M,weights,values, 0);
        return res;
    }

    //2.动态规划解法
    int dpSolution(const vector<int>weights,const vector<int>values,const int M,const int n)
    {
        vector<vector<int> >dp(n+1,vector<int>(M+1));   //二维dp数组

        //初始化边界
        /*因为vector初始值为0，所以这一步可以省略*/

        //开始计算dp表
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=M;j++)
            {
                //剩余容量小于当前物品重量，weights[i-1]表示第i个物品重量
                if(j<weights[i-1])    dp[i][j]=dp[i-1][j];     
                //背包容量大于当前物品重量，考虑拿还是不拿
                else    dp[i][j]=max(dp[i-1][j-weights[i-1]]+values[i-1],dp[i-1][j]);
                //cout<<dp[i][j]<<" ";
            }
            //cout<<endl;
        }
        //返回结果
        return dp[n][M];
    }

    //表示物品的结构体
    struct obj
    {
        int w;  //重量
        int v;  //价值
        double p;  //价值重量比
    };

    //3.贪心
    int greedySolution(const vector<int>weights,const vector<int>values,const int M,const int n)
    {
        
        obj items[n];
        for(int i=0;i<n;i++)
        {
            struct obj newo;
            newo.w=weights[i];
            newo.v=values[i];
            newo.p=double(values[i])/weights[i];
            items[i]=newo;
        }
        //将物品按单位价值从大到小排序
        myQuickSort(0,n-1,items);
        int m=M;    //背包当前容量
        int ans=0;
        for(int i=0;i<n;i++)
        {
            if(m>=items[i].w)
            {
                ans+=items[i].v;
                m-=items[i].w;
            }
            
        }
        return ans;
    }
    
    //快排
    void myQuickSort(int left,int right,obj items[])
    {
        if(left>=right)  return;
        int i=left,j=right;
        double base=items[left].p;  //取最左边的数为基准数
        while(i<j)
        {
            //一直从右边向左找到一个大于base的数
            while(items[j].p<=base&&i<j)
                j--;
            //一直从左往右找到一个小于base的数
            while(items[i].p>=base&&i<j)
                i++;
            //交换
            if(i<j)
            {
                obj temp=items[i];
                items[i]=items[j];
                items[j]=temp;
            }
        }
        //基准数归位
        obj temp=items[left];
        items[left]=items[i];
        items[i]=temp;
        //递归左半区间与右半区间
        myQuickSort(left,i-1,items);
        myQuickSort(i+1,right,items);
    }

};

int main()
{
    // int M=8;   //背包容量
    // int n=5;    //物品数量
    // vector<int>weights={3,5,1,2,2};   //物品重量
    // vector<int>values={4,5,2,1,3};    //物品价值
    int M=255;
    int n=20;
    vector<int>weights={62 ,
                        24 ,
                        90 ,
                        97 ,
                        36 ,
                        38 ,
                        90 ,
                        37 ,
                        91 ,
                        26 ,
                        31 ,
                        82 ,
                        89 ,
                        26 ,
                        54 ,
                        52 ,
                        25 ,
                        71 ,
                        59 ,
                        63 };
    vector<int>values={ 
                          76
                        , 57
                        , 92
                        , 46
                        , 50
                        , 32
                        , 30
                        , 75
                        , 46
                        , 57
                        , 25
                        , 30
                        , 49
                        , 57
                        , 28
                        , 98
                        , 10
                        , 86
                        , 66
                        , 32
                        };
    clock_t start,Brute_finish,DP_finish,Greedy_finish;
    int Brute_ans,DP_ans,Greedy_ans;
    Solution solution1;
    start=clock();      //开始时间

    //蛮力法,O(2^n)
    int cnt=1000;
    while(cnt--)
        Brute_ans=solution1.bruteSolution(weights,values,M,n);
    Brute_finish=clock();

    //动态规划法,O(nM)
    cnt=1000;
    while(cnt--)
    DP_ans=solution1.dpSolution(weights,values,M,n);
    DP_finish=clock();

    //贪心,O(N)
    cnt=1000;
    while(cnt--)
    Greedy_ans=solution1.greedySolution(weights,values,M,n);
    Greedy_finish=clock();

    cout<<"Brute_solution:"<<Brute_ans<<"  执行用时："<<(double)(Brute_finish-start)/CLOCKS_PER_SEC<<endl;
    cout<<"DP_solution:"<<DP_ans<<"  执行用时："<<(double)(DP_finish-Brute_finish)/CLOCKS_PER_SEC<<endl;
    cout<<"Greedy_solution:"<<Greedy_ans<<"  执行用时："<<(double)(Greedy_finish-DP_finish)/CLOCKS_PER_SEC<<endl;
    return 0;
}
