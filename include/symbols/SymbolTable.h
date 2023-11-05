#ifndef LAX_SYMBOLTABLE_H
#define LAX_SYMBOLTABLE_H

#include <memory>
#include <unordered_map>
#include <stack>
#include <vector>

#include "Symbol.h"
#include "Scope.h"

/**
 * @class SymbolTable
 * @brief Singleton class representing the symbol table of the Lax language.
 *
 * The symbol table is a singleton class that represents the symbol table of the
 * Lax language. It is used to store symbols and lookup them when needed.
 */
class SymbolTable {
public:
    /**
     * @brief Begins a new scope in the symbol table.
     *
     * This function creates a new scope in the symbol table. It is used to
     * represent a new lexical scope in the language.
     *
     * The new scope is pushed onto the scope stack, and the previous scope is
     * saved as the parent of the new scope.
     */
    void beginScope();

    /**
     * @brief Ends the current scope in the symbol table.
     *
     * This function ends the current scope in the symbol table.
     *
     * The current scope is popped from the scope stack, and the previous scope
     * is restored as the current scope.
     */
    void endScope();

    /**
     * @brief Returns the current scope.
     *
     * This function returns the current scope in the symbol table.
     *
     * @return A reference to the current scope.
     */
    Scope& currentScope();

    /**
     * @brief Initializes the symbol table with built-in types.
     *
     * This function initializes the symbol table with built-in types. It is
     * called when the symbol table is created.
     */
    void initTypes();

    /**
     * @brief Initializes the symbol table with built-in functions.
     *
     * This function initializes the symbol table with built-in functions. It is
     * called when the symbol table is created.
     */
    void initNativeFunctions();

    /**
     * @brief Defines a symbol in the table.
     *
     * This function defines a symbol in the table. If the symbol already exists
     * in the table, the insertion fails and the function returns `false`.
     *
     * @param scope The scope where to add the symbol.
     * @param symbol A unique_ptr to the symbol to insert.
     *
     * @return `true` if the insertion was successful, `false` otherwise.
     */
    bool define(Scope& scope, std::unique_ptr<Symbol> symbol);

    /**
     * @brief Searches for a given object name in the table.
     *
     * This function performs a lookup operation to find the given object name
     * in the table. It found, it returns the matching object in the table.
     *
     * @param scope The innermost scope where the lookup should happen.
     * @param name The name of the symbol.
     * @param lookupEnclosingScopes If `true`, lookups in parent scopes if
     * no symbol associated to the name is found.
     *
     * @return A pointer to the symbol if found, otherwise returns nullptr.
     */
    Symbol* lookup(Scope& scope, ObjString* name,
        bool lookupEnclosingScopes = true);

    /**
     * @brief Searches for a variable in the table.
     *
     * This function performs a lookup operation to find the given variable name
     * in the table. It found, it returns the matching variable in the table.
     *
     * @param scope The innermost scope where the lookup should happen.
     * @param name The name of the variable.
     * @param lookupEnclosingScopes If `true`, lookups in parent scopes if
     * no symbol associated to the name is found.
     *
     * @return A pointer to the variable symbol if found, otherwise returns
     * nullptr.
     */
    VarSymbol* lookupVariable(Scope& scope, ObjString* name,
        bool lookupEnclosingScopes = true);

    /**
     * @brief Searches for a function in the table.
     *
     * This function performs a lookup operation to find the given function name
     * in the table. It found, it returns the matching function in the table.
     *
     * @param scope The innermost scope where the lookup should happen.
     * @param name The name of the variable.
     * @param lookupEnclosingScopes If `true`, lookups in parent scopes if
     * no symbol associated to the name is found.
     *
     * @return A pointer to the function symbol if found, otherwise returns
     * nullptr.
     */
    FunSymbol* lookupFunction(Scope& scope, ObjString* name,
        bool lookupEnclosingScopes = true);

    /**
     * @brief Returns the symbol table singleton instance.
     *
     * This function returns the symbol table singleton instance. If the symbol
     * table has not been created yet, it creates it.
     *
     * @return A shared_ptr to the symbol table unique instance.
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
     * @brief Class constructor.
     *
     * Constructs a symbol table object.
     */
    SymbolTable();

    /**
     * @brief Creates a new scope.
     *
     * This function creates a new scope and pushes it onto the scope stack.
     * The previous scope is saved as the parent of the new scope. If no
     * previous scope exists, the new scope is a global scope.
     *
     * @param previous A pointer to the previous scope.
     */
    void createScope(Scope* previous);

    /**
     * @brief Lookups a symbol by its name in a scope.
     * @tparam Type The type of symbol to search.
     * @param lookupFunction The function to use for lookup in the scope.
     * @param scope The scope where to search.
     * @param name The name of the symbol to lookup.
     * @param lookupEnclosingScopes If `true`, lookups in parent scopes if
     * no symbol associated to the name is found.
     * @return A pointer to the symbol if found, otherwise returns nullptr.
     */
    template<typename Type>
    Type* lookup(LookupFn<Type> lookupFunction, Scope& scope, ObjString* name,
        bool lookupEnclosingScopes);

    /**
     * @brief Inserts a symbol in a scope.
     * @tparam Type The type of symbol to insert.
     * @param insertFunction The function to use for insertion in the scope.
     * @param scope The scope where to insert the symbol.
     * @param value A unique_ptr to the symbol to insert.
     * @return `true` if the insertion was successful, `false` otherwise.
     */
    template<typename Type>
    bool insert(InsertFn<Type> insertFunction, Scope& scope,
        std::unique_ptr<Type> value);

    /*
     * Private members
     */

    std::stack<Scope*> m_scopeStack;
    std::vector<std::unique_ptr<Scope>> m_scopes;
};

#endif // LAX_SYMBOLTABLE_H
