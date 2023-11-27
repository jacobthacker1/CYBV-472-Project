// Crystal Beasley, Matthew Cash, Kasey Kautenburger
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ItemList.h"
#define     MAX_ITEM_LIST 1024
void ItemListInit(ItemList *pItemList);
int ItemListAddItem(ItemList *pItemList, int itemNumber);
int ItemListRemoveItem(ItemList *pItemList, int itemNumber);
bool ItemListHasItem(ItemList *pItemList, int itemNumber);

void ItemListInit(ItemList *pItemList)
{
    pItemList->itemCount = 6;
    for(int i = 0; i < MAX_ITEM_LIST; i++)
    {
        pItemList->items[i] = -1;
    }
}

int ItemListAddItem(ItemList *pItemList, int itemNumber)
{
    pItemList->items[itemNumber] = itemNumber;
    return pItemList->items[itemNumber];
}

int ItemListRemoveItem(ItemList *pItemList, int itemNumber)
{
    pItemList->items[itemNumber] = -1;
    return pItemList->items[itemNumber];
}

bool ItemListHasItem(ItemList *pItemList, int itemNumber)
{  
    bool hasItem = false;

    if(pItemList->items[itemNumber] == itemNumber)
    {
        hasItem = true;
    }
    
    return hasItem;
}
