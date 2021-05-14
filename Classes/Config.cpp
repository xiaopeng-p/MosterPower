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
	//name:"����"
	//�����ţ� map["name"] = "����";  ���ʱ��map�����name�� ���滻Ϊ����
	//������ظ��洢�����滻��
	//m_mapDatas[strName] = pDataBaseMgr;
	//insert���ظ�key�ǲ������� map.insert(name,���ģ�   ִ����֮�� map��name��Ӧ��������
	m_mapDatas.insert(pair<string, CDataBaseMgr*>(strName, pDataBaseMgr));
}


