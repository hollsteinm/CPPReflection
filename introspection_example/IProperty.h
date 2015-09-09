#ifndef IPROPERTY_H
#define IPROPERTY_H

#include <string>
#include "Meta.h"

namespace core {
	namespace reflection {

		struct IProperty : public Meta {
			IProperty(std::string name, unsigned long typeId);

			virtual void* Get(void* obj) const = 0;
			virtual void Set(void* obj, void* value) = 0;

			virtual ~IProperty();
		};
	}
}

#endif