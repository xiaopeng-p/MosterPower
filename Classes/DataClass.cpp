#include "DataClass.h"

void CEnemyDtMgr::parse(Document& doc)
{
	for (int i = 0; i < doc.Size(); i++)
	{
		rapidjson::Value& vEnemyDt = doc[i];
		SEnemyDt* pData = new SEnemyDt();
		pData->nID = vEnemyDt["id"].GetInt();
		pData->nHp = vEnemyDt["hp"].GetInt();
		pData->nAck = vEnemyDt["ack"].GetInt();
		pData->nDef = vEnemyDt["def"].GetInt();
		pData->nMoney = vEnemyDt["money"].GetInt();
		m_vecDatas.push_back(pData);
	}
}
