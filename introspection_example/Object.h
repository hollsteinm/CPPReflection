#ifndef OBJECT_H
#define OBJECT_H

#include "Types.h"
#include "Class.h"

static long Instances = 0;

class Object;
TYPE(Object)

class Object {
private:
	static Object Object__static;
	long instanceId;

public:
	static Object& StaticInstance();
	static core::reflection::Class& StaticClass();

	//////////////////////////////////////////
	//Must be overriden by inherited classes//
	//////////////////////////////////////////
	virtual Object* CreateSelf() const;
	virtual core::reflection::IProperty* GetProperty(std::string name) const;
	virtual std::vector<core::reflection::IProperty*> GetProperties() const;
	virtual const std::string GetName() const;
	virtual const long GetTypeId() const;

	virtual bool Write(std::ostream& out);
	virtual bool Read(std::istream& in);
	//////////////////////////////////////////
	//////////////////////////////////////////
	//////////////////////////////////////////

	Object();

	bool InstanceOf(Object* other);
	const core::reflection::IType* GetType();

	friend std::ostream& operator<<(std::ostream& out, Object& self);
	friend std::istream& operator>>(std::istream& in, Object& self);

	virtual ~Object();
};
#endif