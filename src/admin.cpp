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
    cout << "请输入你的id(输入0退出): ";
    cin >> idInput;
    while (matchID(idInput) == false) {
        if (idInput == 0) return false;; // 按0退出
        system("cls");
        cout << "输入id错误!" << "\n" << "请输入你的id(输入0退出): ";
        cin >> idInput;
    }
    // 获取动态密码
    Email e = Email("q961017025@163.com");
    password = e.getDppsw();
    e.setDppsw(password);
    e.sendTo();
    cout << "请输入你的密码(输入0退出): ";
    cin >> passInput;
    while (matchPass(passInput) == false) {
        if (passInput == 0) return false;; // 按0退出
        system("cls");
        cout << "Wrong Password!" << "\n" << "请输入你的密码(输入0退出): ";
        cin >> passInput;
    }
    return true;
}

void admin::mainWindow() {
    int opcode = -1;
    while (true) {
        system("cls");
        cout << "欢迎您,管理员!请选择:" << endl;
        cout << "1.添加新读者; 2.查看读者信息; 3.查看图书信息; 4.采编入库; 5.下架图书; 0.退出;" << endl;
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
                if(addStorage() == true) cout << "添加成功";
                else cout << "添加失败";
                cout << endl;
                system("pause");
                break;
            case 5:
                if(deleteBook() == true) cout << "删除成功";
                else cout << "删除失败";
                cout << endl;
                system("pause");
                break;
            default:
                cout << "输入码错误,请重新输入!" << endl;
                system("pause");
                break;
        }
    }
}

void admin::registerReader() {
    cout << "请依次输入读者的id,姓名,密码:" << endl;
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
        "姓名" << setw(10) << "借阅数量" << setw(10) << "是否被禁言" << endl;
    cout << "-------------------------------------------------------" << endl;
    for (int i = 0; i < readerNum; i++) {
        cout << setw(15) << rdata[i].id << setw(10) << rdata[i].name <<
            setw(10) << rdata[i].borrowNum << setw(10);
        if (rdata[i].isBan == true) cout << setw(10) << "是";
        else cout << setw(10) << "否";
        cout << endl;
    }
    cout << "-------------------------------------------------------" << endl;
    int toBan;
    cout << "是否对读者禁言(输入1选择读者禁言,其他键退出): ";
    cin >> toBan;
    if (toBan == 1) {
        cout << "请输入要禁言的读者id: ";
        int idInput;
        while(cin >> idInput) {
            for (int i = 0; i < readerNum; i++) {
                if (rdata[i].id == idInput) {
                    rdata[i].isBan = true;
                    saveReaderData();
                    cout << "禁言成功" << endl;
                    system("pause");
                    return;
                }
            }
            cout << "id输入错误, 请重新输入" << endl;
        }
    }
    system("pause");
}

void admin::bookData() {
    int len = table->getNum();
    Index *data = table->getData();
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << setiosflags(ios::left) << setw(10) << "图书编号" << setw(30) << "图书名称"
        << setw(20) << "作者" << setw(8) << "现存量" << setw(8) << "库存量" << endl;
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
        cout << "仓库已满" << endl;
        return false;
    }
    cout << "请依次输入添加图书的编号, 名称, 作者, 添加量:" << endl;
    int idInput, addNum;
    char name[bookNameLen], author[authorNameLen];
    cin >> idInput >> name >> author >> addNum;
    Index *data = table->binSearch(idInput);
    if (data == NULL) { // 如果不存在存在则创建新的索引
        data = new Index(idInput, name, author, addNum, addNum);
        table->insert(data);
    } else { // 如果存在则在原来基础上添加
        data->addStorage(addNum);
    }
    table->saveIndexTableData(); // 保存到文件
    return true;
}

bool admin::deleteBook() {
    cout << "请输入要删除图书的id:" << endl;
    int idInput;
    cin >> idInput;
    bool ret = table->del(idInput);
    table->saveIndexTableData(); // 保存到文件
    return ret;
}

bool admin::matchID(int i) {
    if (i == id) return true;
    else return false;
}

admin::~admin() {
    free(rdata);
}