#include "IProperty.h"
#include "Meta.h"

using namespace core;
using namespace reflection;

IProperty::IProperty(std::string name, long typeId) :
	Meta(name, typeId)
{}

IProperty::~IProperty() {

}