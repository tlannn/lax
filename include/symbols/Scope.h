#ifndef LAX_SCOPE_H
#define LAX_SCOPE_H

#include <memory>
#include <unordered_map>

#define MAP(type) std::unordered_map<ObjString*, std::unique_ptr<type>>

// Forward declarations
class ObjFunction;
class ObjString;
class Symbol;
class FunSymbol;
class VarSymbol;
class Variable;

class Scope {
public:
    /**
     * Class constructor.
     * @param previous a pointer to the enclosing scope. By default it is a null
     * pointer, meaning the scope is the top-level scope.
     */
	explicit Scope(Scope *previous = nullptr);

    /**
     * Add a symbol to the scope.
     * @param name a pointer to the name of the symbol.
     * @param symbol a unique_ptr to the symbol to add.
     * @return true if the insertion was successful, false otherwise.
     */
    bool insert(ObjString *name, std::unique_ptr<Symbol> symbol);

    /**
     * Lookup a symbol in the scope.
     * @param name a pointer to the name of the symbol to lookup.
     * @return a pointer to the symbol if found, or a null pointer.
     */
    Symbol* lookup(ObjString *name);

    /**
     * Check if the scope is declared global, i.e it is the top-level scope.
     * @return true if the scope is global, false otherwise.
     */
    bool isGlobalScope() const;

    /**
     * Check if the scope is declared local, i.e it has an enclosing scope.
     * @return true if the scope is local, false otherwise.
     */
    bool isLocalScope() const;

    /**
     * Return the enclosing scope of the current scope.
     * @return a pointer to the enclosing scope, or a null pointer if the
     * current scope doesn't have any.
     */
    Scope* enclosingScope() const;

private:
    /**
     * Lookup a symbol by its name in a map object of the current scope.
     * @tparam Type the type of symbol to search.
     * @param map a reference to the map object where to search the symbol.
     * @param name the name of the symbol to lookup.
     * @return a pointer to the symbol if found, or a null pointer.
     */
    template<typename Type>
    Type* lookup(MAP(Type) &map, ObjString *name);

    /**
     * Insert a symbol in a map object of the current scope.
     * @tparam Type the type of symbol to insert.
     * @param map a reference to the map object where to insert the symbol.
     * @param name the name of the symbol to insert.
     * @param value a unique_ptr to symbol to insert.
     * @return true if the insertion was successful, false otherwise.
     */
    template<typename Type>
    bool insert(MAP(Type) &map, ObjString *name, std::unique_ptr<Type>
        value);

    /*
     * Private members
     */

	Scope *m_previous;
    MAP(Symbol) m_symbols;
};

#undef MAP_TYPE

#endif //LAX_SCOPE_H
