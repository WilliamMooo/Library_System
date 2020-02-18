#include "Book.h"

class Index
{
private:
    int ID;
    Book *data;
public:
    Index();
    Index(int id, char *na, char* au, int cur, int inv);
    void addStorage(int num); // 采编入库
    bool borrow(); // 借阅
    void giveBack(); // 归还
    int getID(); // 查看书号
    Book* getData(); // 查看数据
    ~Index();
};
