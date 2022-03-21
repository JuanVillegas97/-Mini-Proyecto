#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct
{
    char line[100];
    int quantity;
} String;

typedef struct
{
    String name;
    String description;
    String categories;
    String profile;
    String ingredients[10];
} Recipes;

FILE *ptrFile;
char chr;

int main(int argc, char const *argv[])
{
    FILE *filePointer;
    Recipes Recipe[3];
    int bufferLength = 100;
    char buffer[bufferLength];
    bool gate = false;
    int lineNum = 0;
    int ingredientsNum = 0;
    int ingredientsQuantity = 0;
    int a = 0;
    int recipeNum = 0;

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
            strcpy(Recipe[recipeNum].name.line, (strchr(buffer, ':') + 1));
            break;
        case 1:
            strcpy(Recipe[recipeNum].description.line, (strchr(buffer, ':') + 1));
            break;
        case 2:
            strcpy(Recipe[recipeNum].categories.line, (strchr(buffer, ':') + 1));
            break;
        case 3:
            strcpy(Recipe[recipeNum].profile.line, (strchr(buffer, ':') + 1));
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
        printf("%s", Recipe[i].name.line);
        printf("%s", Recipe[i].description.line);
        printf("%s", Recipe[i].categories.line);
        printf("%s", Recipe[i].profile.line);
        for (int j = 0; j <= ingredientsNum; j++)
        {
            printf("%s %d\n", Recipe[i].ingredients[j].line, Recipe[i].ingredients[j].quantity);
        }
    }

    fclose(filePointer);
}
