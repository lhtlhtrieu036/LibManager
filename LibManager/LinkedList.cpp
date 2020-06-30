#include "LinkedList.h"

/**
 * Ham khoi tao danh sach lien ket don.
 *
 * @return			con tro den danh sach lien ket moi vua tao.
 */
linkedList* createList() {
	linkedList* newList = (linkedList*)malloc(sizeof(linkedList));
	newList->head = NULL;
	return newList;
}

/**
 * Ham khoi tao mot node cua danh sach lien ket don.
 *
 * @param value		gia tri cua node.
 * @return			con tro den node vua tao.
 */
Node* createNode(int value) {
	Node* newNode  = (Node*)malloc(sizeof(Node));
	newNode->next  = NULL;
	newNode->value = value;
	return newNode;
}

/**
 * Ham chen mot 
 */
void insertHead(linkedList* list, void* value) {
	Node* newNode = createNode(value);
	newNode->next = list->head;
	list->head = newNode;
}