#ifndef TYPE_H
#define TYPE_H

#include "IType.h"

namespace core {
	namespace reflection {
		static long typeidInstance = 0;

		template<typename T>
		struct Type : public IType {
			Type(const std::string name) :
				name(name)
			{
				typeId = typeidInstance++;
				TypeGraph::Get().AddType(typeId, this);
			}

			long GetTypeId() const override { return typeId; }
			virtual const std::string GetTypeName() const override { return name; }

			bool IsTypeOf(IType* other) const override {
				return other->GetTypeId() == typeId;
			}

			typedef typename T TYPE;

		private:
			long typeId;
			const std::string name;
		};
	}
}



#endif