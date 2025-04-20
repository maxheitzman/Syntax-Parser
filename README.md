# Syntax Parser

This project implements a recursive descent syntax parser in C for a small programming language called Cooke. It builds on a custom lexical analyzer to validate whether the input source code follows the grammar rules of the language.

---

## Features

- Validates source code structure based on BNF grammar rules
- Uses a hand-written recursive descent parser
- Detects syntax errors and reports the exact line, lexeme, and token
- Returns exit codes for: success, syntax error, missing input, or missing file

---

## How to Compile

Using the provided Makefile:

    make

Or manually:

    gcc -o cooke_parser cooke_parser.c lexical.c

---

## How to Run

Run the parser with a `.dc` file as input:

    ./cooke_parser input_output/test.dc

---

## Output Format

If the input is valid:

    Cooke Parser :: R11626572
    Syntax Validated

If there’s a syntax error:

    Cooke Parser :: R11626572
    Error encounter on line 3: The next lexeme was = and the next token was EQUAL_OP

---

## Exit Codes

- `0` – syntax validated successfully
- `1` – syntax error
- `2` – file not provided
- `3` – file not found

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
    ├── input/       ← test .dc files go here
    └── output/      ← expected .out files go here


---

## Notes

- The parser uses `getNextToken()` from `lexical.c` to read tokens.
- The program starts parsing from the root rule `P ::= S` according to the Cooke BNF grammar.
- Input files must be passed as command-line arguments.

