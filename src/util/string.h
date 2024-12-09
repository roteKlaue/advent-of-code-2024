//
// Created by roteklaue on 12/5/24.
//

#ifndef STRING_H
#define STRING_H

#include <stddef.h>

typedef struct {
    char *chars;
    size_t length;
    size_t buffer_size;
} string;

string *string_new(const char *chars, size_t length, size_t buffer_size);
void string_free(string *s);

bool string_append(string *dest, const char *chars, size_t length);
bool string_append_s(string *dest, const string *src);
bool string_resize(string *s, size_t new_buffer_size);
bool string_compare(const string *s1, const string *s2);
char string_char_at(const string *s, size_t index, bool *success);
string **string_split(const string *s, char delimiter, int *size);
void string_free_array(string **array, size_t size);

string *substring(const string *s, size_t start, size_t end);
size_t string_find(const string *s, char ch);
size_t string_find_s(const string *s, const string *find);
bool string_starts_with(const string *s, const char *prefix);
bool string_ends_with(const string *s, const char *suffix);
void string_trim(string *s);
size_t count_occurrences(const string *s, char ch);
size_t count_occurrences_s(const string *s, const string *find);

void string_print(const string *s);

#endif //STRING_H
