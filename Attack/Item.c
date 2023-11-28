// Crystal Beasley, Matthew Cash, Kasey Kautenburger
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Item.h"
#define MAX_ITEM_NAME_STRING            25
#define MAX_ITEM_DESCRIPTION_STRING     80
#define MAX_ITEMS                       12
int ItemReadItems(Item items[],int maxItems, char *fileName);
int ItemGetItemNumber(Item items[], int maxItems, char* itemName);

int ItemReadItems(Item items[],int maxItems, char *fileName)
{
    // maxItems is not used -- not a vuln.
    FILE *pItemFile = fopen(fileName, "r");
    char* token;
    char* fileBuffer = calloc(sizeof(Item)*MAX_ITEMS, 1);
    char comma = ',';
    int itemsRead = 0;

    if(pItemFile != NULL)
    {   
        int c = 0;
        while((c = fgetc(pItemFile)) != EOF) // the c variable may allow for int overflow since it is a
            // c is an int when it should be a char.
        {
            if(c == '\"')
            {
                continue;
            }
            else if(c == '\n')
            {
                fileBuffer[itemsRead] = comma;
                ++itemsRead;
            }
            else if(c == '\r')
            {
                continue;
            }
            else
            {
                fileBuffer[itemsRead] = c; // narrowing converstion from int to signed char. This can be an overflow
                ++itemsRead;
            }
        }
        itemsRead = 0;

        token = strtok(fileBuffer, ","); // The token is the string in between the commas

        while((token != NULL))
        {
            // what if items is null...?
            // we can modify the names in the items to cause a buffer overflow.
            // The item name buffer is MAX_ITEM_NAME_STRING (25 bytes) long.
            strcpy(items[itemsRead].name, token); // BoF?
            //token could be null
            token = strtok(NULL, ",");
            // another buffer overflow here.
            strcpy(items[itemsRead].description, token); //BoF?
            token = strtok(NULL, ",");
            ++itemsRead;
        }
        fclose(pItemFile);
        free(fileBuffer);
        return itemsRead;
    }
    else
    {
        printf("Error reading item.txt");
        fclose(pItemFile);
        free(fileBuffer); // maybe a doublefree if you get rid of item.txt?
        return -1;
    }
}

// loops through the items in the item array and looks for an item with the correct name
int ItemGetItemNumber(Item items[], int maxItems, char* itemName)
{
    for(int i = 0; i < maxItems; i++)
    {
        //buffer overflow potential?
        if(strcmp(itemName, items[i].name) == 0)
        {
            return i;
        }
    }
    return -1;
}
