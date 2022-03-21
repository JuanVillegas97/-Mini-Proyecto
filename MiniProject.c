// Juan Eduardo VIllegas Rios A00826615
// Pablo Vera Terán A01730223

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_RECIPE 3
#define MAX_INGREDIENTS 10

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
    Ingredients ingredients[MAX_INGREDIENTS];
    int ingredientsAmount;
} Recipes;

void readFileInfo(FILE *filePointer, Recipes* RecipeArray)
{
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
            RecipeArray[recipeNum].ingredientsAmount = ingredientsNum;
            lineNum--;
            break;
        default:
            break;
        }
        lineNum++;
    }
}

bool linearSearch(int arr[], int n, int x)
{
    int i;
    for (i = 0; i < n; i++)
        if (arr[i] == x)
            return true;
    return false;
}

void getAllIngredients(char** IngredientArray, Recipes* RecipeArray)
{
    // printf("ánimo\n");

}

void tempPrint(Recipes* RecipeArray)
{
    for (size_t i = 0; i < MAX_RECIPE; i++)
    {
        printf("Recipe:%s", RecipeArray[i].name);
        printf("Description:%s", RecipeArray[i].description);
        printf("Categories:%s", RecipeArray[i].categories);
        printf("Profile:%s", RecipeArray[i].profile);
        printf("Amount of ingredients:%d\n", RecipeArray[i].ingredientsAmount);
        printf("Ingredients:\n");
        for (int j = 0; j < RecipeArray[i].ingredientsAmount; j++)
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
    char* IngredientArray[20];
    
    readFileInfo(filePointer, RecipeArray);
    getAllIngredients(IngredientArray, RecipeArray);
    tempPrint(RecipeArray);


    fclose(filePointer);
}
