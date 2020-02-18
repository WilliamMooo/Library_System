#include <list>
#include <string>
using namespace std;

class SensitiveWords {
private:
    struct Node {
        char data;
        bool last;
        Node *sibling;
        Node *next;
    };
public:
    SensitiveWords();
    void getWordList(list <char*>&list_keyword);
    void ReleaseKeyWordList(list <char*>&list_keyword);
    Node* NodeHasExist(Node *cur,char data);
    Node* BuildTree();
    void ReleaseTree(Node *root);
    const char* LookUp(char *content,Node *root);
    char* run();
};
