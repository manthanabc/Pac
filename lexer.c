#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_PAREN_OPEN,
    TOKEN_PAREN_CLOSE,
    TOKEN_SEMICOLON,
    TOKEN_UNKNOWN
} TokenType;

typedef struct{
    TokenType type;
    char* value;
}Token;

void printToken(Token*);
Token* createToken(TokenType, char*);
Token* tokenize(char*);

Token* createToken(TokenType type, char *value){
    // printf("%s", value);
    Token* token = (Token*)malloc(sizeof(Token));
    token->type = type;
    token->value = strdup(value);
    printToken(token);
    return token;
}

// This function recursivly traverses the tokens and prints them from last to first
Token* tokenize(char *ptr){
    while(*ptr){
        if(isspace(*ptr)) ptr++;
        
        else if(isalpha(*ptr)){
            char* j = ptr;
            while(isalpha(*ptr) || isdigit(*ptr)) ptr++;
            char* identifier = strndup(j, ptr - j);
             
            tokenize(ptr);
            return createToken(TOKEN_IDENTIFIER, identifier);
        }
        else if(isdigit(*ptr)){
            char* j = ptr;
            while(isdigit(*ptr)){
                ptr++;
            }
            char* number = strndup(j, ptr - j);
            tokenize(ptr);
            return createToken(TOKEN_NUMBER, number);
        }
        else{
            tokenize(ptr+1);
            switch (*ptr) {
                case '+':
                case '-':
                case '*':
                case '=':
                case '/': {
                    char op[2] = { *ptr, '\0' };
                    return createToken(TOKEN_OPERATOR, op);
                    break;
                    }
                case '(':
                    return createToken(TOKEN_PAREN_OPEN, "(");
                case ')':
                    return createToken(TOKEN_PAREN_CLOSE, ")");
                case ';':
                    return createToken(TOKEN_SEMICOLON, ";");
                default :
                    return NULL;
                
            }
        }
    }

    return NULL;
}

void printToken(Token* token) {
    printf("Type: %d, Value: %s\n", token->type, token->value);
}

// Function to free memory allocated in createtoken
void freeToken(Token* token) {
    free(token->value);
    free(token);
}

int main(){
    char* source = "int a = 10 + y=();";

    Token* token;
    token = tokenize(source);

    return 0;
}
