#ifndef REFLECTION_H
#define REFLECTION_H

#include "Types.h"
#include "IProperty.h"
#include "Class.h"
#include "Property.h"
#include "ObjectFactory.h"
#include "Serialization.h"

#define DECLREFLECTION(C) namespace reflect { namespace generated { core::reflection::Class& C##__Class(); } }
#define DEFREFLECTION(C) namespace reflect { namespace generated { core::reflection::Class& C##__Class() { static core::reflection::Class C##__Class(#C, C##__Type.GetTypeId()); return C##__Class; } } }
#define REFLECTION(C) reflect::generated::C##__Class()

#define VERSION 0
#define PROPERTY(C, PropertyTYPE, NAME) REFLECTION(C).AddProperty(#NAME, new core::reflection::Property<C, PropertyTYPE> (#NAME, TYPEOF(PropertyTYPE), &C::NAME));
#define PARENT(CHILD, C) std::vector<core::reflection::IProperty*> prop = REFLECTION(C).GetProperties(); int count = prop.size(); for(int i = 0; i < count; ++i) { REFLECTION(CHILD).AddProperty(prop[i]->GetName(), prop[i]); }

//NO INHERTIANCE
#define CLASSHEAD(C) class C; TYPE(C) DECLREFLECTION(C) 

#define CLASSBODY(C) private: \
	static C C##__static; \
	long instanceId;\
public:\
	static C& StaticInstance() { return C##__static; }\
	virtual C* CreateSelf() const override{\
		return new C();\
	}\
	virtual core::reflection::IProperty* GetProperty(std::string name) const override {\
		return REFLECTION(C).GetProperty(name);\
	}\
	virtual std::vector<core::reflection::IProperty*> GetProperties() const override {\
		return REFLECTION(C).GetProperties();\
	}\
	virtual const std::string GetName() const override {\
		return REFLECTION(C).GetName();\
	}\
	virtual const long GetTypeId() const override {\
		return TYPEOF(C);\
	}\
	virtual bool Write(std::ostream& out) override {\
		return SERIALIZEWRITE(C, this, out)\
	}\
	virtual bool Read(std::istream& in) override {\
		return SERIALIZEREAD(C, this, in)\
	}

#define CLASS(C) CLASSHEAD(C) \
class C : public Object { \
	CLASSBODY(C) \
	C() {\
		PARENT(C, Object)\
		core::ObjectFactory::Get().AddDefault(#C, &C##__static);

#define DEFSTATICCLASS(C) C C::C##__static;

//SINGLE INHERITANCE
#define RCLASS(C, P) CLASSHEAD(C) \
class C : public P { \
	CLASSBODY(C) \
	C() {\
		PARENT(C, P)\
		core::ObjectFactory::Get().AddDefault(#C, &C##__static);
#endif