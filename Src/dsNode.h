#ifndef _DS_NODE_H_
#define FILENAME "data.txt"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 노드 구조
typedef struct Node {
    int data; // 번호
    char name[20]; // 이름
    struct Node* prev;
    struct Node* next;
} Node;

// 리스트 구조
typedef struct {
    Node* head;
    int size;
} CircularDoublyLinkedList;

Node* createNode(int data, char *name);
void initList(CircularDoublyLinkedList* list);
void insertSorted(CircularDoublyLinkedList* list, char *name, int data);
Node* findNode(CircularDoublyLinkedList* list, int data);
void searchNode(CircularDoublyLinkedList* list, int data);
void countNode(CircularDoublyLinkedList* list);
void renewalNode(CircularDoublyLinkedList* list, char *newName, int newData, int oldData);
void deleteNode(CircularDoublyLinkedList* list, int data);
void displayList(CircularDoublyLinkedList* list);
void displayReverse(CircularDoublyLinkedList* list); 
void freeList(CircularDoublyLinkedList* list);

#endif /* _DS_NODE_H_ */