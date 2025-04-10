/*
 * dsMain.c: This file processing main interface program for a circular doubly linked list.
 *
 * @author yc54616
 * @version 1.0
 * @date 2025/4/10
 */

#include "dsMain.h"

int main() {
    CircularDoublyLinkedList list;
    initList(&list);

    int loop = 1;
    char inputNameValue[20];
    int inputValue, inputValue2;

    while(loop){
        displayList(&list);
        showMenu();

        switch (input()) {
            case 1:
                insertSorted(&list, inputName(inputNameValue), (inputValue = input()));
                break;
            case 2:
                deleteNode(&list, (inputValue = input()));
                break;
            case 3:
                freeList(&list);
                break;
            case 4:
                renewalNode(&list, inputName(inputNameValue), (inputValue = input()), (inputValue2 = input()));
                break;
            case 5:
                searchNode(&list, (inputValue = input()));
                break;
            case 6:
                countNode(&list);
                break;
            case 7:
                saveToFile(&list);
                break;
            case 8:
                loadFromFile(&list);
                break;
            case 9:
                loop = 0;
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid menu. Please try again.\n");
        }
    }
    
    freeList(&list);
    return 0;
}
