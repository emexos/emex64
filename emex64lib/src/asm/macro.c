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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <emex64lib/support/diag.h>
#include <emex64lib/support/parser.h>

#include <emex64lib/asm/macro.h>
#include <emex64lib/asm/code.h>

typedef struct {
    const char *match;
    char **inject_token;
    uint64_t inject_token_cnt;
} assembler_macro_t;

bool assembler_macro_expand(assembler_invocation_t *inv)
{
    /* count the amount of macros */
    uint64_t c = 0;
    for(uint64_t i = 0; i < inv->line_cnt; i++)
    {
        if(inv->line[i]->type == kAssemblerLineTypeMacroDefinition)
        {
            c++;
        }
    }

    /* allocating */
    assembler_macro_t *am = calloc(c, sizeof(assembler_macro_t));
    if(am == NULL)
    {
        diag_error(NULL, "something terrible has happened\n");
        return false;
    }

    /* adding stuff */
    c = 0;
    for(uint64_t i = 0; i < inv->line_cnt; i++)
    {
        if(inv->line[i]->type == kAssemblerLineTypeMacroDefinition)
        {
            am[c].match = inv->line[i]->token[1]->str;
            am[c].inject_token_cnt = inv->line[i]->token_cnt - 2;
            am[c].inject_token = calloc(am[c].inject_token_cnt, sizeof(char*));
            for(uint64_t a = 0; a < am[c].inject_token_cnt; a++)
            {
                am[c].inject_token[a] = inv->line[i]->token[a + 2]->str;
            }
            c++;
        }
    }

    /* now replacing */
    for(uint64_t li = 0; li < inv->line_cnt; li++)
    {
        if(inv->line[li]->type != kAssemblerLineTypeMacroDefinition)
        {
            for(uint64_t ti = 0; ti < inv->line[li]->token_cnt; ti++)
            {
                for(uint64_t ami = 0; ami < c; ami++)
                {
                    /* matching macro */
                    if(strcmp(inv->line[li]->token[ti]->str, am[ami].match) == 0)
                    {
                        uint64_t old_token_cnt = inv->line[li]->token_cnt;
                        uint64_t new_tokens = (am[ami].inject_token_cnt);
                        uint64_t extra = new_tokens - 1;
                        uint64_t column_number = inv->line[li]->token[ti]->column_num;

                        if(extra > 0)
                        {

                            /* reallocating space to insert the macro */
                            inv->line[li]->token_cnt += extra;
                            inv->line[li]->token = realloc(inv->line[li]->token, inv->line[li]->token_cnt * sizeof(assembler_token_t*));

                            /* destroying affected token */
                            free(inv->line[li]->token[ti]->str);
                            free(inv->line[li]->token[ti]);

                            /* making space for macro to be inserted */
                            memmove(&inv->line[li]->token[ti + new_tokens], &inv->line[li]->token[ti + 1], (old_token_cnt - ti - 1) * sizeof(assembler_token_t));
                        }

                        for(uint64_t k = 0; k < new_tokens; k++)
                        {
                            assembler_token_t *at = calloc(1, sizeof(assembler_token_t));
                            at->al = inv->line[li];
                            at->str = strdup(am[ami].inject_token[k]);
                            at->column_num = column_number;
                            inv->line[li]->token[ti + k] = at;
                        }

                        break;
                    }
                }
            }
        }
    }

    free(am);

    return true;
}
