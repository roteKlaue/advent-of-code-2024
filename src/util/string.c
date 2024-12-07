//
// Created by roteklaue on 12/5/24.
//

#include "string.h"

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

int string_append(string *dest, const char *chars, const size_t length) {
    RETURN_IF_NULL(dest, -1);
    RETURN_IF_NULL(chars, -1);

    if (dest->length + length + 1 > dest->buffer_size) {
        const size_t new_size = dest->buffer_size * 2 > dest->length + length + 1
                          ? dest->buffer_size * 2
                          : dest->length + length + 1;
        if (string_resize(dest, new_size) != 0) {
            return -1;
        }
    }

    memcpy(dest->chars + dest->length, chars, length);
    dest->length += length;
    dest->chars[dest->length] = '\0';

    return 0;
}

int string_resize(string *s, const size_t new_buffer_size) {
    RETURN_IF_NULL(s, -1);

    if (new_buffer_size <= s->length) return -1;

    char *new_chars = realloc(s->chars, new_buffer_size);
    if (!new_chars) return -1;

    s->chars = new_chars;
    s->buffer_size = new_buffer_size;

    return 0;
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

size_t string_find(const string *s, const char ch) {
    RETURN_IF_NULL(s, SIZE_MAX);

    for (size_t i = 0; i < s->length; ++i) {
        if (s->chars[i] == ch) {
            return i;
        }
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

void string_trim(string *s) {
    if (s == nullptr || s->length <= 0)
        return;

    size_t start = 0;
    while (start < s->length && (s->chars[start] == ' ' || s->chars[start] == '\t' || s->chars[start] == '\n')) {
        start++;
    }

    size_t end = s->length;
    while (end > start && (s->chars[end - 1] == ' ' || s->chars[end - 1] == '\t' || s->chars[end - 1] == '\n')) {
        end--;
    }

    const size_t new_length = end - start;

    memmove(s->chars, s->chars + start, new_length);
    s->chars[new_length] = '\0';
    s->length = new_length;
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
