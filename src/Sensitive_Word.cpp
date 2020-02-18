#include<iostream>
#include<fstream>
#include<sstream>
#include<cstring>

#include "SensitiveWords.h"

SensitiveWords::SensitiveWords() { };

void SensitiveWords::getWordList(list <char*>&list_keyword) {
	ifstream in;
	stringstream ss;
	in.open("data/keyword.txt");//read keyword all text
	ss << in.rdbuf();
	in.close();
	
	char content[ss.str().length()+1];
	memcpy(content, ss.str().c_str(), ss.str().length());
	content[ss.str().length()] = 0;
 
	list<char*>::iterator it_keyword;
	
	char *temp = strtok(content,"\r\n"); //delim is \r\n
	char *temp2 = 0;
	while(temp != 0){
		bool exist = false;
		for (list<char*>::iterator it_keyword = list_keyword.begin(); it_keyword != list_keyword.end(); ++it_keyword) {
			if (strcmp(*it_keyword,temp) == 0) {
				exist = true;
				break;
			}
		}
		if (!exist) { //push keyword to list except the repeated keyword
			temp2 = new char[strlen(temp)+1];
			memcpy(temp2,temp,strlen(temp));
			temp2[strlen(temp)] = 0;
			list_keyword.push_back(temp2);
		}
		temp = strtok(0,"\r\n");
	}
}
 
void SensitiveWords::ReleaseKeyWordList(list <char*>&list_keyword) {
	for (list<char*>::iterator it_keyword = list_keyword.begin(); it_keyword != list_keyword.end(); ++it_keyword) {
		delete *it_keyword;
	}
}
 
SensitiveWords::Node* SensitiveWords::NodeHasExist(Node *cur,char data) {
	while(cur != 0){
		if(cur->data == data){
			return cur;
		}
		cur = cur->sibling;
	}
	return 0;
}
 
 
SensitiveWords::Node* SensitiveWords::BuildTree() {
	list <char*>list_keyword;
	
	getWordList(list_keyword);
	
	Node *root = new Node(); //make keyword tree by list
	root->next = 0;
	root->sibling = 0;
	root->data = 0;
	Node *cur = root;
	for (list<char*>::iterator it_keyword = list_keyword.begin(); it_keyword != list_keyword.end(); ++it_keyword){//traversal list 
		int length = strlen(*it_keyword);
		for(int i = 0;i < length; i++) { //visit each char
			
			Node *node=NodeHasExist(cur->next,(*it_keyword)[i]);//check char node does exist in cur->next link list
			
			if(node == 0) {
				node=new Node();
				node->data = (*it_keyword)[i];
				node->last = false;
				node->next = 0;
				node->sibling = 0;
				if(cur->next == 0) {
					cur->next = node; //make node become cur->next's first
				} else {
					Node *temp = cur->next;
					while(temp->sibling != 0) { //make point move to cur->next's last
						temp = temp->sibling;
					}
					temp->sibling = node; //add node at cur-next's last
				}			
			}
			
			//if node exist,skip create node again
 
			cur = node; //make cur point at node 
		}
		cur->last = true; //if is the end of word,set sign at the last,because it may has many branches
		cur = root;
	}
	
	ReleaseKeyWordList(list_keyword);
	
	return root;
}
 
void SensitiveWords::ReleaseTree(Node *root) { //post traversal delete
	if(root != 0) {
		ReleaseTree(root->next);
		ReleaseTree(root->sibling); 
		// free(root);
	}
}                 
	                   
const char* SensitiveWords::LookUp(char *content,Node *root) {
	Node* cur = root->next;
	int start = -1;
	stringstream ss;
	bool shouldReview = false;
	for (int i = 0;i < strlen(content); i++) { //traversal content
	
		bool hasfind=false; //if hasfind,find next char
		
		char ch = content[i];
		
		while(cur != 0) {
			if(cur->data == ch) {
				hasfind=true;
				if(start == -1) { //first time find char ,record first time index
					start = i;
				}
				if(cur->last&&cur->next == 0) { //it has arrived at last branch
					start = -1;
					ss<<"*";
					cur = root->next;
					shouldReview = false; 
				} else if (cur->last) { //it may not arrived at last branch
					start = i+1;
					ss<<"*";
					cur = cur->next;
					shouldReview = true;
				} else {
					cur = cur->next;
				}
				break;
			}
			cur = cur->sibling;
		}
		
		if(shouldReview&&!hasfind) {
			i = start-1; //this time is checking cur->next,it should also check root->next,start-1 because of i++
			shouldReview = false;
			start = -1;
			cur = root->next;
		} else if (!hasfind) {
			if(start>-1) {
				i = start; //start must have checked with root->next,so it was not used to be -1
			}
			ss << content[i];
			start = -1;
			cur = root->next;
		}
	}
	
	if(start>-1&&!shouldReview) {
		for(int j = start; j < strlen(content); j++){
			ss<<content[j];
		}
	}
    return ss.str().c_str();
}

char* SensitiveWords::run() {
    Node *root = BuildTree();
    char input[BUFSIZ];
    cin >> input;
    char *ret = new char(200);
	strcpy(ret, LookUp(input,root));
	ReleaseTree(root);
    return ret;
}