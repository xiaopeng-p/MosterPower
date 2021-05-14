#ifndef __DATABASE_H__
#define __DATABASE_H__
#include <string>
#include <vector>
#include <map>
#include "cocos2d.h"

#include "json/document.h"
#include "json/rapidjson.h"
using namespace std;
USING_NS_CC;
using namespace rapidjson;
struct SDataBase
{
	SDataBase()
	{
		nID = 0;
	}
	virtual ~SDataBase() {}

	int nID;
};

class CDataBaseMgr
{
public:
	CDataBaseMgr();
	virtual ~CDataBaseMgr();
	virtual void loadFile(const string& strPath);
	//´¿Ðéº¯Êý
	virtual void parse(Document& doc) = 0;
	SDataBase* getDataByID(const int& nID);
	int getSize();
	SDataBase* getDataByIndex(int nIndex);
	vector<SDataBase*>& getAllData();
protected:
	vector<SDataBase*> m_vecDatas;

};

#endif // ! __DATABASE_H__

