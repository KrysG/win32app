#ifndef _SINGLETON_H_
#define _SINGLETON_H_
#include <assert.h>

template<class C>
class Singleton
{

public:
	static C* Create()
	{
		Singleton<C>::m_currentInstance = ::new C;
		return Singleton<C>::m_currentInstance;
	}
	static void Destroy()
	{
		delete Singleton<C>::m_currentInstance;
	}
	static C* GetInstance()
	{
		
		return m_currentInstance;
	}

protected:
	static C* m_currentInstance;


};

#define DefineSingleton(C) C* Singleton<C>::m_currentInstance = 0;

#endif // _SINGLETON_H_