#include "ObjectFactory.h"
#include "IType.h"
#include "MetaGraph.h"
#include "Object.h"

ObjectFactory* ObjectFactory::__instance;

ObjectFactory& ObjectFactory::Get() {
	if (__instance == nullptr) {
		__instance = new ObjectFactory();
	}
	return *__instance;
}

Object* ObjectFactory::GetDefault(std::string name) {
	if (Graph.find(name) != Graph.end()) {
		return Graph.at(name);
	}
	else {
		return nullptr;
	}
}

Object* ObjectFactory::CreateNew(std::string name) {
	Object* original = GetDefault(name);
	if (original != nullptr) {
		return original->CreateSelf();
	}
	else {
		return NULL;
	}
}

Object* ObjectFactory::GetDefault(unsigned long typeId) {
	auto c = core::reflection::MetaGraph::Get().Get(typeId);
	if (c) {
		return GetDefault(c->GetName());
	}
	else {
		return nullptr;
	}
}

Object* ObjectFactory::CreateNew(unsigned long typeId) {
	auto c = core::reflection::MetaGraph::Get().Get(typeId);
	if (c) {
		return CreateNew(c->GetName());
	}
	else {
		return nullptr;
	}
}

void ObjectFactory::Add(std::string name, Object* obj) {
	if (obj)
	{
		if (Graph.find(name) == Graph.end()) {
			Graph[name] = obj;
		}
	}
}

ObjectFactory::~ObjectFactory() {
}

ObjectFactory::ObjectFactory() {
}