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

			void AddType(long typeId, IType* type);

			const std::string GetTypeName(long typeId);
			const long GetTypeId(std::string name);
			const IType* GetType(std::string name);
			const IType* GetType(long typeId);

			~TypeGraph();

		private:
			TypeGraph();

			static TypeGraph* __instance;
			std::map<long, IType*> idTypeMap;
			std::map<std::string, long> nameIdMap;
		};
	}
}
#endif