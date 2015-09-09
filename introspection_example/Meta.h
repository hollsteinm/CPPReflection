#ifndef META_H
#define META_H

#include "ISerializable.h"
#include <string>

namespace core {
	namespace reflection {
		struct Meta : public core::serial::ISerializable {
			Meta(std::string name, unsigned long typeId);

			virtual ~Meta();

			Meta(const Meta& rhs) = delete;
			Meta& operator = (const Meta & rhs) = delete;

			const std::string GetName() const;
			const long GetTypeId() const;

			virtual bool Read(void* obj, std::istream& in, int version) override;
			virtual bool Write(void* obj, std::ostream& out, int version) const override;

		private:
			std::string name;
			unsigned long typeId;
		};
	}
}

#endif