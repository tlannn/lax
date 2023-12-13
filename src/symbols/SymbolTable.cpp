#include "symbols/SymbolTable.h"
#include "symbols/BuiltInSymbol.h"
#include "symbols/FunSymbol.h"
#include "symbols/VarSymbol.h"
#include "objects/ObjFunction.h"
#include "objects/ObjString.h"
#include "values/PrimitiveType.h"

SymbolTable::SymbolTable() {
    createScope(nullptr); // Create the global scope
    initTypes();
    initNativeFunctions();
}

void SymbolTable::createScope(Scope* previous) {
    auto scope = std::make_unique<Scope>(previous);

    m_scopeStack.push(scope.get());
    m_scopes.push_back(std::move(scope));
}

void SymbolTable::beginScope() {
    createScope(&currentScope());
}

void SymbolTable::endScope() {
    m_scopeStack.pop();
}

Scope& SymbolTable::currentScope() {
    return *m_scopeStack.top();
}

void SymbolTable::initTypes() {
    auto integer = std::make_unique<BuiltInSymbol>(
        ObjString::copyString(PrimitiveType::toString(PrimitiveType::INTEGER)),
        &PrimitiveType::INTEGER
    );
    auto boolean = std::make_unique<BuiltInSymbol>(
        ObjString::copyString(PrimitiveType::toString(PrimitiveType::BOOLEAN)),
        &PrimitiveType::BOOLEAN
    );
    auto string = std::make_unique<BuiltInSymbol>(
        ObjString::copyString(PrimitiveType::toString(PrimitiveType::STRING)),
        &PrimitiveType::STRING
    );

    this->define(currentScope(), std::move(integer));
    this->define(currentScope(), std::move(boolean));
    this->define(currentScope(), std::move(string));
}

void SymbolTable::initNativeFunctions() {
    // Add the native function 'print' to the symbol table
    std::vector<VarSymbol> args;
    args.emplace_back(
        ObjString::copyString("message"), &PrimitiveType::STRING
    );

    auto printFn = std::make_unique<FunSymbol>(
        ObjString::copyString("print"), args, &PrimitiveType::VOID
    );
    define(currentScope(), std::move(printFn));
}

bool SymbolTable::define(Scope& scope, std::unique_ptr<Symbol> symbol) {
    return insert(&Scope::insert, scope, std::move(symbol));
}

Symbol* SymbolTable::lookup(Scope& scope, ObjString* name,
    bool lookupEnclosingScopes) {
    return lookup<Symbol>(&Scope::lookup, scope, name, lookupEnclosingScopes);
}

VarSymbol* SymbolTable::lookupVariable(Scope& scope, ObjString* name,
    bool lookupEnclosingScopes) {
    auto* s = lookup<Symbol>(&Scope::lookup, scope, name, lookupEnclosingScopes);

    return s && s->getSymbolType() == Symbol::Type::VARIABLE
           ? static_cast<VarSymbol*>(s)
           : nullptr;
}

FunSymbol* SymbolTable::lookupFunction(Scope& scope, ObjString* name,
    bool lookupEnclosingScopes) {
    auto* s = lookup<Symbol>(
        &Scope::lookup, scope, name, lookupEnclosingScopes
    );

    return s && s->getSymbolType() == Symbol::Type::FUNCTION
           ? static_cast<FunSymbol*>(s)
           : nullptr;
}

std::shared_ptr<SymbolTable> SymbolTable::instance() {
    static std::shared_ptr<SymbolTable> instance{ new SymbolTable };
    return instance;
}

template<typename Type>
Type* SymbolTable::lookup(LookupFn<Type> lookupFunction, Scope& scope,
    ObjString* name, bool lookupEnclosingScopes) {
    if (!lookupEnclosingScopes)
        return (scope.*lookupFunction)(name);

    for (Scope* s = &scope; s; s = s->enclosingScope()) {
        Type* sym = (s->*lookupFunction)(name);
        if (sym) return sym;
    }

    return nullptr;
}

template<typename Type>
bool SymbolTable::insert(InsertFn<Type> insertFunction, Scope& scope,
    std::unique_ptr<Type> value) {
    auto name = value->getName();
    return (scope.*insertFunction)(name, std::move(value));
}
