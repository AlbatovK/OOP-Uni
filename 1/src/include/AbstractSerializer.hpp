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
    /// \param structName Name of object to use as title if serialization format requires it
    /// \param entity Entity of generic type T to serialize to string
    /// \return Serialized entity stored in string
    virtual std::string serialize(const T &entity, const std::string &structName) = 0;

    /// Transforming c-style string in some format into generic type object
    /// \param input C-String containing serialized object of generic type T
    /// \return Serialized from input object of generic type T
    virtual T deserialize(const char *input) = 0;

    /// Transforming c-array string in some format into generic type object
    /// \param input C-String without null-terminator at the end storing T type object data
    /// \param size Length of C-String object without counting null-terminator used to process input
    /// \return Serialized from input object of generic type T
    virtual T deserialize(const char *input, const size_t &size) = 0;

    /// Transforming std::string in some format into generic type object
    /// \param input C-String without null-terminator at the end storing T type object data
    /// \return Serialized from input object of generic type T
    virtual T deserialize(const std::string &input) = 0;
};

#endif
