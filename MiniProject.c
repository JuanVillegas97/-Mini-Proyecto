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

void readFileInfo(FILE *filePointer, Recipes* RecipeArray)
{
    //Recipes* RecipeArray = &RecipePtr;
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
            strcpy(RecipeArray[recipeNum].name, (strchr(buffer, ':') + 1));
            break;
        case 1:
            strcpy(RecipeArray[recipeNum].description, (strchr(buffer, ':') + 1));
            break;
        case 2:
            strcpy(RecipeArray[recipeNum].categories, (strchr(buffer, ':') + 1));
            break;
        case 3:
            strcpy(RecipeArray[recipeNum].profile, (strchr(buffer, ':') + 1));
            break;
        case 4:
            break;
        case 5:
            RecipeArray[recipeNum].ingredients[ingredientsNum].quantity = atoi((strchr(buffer, ':') + 1));
            strcpy(RecipeArray[recipeNum].ingredients[ingredientsNum].line, strtok(buffer, ":"));
            ingredientsNum++;
            lineNum--;
            break;
        default:
            break;
        }
        lineNum++;
    }
}

void tempPrint(Recipes* RecipeArray)
{
    for (size_t i = 0; i <= 2; i++)
    {
        printf("Recipe:%s", RecipeArray[i].name);
        printf("Description:%s", RecipeArray[i].description);
        printf("Categories:%s", RecipeArray[i].categories);
        printf("Profile:%s", RecipeArray[i].profile);
        printf("Ingredients:\n");
        for (int j = 0; j <= 6; j++)
        {
            printf("%s:%d\n", RecipeArray[i].ingredients[j].line, RecipeArray[i].ingredients[j].quantity);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    FILE *filePointer;
    Recipes RecipeArray[3];
    
    readFileInfo(filePointer, RecipeArray);
    tempPrint(RecipeArray);


    fclose(filePointer);
}
