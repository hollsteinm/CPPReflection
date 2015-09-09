#ifndef TYPEGRAPH_H
#define TYPEGRAPH_H

#include <map>

namespace core {
	namespace reflection {
		struct IType;

		class TypeGraph {
		public:
			static TypeGraph& Get();

			TypeGraph(const TypeGraph& rhs) = delete;
			TypeGraph& operator = (const TypeGraph & rhs) = delete;

			void Add(IType* type);

			const IType* Get(unsigned long typeId) const;

			~TypeGraph();

		private:
			TypeGraph();

			static TypeGraph* __instance;
			std::map<long, IType*> idTypeMap;
		};
	}
}
#endif