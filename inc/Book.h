#define bookNameLen 50
#define authorNameLen 50
#define maxNameLen 50
#define maxCommentLen 200

typedef struct book
{
    int id; // ���
    char name[bookNameLen]; // ����
    char author[authorNameLen]; // ����
    int current; // �ִ���
    int inventory; // ���=�ִ�+����
} Book;

typedef struct {
    int id;
    char name[maxNameLen];
    int password;
    int borrowNum; // ��������
    bool isBan; // �Ƿ񱻽���
} reader_data;

typedef struct {
    int book_id;
    char user_name[maxNameLen];
    char content[maxCommentLen];
} Comment;