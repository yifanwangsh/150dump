#include<iostream>
using namespace std;

struct Node{
	int data;
	Node* next;
};

Node* insert(Node*n, int d){
	Node*nd	= new Node;
	nd->data = d;
	nd->next = n;
	return nd;
}

Node* findByIndex(Node* n, int i){
	if(n == 0) return 0;
	if(i == 0) return n;
	
	return findByIndex(n->next, --i);
}

int findIndexHelper(Node* n, int d, int i){
	if(n == 0) return -1;
	if(n->data == d) return i;
	
	return findIndexHelper(n->next, d, ++i);
}

int findIndex(Node* n, int d){
	findIndexHelper(n, d, 0);
}

Node* removeByIndex(Node*& n, int i){
	if(i <= 0 || n == NULL) return NULL;
	Node* curr = n;
	Node* to_kill = new Node;
	int j = 0;
	while(curr -> next != NULL){
		if(i == 1){
			return n->next;
		}	
		if(i == j+1){
			to_kill = curr -> next;
			curr -> next = curr -> next -> next;
			delete to_kill;
			return n;
		}
		j++;
	}
	return NULL;
}
	

int main(){
	Node* n = NULL;
	n = insert(n, 3);
	n = insert(n, 21);
	n = insert(n, -19);
	n = insert(n, 46);
	n = insert(n, 15);
	n = removeByIndex(n, 4);
	cout << n -> data << endl;

}
	