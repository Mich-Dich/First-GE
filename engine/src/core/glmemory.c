#include "glmemory.h"
#include "logger.h"
#include "../platform/platform.h"
#include <string.h>
#include <stdio.h>

struct memoryStats {
    u64 totalAllocations;
    u64 taggedAllocations[MEMORY_TAG_MAX_TAGS];
};

static const char* memory_tag_strings[MEMORY_TAG_MAX_TAGS] = {
    "UNKNOWN    ",
    "ARRAY      ",
    "DARRAY     ",
    "DICT       ",
    "RING_QUEUE ",
    "BST        ",
    "STRING     ",
    "APPLICATION",
    "JOB        ",
    "TEXTURE    ",
    "MAT_INST   ",
    "RENDERER   ",
    "GAME       ",
    "TRANSFORM  ",
    "ENTITY     ",
    "ENTITY_NODE",
    "SCENE      "
};

static struct memoryStats stats;

// Setup everything needed for memory system
void Init_Memory() {

    platform_zero_memory(&stats, sizeof(stats));
}

// clean up everything needed for memory system
void shutdown_Memory() {
    
}

void* gl_allocate(u64 size, memoryTag tag) {

    if (tag == MEMORY_TAG_UNKNOWN) 
        GL_WARNING("gl_allocate() called using [MEMORY_TAG_UNKNOWN], Technically valid but not recommended. Chouse different memory tag");

    // track memory allocations
    stats.totalAllocations += size;
    stats.taggedAllocations[tag] += size;

    // TODO: Memory Allignment
    void* block = platform_allocate_memory(size, FALSE);
    platform_zero_memory(block, size);
    return block;
}

void gl_free(void* block, u64 size, memoryTag tag) {

    if (tag == MEMORY_TAG_UNKNOWN) 
        GL_WARNING("gl_free() called using [MEMORY_TAG_UNKNOWN], Technically valid but not recommended. Chouse different memory tag");

    // track memory allocations
    stats.totalAllocations -= size;
    stats.taggedAllocations[tag] -= size;

    // TODO: Memory Allignment
    platform_free_memory(block, FALSE);
}


void* gl_zero_memory(void* block, u64 size) {

    return platform_zero_memory(block, size);
}

void* gl_copy_memory(void* dest, const void* source, u64 size) {

    return platform_copy_memory(dest, source, size);
}

void* gl_set_memory(void* dest, int32 value, u64 size) {

    return platform_set_memory(dest, value, size);
}

// Print usage size of every Category
char* get_memory_usage_str() {
    const u64 sizeG = 1024 * 1024 * 1024;
    const u64 sizeM = 1024 * 1024;
    const u64 sizeK = 1024;

    char buffer[8000] = "System memory use (tagged):\n";
    u64 offset = strlen(buffer);

    for (int32 x = 0; x < MEMORY_TAG_MAX_TAGS; x++) {

        char unit[4] = "Xib";
        float amount = 1.0f;

        // Check if size in Gitabyte
        if (stats.taggedAllocations[x] >= sizeG) {

            unit[0] = 'G';
            amount = stats.taggedAllocations[x] / (float)sizeG;
        }
        
        // Check if size in Megabyte
        else if (stats.taggedAllocations[x] >= sizeM) {

            unit[0] = 'M';
            amount = stats.taggedAllocations[x] / (float)sizeM;
        }
        
        // Check if size in Kilobyte
        else if (stats.taggedAllocations[x] >= sizeK) {

            unit[0] = 'K';
            amount = stats.taggedAllocations[x] / (float)sizeK;
        }
        
        // Default Size in Byte
        else {

            unit[0] = 'B';
            unit[1] = 0;
            amount = (float)stats.taggedAllocations[x];
        }
        
        int32 length = snprintf(buffer + offset, 8000, "  %s: %.2f%s\n", memory_tag_strings[x], amount, unit);
        offset += length;
    }
    
    char* outString = _strdup(buffer);
    return outString;
}