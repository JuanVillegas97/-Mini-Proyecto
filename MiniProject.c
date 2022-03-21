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
    Recipes Recipe;
    int bufferLength = 100;
    char buffer[bufferLength];
    bool gate = false;
    int lineNum = 0;
    int ingredientsNum = 0;
    int ingredientsQuantity = 0;
    int a = 0;

    filePointer = fopen("Recipes.txt", "r");
    while (fgets(buffer, bufferLength, filePointer))
    {
        if (strcmp(buffer, "\n") == 0)
        {
            lineNum = -1;
        }
        switch (lineNum)
        {
        case 0:
            strcpy(Recipe.name.line, (strchr(buffer, ':') + 1));
            break;
        case 1:
            strcpy(Recipe.description.line, (strchr(buffer, ':') + 1));
            break;
        case 2:
            strcpy(Recipe.categories.line, (strchr(buffer, ':') + 1));
            break;
        case 3:
            strcpy(Recipe.profile.line, (strchr(buffer, ':') + 1));
            break;
        case 4:
            break;
        case 5:
            Recipe.ingredients[ingredientsNum].quantity = atoi((strchr(buffer, ':') + 1));
            strcpy(Recipe.ingredients[ingredientsNum].line, strtok(buffer, ":"));
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
    printf("%s", Recipe.name.line);
    printf("%s", Recipe.description.line);
    printf("%s", Recipe.categories.line);
    printf("%s", Recipe.profile.line);
    for (int i = 0; i < ingredientsNum; i++)
    {
        printf("%s %d\n", Recipe.ingredients[i].line, Recipe.ingredients[i].quantity);
    }

    fclose(filePointer);
}

// int numRecipes, size;
// bool gate = false;

// printf("How many recipes are?");
// scanf("%d", &numRecipes);
// Recipes Recipe[numRecipes];
// Recipes Recipe;
// printf("Enter something\n");
// scanf("%s", Recipe.ingredients[0].line);
// scanf("%s", Recipe.ingredients[1].line);
// printf("%s", Recipe.ingredients[0].line);
// printf("%s", Recipe.ingredients[1].line);