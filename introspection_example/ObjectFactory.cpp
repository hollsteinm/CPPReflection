#include "ObjectFactory.h"

using namespace core;

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

void ObjectFactory::AddDefault(std::string name, Object* obj) {
	if (Graph.find(name) == Graph.end()) {
		Graph[name] = obj;
	}
}

ObjectFactory::~ObjectFactory() {
}

ObjectFactory::ObjectFactory() {
	AddDefault("Object", &Object::StaticInstance());
}