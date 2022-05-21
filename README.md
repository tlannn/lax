# lax
A custom interpreted language called Lax.

## Supported features
Lax currently supports arithmetic operations computation, if statements (true/false, boolean expressions, (in)equalities), and printing in the console the result of an expression.

## Grammar
The source language is defined as following.
```
stmt -> ifStmt | printStmt | expressionStmt
ifStmt -> "if" "(" logic ")" stmt
printStmt -> "print" expressionStmt
expressionStmt -> expr ";"
logic -> join ("||" join)*
join -> rel ("&&" rel)*
rel -> expr (("==" | "!=" | "<" | "<=" | ">" | ">=") expr)*
expr -> term (("+" | "-") term)*
term -> factor (("*" | "/") factor)*
factor -> "(" logic ")" | NUM | "true" | "false"
```
## Makefile commands
To compile the sources :
`$ make`

To run the interpreter on a specific file :
`$ make run file=lang # replace 'lang' by any Lax file`

To delete all generated assets :
`$ make clean`
