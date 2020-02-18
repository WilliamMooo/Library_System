#include <iostream>
#include <fstream>
#include <stdio.h>

#include "IndexTable.h"

using namespace std;

IndexTable::IndexTable() {
    getIndexTableData();
}

int IndexTable::getNum() {
    return number;
}

Index* IndexTable::getData() {
    return data;
}

void IndexTable::quickSort(int low, int high) {
    int i = low;
    int j = high;
    Index midEle = data[low];
    int key = midEle.getID();
    if (i < j) {
        while (i < j) {
            while (i < j && data[j].getID() >= key) j--;
            data[i] = data[j];
            while (i < j && data[i].getID() < key) i++;
            data[j] = data[i];
        }
        data[i] = midEle;
        quickSort(low, i-1);
        quickSort(i+1, high);
    }
}

void IndexTable::sort() {
    quickSort(0, number-1);
}

Index* IndexTable::binSearch(int id) {
    int low = 0;
    int high = number-1;
    int mid;
    while (low <= high) {
        mid = (low+high)/2;
        int val = data[mid].getID();
        if (id == val) return &data[mid];
        else if (id < val) high = mid-1;
        else if (id > val) low = mid+1;
    }
    return NULL;
}

bool IndexTable::insert(Index *e) {
    if (number == maxTableLen) return false;
    data[number] = *e;
    number++;
    saveIndexTableData();
    return true;
}

bool IndexTable::del(int book_id) {
    if (number == 0) return false;
    Index *e = binSearch(book_id);
    if (e == NULL) return false;
    if (e->getData()->inventory != e->getData()->current) return false;
    number -= 1;
    e = NULL;
    sort();
    free(e);
    return true;
}

IndexTable::~IndexTable() {
    free(data);
}

void IndexTable::getIndexTableData() {
    ifstream infile;
    infile.open("data/book_data.txt", ios::in);
    if (!infile) {
        return;
    }
    int n = 0;
    while (!infile.eof()) {
        int id, current, inventory;
        char name[bookNameLen], author[authorNameLen];
        infile >> id >> name >> author >> current >> inventory;
        if (infile) {
            Index *ne = new Index(id, name, author, current, inventory);
            data[n] = *ne;
            n++;
        } else {
            break;
        }
    }
    infile.close();
    number = n;
}

void IndexTable::saveIndexTableData() {
    fstream outFile;
    outFile.open("data/book_data.txt", ios::out);
    if (!outFile) {
        cout << "open file fail" << endl;
        return;
    }
    for (int i = 0; i < number; i++) {
        Book *out_data = data[i].getData();
        outFile << out_data->id << " " << out_data->name << " " 
            << out_data->author << " " << out_data->current <<
            " " << out_data->inventory << endl;
    }
    outFile.close();
}