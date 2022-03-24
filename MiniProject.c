/**
Juan Eduardo VIllegas Rios  A00826615
Pablo Vera Terán            A01730223
Miguel Tanori Martinez      A01282574
**/
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

bool linearSearch(char** arr, int n, char* x)
{
    //printf("n = %d\n", n);
    int i;
    for (i = 0; i < n; i++)
    {
        //printf("comparing: %s to %s\n", arr[i], x);
        if (strcmp(arr[i], x) == 0)
            return true;
    }
    return false;
}

int linearSearch2(Ingredients* arr, int n, char* x)
{
    //printf("#ings in this rec = %d\n", n);
    int i;
    for (i = 0; i < n; i++)
    {
        //printf("comparing: %s to %s\n", arr[i].line, x);
        if (strcmp(arr[i].line, x) == 0)
        {
            //printf("i: %d\n", i);
            return i;
        }
    }
    return -1;
}

int getAllIngredients(char** IngredientArray, Recipes* RecipeArray)
{
    // IngredientArray = (char**)malloc(sizeof(char) * MAX_INGREDIENTS*MAX_RECIPE );
    // printf("ing array at: %p\n", IngredientArray);
    // IngredientArray[0] = (char*)malloc(sizeof(char)*100);
    int tempIndex = 0;
    for (size_t i = 0; i < MAX_RECIPE; i++)
    {
        for (size_t j = 0; j < RecipeArray[i].ingredientsAmount; j++)
        {
            char* tempIngredient = RecipeArray[i].ingredients[j].line;
            //printf("tempIng: %s\n", tempIngredient);
            if ( !linearSearch(IngredientArray, tempIndex, tempIngredient) )
            {
                IngredientArray[tempIndex] = (char*)malloc(sizeof(char)*100);
                strcpy(IngredientArray[tempIndex], tempIngredient);
                //IngredientArray[tempIndex] = tempIngredient;
                //printf("added %s to IngredientArray at index %d\n", tempIngredient, tempIndex);
                tempIndex++;
            }else{
                //printf("duplicated ingredient, not added\n");
            }
        }        
    }

    int totalAmountIngredients = tempIndex;

    // for (size_t i = 0; i < totalAmountIngredients; i++)
    // {
    //     printf("%s\n", IngredientArray[i]);
    // }
    // printf("\n");

    return totalAmountIngredients;
    
}

void printFormulaMatrix(Recipes* RecipeArray, char** IngredientArray, int n)
{
    printf("\t\t");
    for (size_t i = 0; i < MAX_RECIPE; i++)
    {
        printf("%s\t", RecipeArray[i].name);
    }
    printf("\n");
    
    for (size_t rowIndex = 0; rowIndex < n; rowIndex++)
    {
        //printf("\nhere");
        for (int colIndex = -1; colIndex < MAX_RECIPE; colIndex++)
        {
            //printf("row: %d, col: %d\n", rowIndex, colIndex);
            if (colIndex == -1)
            {
                //printf("ing array at: %p\n", IngredientArray);
                printf("%s     \t", IngredientArray[rowIndex]);
            }else
            {
                //printf("recc array: %p\n", RecipeArray);
                int ingredientFound = linearSearch2( RecipeArray[colIndex].ingredients, RecipeArray[colIndex].ingredientsAmount, IngredientArray[rowIndex] );
                if( ingredientFound != -1 )
                {
                    int amount = RecipeArray[colIndex].ingredients[ingredientFound].quantity;
                    printf("%d\t\t", amount);
                }else
                {
                    printf("0\t\t");
                }             
            }
            //printf("column ends\n");
        }    
        //printf("row ends\n");
        printf("\n");
    }
}

void asInputPrint(Recipes* RecipeArray)
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
    Recipes RecipeArray[MAX_RECIPE];
    char** IngredientArray = NULL;
    // printf("ing array: %p\n", IngredientArray);
    // printf("rec array: %p\n", RecipeArray);
    IngredientArray = (char**)malloc(sizeof(char) * MAX_INGREDIENTS*MAX_RECIPE );
    // printf("ing array: %p\n", IngredientArray);

    readFileInfo(filePointer, RecipeArray);
    int totalAmountIngredients = getAllIngredients(IngredientArray, RecipeArray);
    // printf("ing array at: %p\n", IngredientArray);
    printFormulaMatrix(RecipeArray, IngredientArray, totalAmountIngredients);
    

    //asInputPrint(RecipeArray);


    fclose(filePointer);
}