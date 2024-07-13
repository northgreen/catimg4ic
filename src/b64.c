//
// Created by north on 2024/7/14.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char* base64_encode(const unsigned char* input, int length) {
    const char base64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char* output = (char*)malloc(((length + 2) / 3) * 4 + 1);

    if (output == NULL) {
        return NULL;
    }

    for (int i = 0, j = 0; i < length; ) {
        uint32_t octet_a = i < length ? (unsigned char)input[i++] : 0;
        uint32_t octet_b = i < length ? (unsigned char)input[i++] : 0;
        uint32_t octet_c = i < length ? (unsigned char)input[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        output[j++] = base64chars[(triple >> 3 * 6) & 0x3F];
        output[j++] = base64chars[(triple >> 2 * 6) & 0x3F];
        output[j++] = (i > length) ? '=' : base64chars[(triple >> 1 * 6) & 0x3F];
        output[j++] = (i > length) ? '=' : base64chars[(triple >> 0 * 6) & 0x3F];
    }

    output[((length + 2) / 3) * 4] = '\0';

    return output;
}
