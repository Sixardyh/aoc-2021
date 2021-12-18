// run with < input.txt in STDIN
// edit WITH_AIM accordingly

#include <stdio.h>
#include <string.h>

#define FILE_LINES 1000
#define WITH_AIM 1

int part1and2() {
        char direction[8];
        int horizontal = 0;
        int depth = 0;
        int aim = 0;
        int tmp;
        for (int i = 0 ; i < FILE_LINES ; i++) {
                scanf("%s", direction);
                if (!strcmp(direction, "up")) {
                        scanf("%d", &tmp);
                        if (WITH_AIM) aim -= tmp;
                        else depth -= tmp;
                } else if (!strcmp(direction, "down")) {
                        scanf("%d", &tmp);
                        if (WITH_AIM) aim += tmp;
                        else depth += tmp;
                } else {
                        scanf("%d", &tmp);
                        horizontal += tmp;
                        if (WITH_AIM) depth += aim * tmp;
                }
        }

        return horizontal * depth;
}


int main() {
        printf("Product is %d\n", part1and2());

        return 0;
}

