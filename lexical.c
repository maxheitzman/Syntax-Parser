/* 
Max Heitzman 


Lexical Analyzer (Project #1):
-Tokenization: Learn how source code is scanned and divided into a sequence of tokens, such as
Keywords, identifiers, operators, and literals.
-Pattern Recognition: Implement algorithms to recognize and categorize different lexemes based on
predefined patterns and rules.
-Error Handling: Understand how to detect and handle invalid tokens, enhancing the robustness of
the lexical analyzer.


*/


#include <stdio.h> //input/output for the file
#include <stdlib.h>
#include <ctype.h> //character checks[isalpha(), isdigit()]
#include <string.h> //string comparison

//referencing my other codes or files
#include "tokens.h" //all my token defintions
#include "lexical.h" //just a my file with the function delceration for analyze+lexemes() i could of made this easier but i wanted to implmenet more referencing of files
int currentLine=1;

FILE* open_file(const char* filename); //this declares the file opener desrbibed below the main function.



// Main lexical analyzer function
void analyze_lexemes(FILE *file) 
{
    char ch; //this is going to be seen as the current character (ch) that is being read from the file
    char buffer[256]; //this will allow us to build idfentifers and #'s
    int i = 0; //this is going to be the index which will track the current possition of the buffer

    //first line exactly as seen in the example he prived us. needed for grading
    printf("Cooke Analyzer :: R11626572\n");


    //this will loop thrugh the file reading one loop at a time.
    //remeber EOF is end of file so it will go till the end of the file
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch)) // //this will skip spaces or tabs or blank lines 
        {
            continue;
        }

        //isalpha() checks if the character is a letter so in this case whatever ch is
        if (isalpha(ch)) 
        {
            buffer[i++] = ch;

            //this while statement takes into account for numbers and underscores to complete the identifier
            while ((ch = fgetc(file)) != EOF && (isalnum(ch) || ch == '_')) 
            {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';//will close off the string with a null terminator since strcmp() or printf() migh keep reading past what is needed
            ungetc(ch, file); //if we read to far it will put it back whatever is read that isnt apart of the identifer 

            // Keyword check block: Check if it's a keyword 
            if (strcmp(buffer, "read") == 0)
            {
                printf("read KEY_READ\n");
            } 
            else if (strcmp(buffer, "print") == 0)
            {
                printf("print KEY_PRINT\n");
            }
            else if (strcmp(buffer, "if") == 0)
            {
                printf("if KEY_IF\n");
            }
            else if (strcmp(buffer, "else") == 0)
            {
                printf("else KEY_ELSE\n");
            }
            else if (strcmp(buffer, "begin") == 0)
            {
                printf("begin KEY_BEGIN\n");
            }
            else if (strcmp(buffer, "end") == 0)
            {
                printf("end KEY_END\n");
            }
            else
            {
                printf("%s IDENT\n", buffer);
            }

            i = 0; //resets the buffer for the next lexeme 
        }
        // the number check block: checks if its a #
        else if (isdigit(ch)) 
        {
            buffer[i++] = ch;
            
            //this will keep readings digits to form the full #. still gives the notion it not at the EOF
            while ((ch = fgetc(file)) != EOF && isdigit(ch)) 
            {
                buffer[i++] = ch;
            }

            buffer[i] = '\0'; //will close off the string with a null terminator since strcmp() or printf() migh keep reading past what is needed
            ungetc(ch, file); //if we read to far it will put it back whatever is read that isnt apart of the identifer 

            //below wouldnt make sense having it in the keyword check block because we already know its a #
            printf("%s INT_LIT\n", buffer); //prints # token
            i = 0; //reset
        }
        // Symbol/Operation Check BLock: checks if symbols or operatora are used then prints what is needed.
        else {
            switch (ch) {
                case ':':
                    if ((ch = fgetc(file)) == '='){
                        printf(":= ASSIGN_OP\n");
                    }
                    else 
                    { 
                        ungetc(ch, file); printf(": COLON\n"); 
                    }
                    break;
                case '+':
                    if ((ch = fgetc(file)) == '+')
                    {
                         printf("++ INC_OP\n");
                    }
                    else 
                    {
                        ungetc(ch, file); printf("+ ADD_OP\n"); 
                    }
                    break;
                case '-':
                    if ((ch = fgetc(file)) == '-')
                    {
                        printf("-- DEC_OP\n");
                    }
                    else 
                    {
                        ungetc(ch, file); printf("- SUB_OP\n"); 
                    }
                    break;
                case '*':
                    if ((ch = fgetc(file)) == '*')
                    {
                        printf("** POW_OP\n");
                    }
                    else 
                    { 
                        ungetc(ch, file); printf("* MULT_OP\n"); 
                    }
                    break;
                case '/': 
                    printf("/ DIV_OP\n"); 
                    break;
                case '(': 
                    printf("( LEFT_PAREN\n");
                    break;
                case ')': 
                    printf(") RIGHT_PAREN\n"); 
                    break;
                case ';': 
                    printf("; SEMICOLON\n"); 
                    break;
                case '<':
                    if ((ch = fgetc(file)) == '=') 
                    {
                        printf("<= LEQUAL_OP\n");
                    }
                    else if (ch == '>')
                    {
                        printf("<> NEQUAL_OP\n");
                    }
                    else 
                    { 
                        ungetc(ch, file); printf("< LESSER_OP\n");
                    }
                    break;
                case '>':
                    if ((ch = fgetc(file)) == '=')
                    {
                        printf(">= GEQUAL_OP\n");
                    }
                    else 
                    { 
                        ungetc(ch, file); printf("> GREATER_OP\n"); 
                    }
                    break;
                case '=': 
                    printf("= EQUAL_OP\n"); 
                    break;
                default: 
                    printf("%c UNKNOWN\n", ch); 
                    break;
            }
        }
    }
}

/**
Program Start Point:
when we run ./cooke_analyzer whateverfilename.dc
think of argv[0] is the ./cook_analyzer file or the name of the program 
argv[1] as the filename entered by the user

*/
/**int main(int argc, char *argv[]) 
{
    if (argc != 2) //making sure its not 2 cuz that just wouldnt work in this case...
    {
        printf("Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    FILE *file = open_file(argv[1]);
    if (!file)//if file cant be opened its gonna error
    {
        return 1;
    }

    analyze_lexemes(file); //runs the lexeme analzyer on the file specified
    fclose(file); //closes file after processing
    return 0; //success
}
*/

//this is the file opner for the user. this helps with writting messy error logic basically
FILE* open_file(const char* filename) 
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Eoror: Cannot Open File as Specified: %s\n", filename);
        return NULL;
    }
    return file;
}
//added for proejct 2
int getNextToken(FILE *file, char *outLexeme) {
    char ch;
    int i = 0;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') currentLine++;
        if (isspace(ch)) continue;

        // IDENTIFIER or KEYWORD
        if (isalpha(ch)) {
            outLexeme[i++] = ch;
            while ((ch = fgetc(file)) != EOF && (isalnum(ch) || ch == '_')) {
                outLexeme[i++] = ch;
            }
            outLexeme[i] = '\0';
            if (ch != EOF) ungetc(ch, file);

            if (strcmp(outLexeme, "read") == 0) return KEY_READ;
            if (strcmp(outLexeme, "print") == 0) return KEY_PRINT;
            if (strcmp(outLexeme, "if") == 0) return KEY_IF;
            if (strcmp(outLexeme, "else") == 0) return KEY_ELSE;
            if (strcmp(outLexeme, "begin") == 0) return KEY_BEGIN;
            if (strcmp(outLexeme, "end") == 0) return KEY_END;
            return IDENT;
        }

        // INTEGER LITERAL
        if (isdigit(ch)) {
            outLexeme[i++] = ch;
            while ((ch = fgetc(file)) != EOF && isdigit(ch)) {
                outLexeme[i++] = ch;
            }
            outLexeme[i] = '\0';
            if (ch != EOF) ungetc(ch, file);
            return INT_LIT;
        }

        // SYMBOLS & OPERATORS
        switch (ch) {
            case ':':
                if ((ch = fgetc(file)) == '=') {
                    strcpy(outLexeme, ":=");
                    return ASSIGN_OP;
                } else {
                    if (ch != EOF) ungetc(ch, file);
                    strcpy(outLexeme, ":");
                    return COLON;
                }
            case '+':
                if ((ch = fgetc(file)) == '+') {
                    strcpy(outLexeme, "++");
                    return INC_OP;
                } else {
                    if (ch != EOF) ungetc(ch, file);
                    strcpy(outLexeme, "+");
                    return ADD_OP;
                }
            case '-':
                if ((ch = fgetc(file)) == '-') {
                    strcpy(outLexeme, "--");
                    return DEC_OP;
                } else {
                    if (ch != EOF) ungetc(ch, file);
                    strcpy(outLexeme, "-");
                    return SUB_OP;
                }
            case '*':
                if ((ch = fgetc(file)) == '*') {
                    strcpy(outLexeme, "**");
                    return POW_OP;
                } else {
                    if (ch != EOF) ungetc(ch, file);
                    strcpy(outLexeme, "*");
                    return MULT_OP;
                }
            case '/':
                strcpy(outLexeme,"/");
                return DIV_OP;
            case '<':
                if ((ch = fgetc(file)) == '=') {
                    strcpy(outLexeme, "<=");
                    return LEQUAL_OP;
                } else if (ch == '>') {
                    strcpy(outLexeme, "<>");
                    return NEQUAL_OP;
                } else {
                    if (ch != EOF) ungetc(ch, file);
                    strcpy(outLexeme, "<");
                    return LESSER_OP;
                }
            case '>':
                if ((ch = fgetc(file)) == '=') {
                    strcpy(outLexeme, ">=");
                    return GEQUAL_OP;
                } else {
                    if (ch != EOF) ungetc(ch, file);
                    strcpy(outLexeme, ">");
                    return GREATER_OP;
                }
            case '=':
                strcpy(outLexeme, "=");
                return EQUAL_OP;
            case '(': strcpy(outLexeme, "("); return LEFT_PAREN;
            case ')': strcpy(outLexeme, ")"); return RIGHT_PAREN;
            case ';': strcpy(outLexeme, ";"); return SEMICOLON;
            default:
                outLexeme[0] = ch;
                outLexeme[1] = '\0';
                return UNKNOWN;
        }
    }

    // End of File
    outLexeme[0] = '\0';
    return -1;
}

