//
// Created by roteklaue on 12/5/24.
//

#include "string.h"

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RETURN_IF_NULL(ptr, retval) \
    do { if ((ptr) == nullptr) return (retval); } while (0)

string *string_new(const char *chars, const size_t length, size_t buffer_size) {
    if (buffer_size == 0 || buffer_size <= length) buffer_size = length + 1;

    string *s = malloc(sizeof(string));
    RETURN_IF_NULL(s, nullptr);

    s->chars = malloc(buffer_size);

    if (s->chars == nullptr) {
        free(s);
        return nullptr;
    }

    if (chars && length > 0) {
        memcpy(s->chars, chars, length);
    }

    s->chars[length] = '\0';
    s->length = length;
    s->buffer_size = buffer_size;

    return s;
}

void string_free(string *s) {
    if (!s) return;
    free(s->chars);
    free(s);
}

bool string_append(string *dest, const char *chars, const size_t length) {
    RETURN_IF_NULL(dest, false);
    RETURN_IF_NULL(chars, false);

    if (dest->length + length + 1 > dest->buffer_size) {
        const size_t new_size = dest->buffer_size * 2 > dest->length + length + 1
                          ? dest->buffer_size * 2
                          : dest->length + length + 1;
        if (!string_resize(dest, new_size)) {
            return false;
        }
    }

    memcpy(dest->chars + dest->length, chars, length);
    dest->length += length;
    dest->chars[dest->length] = '\0';

    return true;
}

bool string_append_s(string *dest, const string *src) {
    RETURN_IF_NULL(dest, false);
    RETURN_IF_NULL(src, false);

    if (dest->length + src->length + 1 > dest->buffer_size) {
        const size_t new_size = dest->buffer_size * 2 > dest->length + src->length + 1
            ? dest->buffer_size * 2
            : dest->length + src->length + 1;

        if (!string_resize(dest, new_size)) {
            return false;
        }
    }

    memcpy(dest->chars + dest->length, src->chars, src->length);
    dest->length += src->length;
    dest->chars[dest->length] = '\0';

    return true;
}

bool string_resize(string *s, const size_t new_buffer_size) {
    RETURN_IF_NULL(s, -1);

    if (new_buffer_size <= s->length) return false;

    char *new_chars = realloc(s->chars, new_buffer_size);
    if (!new_chars) return false;

    s->chars = new_chars;
    s->buffer_size = new_buffer_size;

    return true;
}

bool string_compare(const string *s1, const string *s2) {
    RETURN_IF_NULL(s1, false);
    RETURN_IF_NULL(s2, false);

    if (s1->length != s2->length) return false;
    return memcmp(s1->chars, s2->chars, s1->length) == 0;
}

char string_char_at(const string *s, const size_t index, bool *success) {
    RETURN_IF_NULL(s, '\0');

    if (index >= s->length) {
        if (success) *success = false;
        return '\0';
    }

    if (success) *success = true;

    return s->chars[index];
}

string **string_split(const string *s, const char delimiter, int *size) {
    RETURN_IF_NULL(s, nullptr);
    RETURN_IF_NULL(size, nullptr);

    int count = 0;
    for (size_t i = 0; i < s->length; ++i) {
        if (s->chars[i] == delimiter) {
            count++;
        }
    }
    *size = count + 1;

    string **result = malloc(*size * sizeof(string *));
    if (!result) return nullptr;

    size_t start = 0;
    int index = 0;

    for (size_t i = 0; i <= s->length; ++i) {
        if (i == s->length || s->chars[i] == delimiter) {
            const size_t length = i - start;
            result[index++] = string_new(s->chars + start, length, length + 1);
            start = i + 1;
        }
    }

    return result;
}

string *substring(const string *s, const size_t start, const size_t end) {
    RETURN_IF_NULL(s, nullptr);

    if (start >= end || end > s->length || start >= s->length) return nullptr;

    const size_t new_buffer_size = end - start;
    char *temp_bfr = malloc(new_buffer_size + 1);

    RETURN_IF_NULL(temp_bfr, nullptr);

    memcpy(temp_bfr, s->chars + start, new_buffer_size);
    temp_bfr[new_buffer_size] = '\0';

    string *result = string_new(temp_bfr, new_buffer_size, new_buffer_size);
    free(temp_bfr);
    return result;
}


size_t string_find(const string *s, const char ch) {
    RETURN_IF_NULL(s, SIZE_MAX);

    for (size_t i = 0; i < s->length; ++i) {
        if (s->chars[i] == ch) {
            return i;
        }
    }
    return SIZE_MAX;
}

size_t string_find_s(const string *s, const string *find) {
    RETURN_IF_NULL(s, SIZE_MAX);
    RETURN_IF_NULL(find, SIZE_MAX);

    if (s->length < find->length) return SIZE_MAX;

    if (s->length == find->length) {
        for (size_t i = 0; i < s->length; ++i) {
            if (s->chars[i] != find->chars[i])
                return SIZE_MAX;
        }
        return 0;
    }

    for (size_t i = 0; i <= s->length - find->length; ++i) {
        bool match = true;
        for (size_t j = 0; j < find->length; ++j) {
            if (s->chars[i + j] != find->chars[j]) {
                match = false;
                break;
            }
        }
        if (match) return i;
    }

    return SIZE_MAX;
}

bool string_starts_with(const string *s, const char *prefix) {
    RETURN_IF_NULL(s, false);
    RETURN_IF_NULL(prefix, false);

    const size_t prefix_len = strlen(prefix);
    if (prefix_len > s->length) return false;

    return memcmp(s->chars, prefix, prefix_len) == 0;
}

bool string_ends_with(const string *s, const char *suffix) {
    RETURN_IF_NULL(s, false);
    RETURN_IF_NULL(suffix, false);

    const size_t suffix_len = strlen(suffix);
    if (suffix_len > s->length) return false;

    return memcmp(s->chars + (s->length - suffix_len), suffix, suffix_len) == 0;
}

void string_trim(string *str) {
    if (!str || !str->chars) return;

    size_t start = 0;
    while (isspace((unsigned char)str->chars[start])) start++;

    size_t end = str->length;
    while (end > start && isspace((unsigned char)str->chars[end - 1])) end--;

    memmove(str->chars, str->chars + start, end - start);
    str->chars[end - start] = '\0';
    str->length = end - start;
}

void string_print(const string *s) {
    if (!s || !s->chars) return;
    printf("%.*s\n", (int)s->length, s->chars);
}

void string_free_array(string **array, const size_t size) {
    for (int i = 0; i < size; ++i) {
        string_free(array[i]);
    }
    free(array);
}

size_t count_occurrences(const string *s, const char ch) {
    RETURN_IF_NULL(s, 0);

    size_t amount = 0;

    for (size_t i = 0; i < s->length; ++i) {
        if (s->chars[i] == ch) amount++;
    }

    return amount;
}

size_t count_occurrences_s(const string *s, const string *find) {
    RETURN_IF_NULL(s, 0);
    RETURN_IF_NULL(find, 0);

    if (find->length == 0) return 0;
    if (s->length < find->length) return 0;

    size_t *lps = malloc(find->length * sizeof(size_t));
    if (lps == nullptr) return 0;

    lps[0] = 0;
    size_t len = 0;
    for (size_t i = 1; i < find->length; ) {
        if (find->chars[i] == find->chars[len]) {
            len++;
            lps[i] = len;
            i++;
        } else if (len > 0) {
            len = lps[len - 1];
        } else {
            lps[i] = 0;
            i++;
        }
    }

    size_t i = 0;
    size_t j = 0;
    size_t count = 0;

    while (i < s->length) {
        if (s->chars[i] == find->chars[j]) {
            i++;
            j++;

            if (j == find->length) {
                count++;
                j = lps[j - 1];
            }
        } else if (j > 0) {
            j = lps[j - 1];
        } else {
            i++;
        }
    }

    free(lps);

    return count;
}

