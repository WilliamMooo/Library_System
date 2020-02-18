#include "user.h"
#include "Email.h"

#include <fstream>
#include <cstring>
#include <iostream>
#include <iomanip>

using namespace std;

admin::admin(IndexTable *t) {
    id = 961017025;
    strcpy_s(name, "Administrator");
    table = t;
}

bool admin::login() {
    system("cls");
    int idInput, passInput;
    cout << "���������id(����0�˳�): ";
    cin >> idInput;
    while (matchID(idInput) == false) {
        if (idInput == 0) return false;; // ��0�˳�
        system("cls");
        cout << "����id����!" << "\n" << "���������id(����0�˳�): ";
        cin >> idInput;
    }
    // ��ȡ��̬����
    Email e = Email("q961017025@163.com");
    password = e.getDppsw();
    e.setDppsw(password);
    e.sendTo();
    cout << "�������������(����0�˳�): ";
    cin >> passInput;
    while (matchPass(passInput) == false) {
        if (passInput == 0) return false;; // ��0�˳�
        system("cls");
        cout << "Wrong Password!" << "\n" << "�������������(����0�˳�): ";
        cin >> passInput;
    }
    return true;
}

void admin::mainWindow() {
    int opcode = -1;
    while (true) {
        system("cls");
        cout << "��ӭ��,����Ա!��ѡ��:" << endl;
        cout << "1.����¶���; 2.�鿴������Ϣ; 3.�鿴ͼ����Ϣ; 4.�ɱ����; 5.�¼�ͼ��; 0.�˳�;" << endl;
        cin >> opcode;
        if (opcode == 0) break;
        switch(opcode) {
            case 1:
                registerReader();
                break;
            case 2:
                readerData();
                break;
            case 3:
                bookData();
                break;
            case 4:
                if(addStorage() == true) cout << "��ӳɹ�";
                else cout << "���ʧ��";
                cout << endl;
                system("pause");
                break;
            case 5:
                if(deleteBook() == true) cout << "ɾ���ɹ�";
                else cout << "ɾ��ʧ��";
                cout << endl;
                system("pause");
                break;
            default:
                cout << "���������,����������!" << endl;
                system("pause");
                break;
        }
    }
}

void admin::registerReader() {
    cout << "������������ߵ�id,����,����:" << endl;
    int idInput, passwordInput;
    char nameInput[maxNameLen];
    cin >> idInput >> nameInput >> passwordInput;
    rdata[readerNum].id = idInput;
    strcpy_s(rdata[readerNum].name, nameInput);
    rdata[readerNum].password = passwordInput;
    rdata[readerNum].borrowNum = 0;
    rdata[readerNum].isBan = false;
    readerNum += 1;
    saveReaderData();
}

void admin::readerData() {
    getReadersData();
    cout << "-------------------------------------------------------" << endl;
    cout << setiosflags(ios::left) << setw(15) << "id" << setw(10) <<
        "����" << setw(10) << "��������" << setw(10) << "�Ƿ񱻽���" << endl;
    cout << "-------------------------------------------------------" << endl;
    for (int i = 0; i < readerNum; i++) {
        cout << setw(15) << rdata[i].id << setw(10) << rdata[i].name <<
            setw(10) << rdata[i].borrowNum << setw(10);
        if (rdata[i].isBan == true) cout << setw(10) << "��";
        else cout << setw(10) << "��";
        cout << endl;
    }
    cout << "-------------------------------------------------------" << endl;
    int toBan;
    cout << "�Ƿ�Զ��߽���(����1ѡ����߽���,�������˳�): ";
    cin >> toBan;
    if (toBan == 1) {
        cout << "������Ҫ���ԵĶ���id: ";
        int idInput;
        while(cin >> idInput) {
            for (int i = 0; i < readerNum; i++) {
                if (rdata[i].id == idInput) {
                    rdata[i].isBan = true;
                    saveReaderData();
                    cout << "���Գɹ�" << endl;
                    system("pause");
                    return;
                }
            }
            cout << "id�������, ����������" << endl;
        }
    }
    system("pause");
}

void admin::bookData() {
    int len = table->getNum();
    Index *data = table->getData();
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << setiosflags(ios::left) << setw(10) << "ͼ����" << setw(30) << "ͼ������"
        << setw(20) << "����" << setw(8) << "�ִ���" << setw(8) << "�����" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
    for (int i = 0; i < len; i++) {
        Book *b = data[i].getData();
        cout << setiosflags(ios::left) << setw(10) << b->id << setw(30) << b->name <<
            setw(20) << b->author << setw(8) << b->current << setw(8) << b->inventory << endl;
    }
    cout << "-----------------------------------------------------------------------------" << endl;
    system("pause");
}

bool admin::addStorage() {
    if (table->getNum() == maxTableLen) {
        cout << "�ֿ�����" << endl;
        return false;
    }
    cout << "�������������ͼ��ı��, ����, ����, �����:" << endl;
    int idInput, addNum;
    char name[bookNameLen], author[authorNameLen];
    cin >> idInput >> name >> author >> addNum;
    Index *data = table->binSearch(idInput);
    if (data == NULL) { // ��������ڴ����򴴽��µ�����
        data = new Index(idInput, name, author, addNum, addNum);
        table->insert(data);
    } else { // �����������ԭ�����������
        data->addStorage(addNum);
    }
    table->saveIndexTableData(); // ���浽�ļ�
    return true;
}

bool admin::deleteBook() {
    cout << "������Ҫɾ��ͼ���id:" << endl;
    int idInput;
    cin >> idInput;
    bool ret = table->del(idInput);
    table->saveIndexTableData(); // ���浽�ļ�
    return ret;
}

bool admin::matchID(int i) {
    if (i == id) return true;
    else return false;
}

admin::~admin() {
    free(rdata);
}