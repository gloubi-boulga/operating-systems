/******************************************************************************
* S-INFO-054 --- Solution pour Travail 2                                      *
* Groupe 08                                                                   *
* Membres:                                                                    *
* - HOUIOUX Guillaume                                                         *
* - TONGRES Cyril                                                             *
* - PAVLISKO Joseph                                                           *
* - WALEM Hugo                                                                *
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct circular {
    unsigned int size;
    struct node* head;
};

struct node {
    signed int value;
    struct node* next;
};

bool isEven(int number) {
    return number % 2 == 0;
}

enum ROTATION { EVEN, ODD };

struct circular* mkcircular() {
    struct circular* list = malloc(sizeof(struct circular));
    list->size = 0;
    list->head = NULL;
    return list;
}

void insert(struct circular* cycle, signed int elt) {
    struct node* newNode = malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Problem while allocating memory.\n");
        return;
    }

    newNode->value = elt;

    if (cycle->head == NULL) {
        cycle->head = newNode;
        newNode->next = newNode;
    } else {
        struct node* temp = cycle->head;
        while (temp->next != cycle->head)
            temp = temp->next;

        temp->next = newNode;
        newNode->next = cycle->head;
    }
    cycle->size++;
}

signed int extract(struct circular* cycle) {
    if (cycle->head == NULL) {
        printf("Empty list, nothing to extract.\n");
        return 0;
    }

    struct node* temp = cycle->head;
    signed int extractedValue = temp->value;

    if (temp->next == temp) {
        free(temp);
        cycle->head = NULL;
    } else {
        struct node* lastNode = cycle->head;
        while (lastNode->next != cycle->head)
            lastNode = lastNode->next;

        lastNode->next = temp->next;
        cycle->head = temp->next;
        free(temp);
    }

    cycle->size--;
    return extractedValue;
}

struct node* rotate(struct circular* cycle, enum ROTATION rotation) {

    struct node* current = cycle->head;

    if (rotation == EVEN) {
        while (!isEven(current->value)) {
            current = current->next;
        }
    } else if (rotation == ODD) {
        while (isEven(current->value)) {
            current = current->next;
        }
    }

    cycle->head = current;
    return current;
}

struct node* rotateToEven(struct circular* cycle) {
    return rotate(cycle, EVEN);
}

struct node* rotateToOdd(struct circular* cycle) {
    return rotate(cycle, ODD);
}

void displayCircular(struct circular* cycle) {
    if (cycle->head == NULL) {
        printf("Empty list, nothing to display.\n");
        return;
    }
    struct node* current = cycle->head;
    printf("[ ");
    do {
        printf("%d ", current->value);
        current = current->next;
    } while (current != cycle->head);
    printf("]\n");
}

int main() {
    struct circular* list1 = mkcircular();
    struct circular* list2 = mkcircular();

    insert(list1, 1);
    insert(list1, 2);
    insert(list1, 3);
    insert(list1, 4);
    insert(list1, 5);

    insert(list2, 2);
    insert(list2, 3);
    insert(list2, 4);
    insert(list2, 5);
    insert(list2, 6);

    displayCircular(list1);
    rotateToEven(list1);
    displayCircular(list1);

    displayCircular(list2);
    rotateToOdd(list2);
    displayCircular(list2);

    return EXIT_SUCCESS;
}