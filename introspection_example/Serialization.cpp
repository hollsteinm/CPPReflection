#include "Serialization.h"
#include "ObjectFactory.h"
#include "Object.h"

Object* Deserialize(std::istream& in) {
	char str[256];
	in.get(str, 256, ' ');
	std::string className(str);
	className.shrink_to_fit();
	int ugc = className.size();
	for (int i = 0; i < ugc; ++i){
		in.unget();
	}

	Object* o = ObjectFactory::Get().CreateNew(className);
	if (o != nullptr) {
		if (o->Read(in)){
			return o;
		}
		else {
			return nullptr;
		}
	}
	else {
		return nullptr;
	}
}