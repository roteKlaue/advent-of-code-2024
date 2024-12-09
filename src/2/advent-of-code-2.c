//
// Created by roteklaue on 12/5/24.
//

#include "advent-of-code-2.h"
#include "../util/file.h"
#include "../util/string.h"

#include <stdlib.h>

bool isArraySafe(const int *data, const int size) {
    if (data == nullptr || size < 2) return false;

    const bool direction = data[0] - data[1] > 0;

    for (int i = 0; i < size - 1; i++) {
        if (data[i] == data[i + 1]) {
            return false;
        }

        const int diff = data[i] - data[i + 1];
        const int absDiff = abs(diff);

        if (absDiff > 3) {
            return false;
        }

        const bool current_direction = (diff > 0);

        if (current_direction != direction) {
            return false;
        }
    }

    return true;
}

bool isSafe(const string *line) {
    if (line == nullptr || line->length == 0) return false;

    int size = 0;
    string **parts = string_split(line, ' ', &size);

    if (parts == nullptr || size == 0) {
        if (parts) free(parts);
        return false;
    }

    int *data = malloc(sizeof(int) * size);
    if (data == nullptr) {
        string_free_array(parts, size);
        return false;
    }

    for (int i = 0; i < size; i++) {
        data[i] = atoi(parts[i]->chars);
    }

    string_free_array(parts, size);

    if (size == 1) {
        free(data);
        return false;
    }

    const bool safe = isArraySafe(data, size);

    free(data);
    return safe;
}

bool isSafeV2(const string *line) {
    if (line == nullptr || line->length == 0) return false;

    int size = 0;
    string **parts = string_split(line, ' ', &size);

    if (parts == nullptr || size == 0) {
        if (parts) free(parts);
        return false;
    }

    int *data = malloc(sizeof(int) * size);
    if (data == nullptr) {
        string_free_array(parts, size);
        return false;
    }

    for (int i = 0; i < size; i++) {
        data[i] = atoi(parts[i]->chars);
    }

    string_free_array(parts, size);

    if (size == 1) {
        free(data);
        return false;
    }

    const int newSize = size - 1;
    for (int removeIndex = 0; removeIndex < size; removeIndex++) {
        if (newSize < 2) {
            continue;
        }

        int *temp = malloc(sizeof(int) * newSize);
        if (temp == nullptr) {
            continue;
        }

        for (int i = 0, j = 0; i < size; i++) {
            if (i == removeIndex) continue;
            temp[j++] = data[i];
        }

        const bool result = isArraySafe(temp, newSize);
        free(temp);

        if (result) {
            free(data);
            return true;
        }
    }

    free(data);
    return false;
}

int advent_of_code_2_a() {
    int rows, count = 0;
    string **values = read_file("../inputs/day-2.txt", &rows);

    for (int i = 0; i < rows; i++) {
        if (isSafe(values[i])) count++;
    }

    string_free_array(values, rows);
    return count;
}

int advent_of_code_2_b() {
    int rows, count = 0;
    string **values = read_file("../inputs/day-2.txt", &rows);

    for (int i = 0; i < rows; i++) {
        if (isSafeV2(values[i])) count++;
    }

    string_free_array(values, rows);
    return count;
}