#ifndef ABSTRACT_VALIDATOR_HPP

#define ABSTRACT_VALIDATOR_HPP

template <class T>
class AbstractValidator {

    public:

        virtual void validate(T entity) = 0;

        virtual ~AbstractValidator() {}

};

#endif
