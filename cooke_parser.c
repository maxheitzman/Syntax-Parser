// Max Heitzman 
// Project 2 - Syntax Parser for the Cooke Language
//
// This file handles the Syntax Parsing portion of the project.
// It uses a recursive descent parser to verify that the structure
// of a Cooke program matches the grammar described in the BNF form.
// This builds on Project 1 (lexical analyzer) and reads one token
// at a time using getNextToken() from lexical.c
//
// Required Output:
// - Print "Cooke Parser :: R11626572" first
// - Print "Syntax Validated" if the input is valid
// - Else, print exact syntax error w/ line, lexeme, and token
//
// Error Exit Codes:
// 1 - Syntax Error
// 2 - Missing file argument
// 3 - File does not exist

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"
#include "lexical.h"

//declared in lexical.c
extern int currentLine;

const char* tokenToStr(int token);

// buffer to store current lexeme + token
char currentLexeme[256];
int currentToken;
FILE *sourceFile;

// Forward declarations for the grammar rules
void advanceToken();
void match(int expected);
void syntaxError();
void P(), S(), C(), E(), EPrime(), T(), TPrime(), F(), O();

//grabs the next token from file and copies it to the next lexime
void advanceToken() {
    char tempLexeme[256];
    currentToken = getNextToken(sourceFile, tempLexeme);
    strcpy(currentLexeme, tempLexeme); 
}

//chelks if current toklen matches e3xpwect one or else it throws an error
void match(int expected) {
    if (currentToken == expected) {
        advanceToken();
    } else {
        syntaxError();
    }
}
//error message format
void syntaxError() {
    printf("Error encounter on line %d: The next lexeme was %s and the next token was %s\n",
           currentLine, currentLexeme, tokenToStr(currentToken));
    exit(1);
}

// ---GRAMMAR FUNCTIONS--- can be seen in the pdf attached

void F() {
    if (currentToken == INT_LIT) {
        match(INT_LIT);
    } else if (currentToken == IDENT) {
        match(IDENT);
    } else if (currentToken == LEFT_PAREN) {
        match(LEFT_PAREN);
        E();
        match(RIGHT_PAREN);
    } else {
        syntaxError();
    }
}

void TPrime() {
    if (currentToken == MULT_OP) {
        match(MULT_OP); F(); TPrime();
    } else if (currentToken == DIV_OP) {
        match(DIV_OP); F(); TPrime();
    } else if (currentToken == POW_OP) {
        match(POW_OP); F(); TPrime();
    }
    // epsilon: do nothing
}

void T() {
    F(); TPrime();
}
//helps with leftwise reccdursion problem
void EPrime() {
    if (currentToken == ADD_OP) {
        match(ADD_OP); T(); EPrime();
    } else if (currentToken == SUB_OP) {
        match(SUB_OP); T(); EPrime();
    }
    // epsilon: do nothing
}

void E() {
    T(); EPrime();
}

void C() {
    E();
    if (currentToken == LESSER_OP || currentToken == GREATER_OP ||
        currentToken == EQUAL_OP || currentToken == NEQUAL_OP ||
        currentToken == LEQUAL_OP || currentToken == GEQUAL_OP) {
        advanceToken();
    } else {
        syntaxError();
    }
    E();
}

void O() {
    if (currentToken == INC_OP) {
        match(INC_OP); match(IDENT);
    } else if (currentToken == DEC_OP) {
        match(DEC_OP); match(IDENT);
    } else {
        syntaxError();
    }
}

void S() {
    if (currentToken == IDENT) {
        match(IDENT); match(ASSIGN_OP); E();
    } else if (currentToken == INC_OP || currentToken == DEC_OP) {
        O();
    } else if (currentToken == KEY_READ) {
        match(KEY_READ); match(LEFT_PAREN); match(IDENT); match(RIGHT_PAREN);
    } else if (currentToken == KEY_PRINT) {
        match(KEY_PRINT); match(LEFT_PAREN); E(); match(RIGHT_PAREN);
    } else if (currentToken == KEY_IF) {
        match(KEY_IF); C(); match(COLON); match(KEY_BEGIN); S();
        if (currentToken == KEY_ELSE) {
            match(KEY_ELSE); match(COLON); S();
        }
        match(KEY_END);  // Now this comes after ELSE (if present)
    } else {
        syntaxError();
    }

    while (currentToken == SEMICOLON) {
        match(SEMICOLON);
        S(); // handle chained statements
    }
}

void P() {
    S();
if (currentToken != -1) {
syntaxError();
    }

}

// ---- MAIN---- 
//this is comepltley different than compared to the main classed and commented out in lexical.c

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Missing file input.\n");
        return 2;
    }

    sourceFile = fopen(argv[1], "r");
    if (!sourceFile) {
        printf("Error: File does not exist.\n");
        return 3;
    }
//header
    printf("Cooke Parser :: R11626572\n");
//starts parsing from the rtoot
    advanceToken();
    P();

    printf("Syntax Validated\n");
    fclose(sourceFile);
    return 0;
}
//converts toklen value to token name string for error output
const char* tokenToStr(int token) {
    switch (token) {
        case ASSIGN_OP: return "ASSIGN_OP";
        case ADD_OP: return "ADD_OP";
        case SUB_OP: return "SUB_OP";
        case MULT_OP: return "MULT_OP";
        case DIV_OP: return "DIV_OP";
        case POW_OP: return "POW_OP";
        case INC_OP: return "INC_OP";
        case DEC_OP: return "DEC_OP";
        case LESSER_OP: return "LESSER_OP";
        case GREATER_OP: return "GREATER_OP";
        case EQUAL_OP: return "EQUAL_OP";
        case NEQUAL_OP: return "NEQUAL_OP";
        case LEQUAL_OP: return "LEQUAL_OP";
        case GEQUAL_OP: return "GEQUAL_OP";
        case LEFT_PAREN: return "LEFT_PAREN";
        case RIGHT_PAREN: return "RIGHT_PAREN";
        case SEMICOLON: return "SEMICOLON";
        case COLON: return "COLON";
        case KEY_READ: return "KEY_READ";
        case KEY_PRINT: return "KEY_PRINT";
        case KEY_IF: return "KEY_IF";
        case KEY_ELSE: return "KEY_ELSE";
        case KEY_BEGIN: return "KEY_BEGIN";
        case KEY_END: return "KEY_END";
        case IDENT: return "IDENT";
        case INT_LIT: return "INT_LIT";
        case UNKNOWN: return "UNKNOWN";
        default: return "UNKNOWN";
    }
}

