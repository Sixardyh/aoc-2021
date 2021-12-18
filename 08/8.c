// run with < input.txt in STDIN
// comment out the irrelevant part in main

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_LINES 200

int part1() {
        char string[8] = "";
        int counter = 0;

        for (int i = 0 ; i < FILE_LINES ; i++) {
                while (string[0] != '|') scanf("%s", string);
                for (int j = 4 ; j > 0 ; j--) {
                        scanf("%s", string);
                        size_t len = strlen(string);
                        if (len == 2 || len == 3 || len == 4 || len == 7) counter++;
                }
        }

        return counter;
}

int qs_strcmp(const void* a, const void* b) {
        size_t len_a = strlen((const char *)a);
        size_t len_b = strlen((const char *)b);
        return (len_a > len_b) - (len_a < len_b);
}

// returns index: str1 "minus" str2
int strmin(char* str1, char* str2, int skip) {
        for (int i = 0 ; i < strlen(str1) ; i++) {
                if (!memchr(str2, str1[i], strlen(str2)) && i != skip) {
                        return i;
                }
        }
        return -1;
}

int segment_to_digit(char* input, char* key) {
        const char zero[7] = {1, 1, 1, 0, 1, 1, 1};
        const char one[7] = {0, 0, 1, 0, 0, 1, 0};
        const char two[7] = {1, 0, 1, 1, 1, 0, 1};
        const char three[7] = {1, 0, 1, 1, 0, 1, 1};
        const char four[7] = {0, 1, 1, 1, 0, 1, 0};
        const char five[7] = {1, 1, 0, 1, 0, 1, 1};
        const char six[7] = {1, 1, 0, 1, 1, 1, 1};
        const char seven[7] = {1, 0, 1, 0, 0, 1, 0};
        const char eight[7] = {1, 1, 1, 1, 1, 1, 1};
        const char nine[7] = {1, 1, 1, 1, 0, 1, 1};

        char initial[7] = {0, 0, 0, 0, 0, 0, 0};
        for (int i = 0 ; i < strlen(input) ; i++) {
                for (int j = 0 ; j < 7 ; j++) {
                        if (input[i] == key[j]) {
                                initial[j] = 1;
                        }
                }
        }

        if (!memcmp(initial, zero, 7)) return 0;
        if (!memcmp(initial, one, 7)) return 1;
        if (!memcmp(initial, two, 7)) return 2;
        if (!memcmp(initial, three, 7)) return 3;
        if (!memcmp(initial, four, 7)) return 4;
        if (!memcmp(initial, five, 7)) return 5;
        if (!memcmp(initial, six, 7)) return 6;
        if (!memcmp(initial, seven, 7)) return 7;
        if (!memcmp(initial, eight, 7)) return 8;
        if (!memcmp(initial, nine, 7)) return 9;
        return -1;
}



int part2() {
        int sum = 0;
        int i, j, k;
        char string[8] = "";
        char signals[10][8];
        char segments[7];

        for (i = 0 ; i < FILE_LINES ; i++) {
                for (j = 0 ; j < 10 ; j++) {
                        scanf("%s", signals[j]);
                }

                qsort(signals, 10, 8, qs_strcmp);

                // set segments for one, can be mismatched at this stage
                segments[2] = signals[0][0];
                segments[5] = signals[0][1];

                // the top segment is seven "minus" one, can't be mismatched
                segments[0] = signals[1][strmin(signals[1], signals[0], -1)];

                // get the segments for four, can also be mismatched
                int first_index = strmin(signals[2], signals[0], -1);
                segments[1] = signals[2][first_index];
                segments[3] = signals[2][strmin(signals[2],
                                                 signals[0], first_index)];

                // 3 is the only 5-length with both 1 segments.
                // 5 is the only 5-length with both 4 segments.
                int three_index, five_index;
                for (j = 3 ; j < 6 ; j++) {
                        // do one minus current number, gets the three.
                        if (strmin(signals[0], signals[j], -1) == -1)
                                three_index = j;
                        else {
                                int diffindex = strmin(signals[2], signals[j], -1);
                                if (strmin(signals[2], signals[j], diffindex) == -1)
                                        five_index = j;
                        }
                }

                // seven plus four minus three is the bottom segment
                char* seven_plus_four = strndup(signals[2], 8);
                seven_plus_four[4] = segments[0];
                seven_plus_four[6] = seven_plus_four[5] = '\0';
                segments[6] = signals[three_index][strmin(signals[three_index],
                                                          seven_plus_four, -1)];

                // last segment is eight - nearly eight
                seven_plus_four[5] = segments[6]; // it's nearly eight now
                segments[4] = signals[9][strmin(signals[9], seven_plus_four, -1)];

                // still need to check if one and four aren't mismatched
                // The 5 doesn't contain the top 1 segment.
                int index_top_one = strmin(signals[0], signals[five_index], -1);
                char top_one_segment = signals[0][index_top_one];
                if (top_one_segment != segments[2]) {
                        segments[5] = segments[2];
                        segments[2] = top_one_segment;
                }

                // five minus three gives the top 4 segment
                int index_top_four = strmin(signals[five_index],
                                            signals[three_index], -1);
                char top_four_segment = signals[five_index][index_top_four];
                if (top_four_segment != segments[1]) {
                        segments[3] = segments[1];
                        segments[1] = top_four_segment;
                }

                scanf("%s", string);

                for (j = 1000 ; j >= 1 ; j /= 10) {
                        scanf("%s", string);
                        sum += j * segment_to_digit(string, segments);
                }
        }


        return sum;
}


int main() {
//        printf("1, 4, 7 or 8 appear %d times in output.\n", part1());
        printf("The sum of all output values is: %d\n", part2());

        return 0;
}

