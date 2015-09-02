#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <iostream>

namespace core {
	namespace serial {
		struct ISerializable
		{
			virtual bool Read(void* obj, std::istream& in, int version) = 0;
			virtual bool Write(void* obj, std::ostream& out, int version) const = 0;
		};
	}
}

#endif