/**
 * tail.c
 * Řešení IJC-DU2, 2. 4. 2022
 * Autor: tmokenc, FIT
 * Přeloženo: gcc 11.2
 *
 * The program mimic some of the [POSIX tail](https://www.unix.com/man-page/POSIX/1posix/tail/)
 * 
 * Example
 *   ./tail file         # output the last 10 lines of the `file`
 *   ./tail -n 5 file    # output the last 5 lines of the `file`
 *   ./tail -n +5 file   # output the first 5 lines of the `files`
 *   ./tail              # output the last 10 lines from the `stdin`
 *   ./tail -n +20       # output the first 20 lines from the `stdin`
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

// config
#define DEFAULT_LINE_COUNT 10
#define LINE_MAX 4095
// 1 for the '\n' and 1 for the '\0', means we need 2 more bytes
#define C_STR_LEN (LINE_MAX + 2)

// Error codes
#define TOO_MANY_ARGUMENTS 1
#define INVALID_ARGUMENT   2
#define UNKNOWN_PARAMETER  3
#define FAILED_FS          4
#define OUT_OF_MEMORY      10
#define OVER_LINE_LIMIT    11

enum ReadFrom { Top, Bottom };

struct Arguments {
    int n;
    FILE *input;
    enum ReadFrom from;
};

struct Lines {
    char **strings;
    int count;
};

int string2num(const char *str) {
    int i = 0;
    int result = 0;
    char ch = str[i++];

    while (ch) {
        if (ch < '0' || ch > '9') {
            return -1;
        }
        
        int num = ch - '0';
        
        if (result <= (INT_MAX - num) / 10) {
            result = result * 10 + num;
        } else {
            result = INT_MAX;
        }

        ch = str[i++];
    }

    return result;
}

int parse_args(struct Arguments *args, int argc, char **argv) {
    args->n = DEFAULT_LINE_COUNT;
    args->input = NULL;
    args->from = Bottom;
    
    switch (argc) {
        case 1: {
            args->input = stdin;
            break;
        }
        
        case 2: {
            args->input = fopen(argv[1], "r");
            break;
        }
        
        case 3: 
        case 4: {
            if (strcmp(argv[1], "-n") != 0) {
                return UNKNOWN_PARAMETER;
            }
            
            char *num = argv[2];
            
            if (num[0] == '-' || num[0] == '+') {
                args->from = num[0] == '+' ? Top : Bottom;
                num++;
            }
            
            args->n = string2num(num);
            
            if (args->n == -1) {
                return INVALID_ARGUMENT;
            }
            
            args->input = argc == 4 ? fopen(argv[3], "r") : stdin;
            
            break;
        }
        
        default: 
            return TOO_MANY_ARGUMENTS;
    }
    
    if (args->input == NULL) {
        return FAILED_FS;
    }
    
    return 0;
}

int lines_add(struct Lines *lines, const char *str, int limit) {
    if (lines->count >= limit) {
        free(lines->strings[0]);
        
        for (int i = 1; i < lines->count; i++) {
            lines->strings[i-1] = lines->strings[i];
        }
    } else {
        lines->strings = realloc(lines->strings, sizeof(char *) * ++lines->count);
        
        if (lines->strings == NULL) {
            return OUT_OF_MEMORY;
        }
    }
    
    char *s = malloc(strlen(str) + 1);
    
    if (s == NULL) {
        return OUT_OF_MEMORY;
    }
    
    strcpy(s, str);
    lines->strings[lines->count-1] = s;
    
    return 0;
}

void lines_clean_up(struct Lines lines) {
    if (lines.strings == NULL) {
        return;
    }
    
    for (int i = 0; i < lines.count; i++) {
        if (lines.strings[i] != NULL) {
            free(lines.strings[i]);
        }
    }
    
    free(lines.strings);
}

void read_to_end_of_line(FILE *input) {
    int c;
    while ((c = fgetc(input)) != '\n' && c != EOF) {}
}

int read_line(char *buffer, FILE *input) {
    if (fgets(buffer, C_STR_LEN, input) == NULL) {
        return EOF;
    }
    
    int len = strlen(buffer);
    
    // len-1 is the '\0', len-2 is the last character of the string
    if (len >= LINE_MAX && buffer[len-2] != '\n') {
        buffer[len-2] = '\n';
        read_to_end_of_line(input);
        return OVER_LINE_LIMIT;
    }
    
    return 0;
}

int tail_top(struct Arguments *args) {
    bool printed_line_over_error = false;
    char buffer[C_STR_LEN];
    int count = 0;
    int res = 0;
    
    while ((res = read_line(buffer, args->input)) == EOF || count++ <= args->n) {
        if (res == OVER_LINE_LIMIT && !printed_line_over_error) {
            fprintf(stderr, "Warning: a line get over the %d limit", LINE_MAX);
            printed_line_over_error = true;
        }
        
        printf("%s", buffer);
    }
    
    printf("\n");
    
    return 0;
}

int tail(struct Arguments *args) {
    if (args->from == Top) {
        return tail_top(args);
    }
    
    bool printed_line_over_error = false;
    char buffer[C_STR_LEN];
    struct Lines lines;
    lines.strings = NULL;
    lines.count = 0;
    
    int res = 0;
    
    while((res = read_line(buffer, args->input)) != EOF) {
        if (res == OVER_LINE_LIMIT && !printed_line_over_error) {
            fprintf(stderr, "Warning: a line get over the %d limit", LINE_MAX);
            printed_line_over_error = true;
        }
        
        if (lines_add(&lines, buffer, args->n) == OUT_OF_MEMORY) {
            lines_clean_up(lines);
            return OUT_OF_MEMORY;
        }
    }
    
    for (int i = 0; i < lines.count; i++) {
        printf("%s", lines.strings[i]);
    }
    
    printf("\n");
    
    lines_clean_up(lines);
    return 0;
}

int main(int argc, char **argv) {
    struct Arguments args;
    
    switch (parse_args(&args, argc, argv)) {
        case TOO_MANY_ARGUMENTS: {
            fprintf(stderr, "Too many arguments");
            return TOO_MANY_ARGUMENTS;
        }
        
        case INVALID_ARGUMENT: {
            fprintf(stderr, "Invalid argument");
            return INVALID_ARGUMENT;
        }
        
        case UNKNOWN_PARAMETER: {
            fprintf(stderr, "Expected -n\nFound %s\n", argv[1]);
            return UNKNOWN_PARAMETER;
        }
        
        case FAILED_FS: {
            fprintf(stderr, "Cannot open the file \"%s\"\n", argv[argc-1]);
            return UNKNOWN_PARAMETER;
        }
        
        default: {}
    }
    
    int res = 0;
    
    if (args.n != 0) {
        res = tail(&args);
    }
    
    fclose(args.input);
    
    switch (res) {
        case OUT_OF_MEMORY: {
            fprintf(stderr, "Out Of Memory");
            break;
        }
        
        default: {}
    }
    
    return res;
}
