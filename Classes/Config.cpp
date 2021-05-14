#include "Config.h"

CConfigMgr* CConfigMgr::m_spInstance = nullptr;
CConfigMgr::~CConfigMgr()
{
}
CConfigMgr::CConfigMgr()
{
}

CConfigMgr* CConfigMgr::getInstance()
{
	if (!m_spInstance)
	{
		m_spInstance = new CConfigMgr();
	}
	return m_spInstance;
}

CDataBaseMgr* CConfigMgr::getData(string strName)
{
	if (strName=="")
	{
		return nullptr;
	}
	map<string, CDataBaseMgr*>::iterator iter = m_mapDatas.find(strName);
	return iter->second;
}

void CConfigMgr::setData(string strName, CDataBaseMgr* pDataBaseMgr)
{
	if (strName.empty() || !pDataBaseMgr)
	{
		return;
	}
	//name:"张三"
	//中括号： map["name"] = "李四";  这个时候map里面的name会 被替换为李四
	//如果有重复存储，会替换。
	//m_mapDatas[strName] = pDataBaseMgr;
	//insert有重复key是不操作。 map.insert(name,李四）   执行完之后 map的name对应还是张三
	m_mapDatas.insert(pair<string, CDataBaseMgr*>(strName, pDataBaseMgr));
}


