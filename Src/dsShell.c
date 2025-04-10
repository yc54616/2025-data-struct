/*
 * dsShell.c: This file contains the main menu and user interaction functions for a circular doubly linked list program.
 *
 * @author yc54616
 * @version 1.0
 * @date 2025/4/10
 */

#include "dsShell.h"

void showMenu() {
    printf("========================================\n");
    printf("1. Sorted Insert\n");
    printf("2. Delete One\n");
    printf("3. Delete Clear\n");
    printf("4. Renewal\n");
    printf("5. Search\n");
    printf("6. Count\n");
    printf("7. Save Data to File\n");
    printf("8. Load from File\n");
    printf("9. Exit\n");
    printf("========================================\n");
}

int input() {
    printf("> ");
    int menu = 0;
    scanf("%d", &menu);
    return menu;
}

char *inputName(char *name) {
    printf("> ");
    scanf("%19s", name);
    return name;
}