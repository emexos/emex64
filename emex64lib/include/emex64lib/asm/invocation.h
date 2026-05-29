/*
 * MIT License
 *
 * Copyright (c) 2024 emexlab
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef EMEX64ASM_INVOCATION_H
#define EMEX64ASM_INVOCATION_H

#include <emex64lib/asm/type.h>

typedef struct assembler_invocation {
    compiler_file_t *file;                  /* code files */
    size_t file_cnt;                        /* count of files */
    compiler_line_t *line;                  /* token array */
    uint64_t line_cnt;                      /* count of tokens */
    char *label_scope;                      /* current resolved label scope */
    compiler_label_t *label;                /* label array */
    uint64_t label_cnt;                     /* count of labels */
    reloc_table_entry_t *rtbe;              /* relocation table root entry */
    fdwalker_t *fdwalker;

    /* options */
    bool page_align;                        /* default: true */
    const char *start_entry_name;           /* default: _start */
    bool warning_error;                     /* default: false */
    bool warning_deprecated;                /* default: true */
} assembler_invocation_t;

assembler_invocation_t *assembler_invocation_alloc(const char *output_path);
void assembler_invocation_dealloc(assembler_invocation_t *inv);

#endif /* EMEX64ASM_INVOCATION_H */
