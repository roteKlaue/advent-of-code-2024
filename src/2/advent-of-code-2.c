//
// Created by roteklaue on 12/5/24.
//

#include "advent-of-code-2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util/string.h"

string **read_content_2(const char *filename, int *rows) {
    if (filename == nullptr || rows == nullptr) return nullptr;

    *rows = 0;
    FILE *fp = fopen(filename, "r");
    if (!fp) return nullptr;

    string **lines = nullptr;
    int capacity = 0;
    constexpr int LINE_BUFFER_SIZE = 1024;
    char buffer[LINE_BUFFER_SIZE];

    while (fgets(buffer, LINE_BUFFER_SIZE, fp)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }

        string *line_str = string_new(buffer, len, 0);
        if (line_str == nullptr) {
            for (int i = 0; i < *rows; i++) {
                string_free(lines[i]);
            }
            free(lines);
            fclose(fp);
            return nullptr;
        }

        if (*rows >= capacity) {
            capacity = capacity == 0 ? 10 : capacity * 2;
            string **new_lines = realloc(lines, capacity * sizeof(string *));
            if (!new_lines) {
                string_free(line_str);
                for (int i = 0; i < *rows; i++) {
                    string_free(lines[i]);
                }
                free(lines);
                fclose(fp);
                return nullptr;
            }
            lines = new_lines;
        }

        lines[*rows] = line_str;
        (*rows)++;
    }

    fclose(fp);

    if (*rows == 0) {
        free(lines);
        return nullptr;
    }

    return lines;
}

bool isArraySafe(const int *data, const int size) {
    if (size < 2) return false;

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
    string **values = read_content_2("../input-2.txt", &rows);

    for (int i = 0; i < rows; i++) {
        if (isSafe(values[i])) count++;
    }

    string_free_array(values, rows);
    return count;
}

int advent_of_code_2_b() {
    int rows, count = 0;
    string **values = read_content_2("../input-2.txt", &rows);

    for (int i = 0; i < rows; i++) {
        if (isSafeV2(values[i])) count++;
    }

    string_free_array(values, rows);
    return count;
}