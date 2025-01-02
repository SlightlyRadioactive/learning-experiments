#include <stdio.h>
#include <stdlib.h>

typedef struct Array2D {char **array; int rows, cols;} Array2D;

void Error(const char *message){
    printf("Error: %s\n", message);
    exit(1);
}

Array2D Create2DArray(int rows, int cols) {
    Array2D arr = {
        .array = (char **)malloc(rows * sizeof(char *)),
        .rows = rows,
        .cols = cols
    };

    for (int i = 0; i < rows; i++) {
        arr.array[i] = (char *)malloc(cols * sizeof(char));
    }

    return arr;
}

void LoadMap(const char *fileName, Array2D *map) {
    char ch;

    FILE *file_ptr = fopen(fileName, "r");

    if (file_ptr == NULL) {
        Error("Unable to open file\n");
    }

    // First pass to get the dimensions
    int currentCols = 0;
    while ((ch = fgetc(file_ptr)) != EOF) {
        if (ch == ',') {
            continue;
        } else if (ch == '\n') {
            map->rows++;
            if (currentCols > map->cols) {
                map->cols = currentCols;
            }
            currentCols = 0;
        } else {
            currentCols++;
        }
    }

    // Allocate memory for the map
    *map = Create2DArray(map->rows, map->cols);

    if (map == NULL || map->array == NULL) {
        fclose(file_ptr);
        Error("Memory allocation failed for the map\n");
    }

    map->rows = map->cols = 0;
    rewind(file_ptr);

    // Second pass to fill the map
    while ((ch = fgetc(file_ptr)) != EOF) {
        if (ch == ','){
            continue;
        } else if (ch == '\n') {
            map->rows++;
            map->cols = 0;
        } else {
            map->array[map->rows][map->cols] = ch;
            map->cols++;
        }
    }

    fclose(file_ptr);
}

// Function to free the memory of a 2D array
void Free2DArray(Array2D *arr) {
    for (int i = 0; i < arr->rows; i++) {
        free(arr->array[i]);
    }
    free(arr->array);
}

int main(){
    Array2D map;
    LoadMap("map.csv", &map);

    printf("\n");
    for (int i = 0; i <= map.rows; i++){
        for (int j = 0; j < map.cols; j++){
            printf("%c", map.array[i][j]);
        }
        printf("\n");
    }

    Free2DArray(&map);

    return 0;
}