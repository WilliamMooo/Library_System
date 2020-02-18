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
    int readerNum; // 用户数量
    reader_data rdata[100];
    user();
    virtual bool matchID(int i) = 0;
    bool matchPass(int p);
    void getReadersData(); // 从文件中读取用户数据
    void saveReaderData(); // 将修改的用户数据保存到文件
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
    void registerReader(); // 注册新用户
    void readerData(); // 查看用户数据
    void bookData() override; // 查看图书数据
    bool addStorage(); // 采编入库、上架新书
    bool deleteBook(); // 删除图书
    bool isReaderExist(int idConfig); // 用户是否存在
    ~admin();
};

class reader : public user
{
private:
    Index borrow_books[maxBorrow]; // 借阅书籍
    int borrowNum; // 借阅数量
    bool isBan; // 是否被禁言
    reader_data now_reader; // 正在使用系统的用户
    Comment book_comment[20]; // 存放查看的书评
    int commentNum; // 书评的条数
public:
    reader();
    reader(IndexTable *t);
    bool matchID(int i) override;
    bool login() override; // 登陆
    void bookData() override; // 查看图书数据
    void mainWindow() override;
    void borrowDialog(); // 借书对话框 
    bool borrow(int i); // 借书
    bool readBorrowLog(); // 读取借书记录
    bool saveBorrowLog(); // 保存借书记录
    void giveBack(); // 还书
    void commentDialog(); // 查看评论对话框
    void bookComments(int i); // 查看图书评论
    bool readComments(int i); // 从文件中获取评论数据
    void comment(int i); // 评论
    bool saveComment(int i); // 将评论保存到文件
    ~reader();
};