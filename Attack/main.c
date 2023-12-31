// Crystal Beasley, Matthew Cash, Kasey Kautenburger
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Location.h"
#include "Item.h"
#include <string.h>
#define     MAX_INPUT                  24
#define     MAX_MAP_LOCATIONS          9
#define     MAX_ITEM_COUNT             6
#define     MAP_FILE                   "map.txt"
#define     ITEM_FILE                  "items.txt"
#define     MAX_LOC_NAME_STRING        25
#define     MAX_LOC_DESCRIPTION_STRING 250
//
typedef struct
{
    int location;
    ItemList items;
} Player;

typedef struct
{
    int numLocations;
    Location map[MAX_MAP_LOCATIONS];
    int itemCount;
    Item items[MAX_ITEM_COUNT];
    Player player;
} Game;
int GameInitialize(Game *pGame);
void PlayerInit(Player *pPlayer, int locationNumber);
void PlayerAddItem(Player *pPlayer, int itemNumber);
void PlayerRemoveItem(Player *pPlayer, int itemNumber);
bool PlayerHasItem(Player *pPlayer, int itemNumber);
void Describe(int location);
int GetUserInput(char *aline, int maxLine);
void ParseUserInput(char *aline);
int GameInitialize(Game *pGame)
{
    pGame->numLocations = MAX_MAP_LOCATIONS; pGame->itemCount = MAX_ITEM_COUNT;

    if(LocationReadMap(pGame->map, MAX_MAP_LOCATIONS, MAP_FILE) == -1){
        return -1;
    }
    if(ItemReadItems(pGame->items, MAX_ITEM_COUNT, ITEM_FILE) < 0){
        return -1;
    } // what happens if any of the functions fail
    // There's no check for the ret value for these functions, perhaps we can abuse this?
    //Player is initialized to location 0
    PlayerInit(&pGame->player, 0);

    return 0;
}


void PlayerInit(Player *pPlayer, int locationNumber)
{
    pPlayer->location = locationNumber;
    ItemListInit(&pPlayer->items);
}
void PlayerAddItem(Player *pPlayer, int itemNumber)
{
    pPlayer->items.items[itemNumber] = itemNumber;
}
void PlayerRemoveItem(Player *pPlayer, int itemNumber)
{
    pPlayer->items.items[itemNumber] = -1;
}
bool PlayerHasItem(Player *pPlayer, int itemNumber)
{
    if(pPlayer->items.items[itemNumber] == itemNumber)
    {
        return true;
    }
    return false;
}

int main()
{
    char* playerInput = malloc(MAX_INPUT); // playerInput is stored on the heap

    Game game;
    GameInitialize(&game);
    bool isPlaying = true;

    void Describe(int location)
    {
        printf(game.map[location].description);
        printf("\n");
        
        for(int i = 0; i < game.map[location].items.itemCount; i++)
        {
            if(game.map[location].items.items[i] > -1) // iterates through the items and sees if there is more than -1 there
            {
                printf("There is a %s here.\n", game.items[i].name);
            }
        }
    }

    int GetUserInput(char *aline, int maxLine)
    {   
        int i = 0;

        //gets(aline); // vulnerable function
        fgets(aline, MAX_INPUT, stdin); // Heap Based Buffer Overflow Location

        //searches for a newline in the aline buffer, then replaces it with a NULL char
        while(i < maxLine)
        {
            if(aline[i] != '\n')
            {
                aline[i] = aline[i];
                i++;
            }
            else
            {
                aline[i] = '\0';
                return i;
            }
        }
        
        printf("You said...");
        printf("%s", aline); // Format Strings Vuln Location
        printf("\n");
        
        return i;
    }

    void ParseUserInput(char *aline)
    {
        char *verb = NULL;
        char *noun = NULL;
        int itemNumber = -1;

        // Check for a valid verb entry
        if (verb == NULL)
        {
            printf("\nYou did not enter a valid selection. Try again!\n");
            return;
        }  

        verb = strtok(aline, " ");
        noun = strtok(NULL, " ");

        switch(verb[0]) // checks the first character of the first string to get the "verb"
        {
            case 'n': // move north
            case 'N':
                if(game.map[game.player.location].north == -1)
                {
                    printf("You can't go that way\n");
                }
                else
                {
                    game.player.location = game.map[game.player.location].north;
                }
                break;
            case 'e': // move east
            case 'E':
                if(game.map[game.player.location].east == -1)
                {
                    printf("You can't go that way\n");
                }
                else
                {
                    game.player.location = game.map[game.player.location].east;
                }
                break;
            case 's': // move south
            case 'S':
                if(game.map[game.player.location].south == -1)
                {
                    printf("You can't go that way\n");
                }
                else
                {
                    game.player.location = game.map[game.player.location].south;
                }
                break;
            case 'w': // move west
            case 'W':
                if(game.map[game.player.location].west == -1)
                {
                    printf("You can't go that way\n");
                }
                else
                {
                    game.player.location = game.map[game.player.location].west;
                }
                break;
            case 'g':
            case 'G': // get the item number
                // Check for a valid noun entry
                if (noun == NULL)                
                {
                    printf("\nYou did not enter a valid item. Try again!\n");
                    break;
                }
                itemNumber = ItemGetItemNumber(game.items, MAX_ITEM_COUNT, noun); // get the item number
                if(LocationHasItem(&game.map[game.player.location], itemNumber))
                {
                    PlayerAddItem(&game.player, itemNumber);
                    LocationRemoveItem(&game.map[game.player.location], itemNumber);
                    printf("You take the %s.\n", noun);
                }
                else
                {
                    printf("There is no %s here.\n", noun);
                }
                break;
            case 'd':
            case 'D': // drop the item number
                // Check for a valid noun entry
                if (noun == NULL)                
                {
                    printf("\nYou did not enter a valid item. Try again!\n");
                    break;
                }                
                itemNumber = ItemGetItemNumber(game.items, MAX_ITEM_COUNT, noun);
                if(PlayerHasItem(&game.player, itemNumber))
                {
                    PlayerRemoveItem(&game.player, itemNumber);
                    LocationAddItem(&game.map[game.player.location], itemNumber);
                }
                else
                {
                    printf("You do not have a %s in your inventory.\n", noun);
                }
                break;            
            case 'i':
            case 'I': // view the item number
                // Check for a valid noun entry
                if (noun == NULL)                
                {
                    printf("\nYou did not enter a valid item. Try again!\n");
                    break;
                }                
                itemNumber = ItemGetItemNumber(game.items, MAX_ITEM_COUNT, noun);
                if(LocationHasItem(&game.map[game.player.location], itemNumber))
                {
                    printf("%s\n", game.items[itemNumber].description);
                }
                else
                {
                    printf("There is no %s here.\n", noun);
                }
                break;
            case 'q':
            case 'Q': // Quit the game
                printf("Goodbye!\n");
                isPlaying = false;
              break;
            default:
                printf("Invalid input\n");
        }
    }

    for(int i = 0; i < MAX_MAP_LOCATIONS; i++)
    {
        switch (i)
        {
            case 0:
                break;
            case 1:
                LocationAddItem(&game.map[1], 5);
                break;
            case 2:
                LocationAddItem(&game.map[2], 2);
                break;
            case 3:
                LocationAddItem(&game.map[3], 3);
                break;
            case 4:
                LocationAddItem(&game.map[4], 4);
                break;
            case 5:
                LocationAddItem(&game.map[5], 1);
                break;
            case 6: // whats up with this not having anything? No location here?
                break;
            case 7:
                LocationAddItem(&game.map[7], 0);
                break;
            case 8: // no location here either.
                break;
            default:
                break; // Missing Default Case Location
        }
    }

    printf("Welcome to my Game!\n");
    printf("Controls:\nGet <item name>\nDrop <item name>\nNorth, South, East, West\n");
    printf("Inspect <item name> (Item must be in the room)\n");
    printf("Q to quit!\n");

    while(isPlaying)
    {
        Describe(game.player.location);
        printf("What would you like to do?\n");
        GetUserInput(playerInput, MAX_INPUT);
        ParseUserInput(playerInput);
    }
    free(playerInput); // is there any way to use this after it has been freed? not likely
    return 0;
}
// There are at least 12 vulnerabilities in this game
