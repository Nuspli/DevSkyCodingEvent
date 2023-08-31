#include<stdio.h>
#include<stdlib.h>
#include<time.h>

enum {ELECTRONICS, TOYS, HOUSEHOLDITEM, NONE};
#define NEWSHELFCAPACITY 21000000 // 21t in grams

//! sorry aber ich hab echt kein bock auf floats, die sind so ungenau und hab auch kein bock auf die ganzen type casts ...

typedef struct electronics_t {
    int price; // in cents 200 - 1500 00
    int weight; // in grams 500 - 70 000
    int watts; // watts * 10 -> 3 - 25000 
} electronics_t;

typedef struct toys_t {
    int price; // in cents 1200 - 1510 00
    int weight; // in grams 700 - 70 200
    unsigned int producer : 2; // index -> 0 - 2
} toys_t;

char *producers[] = {
    "Kids",
    "Freds",
    "Marvins"
};

typedef struct householdItem_t {
    int price; // in cents 180 - 1499 80
    int weight; // in grams 900 - 70 400
    unsigned int bio : 1; // yes or no
} householdItem_t;

typedef struct product_t {
    unsigned int type : 2; // 0 - 3
    union {
        electronics_t electronics;
        toys_t toys;
        householdItem_t householdItem;
        int none : 1;
    };
} product_t;

typedef struct shelf_t {
    unsigned int type : 2;
    int capacity;
    int weight;
    int numProducts;
    int maxNumProducts;
    product_t *products;
    int price;
    int numE;
    int numT;
    int numH;
} shelf_t;

void init_shelves(shelf_t *shelves) {

    for (int i = 0; i < 3; i++) {

        shelves[i].products = malloc(sizeof(product_t) * shelves[i].numProducts);

        if (shelves[i].products == NULL) {
            printf("failed to allocate %d bytes for shelves!\n", sizeof(product_t) * shelves[i].numProducts);
            exit(1);
        }

        for (int j = 0; j < shelves[i].numProducts; j++) {
            shelves[i].products[j].type = i;
            if (i == ELECTRONICS) {
                shelves[i].products[j].electronics.price =      rand() % 149801 + 200;
                shelves[i].products[j].electronics.weight =     rand() % 69501  + 500;
                shelves[i].products[j].electronics.watts =      rand() % 24998  + 3;
            } else if (i == TOYS) {
                shelves[i].products[j].toys.price =             rand() % 148811 + 1200;
                shelves[i].products[j].toys.weight =            rand() % 69501  + 700;
                shelves[i].products[j].toys.producer =          rand() % 3;
            } else if (i == HOUSEHOLDITEM) {
                shelves[i].products[j].householdItem.price =    rand() % 149801 + 180;
                shelves[i].products[j].householdItem.weight =   rand() % 69501  + 900;
                shelves[i].products[j].householdItem.bio =      rand() % 2;
            }

        }

        // printf("[DEBUG] shelf %d has %d products\n", i, shelves[i].numProducts);
        // printf("[DEBUG] \tsample product: ");
        // printf("price: %d, weight: %d, ", shelves[i].products[42].electronics.price, shelves[i].products[42].electronics.weight);
        // if (i == ELECTRONICS) {
        //     printf("watts: %d\n", shelves[i].products[42].electronics.watts);
        // } else if (i == TOYS) {
        //     printf("producer: %s\n", producers[shelves[i].products[42].toys.producer]);
        // } else if (i == HOUSEHOLDITEM) {
        //     printf("bio: %s\n", shelves[i].products[42].householdItem.bio ? "yes" : "no");
        // }

    }
}

void free_shelves(shelf_t *shelves, shelf_t *newShelves, int numNewShelves) {

    for (int i = 0; i < 3; i++) {
        free(shelves[i].products);
    }

    for (int i = 0; i < numNewShelves; i++) {
        free(newShelves[i].products);
    }

    free(newShelves);
    // printf("[DEBUG] freed shelves\n");
}

int index_of_nth_element(product_t *p, int np, int n) {
    
    int e = 0;

    for (int i = 0; e < np; i++) {
        if (p[i].type != NONE) {
            if (e == n) {
                return i;
            }
            e++;
        }
    }

    return e;
    
}

int rearrange_shelves(shelf_t *shelves, shelf_t *newShelves) {

    int remaining = 3000;

    int n = 0;

    for (; n < 7 && remaining != 0; n++) {

        newShelves[n].type = NONE;
        newShelves[n].numProducts = 0;
        newShelves[n].maxNumProducts = 100;
        newShelves[n].capacity = NEWSHELFCAPACITY;
        newShelves[n].weight = 0;
        newShelves[n].products = malloc(sizeof(product_t) * newShelves[n].maxNumProducts);
        newShelves[n].price = 0;
        newShelves[n].numE = 0;
        newShelves[n].numT = 0;
        newShelves[n].numH = 0;

        while (1) {

            int shelfType = rand() % 3;
            if (shelves[shelfType].numProducts == 0) {
                continue;
            }

            int index = index_of_nth_element(shelves[shelfType].products, shelves[shelfType].numProducts, rand() % shelves[shelfType].numProducts);
            product_t product = shelves[shelfType].products[index];

            shelves[shelfType].products[index].type = NONE;
            shelves[shelfType].products[index].none = 1;
            shelves[shelfType].numProducts--;

            newShelves[n].products[newShelves[n].numProducts++] = product;

            if (product.type == ELECTRONICS) {
                newShelves[n].weight += product.electronics.weight;
                newShelves[n].numE++;
                newShelves[n].price += product.electronics.price;
            } else if (product.type == TOYS) {
                newShelves[n].weight += product.toys.weight;
                newShelves[n].numT++;
                newShelves[n].price += product.toys.price;
            } else if (product.type == HOUSEHOLDITEM) {
                newShelves[n].weight += product.householdItem.weight;
                newShelves[n].numH++;
                newShelves[n].price += product.householdItem.price;
            }

            if (newShelves[n].weight > newShelves[n].capacity) {

                newShelves[n].numProducts--;
                shelves[shelfType].products[index] = product;
                shelves[shelfType].numProducts++;

                if (product.type == ELECTRONICS) {
                    newShelves[n].weight -= product.electronics.weight;
                    newShelves[n].numE--;
                    newShelves[n].price -= product.electronics.price;
                } else if (product.type == TOYS) {
                    newShelves[n].weight -= product.toys.weight;
                    newShelves[n].numT--;
                    newShelves[n].price -= product.toys.price;
                } else if (product.type == HOUSEHOLDITEM) {
                    newShelves[n].weight -= product.householdItem.weight;
                    newShelves[n].numH--;
                    newShelves[n].price -= product.householdItem.price;
                }
                printf("shelf %d |   full   | electronics: %d | toys: %d | household items: %d | total price: %d\n", n+1, newShelves[n].numE, newShelves[n].numT, newShelves[n].numH, newShelves[n].price);
                break;
            }

            remaining--;
            if (remaining == 0) {
                printf("shelf %d | not full | electronics: %d | toys: %d | household items: %d | total price: %d\n", n+1, newShelves[n].numE, newShelves[n].numT, newShelves[n].numH, newShelves[n].price);
                printf("all products have been rearranged!\n");
                break;
            }
            if (newShelves[n].numProducts >= newShelves[n].maxNumProducts) {
                newShelves[n].maxNumProducts += 100;
                newShelves[n].products = realloc(newShelves[n].products, sizeof(product_t) * newShelves[n].maxNumProducts);
                // printf("[DEBUG] reallocated %d bytes for newShelves[%d].products | max: %d\n", sizeof(product_t) * newShelves[n].maxNumProducts, n, newShelves[n].maxNumProducts);
                if (newShelves[n].products == NULL) {
                    printf("failed to reallocate %d bytes for newShelves[%d].products!\n", sizeof(product_t) * newShelves[n].maxNumProducts, n);
                    exit(1);
                }
            }

        }
    }

    if (remaining) {
        printf("not all products could be rearranged! there are %d remaining products!\n", remaining);
    }

    return n;
}

int main() {

    srand(time(NULL));

    shelf_t shelves[3] = {
        {ELECTRONICS, 0, 0, 1000, 0, NULL, 0, 0, 0, 0},
        {TOYS, 0, 0, 1000, 0, NULL, 0, 0, 0, 0},
        {HOUSEHOLDITEM, 0, 0, 1000, 0, NULL, 0, 0, 0, 0}
    };

    init_shelves(shelves);

    shelf_t *newShelves;
    newShelves = malloc(sizeof(shelf_t) * 7);

    int numNewShelves = rearrange_shelves(shelves, newShelves);

    free_shelves(shelves, newShelves, numNewShelves);

    return 0;
}