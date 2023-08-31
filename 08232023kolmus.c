#include<stdio.h>

#define N 8
#define M 8
#define EMPTY 0
#define WALL 1

typedef struct point_t {
    int x;
    int y;
} point_t;

typedef struct path_t {
    char dir[N*M];
    int len;
} path_t;

char directions[4] = {
    'r',
    'u',
    'l',
    'd'
};

int marked[N][M] = {0};

int input[N][M] = {
    {0, 0, 0, 1, 0, 0, 0, 0},
    {1, 1, 0, 1, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0}
};

void get_paths(int x, int y, point_t end, path_t *currPath, path_t *minPath) {

    if (x == end.x && y == end.y) {

        if (minPath->len > currPath->len) {
            *minPath = *currPath;
        }
        
        return;
    }

    marked[y][x] = 1;
    currPath->len += 1;

    if (x < N-1 && input[y][x+1] == EMPTY && !marked[y][x+1]) {

        currPath->dir[currPath->len-1] = directions[0];
        get_paths(x+1, y, end, currPath, minPath);
    }

    if (y > 0 && input[y-1][x] == EMPTY && !marked[y-1][x]) {

        currPath->dir[currPath->len-1] = directions[1];
        get_paths(x, y-1, end, currPath, minPath);
    }

    if (x > 0 && input[y][x-1] == EMPTY && !marked[y][x-1]) {

        currPath->dir[currPath->len-1] = directions[2];
        get_paths(x-1, y, end, currPath, minPath);
    }

    if (y < M-1 && input[y+1][x] == EMPTY && !marked[y+1][x]) {

        currPath->dir[currPath->len-1] = directions[3];
        get_paths(x, y+1, end, currPath, minPath);
    }

    currPath->len -= 1;
    marked[y][x] = 0;
    currPath->dir[currPath->len] = 0;
}

path_t find_shortest_path(point_t start, point_t end) {

    path_t shortest;
    shortest.len = N*M+1;
    shortest.dir[0] = 0;

    path_t temp;
    temp.len = 0;
    temp.dir[0] = 0;

    get_paths(start.x, start.y, end, &temp, &shortest);

    shortest.dir[shortest.len] = 0;

    return shortest;
}

int main() {

    point_t start = {0, 0};
    point_t end = {N-1, M-1};

    path_t shortestPath = find_shortest_path(start, end);

    // printf("[DEBUG] len: %d\n", shortestPath.len);
    // printf("[DEBUG] path: %s\n", shortestPath.dir);

    if (shortestPath.len == N*M+1) {
        printf("there is no path between (x:%d, y:%d) and (x:%d, y:%d) !!!\n", start.x, start.y, end.x, end.y);
        return 1;
    }

    printf("{");
    for (int i = 0; i < shortestPath.len; i++) {

        if      (shortestPath.dir[i] == 'u') printf("\"up\"");
        else if (shortestPath.dir[i] == 'd') printf("\"down\"");
        else if (shortestPath.dir[i] == 'l') printf("\"left\"");
        else if (shortestPath.dir[i] == 'r') printf("\"right\"");

        if (i != shortestPath.len - 1) printf(", ");
    }
    printf("}");

    return 0;
}