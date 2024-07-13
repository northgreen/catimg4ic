//
// Created by north on 2024/7/14.
//
#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include "b64.h"
#include "sh_iterm2.h"

#define TMUX_WRAP_ST "\033Ptmux;"
#define TMUX_WRAP_ED "\033\\"
#define OSC "\033]"
#define CSI "\033["
#define ST "\a"      // \a = ^G (bell)

void it2_showimg(const char *path, uint32_t width, uint32_t height, int preserve_aspect_ratio) {

    FILE *fp = fopen(path, "rb");
    if (fp == NULL) {
        printf("file not found\n");
        return;
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    unsigned char *buffer = (unsigned char *) malloc(size);
    if (buffer == NULL) {
        printf("malloc failed\n");
        return;
    }
    fread(buffer, 1, size, fp);
    char *base64 = base64_encode(buffer, size);

    // printf("\e[s\e[?25l");

    printf("%s1337;File=inline=1", OSC);
    // printf("size=%ld", size);
    if (width > 0) {
        printf(";width=%d", width);
    }
    if (height > 0) {
        printf(";height=%d", height);
    }
    if (preserve_aspect_ratio) {
        printf(";preserveAspectRatio=1");
    }
    printf(":%s", base64);
    printf("%s\n\n\033[1A\r", ST);
    free(buffer);
    free(base64);
    // printf("\e[?25h");
}