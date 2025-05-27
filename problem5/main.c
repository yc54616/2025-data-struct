#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int key) {
    if (root == NULL) return createNode(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    return root;
}

Node* search(Node* root, int key) {
    if (root == NULL || root->key == key) return root;
    if (key < root->key)
        return search(root->left, key);
    else
        return search(root->right, key);
}

Node* findMin(Node* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

Node* delete(Node* root, int key) {
    if (root == NULL) return NULL;
    if (key < root->key)
        root->left = delete(root->left, key);
    else if (key > root->key)
        root->right = delete(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = findMin(root->right);
        root->key = temp->key;
        root->right = delete(root->right, temp->key);
    }
    return root;
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

void preorder(Node* root) {
    if (!root) return;
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}

int main() {
    Node* root = NULL;
    char command[100];

    printf("BST 명령어 사용법: insert N, delete N, search N\n");
    printf("순회: inorder, preorder, postorder\n");
    printf("종료: exit\n");

    while (1) {
        printf("\n> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // 개행 제거

        if (strncmp(command, "insert ", 7) == 0) {
            int num = atoi(&command[7]);
            root = insert(root, num);
            printf("Inserted %d\n", num);
        } else if (strncmp(command, "delete ", 7) == 0) {
            int num = atoi(&command[7]);
            root = delete(root, num);
            printf("Deleted %d\n", num);
        } else if (strncmp(command, "search ", 7) == 0) {
            int num = atoi(&command[7]);
            Node* found = search(root, num);
            printf(found ? "Found %d\n" : "Not found %d\n", num);
        } else if (strcmp(command, "inorder") == 0) {
            inorder(root); printf("\n");
        } else if (strcmp(command, "preorder") == 0) {
            preorder(root); printf("\n");
        } else if (strcmp(command, "postorder") == 0) {
            postorder(root); printf("\n");
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("지원하지 않는 명령어입니다.");
        }
    }

    return 0;
}
