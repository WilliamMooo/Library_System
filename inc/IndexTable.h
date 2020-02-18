#include "Index.h"

#define maxTableLen 1000

class IndexTable
{
private:
    int number; // 图书种类数量
    Index data[maxTableLen]; // 索引表
public:
    IndexTable();
    int getNum(); // 返回图书种类数量
    Index* getData(); // 返回索引表
    void quickSort(int low, int high); // 对索引表从小到大排序
    void sort(); // 封装排序函数
    Index* binSearch(int id); // 在索引表上二分查找
    bool insert(Index *e); // 插入数据
    bool del(int book_id); // 删除数据
    void getIndexTableData(); // 从文件中读取图书数据
    void saveIndexTableData(); // 将索引表数据保存到文件
    ~IndexTable();
};
