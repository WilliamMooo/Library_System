#include "Index.h"

#define maxTableLen 1000

class IndexTable
{
private:
    int number; // ͼ����������
    Index data[maxTableLen]; // ������
public:
    IndexTable();
    int getNum(); // ����ͼ����������
    Index* getData(); // ����������
    void quickSort(int low, int high); // ���������С��������
    void sort(); // ��װ������
    Index* binSearch(int id); // ���������϶��ֲ���
    bool insert(Index *e); // ��������
    bool del(int book_id); // ɾ������
    void getIndexTableData(); // ���ļ��ж�ȡͼ������
    void saveIndexTableData(); // �����������ݱ��浽�ļ�
    ~IndexTable();
};
