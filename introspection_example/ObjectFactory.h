#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <string>
#include <map>
#include "Object.h"

namespace core {
	class ObjectFactory {
	public:
		static ObjectFactory& Get();

		Object* GetDefault(std::string name);
		Object* CreateNew(std::string name);

		void AddDefault(std::string name, Object* obj);

		~ObjectFactory();

		ObjectFactory(const ObjectFactory& rhs) = delete;
		ObjectFactory& operator = (const ObjectFactory & rhs) = delete;

	private:
		ObjectFactory();

		static ObjectFactory* __instance;
		std::map<std::string, Object*> Graph;
	};
}

#endif