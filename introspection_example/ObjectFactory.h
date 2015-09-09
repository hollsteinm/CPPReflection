#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <string>
#include <map>

class ObjectFactory {
public:
	static ObjectFactory& Get();

	class Object* GetDefault(std::string name);
	class Object* CreateNew(std::string name);

	class Object* GetDefault(unsigned long typeId);
	class Object* CreateNew(unsigned long typeId);

	void Add(std::string name, class Object* obj);

	~ObjectFactory();

	ObjectFactory(const ObjectFactory& rhs) = delete;
	ObjectFactory& operator = (const ObjectFactory & rhs) = delete;

private:
	ObjectFactory();

	static ObjectFactory* __instance;
	std::map<std::string, class Object*> Graph;
};

#endif