#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Block {int x, y;} Block;

typedef struct Entity {Block box, spr;} Entity;
typedef struct EntityArr {Entity *instance; int size;} EntityArr;

typedef struct Item {Block position; bool active;} Item;
typedef struct ItemArr {Item *instance; int size;} ItemArr;

int arr[3][3] = {
    {1,0,1},
    {0,1,0},
    {0,0,1}
};

void* AppendElement(void* array, int byte_size, int size, void* new_element){
    void* new_array = realloc(array, (size + 1) * byte_size);
    if (new_array == NULL) {
        printf("Error: Unable to allocate memory\n");
        exit(1);
    }
    memcpy((char*)new_array + (size * byte_size), new_element, byte_size);
    return new_array;
}

int main() {
    EntityArr crates = {NULL, 0};
    ItemArr spaces = {NULL, 0};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            switch (arr[i][j]) {
                case 0: {
                    Item new_item = {{j, i}, 0};
                    spaces.instance = (Item*)AppendElement(spaces.instance, sizeof(Item), spaces.size, &new_item);
                    spaces.size++;
                    break;
                }
                case 1: {
                    Entity new_entity = {{j, i}, {j, i}};
                    crates.instance = (Entity*)AppendElement(crates.instance, sizeof(Entity), crates.size, &new_entity);
                    crates.size++;
                    break;
                }
            }
        }
    }

    printf("Spaces: \n");
    for (int i = 0; i < spaces.size; i++) {
        printf("[%d](%d, %d)", i, spaces.instance[i].position.x, spaces.instance[i].position.y);
        if (i != spaces.size - 1) {
            printf(", ");
        }
    }
    printf("\n\n");

    printf("Crates: \n");
    for (int i = 0; i < crates.size; i++) {
        printf("[%d](%d, %d)", i, crates.instance[i].box.x, crates.instance[i].box.y);
        if (i != crates.size - 1) {
            printf(", ");
        }
    }
    printf("\n\n");

    free(crates.instance);
    free(spaces.instance);
    return 0;
}