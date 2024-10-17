#include <stdio.h>
#include <stdlib.h>

// Node structure for circular queue
struct Node {
    int data;
    struct Node* next;
};

// Structure for the Circular Queue
struct CircularQueue {
    struct Node* front;
    struct Node* rear;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create an empty circular queue
struct CircularQueue* createCircularQueue() {
    struct CircularQueue* queue = (struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to check if the circular queue is empty
int isEmpty(struct CircularQueue* queue) {
    return queue->front == NULL;
}

// Function to enqueue an element into the circular queue
void enqueue(struct CircularQueue* queue, int data) {
    struct Node* temp = createNode(data);
    if (temp == NULL) {
        printf("Memory allocation error\n");
        return;
    }
    if (isEmpty(queue)) {
        queue->front = queue->rear = temp;
        temp->next = queue->front;  // Point the new node to itself
    } else {
        queue->rear->next = temp;
        queue->rear = temp;
        queue->rear->next = queue->front; // Link the new rear to the front
    }
    printf("%d enqueued to queue\n", data);
}

// Function to dequeue an element from the circular queue
int dequeue(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    struct Node* temp = queue->front;
    int data = temp->data;

    if (queue->front == queue->rear) {
        // Only one node in the queue
        queue->front = queue->rear = NULL;
    } else {
        queue->front = queue->front->next;
        queue->rear->next = queue->front; // Update rear to point to new front
    }
    free(temp);
    return data;
}

// Function to display the elements of the circular queue
void displayCircularQueue(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Circular Queue is empty\n");
        return;
    }
    struct Node* temp = queue->front;
    printf("Circular Queue elements: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != queue->front);
    printf("\n");
}

// Main function to demonstrate the circular queue operations
int main() {
    struct CircularQueue* queue = createCircularQueue();
    int choice, value;

    while (1) {
        printf("\n-- Circular Queue Menu --\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display Circular Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(queue, value);
                break;
            case 2:
                value = dequeue(queue);
                if (value != -1) {
                    printf("Dequeued element: %d\n", value);
                }
                break;
            case 3:
                displayCircularQueue(queue);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
