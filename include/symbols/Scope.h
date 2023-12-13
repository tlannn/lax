#ifndef LAX_SCOPE_H
#define LAX_SCOPE_H

#include <memory>
#include <unordered_map>

// Forward declarations
class ObjFunction;
class ObjString;
class Symbol;
class FunSymbol;
class VarSymbol;
class Variable;

/**
 * @class Scope
 * @brief Represents a scope in Lax.
 *
 * A scope is a representation of a lexical scope in Lax. It is used to store
 * information about the scope, such as its symbols and enclosing scope.
 *
 * A scope is represented as a map object, where the key is the name of the
 * symbol and the value is an entry that holds a pointer to the symbol. The
 * benefit on wrapping the symbol in an entry is that it allows us to keep track
 * of the order of insertion of the symbols in the scope.
 */
class Scope {
public:
    /**
     * @brief Class constructor.
     *
     * Constructs a scope with a given enclosing scope.
     *
     * @param previous (optional) A pointer to the enclosing scope.
     *
     * @note The default value for the parameter is a null pointer, which means
     *       that the scope is global.
     */
    explicit Scope(Scope* previous = nullptr);

    /**
     * @brief Inserts a symbol in the scope.
     *
     * This function inserts a symbol in the scope. If the symbol already exists
     * in the scope, the insertion fails and the function returns `false`.
     *
     * @param name The name of the symbol to be inserted.
     * @param symbol A unique_ptr to the symbol to be inserted.
     * @return `true` if the insertion was successful, `false` otherwise.
     */
    bool insert(const ObjString* name, std::unique_ptr<Symbol> symbol);

    /**
     * @brief Searches for a given object name in the scope.
     *
     * This function performs a lookup operation to find the given object name
     * in the scope. It searches for a matching object in the scope and returns
     * it if found.
     *
     * @param name The name of the object to be searched for.
     * @return A pointer to the found object if it exists, otherwise returns
     * nullptr.
     */
    Symbol* lookup(const ObjString* name) const;

    /**
     * @brief Checks if the current scope is a global scope.
     *
     * This function checks if the current scope is a global scope, i.e it
     * doesn't have an enclosing scope.
     *
     * @return `true` if the current scope is a global scope, `false` otherwise.
     */
    bool isGlobalScope() const;

    /**
     * @brief Checks if the current scope is a local scope.
     *
     * This function checks if the current scope is a local scope, i.e it has an
     * enclosing scope.
     *
     * @return `true` if the current scope is a local scope, `false` otherwise.
     */
    bool isLocalScope() const;

    /**
     * @brief Returns the enclosing scope of the current scope.
     *
     * This function returns the enclosing scope of the current scope. If the
     * current scope doesn't have an enclosing scope, it returns a null pointer.
     *
     * @return A pointer to the enclosing scope, or a nullptr if the current
     * scope doesn't have an enclosing scope.
     */
    Scope* enclosingScope() const;

private:
    /**
     * @struct Entry
     * @brief Represents an entry in the scope.
     *
     * An entry in the scope is a representation of a symbol in the scope. It
     * contains a pointer to the symbol, and pointers to the previous and next
     * entries in the scope.
     */
    struct Entry {
        std::unique_ptr<Symbol> symbol;
        Entry* previous;
        Entry* next;
    };

    /*
     * Private members
     */

    std::unordered_map<const ObjString*, std::unique_ptr<Entry>> m_symbols;
    Scope* m_previous;
    Entry* m_firstEntry;
    Entry* m_lastEntry;
};

#endif //LAX_SCOPE_H
