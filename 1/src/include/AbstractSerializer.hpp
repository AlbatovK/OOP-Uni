#ifndef ABSTRACT_SERIALIZER_HPP

#define ABSTRACT_SERIALIZER_HPP 

#include <string>

/**
 * \authors Konstantin Albatov
 * \date 04.09.2024 4:19
 * \version 1.0
 * Base Generic Serializer Interface, used for transforming objects into string format and vice versa
 * Contains prototypes of various serialization/deserialization functions
 */
template<class T>
class AbstractSerializer {
public:
    virtual ~AbstractSerializer() = default;

    /// Serializing generic type object into string with title of structName
    virtual std::string serialize(const T &, const std::string &structName) = 0;

    /// Transforming c-style string in some format into generic type object
    virtual T deserialize(const char *) = 0;

    /// Transforming c-array string in some format into generic type object
    virtual T deserialize(const char *, const size_t &) = 0;

    /// Transforming std::string in some format into generic type object
    virtual T deserialize(const std::string &) = 0;
};

#endif
