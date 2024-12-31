#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

int adjacencyList[MAX_NODES][MAX_NODES] = {0};
int visited[MAX_NODES];

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void insert(Node** root, int value) {
    if (*root == NULL) {
        *root = createNode(value);
    } else if (value < (*root)->data) {
        insert(&(*root)->left, value);
    } else {
        insert(&(*root)->right, value);
    }
}

void preOrder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

void postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

void convertTreeToGraph(Node* root) {
    if (root == NULL) return;

    if (root->left != NULL) {
        adjacencyList[root->data][root->left->data] = 1;
        adjacencyList[root->left->data][root->data] = 1;
        convertTreeToGraph(root->left);
    }

    if (root->right != NULL) {
        adjacencyList[root->data][root->right->data] = 1;
        adjacencyList[root->right->data][root->data] = 1;
        convertTreeToGraph(root->right);
    }
}

void BFS(int start) {
    bool queue[MAX_NODES] = {false};
    int front = 0, rear = 0;
    int queueArray[MAX_NODES];

    queueArray[rear++] = start;
    visited[start] = 1;

    while (front < rear) {
        int current = queueArray[front++];
        printf("%d ", current);

        for (int i = 0; i < MAX_NODES; i++) {
            if (adjacencyList[current][i] && !visited[i]) {
                queueArray[rear++] = i;
                visited[i] = 1;
            }
        }
    }
}

void DFS(int start) {
    visited[start] = 1;
    printf("%d ", start);

    for (int i = 0; i < MAX_NODES; i++) {
        if (adjacencyList[start][i] && !visited[i]) {
            DFS(i);
        }
    }
}

int main() {
    Node* root = NULL;
    int values[] = {5, 3, 8, 2, 4, 7, 9};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        insert(&root, values[i]);
    }

    printf("Duyet tien thu tu: ");
    preOrder(root);
    printf("\n");

    printf("Duyet trung thu tu: ");
    inOrder(root);
    printf("\n");

    printf("Duyet hau thu tu: ");
    postOrder(root);
    printf("\n");

    convertTreeToGraph(root);

    printf("Duyet BFS tren do thi: ");
    for (int i = 0; i < MAX_NODES; i++) visited[i] = 0;
    BFS(5);
    printf("\n");

    printf("Duyet DFS tren do thi: ");
    for (int i = 0; i < MAX_NODES; i++) visited[i] = 0;
    DFS(5);
    printf("\n");

    return 0;
}

