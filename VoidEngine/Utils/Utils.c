#include <stdio.h>
#include "VoidEngine/Debug/Log.h"
#include "VoidEngine/Utils/Utils.h"

const char *VdReadFile(const char *path, u64 *length) {
    u64 len = 0;
    FILE *fp;
    char *buffer;

    if(!(fp = fopen(path, "r"))) {
        VdLogFatal("Failed to read file: %s, %m", path);
    }

    fseek(fp, 0, SEEK_END);
    len = ftell(fp);
    rewind(fp);

    buffer = calloc(len, sizeof(char));
    if(!buffer) {
        VdLogFatal("Failed to allocate source buffer.");
    }

    if(fread(buffer, sizeof(char), len, fp) != len) {
        VdLogError("Failed to read source: length mismatch.");
        return NULL;
    }

    if(length) {
        *length = len;
    }
    
    return buffer;
}
