#include <stdio.h>
#include <stdlib.h>

/******************************************************************************
* S-INFO-054 --- Solution pour Travail 2                                      *
* Groupe 08                                                                   *
* Membres:                                                                    *
* - HOUIOUX Guillaume                                                         *
* - TONGRES Cyril                                                             *
* - PAVLISKO Joseph                                                           *
* - WALEM Hugo                                                                *
******************************************************************************/

struct circular {
    unsigned int size;
    struct node* head;
};

struct node {
    signed int value;
    struct node* next;
};

struct circular* mkcircular() {
    struct circular* list = malloc(sizeof(struct circular));
    list->size = 0;
    list->head = NULL;
    return list;
}

void insert(struct circular* cycle, signed int elt) {
    struct node* newNode = malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation failed");
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
        printf("The list is empty");
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