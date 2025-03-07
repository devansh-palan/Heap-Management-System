#include<stdio.h>
#include<stdlib.h>
#define hsize 100

typedef struct node {
    short int start, end;
    struct node *next;
} node;

node *allocl, *freel;
int heap[hsize];

void initialize() {
    allocl = NULL;
    freel = (node*)malloc(sizeof(node));
    freel->next = NULL;
    freel->start = 0;
    freel->end = hsize - 1;
}

short int firstfit(int size) {
    short int a = -1;
    if (freel != NULL) {
        if (size < 2) size = 2;
        node *t = freel, *prev = NULL;
        while (t != NULL && (t->end - t->start + 1) < size) {
            prev = t;
            t = t->next;
        }
        if (t != NULL) {
            node *temp = (node*)malloc(sizeof(node));
            temp->next = NULL;
            temp->start = t->start;
            temp->end = t->start + size - 1;
            t->start += size;
            temp->next = allocl;
            allocl = temp;
            a = temp->start;
            if (t->start > t->end) {
                if (prev == NULL) {
                    freel = freel->next;
                } else {
                    prev->next = t->next;
                }
                free(t);
            }
        }
    }
    return a;
}

short int bestfit(int size) {
    short int a = -1;
    node *ptr = NULL, *prev = NULL;
    node *t = freel, *tprev = NULL;
    if (freel != NULL) {
        if (size < 2) size = 2;
        while (t != NULL && (t->end - t->start + 1) < size) {
            tprev = t;
            t = t->next;
        }
        if (t != NULL) {
            ptr = t;
            prev = tprev;
            while (t != NULL) {
                if ((t->end - t->start + 1) >= size && (t->end - t->start + 1) < (ptr->end - ptr->start + 1)) {
                    ptr = t;
                    prev = tprev;
                }
                tprev = t;
                t = t->next;
            }
            node *temp = (node*)malloc(sizeof(node));
            temp->next = NULL;
            temp->start = ptr->start;
            temp->end = ptr->start + size - 1;
            ptr->start += size;
            temp->next = allocl;
            allocl = temp;
            a = temp->start;
            if (ptr->start > ptr->end) {
                if (prev == NULL) {
                    freel = freel->next;
                } else {
                    prev->next = ptr->next;
                }
                free(ptr);
            }
        }
    }
    return a;
}

void freeblock(short int a) {
    node *prev = NULL, *ptr = allocl;
    while (ptr != NULL && ptr->start != a) {
        prev = ptr;
        ptr = ptr->next;
    }
    if (ptr != NULL) {
        if (prev == NULL) {
            allocl = allocl->next;
        } else {
            prev->next = ptr->next;
        }
        node *search = freel, *prevFree = NULL;
        while (search != NULL && search->start < ptr->start) {
            prevFree = search;
            search = search->next;
        }
        ptr->next = search;
        if (prevFree == NULL) {
            freel = ptr;
        } else {
            prevFree->next = ptr;
        }
        if (prevFree != NULL && prevFree->end + 1 == ptr->start) {
            prevFree->end = ptr->end;
            prevFree->next = ptr->next;
            free(ptr);
            ptr = prevFree;
        }
        if (search != NULL && ptr->end + 1 == search->start) {
            ptr->end = search->end;
            ptr->next = search->next;
            free(search);
        }
    }
}

void showlists() {
    node *t = freel;
    printf("Free list:\n");
    while (t != NULL) {
        printf("\t start: %d \t end: %d\n", t->start, t->end);
        t = t->next;
    }
    t = allocl;
    printf("Allocated list:\n");
    while (t != NULL) {
        printf("\t start: %d \t end: %d\n", t->start, t->end);
        t = t->next;
    }
}

int main() {
    initialize();
    int size = 0, choice = 1, add = -1;
    while (choice) {
        printf("Choose an option:\n1. First Fit\n2. Best Fit\n3. Free Memory\n4. Show Lists\n5. Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter block size:\n");
                scanf("%d", &size);
                add = firstfit(size);
                if (add != -1) {
                    printf("Allocated at index: %d (Actual Address: %p)\n", add, &heap[add]);
                } else {
                    printf("Heap full. Not enough space.\n");
                }
                break;
            case 2:
                printf("Enter block size:\n");
                scanf("%d", &size);
                add = bestfit(size);
                if (add != -1) {
                    printf("Allocated at index: %d (Actual Address: %p)\n", add, &heap[add]);
                } else {
                    printf("Heap full. Not enough space.\n");
                }
                break;
            case 3:
                printf("Enter start address to free:\n");
                scanf("%d", &add);
                freeblock(add);
                showlists();
                break;
            case 4:
                showlists();
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
