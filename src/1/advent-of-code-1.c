//
// Created by roteklaue on 12/4/24.
//

#include "advent-of-code-1.h"

#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int *array, const int size) {
    if (array == nullptr || size <= 1) {
        return;
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                const int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int **read_content(const char *filename, int *rows) {
    FILE *file = fopen(filename, "r");

    if (file == nullptr) {
        perror("Error opening file");
        return nullptr;
    }

    int rowCount = 0, col1, col2;
    while (fscanf(file, "%d %d", &col1, &col2) == 2) {
        rowCount++;
    }

    rewind(file);

    int **content = malloc(2 * sizeof(int *));
    content[0] = (int *) malloc(rowCount * sizeof(int));
    content[1] = (int *) malloc(rowCount * sizeof(int));

    if (content == nullptr) {
        fclose(file);
        perror("Memory allocation failed");
        return nullptr;
    }

    int i = 0;
    while (fscanf(file, "%d %d", &col1, &col2) == 2) {
        content[0][i] = col1;
        content[1][i] = col2;
        i++;
    }

    fclose(file);
    *rows = rowCount;
    return content;
}

int advent_of_code_1_a() {
    int rows;

    int **content = read_content("../input.txt", &rows);
    bubble_sort(content[0], rows);
    bubble_sort(content[1], rows);

    int distance = 0;
    for (int i = 0; i < rows; i++) {
        distance += abs(content[0][i] - content[1][i]);
    }

    free(content[0]);
    free(content[1]);
    free(content);

    return distance;
}

int count_occurences(const int content[], const int size, const int searchedFor) {
    int occurences = 0;
    for (int i = 0; i < size; ++i) {
        if (content[i] == searchedFor) {
            occurences++;
        }
    }
    return occurences;
}

int advent_of_code_1_b() {
    int rows;
    int **content = read_content("../input.txt", &rows);

    int similarity = 0;
    for (int i = 0; i < rows; ++i) {
        similarity += content[0][i] * count_occurences(content[1], rows, content[0][i]);
    }

    free(content[0]);
    free(content[1]);
    free(content);

    return similarity;
}
