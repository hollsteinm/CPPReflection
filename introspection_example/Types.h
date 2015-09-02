#ifndef TYPES_H
#define TYPES_H

#include "TypeGraph.h"
#include "IType.h"
#include "Type.h"

#define TYPE(X) namespace reflect { namespace generated { static const core::reflection::Type<X> X##__Type(#X); } }
#define TYPEOF(X) reflect::generated::X##__Type.GetTypeId()
#define TYPENAME(X) reflect::generated::X##__Type.GetTypeName()
#define GETTYPE(X) reflect::generated::X##__Type


TYPE(void)
TYPE(int)
TYPE(long)
TYPE(char)
TYPE(bool)
TYPE(float)
TYPE(double)

namespace core {
	__forceinline static std::string GetTypeName(long typeId) { return core::reflection::TypeGraph::Get().GetTypeName(typeId); }
	__forceinline static long GetTypeId(std::string name) { return core::reflection::TypeGraph::Get().GetTypeId(name); }
	__forceinline static const core::reflection::IType* GetType(std::string name) { return core::reflection::TypeGraph::Get().GetType(name); }
	__forceinline static const core::reflection::IType* GetType(long typeId) { return core::reflection::TypeGraph::Get().GetType(typeId); }
}

#endif