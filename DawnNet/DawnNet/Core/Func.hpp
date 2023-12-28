#pragma once

namespace DawnNet
{
    
	template<typename T> 
	class Singleton
	{
	protected:
		Singleton() = default;
		virtual ~Singleton() = default;
		Singleton(const Singleton&) = delete;
		void operator=(const Singleton&) = delete;
	public:
		static T& Instance()
		{
			static T SSingleton;
			return SSingleton;
		}
	};
    
    /* -------------
        TickCounter for cross-platform
    ----------------*/
 
    typedef unsigned long long int tick64_t;
    typedef unsigned long int tick32_t;
    
    tick32_t XGetTickCount();    
    tick64_t XGetTickCount64();


} // namespace DawnNet
