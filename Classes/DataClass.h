#ifndef __DATACLASS_H__
#define __DATACLASS_H__
#include "DataBase.h"
struct SEnemyDt :public SDataBase 
{
	int nHp;
	int nAck;
	int nDef;
	int nMoney;
};

class CEnemyDtMgr :public CDataBaseMgr
{
public:
	virtual void parse(Document& doc);
};

#endif // !__DATACLASS_H__

