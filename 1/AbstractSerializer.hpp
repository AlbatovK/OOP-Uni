#ifndef ABSTRACT_SERIALIZER_HPP

#define ABSTRACT_SERIALIZER_HPP 

#include <string>

template <class T> 
class AbstractSerializer {
    
    public:
        
        virtual std::string serialize(T, std::string structName) = 0;
        
        virtual T deserialize(const char *) = 0;

        virtual T deserialize(const char *, size_t) = 0;
        
        virtual T deserialize(std::string) = 0;

};

#endif