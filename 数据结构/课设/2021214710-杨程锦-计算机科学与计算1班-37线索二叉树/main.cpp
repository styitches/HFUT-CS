#include "bTHRTree.h"

void menu(){
    cout << "----------线索化二叉树----------" << endl;
    cout << "-        中序线索化二叉树       -" << endl;
    cout << "-        先序线索化二叉树       -" << endl;
    cout << "-        后序线索化二叉树       -" << endl;
    cout << "-           插入节点          -" << endl;
    cout << "-           删除节点          -" << endl;
    cout << "-           查找前驱          -" << endl;
    cout << "-           查找后继          -" << endl;
    cout << "-----------------------------" << endl;
    cout << "请输入操作：" << endl;
}

int main(){
    bTHRTree b1;
    int i;
    b1.createTree(b1.T, b1.parent);
    menu();
    cin >> i;
    switch (i) {
        case 1:{
            //中序线索二叉树
            b1.inThreading1(b1.T, b1.pre);
            b1.TinOrder(b1.T, 1);
            break;
        }


        case 2:{
            //先序线索二叉树
            b1.inThreading2(b1.T, b1.pre);
            b1.PreOrder(b1.T, 1);
            break;
        }


        case 3:{
            //后序线索二叉树
            b1.inThreading3(b1.T, b1.pre);
            b1.PostOrder(b1.T, 1);
            break;
        }


        case 4:{
            //插入节点
            cout << "请选择线索化类型：";
            int temp;
            cin >> temp;
            switch (temp) {
                case 1:
                    //中序
                    b1.inThreading1(b1.T, b1.pre);
                    break;
                case 2:
                    //先序
                    b1.inThreading2(b1.T, b1.pre);
                    break;
                case 3:
                    //后序
                    b1.inThreading3(b1.T, b1.pre);
                    break;
            }
            Node2 R = new bTHRNode();
            cout << "请输入节点值：";
            cin >> R->data;
            b1.reverseThread(b1.T);
            b1.insertNode(b1.T->leftChild->leftChild, R);
            b1.pre = NULL;
            switch (temp) {
                case 1:
                    //中序
                    b1.inThreading1(b1.T, b1.pre);
                    b1.TinOrder(b1.T, 1);
                    break;
                case 2:
                    //先序
                    b1.inThreading2(b1.T, b1.pre);
                    b1.PreOrder(b1.T, 1);
                    break;
                case 3:
                    //后序
                    b1.inThreading3(b1.T, b1.pre);
                    b1.PostOrder(b1.T, 1);
                    break;
            }
            break;
        }


        case 5:{
            //删除节点
            cout << "请选择线索化类型：";
            int temp;
            cin >> temp;
            switch (temp) {
                case 1:
                    //中序
                    b1.inThreading1(b1.T, b1.pre);
                    break;
                case 2:
                    //先序
                    b1.inThreading2(b1.T, b1.pre);
                    break;
                case 3:
                    //后序
                    b1.inThreading3(b1.T, b1.pre);
                    break;
            }
            b1.reverseThread(b1.T);
            cout << "请输入要删除的节点：";
            char s;
            cin >> s;
            b1.deleteNode(b1.T, s);
            b1.pre = NULL;
            switch (temp) {
                case 1:
                    //中序
                    b1.inThreading1(b1.T, b1.pre);
                    b1.TinOrder(b1.T, 1);
                    break;
                case 2:
                    //先序
                    b1.inThreading2(b1.T, b1.pre);
                    b1.PreOrder(b1.T, 1);
                    break;
                case 3:
                    //后序
                    b1.inThreading3(b1.T, b1.pre);
                    b1.PostOrder(b1.T, 1);
                    break;
            }
            break;
        }


        case 6:{
            //查找前驱
            int s;
            cout << "请输入线索化类型：";
            cin >> s;
            b1.initStack(b1.T, s);
            cout << "请输入查找节点值：";
            char f;
            cin >> f;
            Node2 x = b1.searchPreNode(f);
            if (x){
                cout << "该节点前驱为：" << x->data << endl;
            } else {
                cout << "该节点无前驱！";
            }
            break;
        }


        case 7:{
            //查找后继
            int s;
            cout << "请输入线索化类型：";
            cin >> s;
            b1.initQueue(b1.T, s);
            cout << "请输入查找节点值：";
            char f;
            cin >> f;
            Node2 x = b1.searchNextNode(f);
            if (x){
                cout << "该节点后继为：" << x->data << endl;
            } else {
                cout << "该节点无前驱！";
            }
            break;
        }
        default:
            break;
        }

}

