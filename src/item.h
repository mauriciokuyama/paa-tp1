#ifndef ITEM_H
#define ITEM_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct Item {
    int id,poder,qtpk;
    bool E, D, C, B;
} item;

void inicializaItem(item *it);

#endif
