# Syntax Parser

This project implements a recursive descent syntax parser in C for a small programming language called Cooke. It builds on a lexical analyzer to validate whether the input source code follows the grammar rules of the language.

---

## Features

- Validates source code structure based on BNF grammar rules
- Uses a hand-written recursive descent parser
- Detects syntax errors and reports the line number, lexeme, and token
- Returns proper exit codes depending on success or type of error

---

## How to Compile

Using the Makefile:

    make

Or manually:

    gcc -o cooke_parser cooke_parser.c lexical.c

---

## How to Run

Run the program with a `.dc` source file from the `input_output/input/` folder:

    ./cooke_parser input_output/input/test.dc

If the file is syntactically valid, you’ll see:

    Cooke Parser :: R11626572
    Syntax Validated

If there’s an error, the output will be in this format:

    Cooke Parser :: R11626572
    Error encounter on line 3: The next lexeme was = and the next token was EQUAL_OP

---

## Exit Codes

- `0` – Syntax validated successfully
- `1` – Syntax error
- `2` – No file provided
- `3` – File not found

---

## File Structure

    Syntax Parser/
    ├── cooke_parser.c
    ├── lexical.c
    ├── lexical.h
    ├── tokens.h
    ├── Makefile
    ├── README.md
    └── input_output/
        ├── input/        # .dc test files to be parsed
        └── output/       # expected .out results

---

## Notes

- The parser starts from the root rule `P ::= S` and uses recursive descent functions for each grammar rule.
- Token stream is provided by `getNextToken()` from the lexical analyzer.
- Only the first syntax error needs to be detected; the parser will exit immediately when one is found.
- File path must be passed as a command-line argument.

