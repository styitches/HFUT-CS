#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
using namespace std;

bool isVN(char a) {
    if (a >= 'A' && a <= 'Z')
        return true;
    else
        return false;
}

int LL_1(string grammar, string stc) {
    char start = grammar[0];          //记录开始符
    int a[10][10] = { 0 };
    vector<char> vn;
    vector<string> drived;
    vector<char> vt;
    int i = 0;
    while (i < grammar.length()) {          //获取非终结符
        if (isVN(grammar[i])) {
            vn.push_back(grammar[i]);
        }
        i++;
    }
    i = 0;

    while (i < grammar.length()) {          //获取所有推导式
        string tmp = "";
        while (grammar[i] != '\n' && i < grammar.length()) {
            tmp += grammar[i];
            i++;
        }
        i++;
        drived.push_back(tmp);
    }

    i = 0;
    while (i < grammar.length()) {          //获取终结符
        if (grammar[i] != '\n' && !isVN(grammar[i]) && grammar[i] != '|' && grammar[i] != '?' && grammar[i] != ' ') {
            vt.push_back(grammar[i]);
        }
        i++;
    }

    sort(vn.begin(), vn.end());          //非终结符去重
    auto pos = unique(vn.begin(), vn.end());     //将相邻的重复元素放到容器的末尾，并返回指向第一个重复元素的迭代器
    vn.erase(pos, vn.end());                                            //删除指向第一个重复元素的迭代器到容器末尾的所有元素

    sort(vt.begin(), vt.end());          //非终结符去重
    auto pos2 = unique(vt.begin(), vt.end());
    vt.erase(pos2, vt.end());

    int f_size = vn.size();   //sizeof FIRST and FOLLOW

    //初始化first集合 找到最基础的first集合
    set<char> first[10];
    for (int i = 0; i < f_size; i++) {               //init first[]
        for (int j = 0; j < drived.size(); j++) {
            for (int k = 2; k < drived[j].size(); k++) {
                if (vn[i] == drived[j][0]) {
                    if ((drived[j][k - 1] == '|' && !isVN(drived[j][k])) || (drived[j][k - 1] == ' ' && !isVN(drived[j][k]))) {
                        first[i].insert(drived[j][k]);
                    }
                }
            }
        }
    }

    for (int j = 0; j < drived.size(); j++) {           //用矩阵记录形如E->T T->S的非终结符通路
        for (int k = 0; k < f_size; k++) {
            if (drived[j][0] == vn[k]) {
                for (int l = 2; l < drived[j].size(); l++) {
                    if (isVN(drived[j][l])) {
                        for (int m = 0; m < f_size; m++) {
                            if (drived[j][l] == vn[m] && (drived[j][l - 1] == '|' || drived[j][l - 1] == ' ')) {
                                a[k][m] = 1;

                            }


                        }
                    }
                }
                break;
            }

        }
    }

    //初始化标志数组 记录first的改变
    int flag[10] = { 0 };
    for (int j = 0; j < 10; j++) {
        flag[j] = first[j].size();
    }
    int sig = 0;
    for (int j = 0; j < f_size; j++) {     //将通路中的非终结符first集合整理
        for (int k = 0; k < f_size; k++) {
            if (a[j][k] == 1) {
                for (set<char>::iterator it = first[k].begin(); it != first[k].end(); it++) {
                    first[j].insert(*it);
                }
            }
        }
    }
    do {
        for (int j = 0; j < f_size; j++) {
            for (int k = 0; k < f_size; k++) {
                if (a[j][k] == 1) {
                    for (set<char>::iterator it = first[k].begin(); it != first[k].end(); it++) {
                        first[j].insert(*it);
                    }
                }
            }
        }
        for (int j = 0; j < 10; j++) {
            if (flag[j] != first[j].size()) {           //当first集合发生改变时，就得执行循环，直到不改变为止
                sig = 1;
                flag[j] = first[j].size();
                break;
            }
            if (j == 9) {
                sig = 0;
            }
        }
    } while (sig);

    set<char> follow[10];
    for (int j = 0; j < f_size; j++) {
        if (vn[j] == start) {
            follow[j].insert('#');
            break;
        }
    }

    //遍历推导式从二位开始 1遇到两个大写连着 后面的first加入前面的follow 2遇到大写后面跟着终结符，加入其follow
    for (int j = 0; j < drived.size(); j++) {
        for (int k = 2; k < drived[j].size() - 1; k++) {
            if (isVN(drived[j][k]) && isVN(drived[j][k + 1])) {         //连着两个非终结符
                for (int l = 0; l < f_size; l++) {
                    if (drived[j][k + 1] == vn[l]) {
                        for (int m = 0; m < f_size; m++) {
                            if (drived[j][k] == vn[m]) {
                                for (set<char>::iterator it = first[l].begin(); it != first[l].end(); it++) {
                                    if (*it != '?') {
                                        follow[m].insert(*it);    //后first-空 插入前follow
                                    }

                                }
                                break;
                            }
                        }
                        break;
                    }
                }
            }

            if (isVN(drived[j][k]) && !isVN(drived[j][k + 1]) && drived[j][k + 1] != '|' && drived[j][k + 1] != '?') {    //大写后面跟着终结符
                for (int l = 0; l < f_size; l++) {
                    if (drived[j][k] == vn[l]) {
                        follow[l].insert(drived[j][k + 1]);  //后跟终结符直接插入follow
                        break;
                    }
                }
            }
        }
    }

    int flag2[10] = { 0 };
    for (int j = 0; j < 10; j++) {
        flag2[j] = follow[j].size();
    }
    sig = 0;

    //follow第三条规则 E->anyH follow E = follow H
    do {
        for (int j = 0; j < drived.size(); j++) {
            for (int k = 2; k < drived[j].size() - 1; k++) {
                if (k == drived[j].size() - 2 && isVN(drived[j][k + 1])) {
                    for (int l = 0; l < f_size; l++) {
                        if (drived[j][k + 1] == vn[l]) {
                            for (int m = 0; m < f_size; m++) {
                                if (drived[j][0] == vn[m]) {
                                    for (set<char>::iterator it = follow[l].begin(); it != follow[l].end(); it++) {
                                        follow[m].insert(*it);                                                                      //H的插入E中
                                    }
                                    for (set<char>::iterator it = follow[m].begin(); it != follow[m].end(); it++) {
                                        follow[l].insert(*it);
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }

                if (isVN(drived[j][k]) && drived[j][k + 1] == '|') {     //将|左边的非终结符的follow添加至第一个符合的follow
                    for (int l = 0; l < f_size; l++) {
                        if (drived[j][k] == vn[l]) {
                            for (int m = 0; m < f_size; m++) {
                                if (drived[j][0] == vn[m]) {
                                    for (set<char>::iterator it = follow[l].begin(); it != follow[l].end(); it++) {
                                        follow[m].insert(*it);
                                    }
                                    for (set<char>::iterator it = follow[m].begin(); it != follow[m].end(); it++) {
                                        follow[l].insert(*it);
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }

        for (int j = 0; j < 10; j++) {
            if (flag2[j] != follow[j].size()) {           //当follow集合发生改变时，就得执行循环，直到不改变为止
                sig = 1;
                flag2[j] = follow[j].size();
                break;
            }
            if (j == 9) {
                sig = 0;
            }
        }
    } while (sig);

    // 构造M[A,a]

    //填写表头
    string m[10][10];
    for (int i = 0; i < vt.size(); i++) {
        string tmp = "";
        tmp += vt[i];
        m[0][i + 1] = tmp;
    }

    for (int i = 0; i < vn.size(); i++) {
        string tmp = "";
        tmp += vn[i];
        m[i + 1][0] = tmp;
    }


    //根据first集合填写
    for (int i = 1; i < vt.size() + 1; i++) {
        for (int j = 1; j < vn.size() + 1; j++) {
            auto pos = first[j - 1].find(m[0][i][0]);
            auto pos2 = first[j - 1].find('?');
            if (pos != first[j - 1].end()) {
                m[j][i] = "o";
                for (int k = 0; k < drived.size(); k++) {
                    if (drived[k][0] == m[j][0][0]) {
                        if (drived[k][2] == m[0][i][0]) {
                            m[j][i] = drived[k];
                        }
                    }
                }

            }

            else if (pos2 != first[j - 1].end()) {         //FIRST集合中包含空串，则查看该终结符是否在该非终结符的FOLLOW集合中
                auto pos3 = follow[j - 1].find(m[0][i][0]);
                if (pos3 != follow[j - 1].end()) {
                    m[j][i] = "?";
                }
                else m[j][i] = "$";
            }
            else m[j][i] = "$";
        }
    }


    //将产生式填入
    for (int i = 1; i < vt.size() + 1; i++) {
        for (int j = 1; j < vn.size() + 1; j++) {
            if (m[j][i][0] == 'o') {
                for (int k = 0; k < drived.size(); k++) {
                    if (drived[k][0] == m[j][0][0]) {
                        if (isVN(drived[k][2])) {
                            m[j][i] = drived[k];
                        }
                    }
                }
            }
        }
    }

    //至此 查找表构造完成
    string st = "";
    st += start;
    st += '#';

    while (stc.length() > 1) {
        char a, b;
        a = stc[0];
        b = st[0];
        int flag = 0;
        if (a == b) {
            cout << "当前两个字符串顶相同，删去" << a << endl;
            stc.erase(0, 1);
            st.erase(0, 1);
            cout << endl;

        }

        else {
            for (int i = 1; i < vt.size() + 1; i++) {
                if (flag)
                    break;
                for (int j = 1; j < vn.size() + 1; j++) {
                    if (a == m[0][i][0] && b == m[j][0][0]) {
                        string tmp = m[j][i];
                        flag = 1;
                        if (tmp[0] == '?') {
                            cout << "匹配式:  " << st<<'	';
                            cout << "语句:  " << stc<<'	';
                            st.erase(0, 1);
                            cout << "用:  ->?" ;
                            cout << endl; cout << endl;
                        }
                        else {
                            cout << "匹配式:  " << st << '	';
                            cout << "语句:  " << stc << '	';
                            tmp.insert(1, "->");
                            cout << "用公式:  " << tmp << '	';
                            tmp.erase(0, 4);
                            st.erase(0, 1);
                            st.insert(0, tmp);

                            cout << endl; cout << endl;
                        }
                        break;
                    }

                }
            }
        }

    }

    while (st.length() > 1) {
        cout << "用->？消除" << st[0] << endl;
        st.erase(0, 1);
    }

    return 0;
}

int main() {
    string s = "E#";
    string
            wenfa = "E TG\nG +TG\nG -TG\nG ?\nT FS\nS *FS\nS /FS\nS ?\nF (E)\nF i"; //文法输入
    string s_in = "i+i*i#";            //待解析语句
    LL_1(wenfa, s_in);
    return 0;
}