#include "user.h"
#include "sensitiveWords.h"

#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

reader::reader(IndexTable *t) {
    table = t;
}

bool reader::matchID(int idInput) {
    for (int i = 0; i < readerNum; i++) {
        if (rdata[i].id == idInput){
            id = rdata[i].id;
            strcpy_s(name, rdata[i].name);
            password = rdata[i].password;
            borrowNum = rdata[i].borrowNum;
            isBan = rdata[i].isBan;
            now_reader = rdata[i];
            return true;
        }
    }
    return false;
}

bool reader::login() {
    system("cls");
    int idInput, passInput;
    cout << "���������id(����0�˳�): ";
    cin >> idInput;
    while (matchID(idInput) == false) {
        if (idInput == 0) return false;; // ��0�˳�
        system("cls");
        cout << "Wrong ID!" << "\n" << "���������id(����0�˳�): ";
        cin >> idInput;
    }
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

void reader::mainWindow() {
    if (readBorrowLog() == false) {
        cout << "��ȡ�����¼ʧ��" << endl;
        system("pause");
    }
    int opcode = -1;
    while (true) {
        system("cls");
        cout << "��ӭ��," << name << "��ѡ��:" << endl;
        cout << "1.����; 2.����; 3.�鿴ͼ������; 0.�˳�;" << endl;
        cin >> opcode;
        if (opcode == 0) break;
        switch(opcode) {
            case 1:
                bookData();
                borrowDialog();
                break;
            case 2:
                giveBack();
                break;
            case 3:
                bookData();
                commentDialog();
                break;
            default:
                cout << "���������,����������!" << endl;
                system("pause");
                break;
        }
    }
}

void reader::giveBack() {
    system("cls");
    if (borrowNum == 0) {
        cout << "��û�н����κ�ͼ��" << endl;
        system("pause");
        return;
    }
    cout << "����ĵ�ͼ������:" << endl;    
    cout << "-----------------------------------------------------------------" << endl;
    cout << setiosflags(ios::left) << setw(10) << "ͼ����" << setw(30) << "ͼ������"
        << setw(20) << "����" << endl;
    for (int i = 0; i < borrowNum; i++) {
        Book *b = borrow_books[i].getData();
        cout << setw(10) << b->id << setw(30) << b->name << setw(20) << b->author << endl;
    }
    int idInput;
    cout << "������Ҫ�黹��ͼ����(��0�˳�):";
    while(cin >> idInput) {
        if (idInput == 0) return;
        Index *e = table->binSearch(idInput);
        if (e == NULL) cout << "�����Ŵ���" << endl;
        else {
            e->giveBack();
            borrowNum -= 1;
            now_reader.borrowNum -= 1;
            saveBorrowLog();
            saveReaderData();
            table->saveIndexTableData();
            break;
        }
    }
    if (isBan == false) {
        int opcode;
        cout << "����ɹ�" << endl << "�Ƿ�Ը����������?(����0��������,�������˳�):";
        cin >> opcode;
        if (opcode == 0) comment(idInput);
    }
    system("pause");
}

void reader::bookData() {
    int len = table->getNum();
    Index *data = table->getData();
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << setiosflags(ios::left) << setw(10) << "ͼ����" << setw(30) << "ͼ������"
        << setw(20) << "����" << setw(8) << "�ִ���" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
    for (int i = 0; i < len; i++) {
        Book *b = data[i].getData();
        cout << setiosflags(ios::left) << setw(10) << b->id << setw(30) << b->name <<
            setw(20) << b->author << setw(8) << b->current << endl;
    }
    cout << "-----------------------------------------------------------------------------" << endl;
}

void reader::borrowDialog() {
    cout << "��ѡ��Ҫ�������ݵ�ͼ����(��0�˳�):";
    int book_id;
    cin >> book_id;
    if (book_id == 0) return;
    if (borrow(book_id) == true) cout << "���ĳɹ�" << endl;
    else cout << "����ʧ��" << endl;
    system("pause");
}

bool reader::borrow(int i) {
    Index *e = table->binSearch(i);
    if (e == NULL) return false;
    if (e->borrow() == false) return false;
    borrow_books[borrowNum] = *e;
    borrowNum += 1;
    now_reader.borrowNum += 1;
    if(saveBorrowLog() == false) return false;
    table->saveIndexTableData();
    return true;
}

bool reader::saveBorrowLog() {
    char file_path[40];
    strcpy(file_path, "data/borrow_list/");
    char id_path[10];
    itoa(id, id_path, 10);
    strcat(file_path, id_path);
    strcat(file_path, ".txt");
    ofstream outFile;
    outFile.open(file_path, ios::out);
    if (!outFile) return false;
    for (int i = 0; i < borrowNum; i++) {
        outFile << borrow_books[i].getID() << " ";
    }
    outFile.close();
    return true;
}

bool reader::readBorrowLog() {
    char file_path[40];
    strcpy(file_path, "data/borrow_list/");
    char id_path[10];
    itoa(id, id_path, 10);
    strcat(file_path, id_path);
    strcat(file_path, ".txt");
    ifstream inFile;
    inFile.open(file_path, ios::in);
    if (!inFile) return false;
    int n = 0;
    while (!inFile.eof()) {
        int book_id;
        inFile >> book_id;
        if (inFile) {
            Index *e = table->binSearch(book_id);
            borrow_books[n] = *e;
            n++;
        } else {
            break;
        }
    }
    inFile.close();
    borrowNum = n;
    return true;
}

void reader::commentDialog() {
    while (true) {
        system("cls");
        bookData();
        cout << "��ѡ����鿴����ͼ��ı��(��0�˳�):";
        int idInput;
        cin >> idInput;
        if (idInput == 0) return;
        system("cls");
        bookComments(idInput);
    }
}

void reader::bookComments(int i) {
    if(readComments(i) == false) {
        cout << "���黹û���˽�������" << endl;
        system("pause");
        return;
    }
    cout << "--------------------------------" << endl;
    for (int i = 0; i < commentNum; i++) {
        cout << book_comment[i].user_name << ":\n" << book_comment[i].content << endl << endl;
    }
    system("pause");
}

bool reader::readComments(int i) {
    char file_path[40];
    strcpy(file_path, "data/comments/");
    char id_path[10];
    itoa(i, id_path, 10);
    strcat(file_path, id_path);
    strcat(file_path, ".txt");
    fstream inFile;
    inFile.open(file_path);
    if (!inFile) {
        return false;
    }
    int n = 0;
    while (!inFile.eof()) {
        char reader_name[maxNameLen];
        char reader_comment[maxNameLen];
        inFile >> reader_name >> reader_comment;
        if (inFile) {
            book_comment[n].book_id = i;
            strcpy_s(book_comment[n].user_name, reader_name);
            strcpy_s(book_comment[n].content, reader_comment);
            n++;
        } else {
            break;
        }
    }
    inFile.close();
    commentNum = n;
    return true;
}

void reader::comment(int i) {
    cout << "�������������:(���100��):" << endl;
    SensitiveWords filter;
    char *comment_text = filter.run();
    if(readComments(i) == false) commentNum = 0;
    book_comment[commentNum].book_id = i;
    strcpy_s(book_comment[commentNum].user_name, name);
    strcpy_s(book_comment[commentNum].content, comment_text);
    commentNum += 1;
    if(saveComment(i) == true) cout << "���۳ɹ�" << endl;
    else cout << "����ʧ��" << endl;
}

bool reader::saveComment(int book_id) {
    char file_path[40];
    strcpy(file_path, "data/comments/");
    char id_path[10];
    itoa(book_id, id_path, 10);
    strcat(file_path, id_path);
    strcat(file_path, ".txt");
    ofstream outFile;
    outFile.open(file_path, ios::out);
    if (!outFile) return false;
    for (int i = 0; i < commentNum; i++) {
        outFile << book_comment[i].user_name << " " << book_comment[i].content << endl;
    }
    outFile.close();
    return true;
}

reader::~reader() {

}