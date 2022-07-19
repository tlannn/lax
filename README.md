# Lax
Lax is an interpreted language, designed to be tolerant and permissive.

## CMake commands
To build with cmake into the directory build/ :
```
$ mkdir build && cd build
$ cmake ..
$ make # Compile to create the executable
```

To run the interpreter with a specific file :
```
# In directory build/
$ ./lax ../lang # replace 'lang' by any Lax file
```


## Supported features

Lax currently supports :
- inline and block comments ;
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

### Notation

Terminal symbols are shown in **bold**. These appear in a program exactly as written in the grammar.

Non-terminal symbols are shown in *italic*. The definition of a non-terminal is introduced by the name of the symbol,
followed by a colon. Then following lines describe all alternatives for the non-terminal. For example :

_DeclarationStatement_:  
&emsp;&emsp; **var** _Identifier_ **;**  
&emsp;&emsp; **var** _Identifier_ **=** _Expression_ **;**

states that a _DeclarationStatement_ may represent either the token **var**, followed by an _Identifier_, followed 
by a semicolon token, or the token **var**, followed by an _Identifier_, followed by an equal sign token, followed 
by an _Expression_, followed by a semicolon token.

The grammar also uses BNF-style conventions :
- _x*_ denotes zero or more occurrences of _x_ ;
- _x?_ denotes one or more occurrences of _x_ ;
- _x | y_ denotes a choice between x and y (the choice is exclusive).

Be aware that parenthesis can appear in the grammar in two cases : either as language token, in that case the 
parenthesis would be bolded, or to regroup multiple symbols to apply a repetition operator, like (_x | y_)*

### Literals and identifiers

Identifiers can begin with an ASCII letter or an underscore, and can be followed by any number of letters, 
underscores or digits. The regular expression defining an identifier is : `(_[a-zA-Z])([_a-zA-Z0-9])*`

Literals are atomic values in Lax. They are defined as following :

_Literal_:  
&emsp;&emsp; _IntegerLiteral_  
&emsp;&emsp; _BooleanLiteral_  
&emsp;&emsp; _StringLiteral_

_IntegerLiteral_ can be any non-floating number.

_BooleanLiteral_ can take two values : **true** or **false**.

_StringLiteral_ must start and end with a double quotation **"**, and can contain any number of characters in between. 
For example : **"This a string literal"**. _StringLiteral_ can be an empty string, with no characters between the 
quotations.

### Types

_Type_:  
&emsp;&emsp; _PrimitiveType_

_PrimitiveType_:  
&emsp;&emsp; **int**  
&emsp;&emsp; **bool**

### Blocks and sequences

_Program_:  
&emsp;&emsp; _Sequence_

_Sequence_:  
&emsp;&emsp; _Statement_*

_Block_:  
&emsp;&emsp; **{** _Sequence_ **}**

### Statements

_Statement_:  
&emsp;&emsp; _IncludeStatement_  
&emsp;&emsp; _DeclarationStatement_  
&emsp;&emsp; _AssignmentStatement_  
&emsp;&emsp; _ConditionalStatement_  
&emsp;&emsp; _PrintStatement_  
&emsp;&emsp; _ExpressionStatement_

_IncludeStatement_:  
&emsp;&emsp; **include** _StringLiteral_ **;**

_DeclarationStatement_:  
&emsp;&emsp; (_Type_ | **var**) _Identifier_ **;**  
&emsp;&emsp; (_Type_ | **var**) _Identifier_ **=** _Expression_ **;**

_AssignmentStatement_:  
&emsp;&emsp; _Identifier_ **=** _Expression_ **;**

_ConditionalStatement_:  
&emsp;&emsp; **if** **(** _Expression_ **)** (_Statement_ | _Block_)  
&emsp;&emsp; **if** **(** _Expression_ **)** (_Statement_ | _Block_) **else** (_Statement_ | _Block_)

_PrintStatement_:  
&emsp;&emsp; **print** _Expression_ **;**

_ExpressionStatement_:  
&emsp;&emsp; _Expression_ **;**

### Expressions

_Expression_:  
&emsp;&emsp; _Logic_

_Logic_:  
&emsp;&emsp; _Join_  
&emsp;&emsp; _Join_ **||** _Join_

_Join_:  
&emsp;&emsp; _Relation_  
&emsp;&emsp; _Relation_ **&&** _Relation_

_Relation_:  
&emsp;&emsp; _BinaryOperation_  
&emsp;&emsp; _BinaryOperation_ _RelationalOp_ _BinaryOperation_

_RelationalOp_:  
&emsp;&emsp; **==**  
&emsp;&emsp; **!=**  
&emsp;&emsp; **<**  
&emsp;&emsp; **<=**  
&emsp;&emsp; **>**  
&emsp;&emsp; **>=**

_BinaryOperation_:  
&emsp;&emsp; _Term_  
&emsp;&emsp; _Term_ (**+** | **-**) _Term_

_Term_:  
&emsp;&emsp; _Factor_  
&emsp;&emsp; _Factor_ (__*__ | **/**) _Factor_

_Factor_:  
&emsp;&emsp; **(** _Expression_ **)**  
&emsp;&emsp; _Literal_  
&emsp;&emsp; _Identifier_

### Comments

More over, inline and block comments are supported as following :

```
// This is an inline comment

/*
    This is a block comment.
    
    /**
        This a nested block comment.
        
        You can identify nested block
        comments with the number of stars
        following the slash.
    **/
*/

/*
    This block comment won't work,
    as the number of stars are not
    the same
**/
```
