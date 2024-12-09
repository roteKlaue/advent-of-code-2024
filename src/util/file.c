//
// Created by roteklaue on 12/7/24.
//

#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string **read_file(const char *filename, int *rows) {
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
