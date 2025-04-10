/*
 * dsFile.c: This file contains functions to save and load a circular doubly linked list to and from a file.
 *
 * @author yc54616
 * @version 1.0
 * @date 2025/4/10
 */ 
 
#include "dsFile.h"

/* CircularDoublyLinkedList save File for macro FILENAME */
void saveToFile(CircularDoublyLinkedList* list) {
    FILE* fp = fopen(FILENAME, "w");
    if (!fp) {
        printf("FILE OPEN ERROR!\n");
        return;
    }

    if (list->head == NULL) {
        fclose(fp);
        return;
    }

    Node* curr = list->head;
    do {
        fprintf(fp, "%d %s\n", curr->data, curr->name); // File save format: phone number(space)name(enter)
        curr = curr->next;
    } while (curr != list->head);

    fclose(fp);
    printf("List saved to file: %s\n", FILENAME);
}

/* CircularDoublyLinkedList load File to macro FILENAME */
void loadFromFile(CircularDoublyLinkedList* list) {
    FILE* fp = fopen(FILENAME, "r");
    if (!fp) {
        printf("FILE OPEN ERROR!\n");
        return;
    }

    int value;
    char name[20];
    while (fscanf(fp, "%d %19s", &value, name) != EOF) {
        insertSorted(list, name, value);  // Insert each line into the list
    }

    fclose(fp);
    printf("List loaded from file: %s\n", FILENAME);
}
