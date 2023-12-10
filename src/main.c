#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "strings.h"

void print_one_token(String_Builder *sb, Lex_Token *tok) {
    sb->count = 0;
    lexer_print_token(sb, tok);
    printf("Token: " SV_FMT "\n", SV_ARG(sb_to_string_view(sb)));
}

int main() {
    FILE *stream = fopen("stuff/test.txt", "r");

    fseek(stream, 0L, SEEK_END);
    size_t fsize = ftell(stream);

    char *data = malloc(fsize + 1);
    memset(data, 0, fsize + 1);

    fseek(stream, 0L, SEEK_SET);
    fread(data, 1, fsize, stream);

    fclose(stream);

    Lex_State lexer = {0};
    lexer_init(&lexer, sv_from_cstring(data, strlen(data)));
    String_Builder sb = {0};

    Lex_Token tok = {0};
    for (;;) {
        tok = lexer_lex(&lexer);
        print_one_token(&sb, &tok);
        if (lex_tok_typ(&tok) == EOS)
            break;
    }
    free(sb.items);

    free(data);

    return 0;
}
