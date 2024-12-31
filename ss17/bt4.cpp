#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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

void measureExecutionTime(void (*function)(), const char* name) {
    clock_t start, end;
    start = clock();
    function();
    end = clock();
    double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Thoi gian thuc thi cua %s: %.6f giay\n", name, timeTaken);
}

void preOrderWrapper(Node* root) { preOrder(root); }
void inOrderWrapper(Node* root) { inOrder(root); }
void postOrderWrapper(Node* root) { postOrder(root); }
void DFSWrapper(int start) { DFS(start); }
void BFSWrapper(int start) { BFS(start); }

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


    printf("Duyet BFS tren do thi: ");
    for (int i = 0; i < MAX_NODES; i++) visited[i] = 0;
    BFS(5);
    printf("\n");

    printf("Duyet DFS tren do thi: ");
    for (int i = 0; i < MAX_NODES; i++) visited[i] = 0;
    DFS(5);
    printf("\n");
    printf("\nSo sanh thoi gian thuc thi:\n");
    measureExecutionTime(preOrderWrapper, "Duyet tien thu tu");
    measureExecutionTime(inOrderWrapper, "Duyet trung thu tu");
    measureExecutionTime(postOrderWrapper, "Duyet hau thu tu");
    measureExecutionTime(BFSWrapper, "Duyet BFS tren do thi");
    measureExecutionTime(DFSWrapper, "Duyet DFS tren do thi");

    return 0;
}

