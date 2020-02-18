#define bookNameLen 50
#define authorNameLen 50
#define maxNameLen 50
#define maxCommentLen 200

typedef struct book
{
    int id; // 书号
    char name[bookNameLen]; // 书名
    char author[authorNameLen]; // 作者
    int current; // 现存量
    int inventory; // 库存=现存+借阅
} Book;

typedef struct {
    int id;
    char name[maxNameLen];
    int password;
    int borrowNum; // 借阅数量
    bool isBan; // 是否被禁言
} reader_data;

typedef struct {
    int book_id;
    char user_name[maxNameLen];
    char content[maxCommentLen];
} Comment;