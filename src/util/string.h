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

int string_append(string *dest, const char *chars, size_t length);
int string_resize(string *s, size_t new_size);
bool string_compare(const string *s1, const string *s2);
char string_char_at(const string *s, size_t index, bool *success);
string **string_split(const string *s, char delimiter, int *size);
void string_free_array(string **array, size_t size);

size_t string_find(const string *s, char ch);
bool string_starts_with(const string *s, const char *prefix);
bool string_ends_with(const string *s, const char *suffix);
void string_trim(string *s);

void string_print(const string *s);

#endif //STRING_H
