#ifndef ABSTRACT_VALIDATOR_HPP

#define ABSTRACT_VALIDATOR_HPP

/**
 * \authors Konstantin Albatov
 * \date 04.09.2024 4:19
 * \version 1.0
 * Base Generic Validator Interface, used for validating object or string data before serialization/deserialization
 * Contains prototype of a supposed validation function throwing ValidationExceptions
 */
template<class T>
class AbstractValidator {
public:
    /// Validate object properties before data transforming and mapping
    virtual void validate(const T &entity) = 0;

    virtual ~AbstractValidator() = default;
};

#endif
