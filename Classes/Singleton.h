#ifndef _SINGLETON_H
#define _SINGLETON_H

template <class T>
class Singleton
{
public:
	//��ȡ���Ψһʵ��
	static inline T* getInstance();
	//�ͷ����Ψһʵ��
	void release();
protected:
	Singleton(void){}
	~Singleton(void){}
	static T* _instance;
};

template <class T>
inline T* Singleton<T>::getInstance()
{
	if(!_instance)
		_instance = new T;
	return _instance;
}

template <class T>
void Singleton<T>::release()
{
	if (!_instance)
		return;
	delete _instance;
	_instance = 0;
}

//cpp�ļ�����Ҫ��������̬����
#define DECLARE_SINGLETON_MEMBER(_Ty)	\
	template <> _Ty* Singleton<_Ty>::_instance = NULL;

#endif//_SINGLETON_H
