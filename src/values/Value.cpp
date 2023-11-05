#include "values/Value.h"
#include "values/LaxType.h"
#include "objects/Object.h"
#include "objects/ObjFunction.h"

Value::Value() :
    Value(ValueType::NUL, { .obj = nullptr }) {}

Value::Value(ValueType type, union value v) :
    type(type),
    as(v) {}

Value::Value(ValueType type, Object* object) :
    type(type),
    as({ .obj = object }) {}

Value Value::null() {
    return { ValueType::NUL, nullptr };
}

Value Value::function(ObjFunction* function) {
    return { ValueType::FUNCTION, static_cast<Object*>(function) };
}

Value Value::object(Object* object) {
    return { ValueType::OBJECT, object };
}

Value Value::boolean(bool b) {
    return Value(ValueType::BOOLEAN, { .b = b });
}

Value Value::integer(int i) {
    return Value(ValueType::INTEGER, { .i = i });
}

bool Value::isFalsy(Value value) {
    return IS_NULL(value) ||
           (IS_INT(value) && AS_INT(value) == 0) ||
           (IS_BOOL(value) && !AS_BOOL(value));
}

bool Value::equals(Value a, Value b) {
    if (a.type != b.type) return false;
    ValueType type = a.type;

    switch (type) {
        case NUL:
            return true;
        case BOOLEAN:
            return AS_BOOL(a) == AS_BOOL(b);
        case INTEGER:
            return AS_INT(a) == AS_INT(b);
        default:
            return AS_OBJ(a) == AS_OBJ(b);
    }
}

std::string Value::toString(Value& value) {
    if (IS_NULL(value))
        return "null";

    else if (IS_INT(value))
        return std::to_string(AS_INT(value));

    else if (IS_BOOL(value))
        return AS_BOOL(value) ? "true" : "false";

    return AS_OBJ(value)->toString();
}

Value& Value::operator=(const Value& value) {
    type = value.type;
    as = value.as;

    return *this;
}
