#include "Object.h"
#include "IProperty.h"
#include "Serialization.h"
#include "Property.h"
#include "ObjectFactory.h"

Object Object::Object__static;

Object& Object::StaticInstance() {
	Object::StaticClass();
	return Object__static;
}

core::reflection::Class& Object::StaticClass() {
	static core::reflection::Class Object__class("Object", TYPEOF(Object));
	return Object__class;
}

//////////////////////////////////////////
//Must be overriden by inherited classes//
//////////////////////////////////////////
Object* Object::CreateSelf() const {
	return new Object();
}

core::reflection::IProperty* Object::GetProperty(std::string name) const {
	return Object::StaticClass().GetProperty(name);
}

std::vector<core::reflection::IProperty*> Object::GetProperties() const {
	return Object::StaticClass().GetProperties();
}

const std::string Object::GetName() const {
	return Object::StaticClass().GetName();
}

const long Object::GetTypeId() const {
	return TYPEOF(Object);
}

bool Object::Write(std::ostream& out) {
	return Object::StaticClass().Write(this, out, VERSION);
}

bool Object::Read(std::istream& in) {
	return Object::StaticClass().Read(this, in, VERSION);
}
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////

Object::Object() {
	instanceId = ++Instances;
	ObjectFactory::Get().Add("Object", &Object__static);
	Object::StaticClass().Add(new core::reflection::Property<Object, long>("instanceId", &Object::instanceId));
}

bool Object::InstanceOf(Object* other) {
	return other->instanceId == instanceId;
}

const core::reflection::IType* Object::GetType() {
	return core::reflection::TypeGraph::Get().Get(GetTypeId());
}

std::ostream& operator<<(std::ostream& out, Object& self) {
	self.Write(out);
	return out;
}

std::istream& operator>>(std::istream& in, Object& self) {
	self.Read(in);
	return in;
}

Object::~Object(){

}