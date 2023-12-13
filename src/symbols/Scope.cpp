#include "symbols/Scope.h"
#include "objects/ObjString.h"
#include "symbols/Symbol.h"

Scope::Scope(Scope* previous) :
    m_previous(previous), m_firstEntry(nullptr), m_lastEntry(nullptr) {}

bool Scope::insert(const ObjString* name, std::unique_ptr<Symbol> symbol) {
    // Don't insert if a symbol with the same name exists
    if (m_symbols.find(name) != m_symbols.end())
        return false;

    // Create a new entry for the value
    const auto entry = new Entry {
        .symbol = std::move(symbol),
        .previous = m_lastEntry
    };

    // Update pointers to entries
    if (m_lastEntry)
        m_lastEntry->next = entry;
    if (!m_firstEntry)
        m_firstEntry = entry;
    m_lastEntry = entry;

    return m_symbols.emplace(name, std::unique_ptr<Entry>(entry)).second;
}

Symbol* Scope::lookup(const ObjString* name) const {
    const auto it = m_symbols.find(name);
    return it == m_symbols.end() ? nullptr : it->second->symbol.get();
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
