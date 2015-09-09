#ifndef TYPES_H
#define TYPES_H

#include "TypeGraph.h"
#include "IType.h"
#include "Type.h"

namespace core{
	namespace reflection{
		template<typename T>
		inline const IType& GetType() {
			static const Type<T> TT("null");
			return TT;
		}
	}
}

#define TYPE(X) namespace core { namespace reflection { template<> inline const IType& GetType<X>() { static const Type<X> TT(#X); return TT; } } }
#define TYPEOF(X) core::reflection::GetType<X>().GetTypeId()
#define TYPENAME(X) core::reflection::GetType<X>().GetTypeName()


TYPE(void)
TYPE(int)
TYPE(long)
TYPE(char)
TYPE(bool)
TYPE(float)
TYPE(double)

namespace core
{
	__forceinline static const core::reflection::IType* GetType(unsigned long typeId) { return core::reflection::TypeGraph::Get().Get(typeId); }
	__forceinline static const std::string GetName(unsigned long typeId) { return core::reflection::TypeGraph::Get().Get(typeId)->GetTypeName(); }
}

#endif