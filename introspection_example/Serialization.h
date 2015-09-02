#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <iostream>

#define VERSION 0

#define SERIALIZEREAD(C, INSTANCE, ISTREAM) reflect::generated::C##__Class().Read(INSTANCE, ISTREAM, VERSION); 
#define SERIALIZEWRITE(C, INSTANCE, OSTREAM) reflect::generated::C##__Class().Write(INSTANCE, OSTREAM, VERSION);

class Object* Deserialize(std::istream& in);

template<typename T>
T* Deserialize(std::istream& in) {
	return (T*)Deserialize(in);
}

#endif