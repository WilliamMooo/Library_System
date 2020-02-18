#include "Index.h"

#include <cstring>
#include <iostream>

Index::Index() { }

Index::Index(int id, char *na, char *au, int cur, int inv) {
    ID = id;
    data = (Book*)malloc(sizeof(Book));
    data->id = id;
    strcpy_s(data->name, na);
    strcpy_s(data->author, au);
    data->current = cur;
    data->inventory = inv;
}

void Index::addStorage(int num) {
    data->inventory += num;
}

bool Index::borrow() {
    if (data->current == 0) return false;
    data->current -= 1;
    return true;
}

void Index::giveBack() {
    data->current += 1;
}

int Index::getID() {
    return ID;
}

Book* Index::getData() {
    return data;
}

Index::~Index() {
    // free(data);
}