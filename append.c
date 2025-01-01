#include <stdio.h>
#include <stdlib.h>

typedef struct Block {int x, y;} Block;
typedef struct Entity {Block box, spr;} Entity;
typedef struct EntityArr {Entity *instance; int size;} EntityArr;

int arr[3][3] = {
    {1,0,1},
    {0,1,0},
    {0,0,1}
};

Entity* append(Entity* array, int size, Entity new_element) {
    Entity* new_array = (Entity*)malloc((size + 1) * sizeof(Entity));

    for (int i = 0; i < size; i++) {
        new_array[i] = array[i];
    }

    new_array[size] = new_element;
    return new_array;
}

int main(){
    EntityArr crates, spaces;
    crates.size = spaces.size = 0;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            switch (arr[i][j]){
                case 0:
                    spaces.instance = append(spaces.instance, spaces.size, (Entity){{j,i}, {j,i}});
                    spaces.size++;
                    break;

                case 1:
                    crates.instance = append(crates.instance, crates.size, (Entity){{j,i}, {j,i}});
                    crates.size++;
                    break;
            }
        }
    }

    printf("Spaces: \n");
    for (int i = 0; i < spaces.size; i++) {
        printf("[%d](%d, %d)", i, spaces.instance[i].box.x, spaces.instance[i].box.y);
        if (i != spaces.size-1){
            printf(", ");
        }
    }
    printf("\n\n");

    printf("Crates: \n");
    for (int i = 0; i < crates.size; i++) {
        printf("[%d](%d, %d)", i, crates.instance[i].box.x, crates.instance[i].box.y);
        if (i != crates.size-1){
            printf(", ");
        }
    }
    printf("\n\n");

    free(crates.instance);
    free(spaces.instance);
    return 0;
}