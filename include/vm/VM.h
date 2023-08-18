#ifndef LAX_VM_H
#define LAX_VM_H

#ifdef DEBUG_TRACE_EXECUTION
#include "common/Debug.h"
#endif

#include "objects/ObjNative.h"
#include "values/Value.h"
#include "vm/Table.h"

#define FRAMES_MAX   64
#define STACK_MAX    (FRAMES_MAX * UINT8_MAX)

// Forward declarations
class AST;
class ObjClosure;
class ObjUpvalue;

/// Enumeration of interpretation result codes
enum InterpretResult {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
};

/// Structure representing a call frame
typedef struct {
    ObjClosure* closure;
    uint8_t* ip;
    Value* slots;
} CallFrame;

/**
 * Virtual Machine that interprets bytecode
 */
class VM {
public:
    /// Class constructor.
    VM();

    /**
     * Compile an Abstract Syntax Tree to bytecode and then run the bytecode
     * generated.
     *
     * @param ast the AST to interpret.
     * @return the interpretation result code.
     */
    InterpretResult interpret(AST& ast);

private:
    /**
     * Execute the bytecode.
     *
     * @return the result code of the interpretation.
     */
    InterpretResult run();

    /**
     * Report an error.
     *
     * @param message the error message.
     */
    static void runtimeError(const std::string& message);

    /**
     * Push a value onto the runtime stack.
     *
     * @param value the value to push.
     */
    void push(Value value);

    /**
     * Pop the topmost value of the runtime stack.
     *
     * @return the value popped of the stack.
     */
    Value pop();

    /**
     * Peek a value at some distance in the runtime stack.
     *
     * @param distance the distance in the stack.
     * @return the value peeked.
     */
    Value peek(int distance);

    /**
     * Create an upvalue for a value in the stack, if it doesn't already exist.
     *
     * The upvalue created is added to the list of opened upvalues, ordered by
     * stack index.
     *
     * @param local the value in the stack to create the upvalue for.
     * @return the upvalue object that points to the value.
     */
    ObjUpvalue* captureUpvalue(Value* local);

    /**
     * Close upvalues in the list of opened upvalues that are above a value in
     * the stack.
     *
     * When leaving a scope, all upvalues used in that scope are closed. Closed
     * upvalues are moved off the stack and saved in the upvalue object itself,
     * so the value can still be accessed outside of its scope.
     *
     * @param last the pointer to value in the stack after which all upvalues
     * must be closed
     */
    void closeUpvalues(Value* last);

    /**
     * Perform a call on a value.
     *
     * @param callee the value called.
     * @param argCount the number of arguments passed to the call.
     * @return true if the call was successful.
     */
    bool callValue(Value callee, int argCount);

    /**
     * Call a function and execute its body.
     *
     * @param closure the closure wrapping the function.
     * @param argCount the number of arguments passed to the call.
     * @return true if the call was successful.
     */
    bool call(ObjClosure* closure, int argCount);

    /**
     * Register a native function in the global scope.
     *
     * @param name the name of the function.
     * @param function the pointer to the native function to call when a call is
     * performed on the name associated.
     */
    void defineNative(const char* name, NativeFn function);

    /*
     * Private members
     */

    CallFrame m_frames[FRAMES_MAX];
    int m_frameCount;

    Value m_stack[STACK_MAX]; // Runtime stack that stores values during execution
    Value* m_stackTop;

    Table m_globals; // Hash table that stores global variables
    ObjUpvalue* m_openUpvalues; // Linked list of upvalues that has been opened
};

#endif //LAX_VM_H
