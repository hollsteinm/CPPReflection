#include "MetaGraph.h"
#include "Class.h"

using namespace core;
using namespace reflection;

MetaGraph* MetaGraph::__instance;

MetaGraph::MetaGraph() {

}

MetaGraph& MetaGraph::Get() {
	if (__instance == nullptr){
		__instance = new MetaGraph();
	}
	return *__instance;
}

void MetaGraph::Add(Meta* Class) {
	if (Class) {
		unsigned long typeId = Class->GetTypeId();
		if (Classes.find(typeId) == Classes.end()){
			Classes[typeId] = Class;
		}
	}
}

const Meta* MetaGraph::Get(unsigned long typeId) const {
	if (Classes.find(typeId) != Classes.end()) {
		return Classes.at(typeId);
	}
	else {
		return nullptr;
	}
}

const Meta* MetaGraph::Get(std::string name) const {
	for (auto C : Classes) {
		if (C.second->GetName() == name) {
			return C.second;
		}
	}
	return nullptr;
}