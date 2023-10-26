#pragma once

#include "../core/defines.h"

enum {
    DARRAY_CAPACITY,
    DARRAY_LENGTH,
    DARRAY_STRIDE,
    DARRAY_FIELD_LENGTH
};

// basics
GLUTTONY_API void* _darray_create(u64 length, u64 stride);
GLUTTONY_API void _darray_destroy(void* array);

// Get & Set hidden values of array
GLUTTONY_API u64 _darray_field_get(void* array, u64 field);
GLUTTONY_API void _darray_field_set(void* array, u64 field, u64 value);

// Because this is a dynamic array, need resize operation
GLUTTONY_API void* _darray_resize(void* array);

// operations at end of array
GLUTTONY_API void* _darray_push(void* array, const void* valuePtr);
GLUTTONY_API void _darray_pop(void* array, void* dest);

// operations anywhere in array
GLUTTONY_API void* _darray_insert_at(void* array, u64 index, void* valuePtr);
GLUTTONY_API void* _darray_pop_at(void* array, u64 index, void* dest);

#define DARRAY_DEFAULT_CAPACITY 1
#define DARRAY_RESIZE_FACTOR 2

#define darray_Create(type) \
    _darray_create(DARRAY_DEFAULT_CAPACITY, sizeof(type))

#define daara_Reserve(type, capacity) \
    _darray_create(capacity, sizeof(type))

#define darray_Destroy(array) _darray_destroy(array);

#define darray_push(array, value)                       \
    {                                                   \
        typeof(value) temp = value;                     \
        array = _darray_push(array, &temp);             \
    }
// NOTE: could use __auto_type for temp above, but intellisense
// for VSCode flags it as an unknown type. typeof() seems to
// work just fine, though. Both are GNU extensions.

#define darray_pop(array, value_ptr)                    \
    _darray_pop(array, value_ptr)

#define darray_insert_at(array, index, value)           \
    {                                                   \
        typeof(value) temp = value;                     \
        array = _darray_insert_at(array, index, &temp); \
    }

#define darray_pop_at(array, index, value_ptr)          \
    _darray_pop_at(array, index, value_ptr)

#define darray_clear(array)                             \
    _darray_field_set(array, DARRAY_LENGTH, 0)

#define darray_capacity(array)                          \
    _darray_field_get(array, DARRAY_CAPACITY)

#define darray_length(array)                            \
    _darray_field_get(array, DARRAY_LENGTH)

#define darray_stride(array)                            \
    _darray_field_get(array, DARRAY_STRIDE)

#define darray_length_set(array, value)                 \
    _darray_field_set(array, DARRAY_LENGTH, value)