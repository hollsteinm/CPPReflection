#ifndef PROPERTY_H
#define PROPERTY_H

#include "IProperty.h"

namespace core {
	namespace reflection {
		template<typename C, typename P>
		struct Property : public IProperty {
			Property(std::string name, long typeId, P C::*property) :
				IProperty(name, typeId),
				property(property)
			{}

			void* Get(void* obj) const override {
				P ret = InternalGet(*(C*)obj);
				P* ptr = &ret;
				return (void*)ptr;
			}

			void Set(void* obj, void* value) override {
				return InternalSet(*(C*)obj, *(P*)value);
			}

			virtual bool Read(void* obj, std::istream& in, int version) override {
				if (IProperty::Read(obj, in, version)) {
					P v;
					in >> v;
					InternalSet(*(C*)obj, v);
					return true;
				}
				else {
					return false;
				}
			}

			virtual bool Write(void* obj, std::ostream& out, int version) const override {
				if (IProperty::Write(obj, out, version)) {
					P v = InternalGet(*(C*)obj);
					out << v << ' ';
					return true;
				}
				else {
					return false;
				}
			}

		protected:
			P InternalGet(C& obj) const {
				return obj.*property;
			}

			void InternalSet(C& obj, P value) {
				obj.*property = value;
			}

		private:
			P C::*property;
		};
	}
}

#endif