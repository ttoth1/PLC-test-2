# Assignment requirements
(Given in PLCTest2.pdf)
## **This question assignment is 8-fold:**
1. (15 Points) Define the rules for recognizing all lexemes as their proper token, and clearly define integer token codes for each token required for this language
    * Should have Regular Grammar, Regular Expression, or Finite Automat defined

2. (15 Points) Define production rules for implementing the mathematical syntax of operators and operands, loops, variable declaration, selection statements
    * Enforce a non PEMDAS (BODMAS) order of operation, must have at least 6 levels of precedence
    * Keywords cannot use the words while, for, do, if, int, short, long
        * Keywords should be unique, if others share your same words, you may lose more points than this problem is worth
    * You must clearly state the structure of your language with production rules
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

