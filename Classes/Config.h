#ifndef __CONFIG_H__
#define __CONFIG_H__
#include "cocos2d.h"
#include "DataBase.h"
#include <string>
using namespace std;
class CConfigMgr
{
public:
	static CConfigMgr* getInstance();
	//定义存取两个接口
	CDataBaseMgr* getData(string strName);
	void setData(string strName, CDataBaseMgr* pDataBaseMgr);
private:
	CConfigMgr();
	~CConfigMgr();
	static CConfigMgr* m_spInstance;
	map<string, CDataBaseMgr*> m_mapDatas;
};

#endif // !__CONFIG_H__

