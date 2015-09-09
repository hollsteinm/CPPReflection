#include "TypeGraph.h"
#include "IType.h"

using namespace core;
using namespace reflection;

TypeGraph* TypeGraph::__instance;

TypeGraph::TypeGraph() {

}

TypeGraph& TypeGraph::Get() {
	if (__instance == nullptr){
		__instance = new TypeGraph();
	}
	return *__instance;
}

void TypeGraph::Add(IType* type) {
	if (idTypeMap.find(type->GetTypeId()) == idTypeMap.cend())
	{
		idTypeMap[type->GetTypeId()] = type;
	}
}


const IType* TypeGraph::Get(unsigned long typeId) const {
	if (idTypeMap.find(typeId) != idTypeMap.end()) {
		return idTypeMap.at(typeId);
	}
	else {
		return nullptr;
	}
}

TypeGraph::~TypeGraph() {
}