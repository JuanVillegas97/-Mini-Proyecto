#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char line[100];
} String;

typedef struct
{
    String description[1];
    String categories[1];
    String profile[1];
    String ingredients[10];
} Recipes;

int main(int argc, char const *argv[])
{
    Recipes Recipe;
    printf("Enter something\n");
    scanf("%s", Recipe.ingredients[0].line);
    scanf("%s", Recipe.ingredients[1].line);
    printf("%s", Recipe.ingredients[0].line);
    printf("%s", Recipe.ingredients[1].line);
}