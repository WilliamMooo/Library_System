#include "IndexTable.h"
#define maxBorrow 10

class user
{
protected:
    IndexTable *table;
    int id;
    char name[maxNameLen];
    int password;
public:
    int readerNum; // �û�����
    reader_data rdata[100];
    user();
    virtual bool matchID(int i) = 0;
    bool matchPass(int p);
    void getReadersData(); // ���ļ��ж�ȡ�û�����
    void saveReaderData(); // ���޸ĵ��û����ݱ��浽�ļ�
    virtual bool login() = 0;
    virtual void mainWindow() = 0;
    virtual void bookData() = 0;
    ~user();
};

class admin : public user
{
public:
    admin(IndexTable *t);
    bool matchID(int i) override;
    bool login() override;
    void mainWindow() override;
    void registerReader(); // ע�����û�
    void readerData(); // �鿴�û�����
    void bookData() override; // �鿴ͼ������
    bool addStorage(); // �ɱ���⡢�ϼ�����
    bool deleteBook(); // ɾ��ͼ��
    bool isReaderExist(int idConfig); // �û��Ƿ����
    ~admin();
};

class reader : public user
{
private:
    Index borrow_books[maxBorrow]; // �����鼮
    int borrowNum; // ��������
    bool isBan; // �Ƿ񱻽���
    reader_data now_reader; // ����ʹ��ϵͳ���û�
    Comment book_comment[20]; // ��Ų鿴������
    int commentNum; // ����������
public:
    reader();
    reader(IndexTable *t);
    bool matchID(int i) override;
    bool login() override; // ��½
    void bookData() override; // �鿴ͼ������
    void mainWindow() override;
    void borrowDialog(); // ����Ի��� 
    bool borrow(int i); // ����
    bool readBorrowLog(); // ��ȡ�����¼
    bool saveBorrowLog(); // ��������¼
    void giveBack(); // ����
    void commentDialog(); // �鿴���۶Ի���
    void bookComments(int i); // �鿴ͼ������
    bool readComments(int i); // ���ļ��л�ȡ��������
    void comment(int i); // ����
    bool saveComment(int i); // �����۱��浽�ļ�
    ~reader();
};