#ifndef ITYPE_H
#define ITYPE_H

#include <string>

namespace core {
	namespace reflection {
		struct IType {
			virtual ~IType() {}
			virtual long GetTypeId() const = 0;
			virtual bool IsTypeOf(IType* other) const = 0;
			virtual std::string GetTypeName() const = 0;
		};
	}
}

#endif