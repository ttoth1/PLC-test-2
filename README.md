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
    |TREVOR_LOOP|50     |Loop                       |TREVOR_LOOP            |
    |TREVOR_SELECTION|51|Selection (like "if")      |TREVOR_SELECTION       |
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
    G = {V, Σ, R, S}

    V = {}
    
    Σ = {}
    
    R = {
        
        <program> -> `[` <stmt> `]`
        
        <stmt> --> <sel_stmt> | <loop_stmt> | <assign_stmt> | <block> | <declare_stmt>
        
        <declare_stmt>  --> (`JUST_ONE_BYTE`|`JUST_TWO_BYTES`|`JUST_FOUR_BYTES`|`JUST_EIGHT_BYTES`) `ident`

        <block> --> `{` { <stmt>`;` } `}`
        
        <assign_stmt>  --> `ident` `=` <expr>
        
        <expr> -> <term> { (`+`|`-`) <term> }
        
        <term> --> <factor> { (`*`|`\`|`%`) <factor> }

        <factor> --> `ident` | `int_lit` | `(` <expr> `)`

    }
    
    S = {`<program>`}
    
3. (10 points) Show whether every rule set in your language conforms to the standard of an LL Grammar.
4. (5 points) Make sure it is not ambiguous grammar
5. (15 points) Write a program that process all lexemes in a file by recognizing all tokens in a file, and produces a list of those tokens in order
    * If a group of characters is not defined in your language your program should print an error message stating what went wrong and terminate (stop running)
    * This program should be written in an Object-Oriented fashion
    * This program should have comments to describe each method that is defined
6. (10 points) Write a program or an extension to the above program that determines if the tokens conform to the correct syntax.
7. (10 points) Create 4 test files that have different names where each should have 30 or more lexemes that can be converted into tokens
    * 1 with a at least 5 lexical errors based on the rules you defined
        * Detail each error and say why it doesn’t work
    * 1 with at least 5 syntax errors based on the rules you defined
        * Detail each error and say why it doesn’t work
    * 2 with no errors at all based on the language you created
8. (20 points) Create a LR (1) parse table for your language. And show the trace of 4 code samples. Each must have 6 or more tokens.
    * Table must be provided, and the rules must be listed
    * 2 code samples must have errors
    * Show were these samples fail and pass the test

