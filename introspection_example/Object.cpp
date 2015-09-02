#include "Object.h"
#include "IProperty.h"
#include "Serialization.h"
#include "Property.h"

namespace reflect {
	namespace generated {
		core::reflection::Class& Object__Class() {
			static core::reflection::Class Object__Class("Object", Object__Type.GetTypeId());
			return Object__Class;
		}
	}
}

Object Object::Object__static;

Object& Object::StaticInstance() {
	return Object__static;
}

//////////////////////////////////////////
//Must be overriden by inherited classes//
//////////////////////////////////////////
Object* Object::CreateSelf() const {
	return new Object();
}

core::reflection::IProperty* Object::GetProperty(std::string name) const {
	return reflect::generated::Object__Class().GetProperty(name);
}

std::vector<core::reflection::IProperty*> Object::GetProperties() const {
	return reflect::generated::Object__Class().GetProperties();
}

const std::string Object::GetName() const {
	return reflect::generated::Object__Class().GetName();
}

const long Object::GetTypeId() const {
	return reflect::generated::Object__Type.GetTypeId();
}

bool Object::Write(std::ostream& out) {
	return reflect::generated::Object__Class().Write(this, out, VERSION);
}

bool Object::Read(std::istream& in) {
	return reflect::generated::Object__Class().Read(this, in, VERSION);
}
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////

Object::Object() {
	instanceId = ++Instances;
	reflect::generated::Object__Class().AddProperty("instanceId", new core::reflection::Property<Object, long>("instanceId", core::GetTypeId("long"), &Object::instanceId));
}

bool Object::InstanceOf(Object* other) {
	return other->instanceId == instanceId;
}

const core::reflection::IType* Object::GetType() {
	return core::reflection::TypeGraph::Get().GetType(GetTypeId());
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