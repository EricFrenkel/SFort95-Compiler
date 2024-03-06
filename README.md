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