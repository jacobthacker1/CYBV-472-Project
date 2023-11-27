// Crystal Beasley, Matthew Cash, Kasey Kautenburger
#ifndef ITEMLIST_H
#define ITEMLIST_H
#include <stdbool.h>

#define     MAX_ITEM_LIST 1024

typedef struct
{
    int items[MAX_ITEM_LIST];
    int itemCount;
} ItemList;

void ItemListInit(ItemList *pItemList);
int ItemListAddItem(ItemList *pItemList, int itemNumber);
int ItemListRemoveItem(ItemList *pItemList, int itemNumber);
bool ItemListHasItem(ItemList *pItemList, int itemNumber);

#endif
