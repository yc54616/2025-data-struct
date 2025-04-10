/*
 * dsNode.c: Circular Doubly Linked List Implementation Functions
 *
 * @author yc54616
 * @version 1.0
 * @date 2025/4/10
 */

#include "dsNode.h"

/* create CircularDoublyLinkedList init */
Node* createNode(int data, char *name) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    strcpy(newNode->name, name); // copy name
    newNode->prev = newNode->next = NULL;
    return newNode;
}

/* CircularDoublyLinkedList initialized */
void initList(CircularDoublyLinkedList* list) {
    list->head = NULL;
    list->size = 0;
}

// front insert ordering 
void insertSorted(CircularDoublyLinkedList* list, char *name, int data) {
    Node* newNode = createNode(data, name);

    list->size += 1;

    if (list->head == NULL) {
        newNode->next = newNode->prev = newNode;
        list->head = newNode;
        return;
    }

    Node* curr = list->head;

    //new node가 head보다 작으면 head 앞에 삽입
    if (data < list->head->data) {
        Node* tail = list->head->prev;

        newNode->next = list->head;
        newNode->prev = tail;
        tail->next = newNode;
        list->head->prev = newNode;
        list->head = newNode;
        return;
    }

    // 중간 또는 끝에 삽입
    do {
        if (curr->data <= data && curr->next->data >= data){
            break;
        }
        else if(curr->next == list->head){
            break;
        }
        else{
            curr = curr->next;
        }
    } while (curr != list->head);
    
    // 위치 찾았으면 curr 다음에 삽입
    Node* nextNode = curr->next;
    curr->next = newNode;
    newNode->prev = curr;
    newNode->next = nextNode;
    nextNode->prev = newNode;
}

/* phone number to find node */
Node* findNode(CircularDoublyLinkedList* list, int data) {
    if (list->head == NULL) return NULL;

    Node* curr = list->head;
    do {
        if (curr->data == data)
            return curr;
        curr = curr->next;
    } while (curr != list->head);

    return NULL;
}

/* findNode function to Node exist */
void searchNode(CircularDoublyLinkedList* list, int data) {
    Node* target = findNode(list, data);
    if (target == NULL) {
        printf("Node with data %d not found.\n", data);
        return;
    }
    printf("Found node: [%p] | %011d | %s \n", target, target->data, target->name);
}

/* Node size check */
void countNode(CircularDoublyLinkedList* list) {
    if (list->head == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("Count: %d\n", list->size);
}

void renewalNode(CircularDoublyLinkedList* list, char *newName, int newData, int oldData) {
    Node* target = findNode(list, oldData);
    if (target == NULL) {
        printf("Node with data %d not found.\n", oldData);
        return;
    }

    // delete old node
    deleteNode(list, oldData);

    // insert new node
    insertSorted(list, newName, newData);
}

/* Node connection delete */
void deleteNode(CircularDoublyLinkedList* list, int data) {
    Node* target = findNode(list, data);
    if (target == NULL){
        printf("Node with data %d not found.\n", data);
        return;
    }

    list->size -= 1;

    // 노드가 하나뿐인 경우
    if (target->next == target) {
        free(target);
        list->head = NULL;
        return;
    }

    target->prev->next = target->next;
    target->next->prev = target->prev;

    if (target == list->head)
        list->head = target->next;

    free(target);
}

/* print CircularDoublyLinkedList for follow link */
void displayList(CircularDoublyLinkedList* list) {
    if (list->head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node* curr = list->head;
    do {
        if(curr != list->head){
            printf("<-> ");
        }
        printf("[%p] | %011d | %s ", curr, curr->data, curr->name);
        curr = curr->next;
    } while (curr != list->head);
    printf("\n");
}

// free all nodes in CircularDoublyLinkedList
void freeList(CircularDoublyLinkedList* list) {
    if (list->head == NULL) return;

    Node* curr = list->head;
    Node* next;
    do {
        next = curr->next;
        free(curr);
        curr = next;
    } while (curr != list->head);

    list->head = NULL;
    list->size = 0;
}