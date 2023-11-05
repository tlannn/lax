#ifndef LAX_FUNCTIONTYPE_H
#define LAX_FUNCTIONTYPE_H

#include <vector>

#include "LaxType.h"

/**
 * @class FunctionType
 * @brief Class representing the type of a function.
 *
 * This class is used to represent the type of a function in Lax. It is used to
 * distinguish functions from other types of values, and to perform type checking.
 *
 * A function type is defined by the type of data returned by the function, and
 * the type of data expected for each parameter of the function.
 */
class FunctionType : public LaxType {
public:
    /**
     * @brief Class constructor.
     *
     * Creates a function type given the type of data returned by the function,
     * and the type of data expected for each parameter of the function.
     *
     * @param returnType The type of value returned by the function.
     * @param paramTypes A vector of pointers to types, corresponding to the
     * ordered parameter types of the function.
     */
    FunctionType(const LaxType& returnType, std::vector<LaxType*>&& paramTypes);

    /**
     * @brief Class constructor.
     *
     * Creates a function type given the type of data returned by the function,
     * and the type of data expected for each parameter of the function.
     *
     * @param returnType The type of value returned by
     * the function.
     * @param paramTypes A vector of pointers to types, corresponding to the
     * ordered parameter types of the function.
     */
    FunctionType(const LaxType& returnType, const std::vector<LaxType*>& paramTypes);

    /**
     * @brief Retrieves the type of data expected for each parameter of the
     * function.
     * @return A constant reference to a vector of pointers to types,
     * corresponding to the ordered parameter types of the function.
     */
    const std::vector<LaxType*>& getParamTypes() const;

    /**
     * @brief Retrieves the type of data returned by the function.
     * @return The type of data returned.
     */
    const LaxType& getReturnType() const;

    /**
     * @copydoc LaxType::toString()
     */
    std::string toString() const override;

private:
    /**
     * @copydoc LaxType::equals(const LaxType&)
     */
    bool equals(const LaxType& type) const override;

private:
    const std::vector<LaxType*> m_params;
    const LaxType& m_returnType;
};

#endif // LAX_FUNCTIONTYPE_H
