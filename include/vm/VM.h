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

/**
 * @enum InterpretResult
 * @brief Enumeration of the possible results of the interpretation.
 */
enum InterpretResult {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
};

/**
 * @struct CallFrame
 * @brief Structure representing a call frame.
 *
 * A call frame is used to keep track of the execution of a function. It stores
 * the closure of the function, the instruction pointer, and the stack pointer.
 *
 * The instruction pointer is used to keep track of the instruction to be
 * executed next. The stack pointer is used to keep track of the top of the
 * stack.
 *
 * The call frame is pushed onto the call stack when a function is called, and
 * popped off the call stack when the function returns.
 */
struct CallFrame {
    ObjClosure* closure;
    uint8_t* ip;
    Value* slots;
};

/**
 * @class VM
 * @brief The virtual machine that interprets the bytecode.
 *
 * The virtual machine is stack-based. It has a runtime stack that stores values
 * during the execution of the program. It also has a call stack that stores
 * call frames, which are used to keep track of the execution of functions.
 *
 * The virtual machine also has a global hash table that stores global variables.
 *
 * The virtual machine is responsible for interpreting the bytecode generated
 * from the Abstract Syntax Tree (AST).
 *
 * The virtual machine is also responsible for garbage collection. It is
 * implemented using a mark-and-sweep algorithm.
 */
class VM {
public:
    /**
     * @brief Class constructor.
     *
     * Initializes the virtual machine with an empty call stack and an empty
     * runtime stack. It also initializes the global hash table, and registers
     * the native functions of Lax.
     */
    VM();

    /**
     * @brief Interprets an Abstract Syntax Tree (AST).
     *
     * The AST is first compiled to bytecode, and then the
     * bytecode is interpreted.
     *
     * @param ast The AST to interpret.
     * @return The interpretation result.
     */
    InterpretResult interpret(AST& ast);

private:
    /**
     * @brief Interpret a chunk of bytecode.
     *
     * This function interprets a chunk of bytecode. It is called recursively
     * when a function call is performed. It is also called when a function
     * returns, to continue the execution of the caller function.
     *
     * @return The result code of the interpretation.
     */
    InterpretResult run();

    /**
     * @brief Reports a runtime error.
     *
     * This function is called when an error occurs during the execution of the
     * program to log the error.
     *
     * @param message The error message.
     */
    static void runtimeError(const std::string& message);

    /**
     * @brief Pushes a value onto the runtime stack.
     * @param value The value to push.
     */
    void push(Value value);

    /**
     * @brief Pops the topmost value from the runtime stack.
     * @return The value popped of the stack.
     */
    Value pop();

    /**
     * @brief Peeks a value from the runtime stack.
     *
     * This function retrieves the value at a specific distance from the top of
     * the stack, without removing it. The distance is supplied as a parameter,
     * where a distance of 0 represents the topmost value, 1 represents the
     * second-topmost value, and so on.
     *
     * @param distance The distance from the top of the stack of the value to
     * retrieve.
     * @return The value at the specified distance from the top of the stack.
     * @throws std::out_of_range If the distance specified is greater than or
     * equal to the stack size.
     */
    Value peek(int distance);

    /**
     * @briefs Creates an upvalue for a value in the stack.
     *
     * This function is used to capture a local variable in a closure. The
     * upvalue created for that variable is added to the list of opened upvalues,
     * ordered by stack index.
     *
     * Opened upvalues are upvalues that are still in scope, and are not yet
     * closed.
     *
     * @note The upvalue is not created if the value is already an upvalue.
     *
     * @param local The pointer to the value in the stack.
     * @return The upvalue created.
     */
    ObjUpvalue* captureUpvalue(Value* local);

    /**
     * @brief Closes upvalues in the stack.
     *
     * This function is used to close upvalues in the stack. It is called when
     * leaving a scope, to close all upvalues used in that scope.
     *
     * Upvalues are closed by moving them off the stack and saving them in the
     * upvalue object itself, so the value can still be accessed outside of its
     * scope. The upvalues are moved off the stack by moving the stack pointer.
     *
     * @param last A pointer to the last value to close.
     */
    void closeUpvalues(Value* last);

    /**
     * @brief Calls a function with the given callee and number of arguments.
     *
     * This function is responsible for invoking a function represented by the
     * callee value, passing the specified number of arguments to it. The callee
     * should be a callable object, such as a function or a method, that can be
     * invoked with the given number of arguments.
     *
     * In case the callee is not a callable object, this function returns
     * `false`.
     *
     * The result of the function call is pushed onto the stack.
     *
     * @param callee The value representing the function or method to be called.
     * @param argCount The number of arguments to be passed to the callee.
     *
     * @return `true` if the call was successful, `false` otherwise.
     */
    bool callValue(Value callee, int argCount);

    /**
     * @brief Performs a call on a closure.
     *
     * This function performs a call on a closure. It creates a call frame and
     * pushes it onto the call stack. The call frame contains the closure to
     * call, the instruction pointer, and the stack pointer.
     *
     * The function also checks if the number of arguments passed to the call
     * matches the number of parameters of the function.
     *
     * @param closure The closure to call.
     * @param argCount The number of arguments passed to the call.
     * @return `true` if the call was successful, `false` otherwise.
     */
    bool call(ObjClosure* closure, int argCount);

    /**
     * @brief Registers a Lax native function in the global scope.
     * @param name The name of the function.
     * @param function The pointer to the native function to call when a call is
     * performed on the name associated.
     */
    void defineNative(const char* name, NativeFn function);

    /*
     * Private members
     */

    CallFrame m_frames[FRAMES_MAX]; // Call stack that stores call frames
    int m_frameCount;

    Value m_stack[STACK_MAX];       // Runtime stack
    Value* m_stackTop;

    Table m_globals;                // Global hash table
    ObjUpvalue* m_openUpvalues;     // Linked list of opened upvalues
};

#endif //LAX_VM_H
