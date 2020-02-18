#include <iostream>
#include <cstring>

#include "user.h"

using namespace std;

int main() {
    IndexTable *book_data = new IndexTable();
    while (true) {
        system("cls");
        cout << "欢迎使用图书馆管理系统!" << endl;
        int opcode;
        cout << "请选择: 1.管理员入口; 2.读者入口; 0.退出;" << endl;
        cin >> opcode;
        if (opcode == 0) break;
        else if (opcode == 1) { // 管理员登陆
            admin *newAdmin = new admin(book_data);
            if (newAdmin->login() == true) {
                newAdmin->getReadersData(); // 读取用户数据
                newAdmin->mainWindow(); // 启动主窗口
            } else {
                cout << "登陆失败" << endl;
                system("pause");
            }
        } else if (opcode == 2) { // 读者登陆
            reader *newReader = new reader(book_data);
                newReader->getReadersData(); // 读取用户数据
            if (newReader->login() == true) {
                newReader->mainWindow(); // 启动主窗口
            } else {
                cout << "登陆失败" << endl;
                system("pause");
            }
        } else {
            cout << "输入操作码错误!" << endl;
            system("pause");
        }
    }
    cout << "感谢使用本系统, 您已成功退出!" << endl;
    system("pause");
    return 0;
}


    // Index newbook = Index(1,"test", "mi",10,10);
    // int op;
    // while (cin >> op) {
    //     switch(op) {
    //         case 1:
    //             int num;
    //             cin >> num;
    //             newbook.addStorage(num);
    //             break;
    //         case 2:
    //             if(newbook.borrow());
    //             break;
    //         case 3:
    //             newbook.giveBack();
    //             break;
    //         default:
    //             break;
    //     }
    //     Book *data = newbook.getData();
    //     cout << "ID:" << data->id << "\nname:" << data->name << "\nauthor:" <<
    //         data->author << "\ncurrent:" << data->current << "\ninventory:"
    //         << data->inventory << endl;
    // }

    // Index t[100];
    // for(int i = 0; i < 10; i++) t[i] = Index(10-i,"test", "mi",10,10);
    // t[3] = t[7];
    // IndexTable tb = IndexTable(10, t);
    // Index *t1 = tb.getData();
    // for(int i = 0; i < 10; i++) cout << t1[i].getID();
    // cout << endl;
    // tb.sort();
    // for(int i = 0; i < 10; i++) cout << t1[i].getID();
    // cout << endl;
    // int id;
    // cin >> id;
    // Index res = tb.binSearch(id);
    // if (res.getID() == 0) cout << "doesn't exist" << endl;
    // else cout << res.getData()->id << endl;