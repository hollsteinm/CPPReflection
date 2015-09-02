// introspection_example.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Reflection.h"
#include <sstream>

/**Examples below (inline class definitions)*/
CLASS(ChildObject)
		PROPERTY(ChildObject, int, aNumber);
		aNumber = 13;
	}

	~ChildObject(){

	}

	void SetNumber(int value) { aNumber = value; }
	int GetNumber() const { return aNumber; }

protected:
	int aNumber;
};

DEFREFLECTION(ChildObject)
DEFSTATICCLASS(ChildObject)

RCLASS(GrandChildObject, ChildObject)
		PROPERTY(GrandChildObject, float, aValue);
		PROPERTY(GrandChildObject, Object, inner);
		aValue = 13.45f;
		aNumber = 1337;
		inner = Object();
	}

private:
	float aValue;
	Object inner;
};

DEFREFLECTION(GrandChildObject)
DEFSTATICCLASS(GrandChildObject)

void MagicHandleDemo();

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << Object::StaticInstance().GetName() << std::endl;

	std::vector<core::reflection::IProperty*> properties = Object::StaticInstance().GetProperties();
	int count = properties.size();
	for (int i = 0; i < count; ++i)
	{
		std::cout << properties[i]->GetName() << std::endl;
	}

	std::cout << std::endl;
	std::cout << ChildObject::StaticInstance().GetName() << std::endl;

	properties = ChildObject::StaticInstance().GetProperties();
	count = properties.size();
	for (int i = 0; i < count; ++i)
	{
		std::cout << properties[i]->GetName() << " is a(n) " << core::GetTypeName(properties[i]->GetTypeId()) << std::endl;
	}

	std::cout << std::endl;
	std::cout << GrandChildObject::StaticInstance().GetName() << std::endl;

	properties = core::ObjectFactory::Get().GetDefault("GrandChildObject")->GetProperties();
	count = properties.size();
	for (int i = 0; i < count; ++i)
	{
		std::cout << properties[i]->GetName() << " is a(n) " << core::GetTypeName(properties[i]->GetTypeId()) << std::endl;
	}

	std::cout << std::endl;
	std::cout << "Brand New GrandChildObject - Stringified" << std::endl;
	std::stringstream output;
	GrandChildObject* newPtr = (GrandChildObject*)core::ObjectFactory::Get().CreateNew("GrandChildObject");
	newPtr->Write(output);
	std::cout << output.str() << std::endl;
	std::cout << "Now print it using << operators" << std::endl;
	std::cout << *newPtr << std::endl;

	std::cout << std::endl;
	std::cout << ChildObject::StaticInstance().GetName() << " - Serialized" << std::endl;

	std::stringstream stream;
	ChildObject* toserialize = new ChildObject();
	toserialize->SetNumber(1234567);
	SERIALIZEWRITE(ChildObject, toserialize, stream)

	std::cout << stream.str() << std::endl;
	std::cout << std::endl;
	std::cout << ChildObject::StaticInstance().GetName() << " - Deserialized" << std::endl;

	ChildObject* tocreate = Deserialize<ChildObject>(stream);
	if (tocreate != nullptr){

		properties = tocreate->GetProperties();
		count = properties.size();
		for (int i = 0; i < count; ++i)
		{
			std::cout << properties[i]->GetName() << " is a(n) " << core::GetTypeName(properties[i]->GetTypeId()) << std::endl;
		}

		auto prop = tocreate->GetProperty("aNumber");
		if (prop != NULL) {
			long value = *(long*)prop->Get(tocreate);

			std::cout << std::endl;
			std::cout << value;
		}
	}

	std::cout << std::endl;
	MagicHandleDemo();

	std::cout << std::endl;
	std::cout << "Operators" << std::endl;
	std::cout << *tocreate << std::endl;

	delete toserialize;
	delete tocreate;
	stream.flush();

	return 0;
}

struct IHandler {
	virtual bool Handles(long typeId) = 0;
	virtual void Handle(void* obj) = 0;
};

template<typename T>
struct AHandler : public IHandler {
	void Handle(void* obj) override {
		InnerHandle(*(T*)obj);
	}

protected:
	virtual void InnerHandle(T& msg) = 0;
};

class ObjectHandler : public AHandler < Object > {
public:
	virtual bool Handles(long typeId) override {
		return typeId == TYPEOF(Object);
	}

protected:
	virtual void InnerHandle(Object& msg) override {
		std::cout << "Handling an Object: " << msg.GetName();
	}
};

class ChildObjectHandler : public AHandler < ChildObject > {
public:
	virtual bool Handles(long typeId) override {
		return typeId == TYPEOF(ChildObject);
	}

protected:
	virtual void InnerHandle(ChildObject& msg) override {
		std::cout << "Handling a ChildObject: " << msg.GetName() << "/" << msg.GetNumber();
	}
};

class GrandChildObjectHandler : public AHandler < GrandChildObject > {
public:
	virtual bool Handles(long typeId) override {
		return typeId == TYPEOF(GrandChildObject);
	}

protected:
	virtual void InnerHandle(GrandChildObject& msg) override {
		std::cout << "Handling a GrandChildObject: " << msg.GetName() << "/" << msg.GetNumber();
	}
};

void MagicHandleDemo() {
	std::vector<IHandler*> handlers;
	handlers.push_back(new ObjectHandler());
	handlers.push_back(new ChildObjectHandler());
	handlers.push_back(new GrandChildObjectHandler());

	ChildObject co;
	co.SetNumber(42);

	std::stringstream ss;
	co.Write(ss);

	Object* handled = Deserialize(ss);
	for (unsigned int i = 0; i < handlers.size(); ++i){
		if (handlers[i]->Handles(core::GetTypeId(handled->GetName()))){
			handlers[i]->Handle(handled);
		}
	}

	delete handled;
	for (unsigned int i = 0; i < handlers.size(); ++i){
		delete handlers[i];
	}	
}