#pragma once
#include <unordered_map>

namespace Crystal {
	namespace Core {
		template<typename T>
		class Pool {
		public:
			std::unordered_map<std::string, T> m_PoolItems;
			
			//Pool& CreateItem
		private:
		};
	}
}