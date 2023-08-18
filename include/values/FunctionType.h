#ifndef LAX_FUNCTIONTYPE_H
#define LAX_FUNCTIONTYPE_H

#include <vector>

#include "LaxType.h"

/**
 * Function type in Lax. As functions can be considered as values to store in
 * variables, function types can help distinguish different functions.
 */
class FunctionType : public LaxType {
public:
    /**
     * Class constructor.
     * @param returnType a reference to the type of value returned by the
     * function.
     * @param paramTypes a vector of pointers to types, each nth type being the
     * type of the nth parameter of the function.
     */
    FunctionType(const LaxType& returnType, std::vector<LaxType*>&& paramTypes);

    FunctionType(const LaxType& returnType, const std::vector<LaxType*>& paramTypes);

    /**
     * Getter for the type of data expected for each parameter of the function.
     * @return a reference to a vector of pointers to types, corresponding to
     * the ordered parameter types of the function.
     */
    const std::vector<LaxType*>& getParamTypes() const;

    /**
     * Getter for the type of data returned by the function.
     * @return a reference to the type of value returned.
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
