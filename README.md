# Lax
A custom interpreted language called Lax.

## Supported features
Lax currently supports :
- arithmetic operations (addition, subtraction...) ;
- conditional statements, as well as logical expressions ; 
- variables declaration and assignment, in addition to the use of variables in expressions ;
- printing in the console the result of an expression.

## Grammar
The source language is defined as following.
```
program -> (stmt)*
block -> "{" (stmt)* "}"
stmt -> varDeclStmt | varAssignStmt | conditionalStmt | printStmt | expressionStmt
varDeclStmt -> "var" ID ":" TYPE ("=" logic)? ";"
varAssignStmt -> ID "=" logic ";"
conditionalStmt -> "if" "(" logic ")" (block | stmt) (("else" conditionalStmt)* | "else" (block | stmt))?
printStmt -> "print" expressionStmt
expressionStmt -> expr ";"
logic -> join ("||" join)*
join -> rel ("&&" rel)*
rel -> expr (("==" | "!=" | "<" | "<=" | ">" | ">=") expr)*
expr -> term (("+" | "-") term)*
term -> factor (("*" | "/") factor)*
factor -> "(" logic ")" | NUM | "true" | "false" | ID
```

## CMake commands
To build with cmake into the directory build/ :
```
$ mkdir build && cd build
$ cmake ..
$ make # Compile then to create the executable
```

To run the interpreter on a specific file :
```
# In directory build/
$ ./lax ../lang # replace 'lang' by any Lax file
```
