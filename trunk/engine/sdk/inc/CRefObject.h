#pragma once
//------------------------------------------------------------------------------
/**
    @class sqr::CRefObject

	���ü�������.
	1. ���Ը�TRefPointer<T>���ʹ��(��Ҫ����ջ����)
	2. ������ֻ����һ��Ĭ�Ϲ��캯����һ������������
	3. ����������ܽ��п���, �����������ü�������

    (C) 2009 ThreeOGCMan
*/
#ifndef _WIN32
#include <pthread.h>
typedef pthread_mutex_t		HLOCK;
#else
#include <intrin.h>
#endif

#include "TRefPointer.h"
#include "ExpHelper.h"

#ifndef _WIN32
#define DECLARE_REF() \
public: \
	virtual int32	GetRefCount() const; \
	virtual int32	AddRef(); \
	virtual void	Release(); \
	virtual void	SetRefInfo(const string& info); \
	const string&	GetRefInfo(void); \
private: \
	volatile int32 refCount;\
	HLOCK	 m_Lock;\
	string   m_sRefInfo;
#else
#define DECLARE_REF() \
public: \
	virtual int32	GetRefCount() const; \
	virtual int32	AddRef(); \
	virtual void	Release(); \
	virtual void	SetRefInfo(const string& info); \
	const string&	GetRefInfo(void); \
private: \
	volatile int32 refCount;\
	string   m_sRefInfo;
#endif

#define CLEAR_REF_COUNT() refCount = 0;

#define DEFAULT_GETREFCOUNT(classname) \
int32 classname::GetRefCount() const \
{ return this->refCount; }

#define DEFAULT_ADDREF(classname)\
int32 classname::AddRef() \
{ \
	_InterlockedIncrement((volatile long*)&this->refCount); \
	return iRefCount; \
}

#define DEFAULT_RELEASEREF(classname) \
void classname::Release() \
{ \
	Ast(this->refCount > 0); \
	_InterlockedDecrement((volatile long*)&this->refCount); \
	if (0 == this->refCount) \
		delete this; \
}

#define DEFAULT_SETREFINFO(classname)\
void classname::SetRefInfo(const string& info) \
{ \
	m_sRefInfo = info; \
} \
const string& classname::GetRefInfo(void) \
{ \
	return m_sRefInfo; \
} \

namespace sqr
{
class CRefObject
{
	DECLARE_REF();
public:
	//���캯��
	CRefObject() : refCount(0) 
	{
#ifndef _WIN32
		pthread_mutexattr_t attr;

		pthread_mutexattr_init(&attr);
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);

		pthread_mutex_init(&m_Lock, &attr);
		pthread_mutexattr_destroy(&attr);
#endif
	}
protected:
	// ��������
	virtual ~CRefObject();
	virtual void   Free();
private:
	CRefObject(const CRefObject&);
};

//------------------------------------------------------------------------------
inline
int32 CRefObject::GetRefCount() const
{
	return this->refCount;
}

//------------------------------------------------------------------------------
inline
int32 CRefObject::AddRef()
{

#ifndef _WIN32
	pthread_mutex_lock(&m_Lock);
	++this->refCount;
	pthread_mutex_unlock(&m_Lock);
#else
	_InterlockedIncrement((volatile long*)&this->refCount);
#endif
	return this->refCount;
}

//------------------------------------------------------------------------------
inline
void CRefObject::Release()
{
	// string msg = "���ü����쳣, ��������Ѿ����ͷ�" +this->m_sRefInfo;
	// AstMsg(this->refCount > 0, msg);
#ifndef _WIN32
	pthread_mutex_lock(&m_Lock);
	--this->refCount;
	pthread_mutex_unlock(&m_Lock);
#else
	_InterlockedDecrement((volatile long*)&this->refCount);
#endif
	if (0 == this->refCount)
	{
		Free();
	}
}

//------------------------------------------------------------------------------
inline
void CRefObject::SetRefInfo(const string& info)
{
	m_sRefInfo = info;
}

inline 
const string& CRefObject::GetRefInfo(void)
{
	return m_sRefInfo;
}
//------------------------------------------------------------------------------
inline
CRefObject::~CRefObject()
{
	string msg = "���ü����쳣,������ɾ��ʱ��Ϊ0 " + m_sRefInfo;
	AstMsg(0 == this->refCount, msg);
#ifndef _WIN32
	pthread_mutex_destroy(&m_Lock);
#endif
}

inline 
void CRefObject::Free()
{
	delete this;
}

}// namespace sqr
