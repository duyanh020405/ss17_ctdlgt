#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adjList[MAX];
bool visited[MAX];

typedef struct Queue {
    int items[MAX];
    int front, rear;
} Queue;

void initGraph(int vertices) {
    for (int i = 0; i < vertices; i++) {
        adjList[i] = NULL;
    }
}

void addEdge(int src, int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = adjList[src];
    adjList[src] = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->next = adjList[dest];
    adjList[dest] = newNode;
}

void DFS(int vertex) {
    visited[vertex] = true;
    printf("%d ", vertex);

    Node* temp = adjList[vertex];
    while (temp) {
        int connectedVertex = temp->vertex;
        if (!visited[connectedVertex]) {
            DFS(connectedVertex);
        }
        temp = temp->next;
    }
}

void initQueue(Queue* q) {
    q->front = q->rear = -1;
}

bool isEmpty(Queue* q) {
    return q->front == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX - 1) {
        printf("Queue is full\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->items[++q->rear] = value;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int item = q->items[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return item;
}

void BFS(int startVertex) {
    Queue q;
    initQueue(&q);

    visited[startVertex] = true;
    enqueue(&q, startVertex);

    while (!isEmpty(&q)) {
        int currentVertex = dequeue(&q);
        printf("%d ", currentVertex);

        Node* temp = adjList[currentVertex];

        while (temp) {
            int adjVertex = temp->vertex;

            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                enqueue(&q, adjVertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int vertices, edges;

    printf("Nhap so luong dinh: ");
    scanf("%d", &vertices);
    
    printf("Nhap so luong canh: ");
    scanf("%d", &edges);

    initGraph(vertices);

    printf("Nhap cac cap canh (u v):\n");
    for (int i = 0; i < edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    int startVertex;
    printf("Nhap dinh bat dau duyet: ");
    scanf("%d", &startVertex);

    printf("Duyet DFS: ");
    for (int i = 0; i < vertices; i++) {
        visited[i] = false;
    }
    DFS(startVertex);
    printf("\n");

    printf("Duyet BFS: ");
    for (int i = 0; i < vertices; i++) {
        visited[i] = false;
    }
    BFS(startVertex);
    printf("\n");

    return 0;
}

