#include "user.h"

#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

user::user() { }

bool user::matchPass(int p) {
    if (p == password) return true;
    else return false;
}

void user::getReadersData() {
    ifstream infile;
    infile.open("data/readers.txt", ios::in);
    if (!infile) {
        return;
    }
    int n = 0;
    while (!infile.eof()) {
        int id, password, borrowNum, isBan;
        char name[maxNameLen];
        infile >> id >> name >> password >> borrowNum >> isBan;
        if (infile) {
            rdata[n].id = id;
            strcpy_s(rdata[n].name,name);
            rdata[n].password = password;
            rdata[n].borrowNum = borrowNum;
            rdata[n].isBan = isBan;
            n++;
        } else {
            break;
        }
    }
    infile.close();
    readerNum = n;
}

void user::saveReaderData() {
    fstream outFile;
    outFile.open("data/readers.txt", ios::out);
    if (!outFile) {
        cout << "open file fail" << endl;
        return;
    }
    for (int i = 0; i < readerNum; i++) {
        outFile << rdata[i].id << " " << rdata[i].name << " " <<
            rdata[i].password << " " << rdata[i].borrowNum << " "
            << int(rdata[i].isBan) << endl;
    }
    outFile.close();
}

user::~user() {
    free(table);
}