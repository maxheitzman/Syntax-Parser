//defining all my tokens by a # then using a stucture for future use
#define ASSIGN_OP 1
#define ADD_OP 2
#define SUB_OP 3
#define MULT_OP 4
#define DIV_OP 5
#define POW_OP 6
#define INC_OP 7
#define DEC_OP 8
#define LESSER_OP 9
#define GREATER_OP 10
#define EQUAL_OP 11
#define NEQUAL_OP 12
#define LEQUAL_OP 13
#define GEQUAL_OP 14
#define LEFT_PAREN 15
#define RIGHT_PAREN 16
#define SEMICOLON 17
#define COLON 18
#define KEY_READ 19
#define KEY_PRINT 20
#define KEY_IF 21
#define KEY_ELSE 22
#define KEY_BEGIN 23
#define KEY_END 24
#define IDENT 25
#define INT_LIT 26
#define UNKNOWN 99


//strucutre as mentioned
typedef struct {
    int tokenId;
    const char* tokenName;
} TokenInfo;
