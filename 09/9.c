// run with < input.txt in STDIN
// comment the irrelevant part

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 100
#define FILE_LINES 100

typedef int Matrix[LINE_LENGTH][FILE_LINES];

void check_new_max(int* top3, int value) {
        if (value <= top3[0]) return;
        if (value < top3[1]) {
                top3[0] = value;
                return;
        }

        top3[0] = top3[1];
        if (value < top3[2]) {
                top3[1] = value;
        } else {
                top3[1] = top3[2];
                top3[2] = value;
        }
}

void parse_matrix(Matrix matrix) {
        char current_line[LINE_LENGTH];
        for (int line = 0 ; line < FILE_LINES ; line++) {
                scanf("%s", current_line);
                for (int col = 0 ; col < LINE_LENGTH ; col++)
                        matrix[line][col] = current_line[col] - 48;
        }
}

void bassin(Matrix matrix, size_t line, size_t col, int* top3, int* size, int* sum) {
        // line & col unsigned so larger than FILE_LINES and LINE_LENGTH if negative
        (*size)++;
        int current = matrix[line][col];

        if ((*size) == 1) {     // make sure initial point is local lowest point
                if (line - 1 < FILE_LINES && matrix[line-1][col] < current) return;
                if (line + 1 < FILE_LINES && matrix[line+1][col] < current) return;
                if (col - 1 < LINE_LENGTH && matrix[line][col-1] < current) return;
                if (col + 1 < LINE_LENGTH && matrix[line][col+1] < current) return;
                (*sum) += current + 1;
        }

        matrix[line][col] = 9; // don't pass twice over same cell
        if (line - 1 < FILE_LINES && matrix[line-1][col] > current && matrix[line-1][col] != 9)
                bassin(matrix, line - 1, col, top3, size, NULL);
        if (line + 1 < FILE_LINES && matrix[line+1][col] > current && matrix[line+1][col] != 9)
                bassin(matrix, line + 1, col, top3, size, NULL);
        if (col - 1 < LINE_LENGTH && matrix[line][col-1] > current && matrix[line][col-1] != 9)
                bassin(matrix, line, col - 1, top3, size, NULL);
        if (col + 1 < LINE_LENGTH && matrix[line][col+1] > current && matrix[line][col+1] != 9)
                bassin(matrix, line, col + 1, top3, size, NULL);
}

int main() {
        Matrix matrix;
        parse_matrix(matrix);
        int top3[3] = {0, 0, 0};
        int sum = 0;

        for (size_t line = 0 ; line < FILE_LINES ; line++) {
                for (size_t col = 0 ; col < LINE_LENGTH ; col++) {
                        int size = 0;
                        if (matrix[line][col] != 9) {
                                bassin(matrix, line, col, top3, &size, &sum);
                                if (size > 1) check_new_max(top3, size);
                        }
                }
        }

        printf("The sum is: %d\n", sum);
        printf("Largest bassin is: %d\n", top3[2]);
        printf("Second largest bassin is: %d\n", top3[1]);
        printf("Third largest bassin is: %d\n", top3[0]);

        printf("The product is: %d\n", top3[0] * top3[1] * top3[2]);
        return 0;
}

