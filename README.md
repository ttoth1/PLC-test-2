## How to run my program for lexical/syntax analysis of my language:
Disclaimer: This works for me in a wsl terminal. If you have a different setup, you may need to run different commands.

1. Download the files from this repository into a folder.
2. Open the folder in wsl terminal.
3. Run the following commands in order

- `gcc -o main mainProgramTest2.cpp`

- `./main <input_filename_here>`

This will run the analyzer on the given input file and display information about the analysis to the terminal. Any errors will be displayed, stopping the program. If there are no errors, there will be a success message displayed at the end.
# Assignment requirements
(Given in PLCTest2.pdf)
## **This question assignment is 8-fold:**
1. (15 Points) Define the rules for recognizing all lexemes as their proper token, and clearly define integer token codes for each token required for this language
    * Should have Regular Grammar, Regular Expression, or Finite Automat defined
    ---
    |Token      |Code   |Description                |Regular Expression     |
    |:---       |:---   |:---                       |:---                   |
    |INT_LIT    |10     |Integer literal            |\d+                    |
    |IDENT      |11     |Identifier                 |[a-zA-Z][a-zA-Z_]{5,7} |
    |ASSIGN_OP  |20     |Assignment operator        |=                      |
    |ADD_OP     |21     |Addition operator          |\\+                    |
    |SUB_OP     |22     |Subtraction operator       |-                      |
    |MULT_OP    |23     |Multiplication operator    |\\*                    |
    |DIV_OP     |24     |Division operator          |/                      |
    |LEFT_PAREN |25     |Left parenthesis           |\\(                    |
    |RIGHT_PAREN|26     |Right parenthesis          |\\)                    |
    |MOD_OP     |27     |Multiplication operator    |%                      |
    |GREATER_THAN|28    |Greater than comparison operator|>                 |
    |LESS_THAN  |29     |Less than comparison operator|<                    |
    |SEMICOLON  |31     |Semicolon                  |;                      |
    |LEFT_BRACE |32     |Left brace                 |\\{                    |
    |RIGHT_BRACE|33     |Right brace                |\\}                    |
    |NOT_EQUAL  |34     |Not equal to comparison operator|\\!               |
    |LEFT_BRACKET|35    |Left bracket               |\\[                    |
    |RIGHT_BRACKET|36   |Right bracket              |\\]                    |
    |UNDERSCORE |37     |Underscore                 |_                      |
    |EQUAL      |38     |Equal to comparison operator|\\\|                  |
    |GREATER_THAN_EQUAL|39|Greater than equal to comparison operator|@      |
    |LESS_THAN_EQUAL|40 |Less than equal to comparison operator|\\$         |
    |TREVOR_LOOP|50     |Loop                       |TREVOR_LOOP            |
    |TREVOR_SELECTION|51|Selection (like "if")      |TREVOR_SELECTION       |
    |TREVOR_ALT_SELECTION|52|Selection (like "else")|TREVOR_ALT_SELECTION   |
    |JUST_ONE_BYTE|60   |One-byte integer type      |JUST_ONE_BYTE          |
    |JUST_TWO_BYTES|61  |Two-byte integer type      |JUST_TWO_BYTES         |
    |JUST_FOUR_BYTES|62 |Four-byte integer type     |JUST_FOUR_BYTES        |
    |JUST_EIGHT_BYTES|63|Eight-byte integer type    |JUST_EIGHT_BYTES       |

2. (15 Points) Define production rules for implementing the mathematical syntax of operators and operands, loops, variable declaration, selection statements
    * Enforce a non PEMDAS (BODMAS) order of operation, must have at least 6 levels of precedence
    * Keywords cannot use the words while, for, do, if, int, short, long
        * Keywords should be unique, if others share your same words, you may lose more points than this problem is worth
    * You must clearly state the structure of your language with production rules
    ---
    It is important to stay positive. As a reminder of this mindset, I have moved the `+` operator up in precedence to be with `*`, `/`, `%`

    G = {V, ??, R, S}

    V = {`<program>, <stmt>, <sel_stmt>, <loop_stmt>, <assign_stmt>, <block>, <declare_stmt>, <expr>, <term>, <factor>`}
    
    ?? = {`TREVOR_SELECTION, TREVOR_ALT_SELECTION, TREVOR_LOOP, JUST_ONE_BYTE, JUST_TWO_BYTES, JUST_FOUR_BYTES, JUST_EIGHT_BYTES, (, ), +, -, *, /, %, >, <, =, ;, {, }, [, ], !, _, |, @, $, ident, int_lit`}
    
    R = {
        
        <program> --> `[` <stmt> `]`
        
        <stmt> --> <sel_stmt> | <loop_stmt> | <assign_stmt> | <block> | <declare_stmt>
        
        <sel_stmt> -->  `TREVOR_SELECTION``(`<expr>`)` <stmt> [ `TREVOR_ALT_SELECTION` <stmt> ]
        
        <loop_stmt> -->  `TREVOR_LOOP``(`<expr>`)` <stmt> 
        
        <declare_stmt>  --> (`JUST_ONE_BYTE`|`JUST_TWO_BYTES`|`JUST_FOUR_BYTES`|`JUST_EIGHT_BYTES`) `ident`

        <block> --> `{` { <stmt>`;` } `}`
        
        <assign_stmt>  --> `ident` `=` <expr>
        
        <expr> --> <term> { `-` <term> }
        
        <term> --> <factor> { (`+`|`*`|`/`|`%`) <factor> }

        <factor> --> `ident` | `int_lit` | `(` <expr> `)`

    }
    
    S = {`<program>`}
    
3. (10 points) Show whether every rule set in your language conforms to the standard of an LL Grammar.
---
To be a LL Grammar, all rules must pass the pairwise disjointness test(PDT), and there must be no lefthand recursion.

        Rule: <program> --> `[` <stmt> `]`
        PDT: FIRST(<program>) --> {`[`}
        No lefthand recursion.

        Rule: <stmt> --> <sel_stmt> | <loop_stmt> | <assign_stmt> | <block> | <declare_stmt>
        PDT: FIRST(<stmt>) --> {`TREVOR_SELECTION`}{`TREVOR_LOOP`}{`ident`}{`{`}{`JUST_ONE_BYTE`,`JUST_TWO_BYTES`,`JUST_FOUR_BYTES`,`JUST_EIGHT_BYTES`}
        No lefthand recursion.

        Rule: <sel_stmt> -->  `TREVOR_SELECTION``(`<expr>`)` <stmt> [ `TREVOR_ALT_SELECTION` <stmt> ]
        PDT: FIRST(<sel_stmt>) --> {`TREVOR_SELECTION`}
        No lefthand recursion.

        Rule: <loop_stmt> -->  `TREVOR_LOOP``(`<expr>`)` <stmt> 
        PDT: FIRST(<loop_stmt>) --> {`TREVOR_LOOP`}
        No lefthand recursion.

        Rule: <declare_stmt>  --> (`JUST_ONE_BYTE`|`JUST_TWO_BYTES`|`JUST_FOUR_BYTES`|`JUST_EIGHT_BYTES`) `ident`
        PDT: FIRST(<declare_stmt>) --> {`JUST_ONE_BYTE`,`JUST_TWO_BYTES`,`JUST_FOUR_BYTES`,`JUST_EIGHT_BYTES`}
        No lefthand recursion.

        Rule: <block> --> `{` { <stmt>`;` } `}` 
        PDT: FIRST(<block>) --> {`{`}
        No lefthand recursion.

        Rule: <assign_stmt>  --> `ident` `=` <expr>
        PDT: FIRST(<assign_stmt>) --> {`ident`}
        No lefthand recursion.

        Rule: <expr> --> <term> { `-` <term> }
        PDT: FIRST(<expr>) --> {`ident`, `int_lit`, `(`}
        No lefthand recursion.

        Rule: <term> --> <factor> { (`+`|`*`|`/`|`%`) <factor> }
        PDT: FIRST(<term>) --> {`ident`, `int_lit`, `(`}
        No lefthand recursion.

        Rule: <factor> --> `ident` | `int_lit` | `(` <expr> `)`
        PDT: FIRST(<factor>) --> {`ident`, `int_lit`, `(`}
        No lefthand recursion.

Since all rules pass the pairwise disjointness test and there is no lefthand recursion, my language is an LL Grammar.

4. (5 points) Make sure it is not ambiguous grammar
---
In the screenshots folder, you can see the rules in the 5 LRtable files that show the grammar is not ambiguous.

5. (15 points) Write a program that process all lexemes in a file by recognizing all tokens in a file, and produces a list of those tokens in order
    * If a group of characters is not defined in your language your program should print an error message stating what went wrong and terminate (stop running)
    * This program should be written in an Object-Oriented fashion
    * This program should have comments to describe each method that is defined
    ---
    `front.cpp` is the lexical analyzer that checks the input file for valid lexemes and outputs their token codes as a space separated list to `tokenList.txt`

    If there is a lexical error, it will be printed to the terminal in the format `LEXICAL ERROR AT LEXEME <lexeme>` and halt program execution. The program also displays the token codes and lexemes to the terminal to help with debugging if an error is found
6. (10 points) Write a program or an extension to the above program that determines if the tokens conform to the correct syntax.
    ***
    `rda.cpp` is the syntax analyzer that checks the token order for valid syntax, according to the language rules.

    If there is a syntax error, it will be printed to the terminal in the format `SYNTAX ERROR AT LEXEME <lexeme>` and halt program execution. The program also displays the functions it is entering/exiting to the terminal to help with debugging if an error is found.
7. (10 points) Create 4 test files that have different names where each should have 30 or more lexemes that can be converted into tokens
    * 1 with a at least 5 lexical errors based on the rules you defined
        * Detail each error and say why it doesn???t work
    * 1 with at least 5 syntax errors based on the rules you defined
        * Detail each error and say why it doesn???t work
    * 2 with no errors at all based on the language you created
    ---
    In the inputFiles folder is where my test files are located.

    inputLexError.txt has several characters that are not in my language: *, ^, ", and #. It also has var_threeeee which is too long of a variable name and var which is too short.

    inputSynError.txt has no [ at the start of the program. It needs a ; after var_two. var_two cannot be assigned TREVOR_LOOP. There cannot be a ] in the middle of the program. =+ is not an operator in my language.
8. (20 points) Create a LR (1) parse table for your language. And show the trace of 4 code samples. Each must have 6 or more tokens.
    * Table must be provided, and the rules must be listed
    * 2 code samples must have errors
    * Show were these samples fail and pass the test
---
Check the screenshots folder for these code traces. 
* LRtraceError1.png has an issue where there is an asterisk in between JUST_ONE_BYTE and ident that should be removed. 
* LRtraceError2.png has an issue where there is a = in between the second ident and int_lit that should be changed into another math operator like +, -, * etc. 
* The other two traces have no errors.