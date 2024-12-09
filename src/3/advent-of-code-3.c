//
// Created by roteklaue on 12/7/24.
//

#include <stdlib.h>
#include <regex.h>
#include <stdio.h>

#include "../util/string.h"
#include "../util/file.h"


int advent_of_code_3_a() {
    int rows, result = 0;
    const char *pattern = "(mul\\s*\\(\\d+,\\d+\\))";


    string **garbage_memory_dump = read_file("../inputs/day-3.txt", &rows);

    if (rows < 1) return 0;

    string *working_data = garbage_memory_dump[0];

    for (int i = 1; i < rows; ++i) {
        string_append_s(working_data, garbage_memory_dump[i]);
        string_free(garbage_memory_dump[i]);
    }

    free(garbage_memory_dump);

    for (char *p = working_data->chars; *p; ++p) {
        if (*p == '\n' || *p == '\r') {
            *p = ' ';
        }
    }

    regex_t regex;
    regmatch_t match[1];

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        return 0;
    }

    const char *cursor = working_data->chars;

    while (!regexec(&regex, cursor, 1, match, 0)) {
        const int start = match[0].rm_so;
        const int end = match[0].rm_eo;
        printf("Match found: %.*s\n", end - start, cursor + start);

        cursor += end;
    }

    regfree(&regex);

    return result;
}

int advent_of_code_3_b() {
    return 0;
}