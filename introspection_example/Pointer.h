#ifndef POINTER_H
#define POINTER_H

#include "Object.h"

template<typename T>
class ObjectPtr {
public:
	ObjectPtr() {
		Pointer = nullptr;
	}

	~ObjectPtr() {
	}

	bool IsValid() const {
		return Pointer != nullptr;
	}

	T* const Get() const {
		return (T*)Pointer;
	}

	void Set(T* NewValue) {
		Pointer = (Object*)NewValue;
	}

	friend std::ostream& operator<<(std::ostream& out, ObjectPtr<T>& self) {
		if (self.IsValid())
		{
			self.Pointer->Write(out);
		}
		return out;
	}

	friend std::istream& operator>>(std::istream& in, ObjectPtr<T>& self) {
		if (!self.IsValid())
		{
			self.Set(new T());
		}
		self.Pointer->Read(in);
		return in;
	}
private:
	Object* Pointer;

protected:
};

#endif