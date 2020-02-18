#include <iostream>
#include <cstring>

#include "user.h"

using namespace std;

int main() {
    IndexTable *book_data = new IndexTable();
    while (true) {
        system("cls");
        cout << "��ӭʹ��ͼ��ݹ���ϵͳ!" << endl;
        int opcode;
        cout << "��ѡ��: 1.����Ա���; 2.�������; 0.�˳�;" << endl;
        cin >> opcode;
        if (opcode == 0) break;
        else if (opcode == 1) { // ����Ա��½
            admin *newAdmin = new admin(book_data);
            if (newAdmin->login() == true) {
                newAdmin->getReadersData(); // ��ȡ�û�����
                newAdmin->mainWindow(); // ����������
            } else {
                cout << "��½ʧ��" << endl;
                system("pause");
            }
        } else if (opcode == 2) { // ���ߵ�½
            reader *newReader = new reader(book_data);
                newReader->getReadersData(); // ��ȡ�û�����
            if (newReader->login() == true) {
                newReader->mainWindow(); // ����������
            } else {
                cout << "��½ʧ��" << endl;
                system("pause");
            }
        } else {
            cout << "������������!" << endl;
            system("pause");
        }
    }
    cout << "��лʹ�ñ�ϵͳ, ���ѳɹ��˳�!" << endl;
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