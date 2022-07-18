# Lax
A custom interpreted language called Lax.

## Supported features
Lax currently supports :
- arithmetic operations (addition, subtraction...) ;
- conditional statements, as well as logical expressions ;
- blocks of statements ; 
- variables declaration and assignment, in addition to the use of variables in expressions ;
- integers, booleans and strings (character sequences) types ;
- variable scopes ;
- inclusion of other source files in the code ;
- error handling ;
- printing in the console the result of an expression.

## Grammar
The source language is defined as following.
```
program -> (stmt)*
block -> "{" (stmt)* "}"
stmt -> includeStmt | declaration | varAssignStmt | conditionalStmt | printStmt | expressionStmt
includeStmt -> "include" STRING ";"
declaration -> ("var" | TYPE) ID ("=" logic)? ";"
varAssignStmt -> ID "=" logic ";"
conditionalStmt -> "if" "(" logic ")" (block | stmt) (("else" conditionalStmt)* | "else" (block | stmt))?
printStmt -> "print" expressionStmt
expressionStmt -> expr ";"
logic -> join ("||" join)*
join -> rel ("&&" rel)*
rel -> expr (("==" | "!=" | "<" | "<=" | ">" | ">=") expr)*
expr -> term (("+" | "-") term)*
term -> factor (("*" | "/") factor)*
factor -> "(" logic ")" | STRING | NUM | "true" | "false" | ID
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
