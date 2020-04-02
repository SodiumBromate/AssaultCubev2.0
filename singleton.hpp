#pragma once

//singleton class for addresses etc

template <class c>
class singleton
{
public:
	static c* instance()
	{
		if (!m_instance) { m_instance = new c(); }

		return m_instance;
	}

	virtual ~singleton() { m_instance = nullptr; }
private:
	static c* m_instance;
protected:
	singleton() = default;
};
template <typename c> c* singleton<c>::m_instance = nullptr;

#define SETUP_SINGLETON(classname) friend class singleton<procAndAddr>
