#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct Deque {
    Node* front;
    Node* rear;
} Deque;


Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}


void initialize(Deque* deque) {
    deque->front = NULL;
    deque->rear = NULL;
}


int isEmpty(Deque* deque) {
    return (deque->front == NULL);
}


void insertFront(Deque* deque, int value) {
    Node* newNode = createNode(value);
    if (isEmpty(deque)) {
        deque->front = newNode;
        deque->rear = newNode;
    } else {
        newNode->next = deque->front;
        deque->front->prev = newNode;
        deque->front = newNode;
    }
    printf("Inserted %d at the front\n", value);
}


void insertRear(Deque* deque, int value) {
    Node* newNode = createNode(value);
    if (isEmpty(deque)) {
        deque->front = newNode;
        deque->rear = newNode;
    } else {
        newNode->prev = deque->rear;
        deque->rear->next = newNode;
        deque->rear = newNode;
    }
    printf("Inserted %d at the rear\n", value);
}


int deleteFront(Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty\n");
        return -1;
    }
    Node* temp = deque->front;
    int value = temp->data;

    if (deque->front == deque->rear) {
        // Only one element was present
        deque->front = NULL;
        deque->rear = NULL;
    } else {
        deque->front = deque->front->next;
        deque->front->prev = NULL;
    }
    free(temp);
    printf("Removed %d from the front\n", value);
    return value;
}


int deleteRear(Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty\n");
        return -1;
    }
    Node* temp = deque->rear;
    int value = temp->data;

    if (deque->front == deque->rear) {
        
        deque->front = NULL;
        deque->rear = NULL;
    } else {
        deque->rear = deque->rear->prev;
        deque->rear->next = NULL;
    }
    free(temp);
    printf("Removed %d from the rear\n", value);
    return value;
}


void display(Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty\n");
        return;
    }
    Node* current = deque->front;
    printf("Deque elements: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}


int main() {
    Deque deque;
    initialize(&deque);

    int choice, val;

    do {
        printf("\n1. Insert Front\n2. Insert Rear\n3. Delete Front\n4. Delete Rear\n5. Display\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert at the front: ");
                scanf("%d", &val);
                insertFront(&deque, val);
                break;
            case 2:
                printf("Enter the value to insert at the rear: ");
                scanf("%d", &val);
                insertRear(&deque, val);
                break;
            case 3:
                deleteFront(&deque);
                break;
            case 4:
                deleteRear(&deque);
                break;
            case 5:
                display(&deque);
                break;
            case 6:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
