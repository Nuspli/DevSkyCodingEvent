#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define TRACKLEN 50000 // in decimeters
#define PARTICIPANTS 20
enum {sled, ski};

typedef struct participant_t {

    int number;
    int type : 2;
    int dogs;
    int skilen;
    int speed;
    int distance;
    int finishTime;
    int started : 2;

} participant_t;

participant_t participants[PARTICIPANTS] = {
    [0 ... 19] = {0}
};

const int participant_t_size = sizeof(participant_t);

void part_one() {

    printf("1 generating participants...\n\n");

    for (int i = 0; i < PARTICIPANTS; i++) {

        participants[i].number = i+1; // participant number is 1-indexed
        participants[i].type = rand() % 100 < 35; // 35% chance of being a ski
        participants[i].speed = rand() % PARTICIPANTS + 45; // 45-64 / 10 m/s

        if (participants[i].type == sled) {
            participants[i].dogs = rand() % 3 + 5; // 5-7 dogs
            // printf("[DEBUG] participant %d is a sled, has %d dogs and a speed of %ddm/s\n", i+1, participants[i].dogs, participants[i].speed);
        } else {
            participants[i].skilen = rand() % 41 + 180; // 180-2PARTICIPANTS cm skis
            // printf("[DEBUG] participant %d is a ski, has %dcm skis and a speed of %ddm/s\n", i+1, participants[i].skilen, participants[i].speed);
        }

    }

}

void part_two() {

    printf("2 starting race...\n\n");

    int c = 0; // time counter
    int start = 0; // number of participants who have started
    int done = 0; // number of participants who have finished
    participant_t best = {0}; // best participant

    while (1) {

        if (done >= PARTICIPANTS) {
            printf("[STATUS] all participants have finished the race!\n");
            break;
        }

        if (c % 60 == 0) {
            // print status
            if (c == 0) {
                printf("[STATUS] time: %ds \t| done: %d | remaining: %d | best: 0dm num: - -\n", c, done, PARTICIPANTS-done);
            } else {
                printf("[STATUS] time: %ds \t| done: %d | remaining: %d | best: %ddm num: %d %s\n", c, done, PARTICIPANTS-done, best.distance, best.number, best.type == ski ? "ski" : "sled");
            }
        }

        if (c % 10 == 0) {
            // every 10 seconds, a new participant starts
            if (start < PARTICIPANTS) {
                participants[start].started = 1;
                start++;
            }
        }
        
        if (c == 221) {
            // wind turns
            for (int i = 0; i < PARTICIPANTS; i++) {
                if (participants[i].type == ski) {
                    participants[i].speed -= 6;
                } else {
                    participants[i].speed -= 5;
                }
            }
        }

        for (int i = 0; i < PARTICIPANTS; i++) {
            // update distance
            if (!participants[i].finishTime && participants[i].started) {

                participants[i].distance += participants[i].speed;

                if (participants[i].distance >= TRACKLEN) {
                    participants[i].finishTime = c;
                    // printf("[DEBUG] \tparticipant %d finished at %d\n", i+1, c);
                    done++;
                }

                if (participants[i].distance > best.distance && !(done > 1)) {
                    best = participants[i];
                }
            }
        }

        c++;
    }

}

void swap(int x, int y) {

    participant_t t = participants[x];
    participants[x] = participants[y];
    participants[y] = t;
}

void part_three() {

    printf("\n3 rankings:\n\n");

    // bubble sort them

    int sorted = 0;

    for (int n = 0; !sorted; n++) {

        sorted = 1;

        for (int i = 0; i < PARTICIPANTS - n - 1; i++) {
            // if-else just for illustration, could be a single if
            if (participants[i].finishTime > participants[i+1].finishTime) {
                sorted = 0;
                swap(i, i+1);

            } else if (participants[i].finishTime == participants[i+1].finishTime) {

                if (participants[i].type == sled && participants[i+1].type == ski) {
                    sorted = 0;
                    swap(i, i+1);

                } else if (participants[i].type == sled && participants[i+1].type == sled) {
                        
                    if (participants[i].dogs > participants[i+1].dogs) {
                        sorted = 0;
                        swap(i, i+1);
                    } else if (participants[i].number > participants[i+1].number) {
                        sorted = 0;
                        swap(i, i+1);
                    }

                } else if (participants[i].type == ski && participants[i+1].type == ski) {

                    if (participants[i].skilen > participants[i+1].skilen) {
                        sorted = 0;
                        swap(i, i+1);
                    } else if (participants[i].number > participants[i+1].number) {
                        sorted = 0;
                        swap(i, i+1);
                    }
                }
            }
        }
    }

    for (int i = 0; i < PARTICIPANTS; i++) {
        printf("%d.\tnr.: %d time: %d ", i+1, participants[i].number, participants[i].finishTime);
        if (participants[i].type == ski) {
            printf("ski - skilen: %dcm\n", participants[i].skilen);
        } else {
            printf("sled - dogs: %d\n", participants[i].dogs);
        }
    }

}

int main() {

    srand(time(NULL));

    part_one();
    part_two();
    part_three();

    return 0;
}