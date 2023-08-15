#include "symbols/Scope.h"
#include "symbols/FunSymbol.h"
#include "symbols/VarSymbol.h"

Scope::Scope(Scope *previous) : m_previous(previous) {}

bool Scope::insert(ObjString *name, std::unique_ptr<Symbol> symbol) {
    return insert(m_symbols, name, std::move(symbol));
}

Symbol* Scope::lookup(ObjString *name) {
    return lookup(m_symbols, name);
}

bool Scope::isGlobalScope() const {
    return !m_previous;
}

bool Scope::isLocalScope() const {
    return m_previous;
}

Scope* Scope::enclosingScope() const {
    return m_previous;
}

template<typename Type>
Type* Scope::lookup(
    std::unordered_map<ObjString*, std::unique_ptr<Type>> &map,
    ObjString *name
) {
    auto it = map.find(name);

    if (it == map.end()) return nullptr;

    return it->second.get();
}

template<typename Type>
bool Scope::insert(
    std::unordered_map<ObjString*, std::unique_ptr<Type>> &map,
    ObjString *name, std::unique_ptr<Type> value
) {
    // Don't insert if a symbol with the same name exists
    if (map.find(name) != map.end())
        return false;

    map.emplace(std::make_pair(name, std::move(value)));

    return true;
}
