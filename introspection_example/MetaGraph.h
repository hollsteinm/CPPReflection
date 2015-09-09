#ifndef MetaGraph_H
#define MetaGraph_H

#include <map>

namespace core
{
	namespace reflection
	{
		class MetaGraph
		{
		public:
			static MetaGraph& Get();
			~MetaGraph();

			void Add(struct Meta* Class);

			const Meta* Get(unsigned long typeId) const;
			const Meta* Get(std::string name) const;

		private:
			static MetaGraph* __instance;
			MetaGraph();

			std::map<long, Meta*> Classes;
		};
	}
}

#endif