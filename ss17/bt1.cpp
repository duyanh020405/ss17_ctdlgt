#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
    bool* visited;
} Graph;

typedef struct Queue {
    int* items;
    int front;
    int rear;
    int size;
} Queue;
Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest);
void DFS(Graph* graph, int vertex);
void BFS(Graph* graph, int startVertex);
Node* createNode(int vertex);

// Function prototypes for queue operations
Queue* createQueue(int size);
void enqueue(Queue* queue, int value);
int dequeue(Queue* queue);
bool isEmpty(Queue* queue);

int main() {
    int vertices, edges;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    Graph* graph = createGraph(vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the edges (source and destination):\n");
    for (int i = 0; i < edges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    int startVertex;
    printf("Enter the starting vertex for DFS and BFS: ");
    scanf("%d", &startVertex);

    printf("DFS Traversal: ");
    DFS(graph, startVertex);

    for (int i = 0; i < vertices; i++) {
        graph->visited[i] = false;
    }

    printf("\nBFS Traversal: ");
    BFS(graph, startVertex);

    return 0;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (bool*)malloc(vertices * sizeof(bool));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

void DFS(Graph* graph, int vertex) {
    graph->visited[vertex] = true;
    printf("%d ", vertex);

    Node* temp = graph->adjLists[vertex];

    while (temp) {
        int connectedVertex = temp->vertex;

        if (!graph->visited[connectedVertex]) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

void BFS(Graph* graph, int startVertex) {
    Queue* queue = createQueue(graph->numVertices);

    graph->visited[startVertex] = true;
    enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        Node* temp = graph->adjLists[currentVertex];

        while (temp) {
            int connectedVertex = temp->vertex;

            if (!graph->visited[connectedVertex]) {
                graph->visited[connectedVertex] = true;
                enqueue(queue, connectedVertex);
            }
            temp = temp->next;
        }
    }

    free(queue->items);
    free(queue);
}

Queue* createQueue(int size) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->items = (int*)malloc(size * sizeof(int));
    queue->front = -1;
    queue->rear = -1;
    queue->size = size;
    return queue;
}

void enqueue(Queue* queue, int value) {
    if (queue->rear == queue->size - 1) {
        return;
    }
    if (queue->front == -1) {
        queue->front = 0;
    }
    queue->items[++queue->rear] = value;
}

int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        return -1;
    }
    int item = queue->items[queue->front++];
    if (queue->front > queue->rear) {
        queue->front = queue->rear = -1;
    }
    return item;
}

bool isEmpty(Queue* queue) {
    return queue->front == -1;
}

