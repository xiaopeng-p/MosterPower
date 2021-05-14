#include "Global.h"

CGlobal* CGlobal::m_pInstance = nullptr;
CGlobal::CGlobal()
{
	m_pGameScene = NULL;

	m_pGameLayer = NULL;

	m_pControlLayer = NULL;

	m_pGameMap = NULL;
	m_pPlayInfo = NULL;
	m_pEnemyMgr = NULL;
	m_pHero = NULL;
	//m_pFight = NULL;
	//新游戏，当前地图层数为0
	m_nCurrentLevel = 0;
	m_nPreLevel = 0;

	//勇士出生位置
	heroSpawnTileCoord = Point(192, 32);
}

CGlobal::~CGlobal()
{
}

CGlobal* CGlobal::getInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new CGlobal();
	}
	return m_pInstance;
}

char* CGlobal::FontToUTF8(const char* font)
{
	int len = MultiByteToWideChar(CP_ACP, 0, font, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, font, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr)delete[] wstr;
	return str;
}

void CGlobal::updateLevel()
{
	m_nPreLevel = m_nCurrentLevel;
}
