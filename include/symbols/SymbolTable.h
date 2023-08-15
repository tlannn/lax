#ifndef LAX_SYMBOLTABLE_H
#define LAX_SYMBOLTABLE_H

#include <memory>
#include <unordered_map>
#include <stack>
#include <vector>

#include "Symbol.h"
#include "Scope.h"

/**
 * Data structure implement as a hashmap that keeps track of symbols in the
 * program
 */
class SymbolTable {
public:
    /**
     * Start in a new scope in the symbol table, with the current scope as
     * a parent.
     */
    void beginScope();

    /**
     * End the current scope in the symbol table.
     */
    void endScope();

    /**
     * Return the current scope in the symbol table.
     * @return a reference to the current scope.
     */
    Scope& currentScope();

    /**
     * Initialize built-in types and add them as symbols in the table.
     */
    void initTypes();

    /**
     * Initialize native functions of Lax and add them as symbols in the table.
     */
    void initNativeFunctions();

    /**
     * Add a symbol to the table.
     * @param scope a reference to the scope where to add the symbol.
     * @param symbol the symbol to add.
     * @return true if the insertion was successful, false otherwise.
     */
    bool define(Scope &scope, std::unique_ptr<Symbol> symbol);

    /**
     * Fetch a symbol in the table.
     * @param scope the innermost scope where the lookup should happen.
     * @param name the name of the symbol.
     * @param lookupEnclosingScopes if true, lookup in parent scopes if
     * no symbol associated to the name is found.
     * @return a pointer to the symbol if found, or a null pointer.
     */
    Symbol* lookup(Scope &scope, ObjString *name,
                   bool lookupEnclosingScopes = true);

    /**
     * Fetch a symbol representing a variable in the table.
     * @param scope the innermost scope where the lookup should happen.
     * @param name the name of the variable.
     * @param lookupEnclosingScopes if true, lookup in parent scopes if
     * no symbol associated to the name is found.
     * @return a pointer to the symbol if found, or a null pointer.
     */
    VarSymbol* lookupVariable(Scope &scope, ObjString *name,
                              bool lookupEnclosingScopes = true);

    /**
     * Fetch a symbol representing a function in the table.
     * @param scope the innermost scope where the lookup should happen.
     * @param name the name of the function.
     * @param lookupEnclosingScopes if true, lookup in parent scopes if
     * no symbol associated to the name is found.
     * @return a pointer to the symbol if found, or a null pointer.
     */
    FunSymbol* lookupFunction(Scope &scope, ObjString *name,
                              bool lookupEnclosingScopes = true);

    /**
     * Return the instance of the symbol table singleton.
     * @return a shared_ptr to the symbol table unique instance.
     */
    static std::shared_ptr<SymbolTable> instance();

private:
    /// Alias for functions used to lookup a symbol in a Scope object.
    template<typename T>
    using LookupFn = T* (Scope::*)(ObjString*);

    /// Alias for functions used to insert a symbol in a Scope object.
    template<typename T>
    using InsertFn = bool (Scope::*)(ObjString*, std::unique_ptr<T>);

    /**
     * Class constructor.
     */
    SymbolTable();

    /**
     * Create a new scope in the symbol table with a specific scope as parent.
     * @param previous a pointer to the previous scope. May be a null pointer
     * to indicate that this scope has no parent.
     */
    void createScope(Scope *previous);

    /**
     * Lookup a symbol by its name in a scope.
     * @tparam Type the type of symbol to search.
     * @param lookupFunction the function to use for lookup in the scope.
     * @param scope a reference to the scope where to search.
     * @param name the name of the symbol to lookup.
     * @param lookupEnclosingScopes if true, lookup in parent scopes if
     * no symbol associated to the name is found.
     * @return a pointer to the symbol if found, or a null pointer.
     */
    template<typename Type>
    Type* lookup(LookupFn<Type> lookupFunction, Scope &scope, ObjString *name,
        bool lookupEnclosingScopes);

    /**
     * Insert a symbol in a scope.
     * @tparam Type the type of symbol to insert.
     * @param insertFunction the function to use for insertion in the scope.
     * @param scope a reference to scope where to insert the symbol.
     * @param value a unique_ptr to the symbol to insert.
     * @return true if the insertion was successful, false otherwise.
     */
    template<typename Type>
    bool insert(InsertFn<Type> insertFunction, Scope &scope,
        std::unique_ptr<Type> value);

    /*
     * Private members
     */

    std::stack<Scope*> m_scopeStack;
    std::vector<std::unique_ptr<Scope>> m_scopes;
};

#endif // LAX_SYMBOLTABLE_H
