#include "DataBase.h"

CDataBaseMgr::CDataBaseMgr()
{
}

CDataBaseMgr::~CDataBaseMgr()
{
	for (SDataBase* pData : m_vecDatas) {
		CC_SAFE_DELETE(pData);
	}
	m_vecDatas.clear();
}

void CDataBaseMgr::loadFile(const string& strPath)
{
	//获取全路径
	string strFullPath = FileUtils::getInstance()->fullPathForFilename(strPath);
	//获取该文件内容
	string strData = FileUtils::getInstance()->getStringFromFile(strFullPath);
	//解析strData
	Document doc;
	doc.Parse(strData.c_str());
	this->parse(doc);
	doc.Clear();
}

SDataBase* CDataBaseMgr::getDataByID(const int& nID)
{
	for (SDataBase* pData : m_vecDatas)
	{
		if (pData->nID == nID)
		{
			return pData;
		}
	}
	return nullptr;
}

int CDataBaseMgr::getSize()
{
	return m_vecDatas.size();
}

SDataBase* CDataBaseMgr::getDataByIndex(int nIndex)
{
	if (nIndex < 0 || nIndex > m_vecDatas.size() - 1)
	{
		return nullptr;
	}
	return m_vecDatas[nIndex];
}

vector<SDataBase*>& CDataBaseMgr::getAllData()
{
	return m_vecDatas;
}
