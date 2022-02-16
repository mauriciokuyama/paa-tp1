#ifndef ITEM_H
#define ITEM_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct Item {
    int id;
    bool E, D, C, B;
} item;

void inicializaItem(item *it);

#endif
