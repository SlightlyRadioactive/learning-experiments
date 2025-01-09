#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIGITS 2

typedef struct Map {char ***array; int rows, cols;} Map;

void Error(const char *message){
    printf("Error: %s\n", message);
    exit(1);
}

void AllocMap(Map *arr){
    arr->array = (char ***)malloc(arr->rows * sizeof(char **));
    if (arr->array == NULL) Error("Memory allocation failed for rows");

    for (int i = 0; i < arr->rows; i++){
        arr->array[i] = (char **)malloc(arr->cols * sizeof(char*));
        if (arr->array[i] == NULL) Error("Memory allocation failed for columns");

        for (int j = 0; j < arr->cols; j++){
            arr->array[i][j] = (char *)malloc((DIGITS+1) * sizeof(char));
            if (arr->array[i][j] == NULL) Error("Memory allocation failed for elements");
        }
    }
}

void LoadMap(const char *fileName, Map *map){
    FILE *file = fopen(fileName, "r");
    if (file == NULL) Error("Unable to open file\n");

    char ch;
    while ((ch = fgetc(file)) != EOF){
        if (ch == ','){
            map->cols++;
        } else if (ch == '\n'){
            map->cols = 1;
            map->rows++;
        }
    }

    AllocMap(map);
    
    rewind(file);

    // Second pass to fill the map
    int digit = 0;
    map->cols = map->rows = 0;
    while ((ch = fgetc(file)) != EOF){
        if (ch == ','){
            map->cols++;
            digit = 0;
        } else if (ch == '\n'){
            map->cols = 0;
            map->rows++;
            digit = 0;
        } else {
            map->array[map->rows][map->cols][digit] = ch;
            if (digit == DIGITS-1){
                map->array[map->rows][map->cols][digit+1] = '\0';
            }
            digit++;
        }
    }
    map->rows++;
    map->cols++;

    fclose(file);
}

void FreeMap(Map *arr){
    for (int i = 0; i < arr->rows; i++){
        for (int j = 0; j < arr->cols; j++){
            free(arr->array[i][j]);
        }
        free(arr->array[i]);
    }
    free(arr->array);
}

int main(){
    Map myMap = {NULL, 1, 1};
    LoadMap("map.csv", &myMap);

    printf("A:%zu\n", myMap.rows * sizeof(char**)); //Size of each row
    printf("R:%zu\n", myMap.cols * sizeof(char*));  //Size of each column
    printf("C:%zu\n", (DIGITS+1) * sizeof(char));   //Size of each element

    //Total memory allocation
    printf("T:%zu\n", myMap.rows * sizeof(char**) + myMap.rows * myMap.cols * sizeof(char*) + myMap.rows * myMap.cols * (DIGITS+1) * sizeof(char));

    printf("rows %d\n", myMap.rows);
    printf("cols %d\n", myMap.cols);
    printf("\n");
    
    for (int i = 0; i < myMap.rows; i++){
        for (int j = 0; j < myMap.cols; j++){
            //printf("[%d, %d] - %s\n", i, j, myMap.array[i][j]);
            printf("%s", myMap.array[i][j]);
            if (j != myMap.cols-1) printf(",");
        }
        printf("\n");
    }

    FreeMap(&myMap);
    return 0;
}