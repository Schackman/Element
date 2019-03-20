#pragma once

namespace elm
{
	namespace sys
	{
		class ISystem
		{
		public:
			virtual ~ISystem() = default;
		protected:
			virtual void Init() = 0;
			virtual void Update(float deltaTime);
			virtual void ShutDown() = 0;
		private:
		};

		inline void ISystem::Update(float deltaTime)
		{
		}
	}
}
