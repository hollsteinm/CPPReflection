#ifndef REFLECTION_H
#define REFLECTION_H

#include "Types.h"
#include "IProperty.h"
#include "Class.h"
#include "Property.h"
#include "ObjectFactory.h"
#include "Object.h"
#include "Serialization.h"
#include "MetaGraph.h"

#define VERSION 0
#define PROPERTY(C, PropertyTYPE, NAME) C::StaticClass().Add(new core::reflection::Property<C, PropertyTYPE> (#NAME, &C::NAME));
#define PARENT(CHILD, C) std::vector<core::reflection::IProperty*> prop = C::StaticClass().GetProperties(); int count = prop.size(); for(int i = 0; i < count; ++i) { CHILD::StaticClass().Add(prop[i]); }

//NO INHERTIANCE
#define CLASSHEAD(C) class C; TYPE(C)

#define CLASSBODY(C) private: \
	static C C##__static; \
	long instanceId;\
public:\
	static core::reflection::Class& StaticClass() { static core::reflection::Class C##__class(#C, TYPEOF(C)); return C##__class; } \
	static C& StaticInstance() { C::StaticClass(); return C##__static; }\
	virtual C* CreateSelf() const override{\
		return new C();\
	}\
	virtual core::reflection::IProperty* GetProperty(std::string name) const override {\
		return C::StaticClass().GetProperty(name);\
	}\
	virtual std::vector<core::reflection::IProperty*> GetProperties() const override {\
		return C::StaticClass().GetProperties();\
	}\
	virtual const std::string GetName() const override {\
		return C::StaticClass().GetName();\
	}\
	virtual const long GetTypeId() const override {\
		return TYPEOF(C); \
	}\
	virtual bool Write(std::ostream& out) override {\
		return C::StaticClass().Write(this, out, VERSION);\
	}\
	virtual bool Read(std::istream& in) override {\
		return C::StaticClass().Read(this, in, VERSION);\
	}

#define CLASS(C) CLASSHEAD(C) \
class C : public Object { \
	CLASSBODY(C) \
	C() {\
		PARENT(C, Object)\
		ObjectFactory::Get().Add(#C, &C##__static);

#define DEFSTATICCLASS(C) C C::C##__static;

//SINGLE INHERITANCE
#define RCLASS(C, P) CLASSHEAD(C) \
class C : public P { \
	CLASSBODY(C) \
	C() {\
		PARENT(C, P)\
		ObjectFactory::Get().Add(#C, &C##__static);
#endif