#include "Book.h"

class Index
{
private:
    int ID;
    Book *data;
public:
    Index();
    Index(int id, char *na, char* au, int cur, int inv);
    void addStorage(int num); // �ɱ����
    bool borrow(); // ����
    void giveBack(); // �黹
    int getID(); // �鿴���
    Book* getData(); // �鿴����
    ~Index();
};
