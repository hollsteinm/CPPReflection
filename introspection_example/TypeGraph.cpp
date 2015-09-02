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

void TypeGraph::AddType(long typeId, IType* type) {
	if (idTypeMap.find(typeId) == idTypeMap.cend())
	{
		idTypeMap[typeId] = type;
		nameIdMap[type->GetTypeName()] = typeId;
	}
}

const std::string TypeGraph::GetTypeName(long typeId) {
	if (idTypeMap.find(typeId) != idTypeMap.end())
		return idTypeMap[typeId]->GetTypeName();
	else
		return idTypeMap[0]->GetTypeName();
}

const long TypeGraph::GetTypeId(std::string name) {
	if (nameIdMap.find(name) != nameIdMap.end()){
		return nameIdMap[name];
	}
	else {
		return 0;
	}
}

const IType* TypeGraph::GetType(std::string name) {
	if (nameIdMap.find(name) != nameIdMap.end()){
		return idTypeMap[nameIdMap[name]];
	}
	else {
		return idTypeMap[0];
	}
}

const IType* TypeGraph::GetType(long typeId) {
	if (idTypeMap.find(typeId) != idTypeMap.end())
		return idTypeMap[typeId];
	else
		return idTypeMap[0];
}

TypeGraph::~TypeGraph() {
}