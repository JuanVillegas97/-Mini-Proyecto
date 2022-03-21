// Juan Eduardo VIllegas Rios A00826615
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    char line[100];
    int quantity;
} Ingredients;

typedef struct
{
    char name[100];
    char description[100];
    char categories[100];
    char profile[100];
    Ingredients ingredients[10];
} Recipes;

FILE *ptrFile;
char chr;

int main(int argc, char const *argv[])
{
    FILE *filePointer;
    Recipes Recipe[3];
    int bufferLength = 100;
    char buffer[bufferLength];
    int lineNum = 0, ingredientsNum = 0, recipeNum = 0, ingredientsQuantity = 0;
    filePointer = fopen("Recipes.txt", "r");
    while (fgets(buffer, bufferLength, filePointer))
    {
        if (strcmp(buffer, "\n") == 0)
        {
            lineNum = -1;
            ingredientsNum = 0;
            recipeNum++;
        }
        switch (lineNum)
        {
        case 0:
            strcpy(Recipe[recipeNum].name, (strchr(buffer, ':') + 1));
            break;
        case 1:
            strcpy(Recipe[recipeNum].description, (strchr(buffer, ':') + 1));
            break;
        case 2:
            strcpy(Recipe[recipeNum].categories, (strchr(buffer, ':') + 1));
            break;
        case 3:
            strcpy(Recipe[recipeNum].profile, (strchr(buffer, ':') + 1));
            break;
        case 4:
            break;
        case 5:
            Recipe[recipeNum].ingredients[ingredientsNum].quantity = atoi((strchr(buffer, ':') + 1));
            strcpy(Recipe[recipeNum].ingredients[ingredientsNum].line, strtok(buffer, ":"));
            ingredientsNum++;
            break;
        default:
            break;
        }
        lineNum++;
        if (lineNum == 6)
        {
            lineNum = 5;
        }
    }

    for (size_t i = 0; i <= recipeNum; i++)
    {
        printf("Recipe:%s", Recipe[i].name);
        printf("Description:%s", Recipe[i].description);
        printf("Categories:%s", Recipe[i].categories);
        printf("Profile:%s", Recipe[i].profile);
        printf("Ingredients:");
        for (int j = 0; j <= ingredientsNum; j++)
        {
            printf("%s:%d\n", Recipe[i].ingredients[j].line, Recipe[i].ingredients[j].quantity);
        }
        printf("\n");
    }

    fclose(filePointer);
}
