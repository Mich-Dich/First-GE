#include "containers/darray.h"
#include "core/glmemory.h"
#include "core/logger.h"


// basics
void* _darray_create(u64 length, u64 stride) {

    // Create header INFO
    u64 headerSize = DARRAY_FIELD_LENGTH * sizeof(u64);
    u64 array_size = length * stride;
    u64* newArray = gl_allocate(headerSize + array_size, MEMORY_TAG_DARRAY);

    // Set basics
    gl_set_memory(newArray, 0, headerSize + array_size);
    newArray[DARRAY_CAPACITY] = length;
    newArray[DARRAY_LENGTH] = 0;
    newArray[DARRAY_STRIDE] = stride;

    // slide pointer by 24byte to only return content (no header info)
    return (void*)(newArray + DARRAY_FIELD_LENGTH);
}

void _darray_destroy(void* array) {

    // slide pointer back by 24byte to include header info
    u64* header = (u64*)(array - DARRAY_FIELD_LENGTH);

    // Calc total Length
    u64 headerSize = DARRAY_FIELD_LENGTH * sizeof(u64);
    u64 totalSize = headerSize + header[DARRAY_CAPACITY] * header[DARRAY_STRIDE];

    // free momory
    gl_free(header, totalSize, MEMORY_TAG_DARRAY);
}

u64 _darray_field_get(void* array, u64 field) {

    // slide pointer back by 24byte to include header info
    u64* header = (u64*)(array - DARRAY_FIELD_LENGTH);

    return header[field];
}

void _darray_field_set(void* array, u64 field, u64 value) {

    // slide pointer back by 24byte to include header info
    u64* header = (u64*)(array - DARRAY_FIELD_LENGTH);

    header[field] = value;
}


// Because this is a dynamic array, need resize operation
void* _darray_resize(void* array) {

    u64 length = darray_length(array);
    u64 stride = darray_stride(array);
    void* temp = _darray_create((DARRAY_RESIZE_FACTOR * darray_capacity(array)), stride);

    gl_copy_memory(temp, array, length * stride);

    _darray_field_set(temp, DARRAY_LENGTH, length);
    _darray_destroy(array);

    return temp;
}

// operations at end of array
void* _darray_push(void* array, const void* valuePtr) {

    u64 length = darray_length(array);
    u64 stride = darray_stride(array);

    if (length >= darray_capacity(array)) 
        array = _darray_resize(array);

    u64 addr = (u64)array;
    addr += (length * stride);

    gl_copy_memory((void*)addr, valuePtr, stride);
    _darray_field_set(array, DARRAY_LENGTH, length + 1);

    return array;
}

void _darray_pop(void* array, void* dest) {

    u64 length = darray_length(array);
    u64 stride = darray_stride(array);
    
    u64 addr = (u64)array;
    addr += ((length - 1) * stride);

    gl_copy_memory(dest, (void*)addr, stride);
    _darray_field_set(array, DARRAY_LENGTH, length - 1);
}

// pop anywhere in array
void* _darray_pop_at(void* array, u64 index, void* dest) {
    
    u64 length = darray_length(array);
    u64 stride = darray_stride(array);

    // Savegard against invalid index
    if (index >= length) {

        GL_ERROR("[darray_pop_at] index out of bounds [length: %i, index: %i]", length, index);
        return array;
    }

    u64 addr = (u64)array;
    gl_copy_memory(dest, (void*)(addr + (index * stride)), stride);

    // if pop in not at end => shift content by 1
    if (index != length - 1)
        gl_copy_memory(
            (void*)(addr + (index * stride)),
            (void*)(addr + ((index + 1) * stride)),
            stride * (length - index));
    
    _darray_field_set(array, DARRAY_LENGTH, length - 1);
    return array;
}

// insert anywhere in array
void* _darray_insert_at(void* array, u64 index, void* valuePtr) {

    u64 length = darray_length(array);
    u64 stride = darray_stride(array);
    
    // Savegard against invalid index
    if (index >= length) {

        GL_ERROR("[darray_insert_at] index out of bounds [length: %i, index: %i]", length, index);
        return array;
    }

    // resize if needed
    if (length >= darray_capacity(array)) 
        array = _darray_resize(array);

    u64 addr = (u64)array;

    // if insert in not at end => shift content by 1
    if (index != length -1) 
        gl_copy_memory(
            (void*)(addr + ((index + 1) * stride)),
            (void*)(addr + (index * stride)),
            stride * (length - index));

    gl_copy_memory((void*)(addr + (index * stride)), valuePtr, stride);

    _darray_field_set(array, DARRAY_LENGTH, length + 1);
    return array;
}