#ifndef TYPE_H
#define TYPE_H

#include "IType.h"
#include <functional>

namespace core {
	namespace reflection {

		static long MakeTypeHash(std::string constantName) {
			return std::hash<std::string>()(constantName);
		}

		template<typename T>
		struct Type : public IType {
			Type(std::string constantName) :
				name(constantName),
				typeId(MakeTypeHash(constantName))
			{
				TypeGraph::Get().Add(this);
			}

			long GetTypeId() const override { return typeId; }
			std::string GetTypeName() const override { return name; }

			bool IsTypeOf(IType* other) const override {
				return other->GetTypeId() == typeId;
			}

			typedef typename T TYPE;

		private:
			unsigned long typeId;
			std::string name;
		};
	}
}



#endif