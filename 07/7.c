#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* parse_file(size_t* array_size) {
        FILE *f = fopen("input.txt", "r");
        fseek(f, 0, SEEK_END);
        int string_length = ftell(f);
        rewind(f);
        char* data = malloc((string_length * sizeof(char)) + 1);
        fread(data, sizeof(char), string_length, f);
        data[string_length] = '\0';
        fclose(f);

        // duplicate data so we can split twice:
        // once for count, once for filling array
        char *data_copy = strndup(data, string_length);

        char *split = strtok(data_copy, ",");
        while (split != NULL) {
                (*array_size)++;
                split = strtok(NULL, ",");
        }
        free(data_copy);

        split = strtok(data, ",");
        int* positions = malloc(sizeof(size_t) * *array_size);
        for (size_t i = 0 ; split != NULL ; i++) {
                int position = strtoul(split, NULL, 10);
                positions[i] = position;
                split = strtok(NULL, ",");
        }

        free(data);
        return positions;
}

int uicmp(const void* a, const void* b) {
        return *(int*)a - *(int*)b;
}

int part1(int* positions, size_t array_size) {
        // optimal solution is median
        int median = positions[(array_size + 1) / 2];
        printf("median: %d\n", median);

        int fuel = 0;
        for (size_t i = 0 ; i < array_size ; i++)
                fuel += abs(positions[i] - median);

        printf("fuel: %d\n", fuel);
        return median;
}

void part2(int* positions, size_t array_size, int median) {
        // optimal solution is more or less mean
        int mean = 0;
        for (size_t i = 0 ; i < array_size ; i++) mean += positions[i];
        mean /= array_size;
        printf("mean: %d\n", mean);

        int fuel = 0;
        for (size_t i = 0 ; i < array_size ; i++) {
                int distance = abs(positions[i] - mean);
                fuel += distance * 0.5 * (1 + distance);
        }

        printf("fuel2: %d\n", fuel);
}

int main() {
        size_t array_size = 0;
        int* positions = parse_file(&array_size);
        qsort(positions, array_size, sizeof(int), uicmp);

        part2(positions, array_size, part1(positions, array_size));

        free(positions);
        return 0;
}

