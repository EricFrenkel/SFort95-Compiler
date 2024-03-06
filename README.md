# SFort95-Compiler
This repository consist of a three part project in building a simple compiler for a small programming language called Simple Fortran95-Like (SFort95) and a program to test it. The first Project Assignment (PA1) consists of a Lexical Analyzer, the second assignment (PA2) consist of a parser, and the final assignment (PA3) of an interpreter. The syntax definitions for SFort95 are given using the following EBNF notations: 

1. Prog ::= PROGRAM IDENT {Decl} {Stmt} END PROGRAM IDENT
2. Decl ::= Type :: VarList
3. Type ::= INTEGER | REAL | CHARARACTER [\(LEN = (ICONST \ *) \)]
4. VarList ::= Var [= Expr] {, Var [= Expr]}
5. Stmt ::= AssigStmt | BlockIfStmt | PrintStmt | SimpleIfStmt
6. PrintStmt ::= PRINT *, ExprList
7. BlockIfStmt ::= IF (RelExpr) THEN {Stmt} [ELSE {Stmt}] END IF
8. SimpleIfStmt ::= IF (RelExpr) SimpleStmt
9. SimpleStmt ::= AssigStmt | PrintStmt
10. AssignStmt ::= Var = Expr
11. ExprList ::= Expr {, Expr}
12. RelExpr ::= Expr [ ( == | < | > ) Expr ]
13. Expr ::= MultExpr { ( + | - | // ) MultExpr }
14. MultExpr ::= TermExpr { ( * | / ) TermExpr }
15. TermExpr ::= SFactor { ** SFactor }
16. SFactor ::= [+ | -] Factor
17. Var = IDENT
18. Factor ::= IDENT | ICONST | RCONST | SCONST | (Expr)

## PA1: Lexical Analyzer
In the Lexical Analyzer, the goal is given certain test case files (in the TestCases directory), convert the given file into its appropriate tokens based on the regular expressions shown below.

### Identifiers (IDENT)
- **IDENT:** `Letter (Letter | Digit | _) *`
- **Letter:** `[a-z A-Z]`
- **Digit:** `[0-9]`
- *Note that all identifiers are case-sensitive.*

### Integer Constants (ICONST)
- **ICONST:** `[0-9]+`

### Real Constants (RCONST)
- **RCONST:** `([0-9]*)\.([0-9]+)`
- *For example, real number constants such as 12.0, 0.2, and .5 are accepted as real constants, but 2. is not. Note that “2.” is recognized as an integer followed by a DOT.*

### String Constants (SCONST)
- A string literal is referred to by the SCONST terminal, which is defined as a sequence of characters delimited by either single or double quotes, that should all appear on the same line. For example,
  - `‘Hello to CS 280.’` or `"Hello to CS 280."` are valid string literals.
- While,
  - `‘Hello to CS 280.”` or `"Hello to CS 280.’"` are not.

### Chart of tokens to be recognized

| Reserved Word | Token   |   | Operator Symbol | Token | Description                                 |   | Character | Token | Description               |
|---------------|---------|---|------------------|-------|---------------------------------------------|---|-----------|-------|---------------------------|
| program       | PROGRAM |   | +                | PLUS  | Arithmetic addition or concatenation       |   | ,         | COMMA | Comma                     |
| end           | END     |   | -                | MINUS | Arithmetic subtraction                      |   | (         | LPAREN | Left Parenthesis          |
| else          | ELSE    |   | *                | MULT  | Multiplication                              |   | )         | RPAREN | Right parenthesis         |
| if            | IF      |   | /                | DIV   | Division                                    |   | ::        | DCOLON | Double Colons             |
| integer       | INTEGER |   | **               | POW   | Exponentiation                              |   | .         | DOT   | Dot                       |
| real          | REAL    |   | =                | ASSOP | Assignment operator                         |   | *         | DEF   | Default mark              |
| character     | CHARACTER | | ==               | EQ    | Equality                                    |                                               |
| print         | PRINT   |   | <                | LTHAN | Less than operator                          |                                               |
| len           | LEN     |   | >                | GTHAN | Greater than operator                       |                                               |
