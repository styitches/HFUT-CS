/*#include<iostream>
using namespace std;
#include<vector>
#include<set>

bool isF1(vector<vector<int>>A) //检验关系矩阵是否具有自反性
{
    for (int n = 0; n < A.size(); n++)
    {
        if (A[n][n] == 0)
        {
            return false;
        }
    }
    return true;
}

bool isF2(vector<vector<int>>A) //检验关系矩阵是否具有对称性
{
    for (int n = 0; n < A.size(); n++)
    {
        for (int m = 0; m < A.size(); m++)
        {
            if (A[m][n] != A[n][m])
            {
                return false;
            }
        }
    }
    return true;
}

bool isF3(vector<vector<int>>A) //检验关系是否具有传递性
{
    vector<vector<int>>B;
    for (int n = 0; n < A.size(); n++)
    {
        for (int m = 0; m < A.size(); m++)
        {
            if (A[n][m] == 1)
            {
                B.push_back({ n,m });
            }
        }
    }
    for (int n = 0; n < B.size(); n++)
    {
        for (int m = 0; m < B.size(); m++)
        {
            if (B[n][1] == B[m][0])
            {
                if (A[B[n][0]][B[m][1]] == 0)
                {
                    //cout << "关系为" << B[n][0] << B[m][1] << endl;
                    return false;
                }
            }
        }
    }
    return true;
}

bool project1(vector<vector<int>>A) //检验关系是否为等价关系
{
    if (isF1(A) == 1)
    {
        if (isF2(A) == 1)
        {
            if (isF3(A) == 1)
            {
                return true;
            }
            else
            {
                cout << "不满足传递性" << endl;
                return false;
            }
        }
        else
        {
            cout << "不满足对称性" << endl;
            return false;
        }
    }
    else
    {
        cout << "不满足自反性" << endl;
        return false;
    }
}

bool project2(vector<vector<int>> A) //检验关系是否为偏序关系
{
    if (isF1(A) == 1)
    {
        if (isF2(A) == 0)
        {
            if (isF3(A) == 1)
            {
                return true;
            }
            else
            {
                cout << "不满足传递性" << endl;
                return false;
            }
        }
        else
        {
            cout << "不满足反对称性" << endl;
            return false;
        }
    }
    else
    {
        cout << "不满足自反性" << endl;
        return false;
    }
}

void F(vector<vector<int>> A) //求等价关系的商集
{
    vector<vector<int>>B;
    set<set<int>>D;
    for (int n = 0; n < A.size(); n++)
    {
        for (int m = 0; m < A.size(); m++)
        {
            if (A[n][m] == 1)
            {
                B.push_back({ n,m });
            }
        }
    }
    for (int n = 0; n < B.size(); n++)
    {
        set<int> C;
        for (int m = 0; m < B.size(); m++)
        {
            if (B[n][1] == B[m][0])
            {
                C.insert(B[n][0]);
                C.insert(B[n][1]);
                C.insert(B[m][1]);
            }
        }
        D.insert(C);
    }
    cout << "（商集）等价类有" << endl;
    for (set<set<int>>::iterator it1 = D.begin(); it1!= D.end(); it1++)
    {
        cout << "{";
        for (set<int>::iterator it2 = it1->begin(); it2 != it1->end(); it2++)
        {
            cout << *it2 + 1 << " ";
        }
        cout << "}" << endl;
    }
    return;
}

void final(vector<vector<int>>A)  //打印哈斯图
{
    for (int a = 0; a < A.size(); a++)
    {
        for (int b = 0; b < A.size(); b++)
        {
            A[a][a] = 0;
        }
    }
    for (int n = 0; n < A.size(); n++)
    {
        for (int m = 0; m < A.size(); m++)
        {
            if (A[n][m] == 1)
            {
                for (int k = 0; k < A.size(); k++)
                {
                    if (A[n][k] == 1 && A[k][m] == 1)
                    {
                        A[n][m] = 0;
                    }
                }
            }
        }
    }
    cout << "哈斯图路径为" << endl;
    for (int a = 0; a < A.size(); a++)
    {
        for (int b = 0; b < A.size(); b++)
        {
            if (A[a][b] == 1)
            {
                cout << "<" << a+1 << "," << b+1 << ">" << endl;
            }
        }
    }
    return;
}

int main()
{
    vector<vector<int>>A1 =
            {   {1,0,0,0,0},
                {0,1,1,1,0},
                {0,1,1,1,0},
                {0,1,1,1,0},
                {0,0,0,0,1}
            }; //定义等价关系矩阵
    cout << "关系矩阵为"<< endl;
    cout << "1 0 0 0 0" << endl;
    cout << "0 1 1 1 0" << endl;
    cout << "0 1 1 1 0" << endl;
    cout << "0 1 1 1 0" << endl;
    cout << "0 0 0 0 1" << endl;
    //cout << isF1(A1) << isF2(A1) << isF3(A1) << endl;
    if (project1(A1))
    {
        cout << "该关系是等价关系" << endl;
        F(A1);
    } else {
        cout << "不是等价关系" << endl;
    }


    vector<vector<int>>A2 =
            {
                    {1,0,1,1,1,1,1,1},
                    {0,1,0,1,0,1,1,1},
                    {0,0,1,0,1,1,1,1},
                    {0,0,0,1,0,1,1,1},
                    {0,0,0,0,1,0,1,1},
                    {0,0,0,0,0,1,1,1},
                    {0,0,0,0,0,0,1,0},
                    {0,0,0,0,0,0,0,1}
            }; //定义偏序关系矩阵
    cout << endl;
    cout << "{1,0,1,1,1,1,1,1}" << endl;
    cout << "{0,1,0,1,0,1,1,1}" << endl;
    cout << "{0,0,1,0,1,1,1,1}" << endl;
    cout << "{0,0,0,1,0,1,1,1}" << endl;
    cout << "{0,0,0,0,1,0,1,1}" << endl;
    cout << "{0,0,0,0,0,1,1,1}" << endl;
    cout << "{0,0,0,0,0,0,1,0}" << endl;
    cout << "{0,0,0,0,0,0,0,1}" << endl;
    if (project2(A2))
    {
        cout << "该关系是偏序关系" << endl;
        final(A2);
    } else {
        cout << "不是偏序关系" << endl;
    }

    return 0;
}
*/
