/* list.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

// Creation/Deletion Functions

Node* new_node(char* str) {

    Node* newNode = malloc(sizeof(Node));
    newNode->value = strcpy(strdup(str), str);
    newNode->next = NULL;

    return newNode;
}

List new_list() {

    Node **list = malloc(sizeof(List));
    *list = NULL;

    return list;
}

List load_list(char* fileName) {

    FILE* file = fopen(fileName, "r");
    List list = new_list();

    if (file == 0) {
        printf("History file not found\n");
        return NULL;
    }
    char buffer[MAX_INPUT + 2];
    while (fgets(buffer, MAX_INPUT + 2, file)) {
        char* string = strdup(buffer);
        if (strlen(string) > 512) {
            // Failsafe in case the input line is over the maximum command length
            string[MAX_INPUT] = '\n';
            string[MAX_INPUT + 1] = '\0';
        } 
        add(list, string);
    }
    fclose(file);
    return list;
}

List copy_list(List list) {

    List newList = new_list();
    Node* node = *list;

    while (node != NULL) {
        push(newList, node->value);
        node = node->next;
    }
    return newList;
}

List sublist(List list, int start, int end) {

    List sublist = NULL;

    if ((start > -1) & (end <= size(list)) & (start < end)) {
        sublist = new_list();
        for (int i = start; i < end; i++) {
            add(sublist, get_at(list, i));
        }
    }
    return sublist;
}

void delete_node(Node* node) {
    free(node);
    node = NULL;
}

void clear(List list) {

    Node* node = *list;
    Node* nextNode;
    while (node != NULL) {
        nextNode = node->next;
        delete_node(node);
        node = nextNode;
    }
    *list = NULL;
}

void push(List list, char* value) {

    if (size(list) == HISTORY_SIZE)
        pop(list);

    if (*list != NULL) {
        // Has Item(s)
        Node* newNode = new_node(value);
        Node* node = *list;
        newNode->next = node;
        *list = newNode;
    } else {
        // Empty List
        *list = new_node(value);
    }
}

void add(List list, char* value) {

    if (*list != NULL) {
        Node *node = *list;
        while (node->next != NULL) {
            node = node->next;
        }
        node->next = new_node(value);
    } else {
        *list = new_node(value);
    }
}

void print_list(List list) {

    if (!is_empty(list)) {
        if ((*list)->next == NULL) {
            printf("[\"%s\"]\n", (*list)->value);
        } else {
            Node* node = *list;
            printf("[");
            while (node != NULL) {
                printf("\"%s\"", node->value);
                node = node->next;
                if(node != NULL) {
                    printf(", ");
                }
            }
            printf("]\n");
        }
    } else {
        printf("[]\n");
    }
}

char* pop(List list) {

    char* value = NULL;

    if (*list != NULL) {
        if ((*list)->next == NULL) {
            value = (*list)->value;
            delete_node(*list);
            *list = NULL;
        } else {
            Node* prevNode = *list;
            Node* currNode = prevNode->next;
            while (currNode->next != NULL) {
                prevNode = currNode;
                currNode = currNode->next;
            }
            value = currNode->value;
            delete_node(currNode);
            prevNode->next = NULL;
        }
    }
    return value;
}

char* peek(List list) {

    char* value = NULL;

    if (*list != NULL) {
        if ((*list)->next == NULL) {
            value = (*list)->value;
        } else {
            Node* node = *list;
            while (node->next != NULL) {
                node = node->next;
            }
            value = node->value;
        }
    }
    return value;
}


char* rem(List list) {

    char* value = NULL;

    if (*list != NULL) {
        if ((*list)->next == NULL) {
            // Single Element
            value = (*list)->value;
            delete_node(*list);
            *list = NULL;
        } else {
            // Multiple Elements
            Node* firstNode = *list;
            Node* secondNode = firstNode->next;
            value = firstNode->value;
            *list = secondNode;
            delete_node(firstNode);
        }
    }
    return value;
}

char* get_at(List list, int index) {

    char* value = NULL;
    int currIndex = 0;

    if (size(list)-1 >= index) {
        Node* node = *list;
        while (currIndex != index) {
            node = node->next;
            currIndex++;
        }
        value = node->value;
    }
    return value;
}

int index_of(List list, char* value) {

    int indexFound = -1;
    int currIndex = 0;
    Node* node = *list;

    while(node != NULL) {
        if (strcmp(value, node->value) == 0) {
            indexFound = currIndex;
            break;
        }
        node = node->next;
        currIndex++;
    }
    return indexFound;
}

int contains(List list, char* value) {

    if (index_of(list, value) == -1) {
        return 0;
    }
    return 1;
}

int replace_at(List list, int index, char* value) {

    int successful = 0;
    int currIndex = 0;

    if (size(list)-1 >= index) {
        Node* node = *list;
        while ((currIndex != index) & (node != NULL)) {
            node = node->next;
            currIndex++;
        }
        node->value = value;
        if (strcmp(value, node->value) == 0) {
            successful = 1;
        }
    }
    return successful;
}

int insert_at(List list, int index, char* value) {

    int successful = 0;

    if (index == 0) {
        add(list, value);
        successful = 1;
    } else if (index == size(list)) {
        add(list, value);
        successful = 1;
    } else if ((index > 0) & (index <= size(list)-1)) {
        Node* prevNode = *list;
        Node* currNode = prevNode->next;
        Node* newNode = new_node(value);
        for (int i = 1; i != index; i++) {
            prevNode = currNode;
            currNode = currNode->next;
        }
        prevNode->next = newNode;
        newNode->next = currNode;
        successful = 1;
    }
    return successful;
}

char* remove_at(List list, int index) {

    char* value = NULL;

    if ((list != NULL) & (size(list)-1 >= index) & (index >= 0)) {
        if (index == 0) {
            value = rem(list);
        } else if (index == size(list)-1) {
            value = pop(list);
        } else {
            Node* prevNode = *list;
            Node* currNode = prevNode->next;
            for (int i = 1; i != index; i++) {
                prevNode = currNode;
                currNode = currNode->next;
            }
            value = currNode->value;
            prevNode->next = currNode->next;
            delete_node(currNode);
        }
    }
    return value;
}

int save_list(List list, char* fileName) {

    FILE* file = fopen(fileName, "w");
    Node* node = *list;

    if (file == 0) {
        printf("History file not found\n");
        return -1;
    }
    int numElements = 0;
    while (node != NULL) {
        fprintf(file, "%s", node->value);
        node = node->next;
        numElements++;
    }
    fclose(file);
    return numElements;
}

int is_empty(List list) {

    if (*list == NULL) {
        return 1;
    }
    return 0;
}

int size(List list) {

    int listSize = 0;

    if (!is_empty(list)) {
        Node *node = *list;
        while (node != NULL) {
            node = node->next;
            listSize++;
        }
    }
    return listSize;
}


