// Crystal Beasley, Matthew Cash, Kasey Kautenburger
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Location.h"
#define     MAX_LOC_NAME_STRING         25
#define     MAX_LOC_DESCRIPTION_STRING 250
int LocationReadMap(Location map[], int maxLocations, char *filename);
void LocationAddItem(Location *pLocation, int itemNumber);
void LocationRemoveItem(Location *pLocation, int itemNumber);
bool LocationHasItem(Location *pLocation, int itemNumber);

int LocationReadMap(Location map[], int maxLocations, char *filename)
{
    FILE *pMapFile = fopen(filename, "r");
    char* token;
    char* mapBuffer = malloc(sizeof(Location)*10);
    char comma = ',';
    int counter = 0;

    for(int i = 0; i < maxLocations; i++)
    {
        ItemListInit(&map[i].items);
    }
    

    if(pMapFile != NULL)
    {   
        int c = 0;
        while((c = fgetc(pMapFile)) != EOF)
        {
            if(c == '\"')
            {
                continue;
            }
            else if(c == '\n')
            {
                mapBuffer[counter] = comma;
                ++counter;
            }
            else if(c == '\r')
            {
                continue;
            }
            else
            {
                mapBuffer[counter] = c; //map buffer
                ++counter;
            }
        }
    }
    else{
        printf("There was a problem opening the map file.\n");
        return -1;
    } 
    counter = 0;

    token = strtok(mapBuffer, ",");

    while((token != NULL))
        {
            map[counter].north = atoi(token); // function will not report conversion errors...
            token = strtok(NULL, ",");
            map[counter].east = atoi(token);
            token = strtok(NULL, ",");
            map[counter].south = atoi(token);
            token = strtok(NULL, ",");
            map[counter].west = atoi(token);
            token = strtok(NULL, ",");
            strcpy(map[counter].name, token); //BoF?
            token = strtok(NULL, ",");
            strcpy(map[counter].description, token); //BoF?
            token = strtok(NULL, ",");
            ++counter;
        }
    
    free(mapBuffer);
    fclose(pMapFile);

    return counter;
}

void LocationAddItem(Location *pLocation, int itemNumber)
{
    pLocation->items.items[itemNumber] = itemNumber;
}

void LocationRemoveItem(Location *pLocation, int itemNumber)
{
    pLocation->items.items[itemNumber] = -1;
}

bool LocationHasItem(Location *pLocation, int itemNumber)
{
    if(pLocation->items.items[itemNumber] == itemNumber)
    {
        return true;
    }

    return false;
}
