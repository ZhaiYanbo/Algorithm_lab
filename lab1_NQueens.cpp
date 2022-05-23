/*
    实验名称：n皇后问题
    使用算法技术：回溯法
    问题描述：给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
             每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。
    例：输入：n = 4
        输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
        解释：4 皇后问题存在以上两个不同的解法。
    使用说明：在主函数中先实例化一个Solution类的对象，再通过该对象调用bt_solveNQueens、brute_solveNQueens函数，
             传入的参数为整型变量n皇后的n，得到的是一个字符串类型的二维数组，打印验证即可。
    创建时间：2022.5.12
    最后修改时间:2022.5.23
    作者：计算机2006班翟衍博 8207200203
*/

#include<iostream>
#include<vector>
#include<time.h>
#include<unordered_set>
#include<string>
using namespace std;

class Solution {
public:
    //1.回溯法解决N皇后问题（借助集合思想）
    vector<vector<string>> bt_solveNQueens(int n) 
    {
        auto res=vector<vector<string> >();     //记录结果
        auto queens=vector<int>(n,-1);           //记录每一行的皇后放在哪一列
        auto columns=unordered_set<int>();             //记录哪一列被使用过
        auto diagonals1=unordered_set<int>();          //记录哪一条对角线被使用过（从左上到右下）
        auto diagonals2=unordered_set<int>();          //记录哪一条对角线被使用过（从左下到右上）
        backtrack(res,queens,n,0,columns,diagonals1,diagonals2);
        return res;
    }

    /*
        函数名称：回溯函数
        参数列表：记录结果的字符串二维数组solutions、
                 记录皇后放置在哪一列的数组queens、
                 表示棋盘大小的变量n（即n皇后的n）
                 表示处理到哪一行的变量row
                 表示哪一列被放置过皇后的集合columns
                 表示哪一右斜对角线被放置过皇后的集合diagonals1
                 表示哪一左斜对角线被放置过皇后的集合diagonals2

    */
    void backtrack(vector<vector<string>> &solutions, vector<int> &queens, int n, int row, unordered_set<int> &columns, unordered_set<int> &diagonals1, unordered_set<int> &diagonals2) 
    {
        if (row == n) 
        {
            vector<string> board = generateBoard(queens, n);
            solutions.push_back(board);
        } 
        else 
        {
            for (int i = 0; i < n; i++) 
            {
                //该列已经放过皇后，直接跳过
                if (columns.find(i) != columns.end()) 
                {
                    continue;
                }
                int diagonal1 = row - i;
                //该右斜对角线已经放过皇后，直接跳过
                if (diagonals1.find(diagonal1) != diagonals1.end()) 
                {
                    continue;
                }
                int diagonal2 = row + i;
                //该左斜对角线已经放过皇后，直接跳过
                if (diagonals2.find(diagonal2) != diagonals2.end()) 
                {
                    continue;
                }
                //满足条件，可以放皇后
                queens[row] = i;                //保存皇后位置
                columns.insert(i);              //记录在列中
                diagonals1.insert(diagonal1);   //记录在右斜对角线中
                diagonals2.insert(diagonal2);   //记录在左斜对角线中
                //继续向下搜索
                backtrack(solutions, queens, n, row + 1, columns, diagonals1, diagonals2);

                //回溯操作
                queens[row] = -1;
                columns.erase(i);
                diagonals1.erase(diagonal1);
                diagonals2.erase(diagonal2);
            }
        }
    }

    //产生结果字符串数组的函数
    vector<string> generateBoard(vector<int> &queens, int n) {
        auto board = vector<string>();
        for (int i = 0; i < n; i++) 
        {
            string row = string(n, '.');
            row[queens[i]] = 'Q';       //queue[i]的位置放置了皇后
            board.push_back(row);
        }
        return board;
    }

    //2.暴力枚举
    bool check(vector<int>queens,int n)
    {
        int i,j;
        //每两个皇后间都必须检查一下
        for(int i=1;i<n;i++)
            for(j=0;j<i;j++)
                if((queens[i]==queens[j])||abs(queens[i]-queens[j])==abs(i-j))
                    return 0;
        return 1;
    }

    vector<vector<string>> solve4Queens() 
    {
        vector<vector<string>>res;
        vector<int>queens(4);
        for(queens[0]=0;queens[0]<4;queens[0]++)
            for(queens[1]=0;queens[1]<4;queens[1]++)
                for(queens[2]=0;queens[2]<4;queens[2]++)
                    for(queens[3]=0;queens[3]<4;queens[3]++)
                    {
                        //不满足则跳过
                        if(check(queens,4)==0)  continue;
                        else
                        {
                            vector<string> board = generateBoard(queens, 4);
                            res.push_back(board);
                        }
                    }
        return res;
    }
    vector<vector<string>> solve8Queens() 
    {
        vector<vector<string>>res;
        vector<int>queens(8);
        for(queens[0]=0;queens[0]<8;queens[0]++)
            for(queens[1]=0;queens[1]<8;queens[1]++)
                for(queens[2]=0;queens[2]<8;queens[2]++)
                    for(queens[3]=0;queens[3]<8;queens[3]++)
                        for(queens[4]=0;queens[4]<8;queens[4]++)
                            for(queens[5]=0;queens[5]<8;queens[5]++)
                                for(queens[6]=0;queens[6]<8;queens[6]++)
                                    for(queens[7]=0;queens[7]<8;queens[7]++)
                                    {
                                        //不满足则跳过
                                        if(check(queens,8)==0)  continue;
                                        else
                                        {
                                            vector<string> board = generateBoard(queens, 8);
                                            res.push_back(board);
                                        }
                                    }
        return res;
    }
    
    //输出结果
    void prinres(vector<vector<string> >res)
    {
        int row=res.size();
        int column=res[0].size();
        //输出结果
        for(int i=0;i<row;i++)
        {
            cout<<'[';
            for(int j=0;j<column;j++)
            {
                cout<<'"'<<res[i][j]<<'"';
            }
            cout<<']'<<endl;
        }
    }
};

int main()
{
    Solution solution;
    vector<vector<string>>bt4_res,bt8_res,brute4_res,brute8_res;
    clock_t start,Backtrack_finish1,Backtrack_finish2,Brute4_finish,Brute8_finish;
    //1.回溯法
    start=clock();
    bt4_res=solution.bt_solveNQueens(4);
    Backtrack_finish1=clock();
    bt8_res=solution.bt_solveNQueens(8);
    Backtrack_finish2=clock();

    //2.暴力枚举法
    brute4_res=solution.solve4Queens();
    Brute4_finish=clock();
    brute8_res=solution.solve8Queens();
    Brute8_finish=clock();

    cout<<"4皇后："<<endl;
    cout<<"回溯法用时："<<(double)(Backtrack_finish1-start)<<",有效结果如下："<<endl;
    solution.prinres(bt4_res);
    cout<<"暴力枚举用时："<<(double)(Brute4_finish-Backtrack_finish2)<<",有效结果如下："<<endl;
    solution.prinres(brute4_res);
    cout<<"8皇后："<<endl;
    cout<<"回溯法用时："<<(double)(Backtrack_finish2-Backtrack_finish1)<<",有效结果如下："<<endl;
    solution.prinres(bt8_res);
    cout<<"暴力枚举用时："<<(double)(Brute8_finish-Brute4_finish)<<",有效结果如下："<<endl;
    solution.prinres(brute8_res);

    return 0;
}