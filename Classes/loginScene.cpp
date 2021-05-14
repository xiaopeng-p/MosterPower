#include "MainMenu.h"
#include "loginScene.h"

CLoginScene::CLoginScene()
{
}
CLoginScene::~CLoginScene()
{

}
bool CLoginScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 ori = Director::getInstance()->getVisibleOrigin();

	

	Sprite* pBg = Sprite::create("image/main_bg.jpg");
	pBg->setPosition(208, 370);
	this->addChild(pBg);

	pName = TextField::create("name","fonts/arial.ttf",30);
	pName->setPosition(Vec2(220, 500));
	this->addChild(pName);

	pPassword = TextField::create("password", "fonts/arial.ttf", 30);
	pPassword->setPosition(Vec2(220, 470));
	pPassword->setPasswordEnabled(true);
	pPassword->setBright(true);
	this->addChild(pPassword);

	

	Label* pLableName = Label::createWithTTF(CGlobal::getInstance()->FontToUTF8("用户名:"), "fonts/simhei.ttf", 30);
	pLableName->setPosition(130, 500);
	pLableName->setAnchorPoint(Vec2(1, 0.5));
	this->addChild(pLableName);

	Label* pLabelpassw = Label::createWithTTF(CGlobal::getInstance()->FontToUTF8("密码:"), "fonts/simhei.ttf", 30);
	pLabelpassw->setPosition(130, 470);
	pLabelpassw->setAnchorPoint(Vec2(1, 0.5));
	this->addChild(pLabelpassw);

	login_btn = Sprite::create("image/login.png");
	register_btn = Sprite::create("image/resign.png");
	login_btn->setPosition(Vec2(ori.x+visibleSize.width / 2, ori.y + visibleSize.height / 2));
	register_btn->setPosition(Vec2(ori.x + visibleSize.width / 2, ori.y + visibleSize.height / 2 - 60));
	this->addChild(login_btn);
	this->addChild(register_btn);

	this->addEventTouch();
	return true;
}


void CLoginScene::login() {
		string uid;
		string pwd;
		uid = pName->getString();
		pwd = pPassword->getString();

		string strid("uname=");
		string strpwd("&upass=");


		string url("http://localhost/login.php?");
		string userid(uid);
		string password(pwd);
		url += strid + userid + strpwd + password;

		HttpClient* client = HttpClient::getInstance();
		HttpRequest* req = new HttpRequest();

		req->setUrl(url.c_str());
		req->setRequestType(HttpRequest::Type::GET);
		req->setResponseCallback(CC_CALLBACK_2(CLoginScene::httpResponse,this));
		client->send(req);
		req->release();
}
void CLoginScene::httpResponse(HttpClient* client, HttpResponse* response)
{
	if (!response->isSucceed())
	{
		log("Receive from server error and the error code is %s\n", response->getErrorBuffer());
		simulatePop("Unable to connect to server");
		return;
	}
	else
	{
		vector<char>* buffer = response->getResponseData();    //...获得返回数据的信息
		char* strtmp = (char*)malloc(sizeof(char) * buffer->size());
		//通过返回值判断是否登录成功
		for (int i = 0; i < buffer->size(); i++)
		{
			strtmp[i] = (*buffer)[i];
			log((*buffer)[i]);
		}
		string analys(strtmp);
		free(strtmp);
		strtmp = NULL;


		if (analys.find("status:ok") < analys.length())
		{ 
			//MessageBox(NULL, (LPCTSTR)TEXT("success"), (LPCTSTR)TEXT("弹窗测试"), MB_OK);
			auto sc = CMainMenu::create();
			Director::getInstance()->replaceScene(sc);
		}
		else
		{
			simulatePop("Login false");
		}
	}
}


void CLoginScene::regist() {
		string uid;
		string pwd;
		auto target = Application::getInstance()->getTargetPlatform();
		if (target == ApplicationProtocol::Platform::OS_WINDOWS) {
			uid = pName->getString();
			pwd = pPassword->getString();
		}
		string strid("uname=");
		string strpwd("&upass=");
		string url("http://localhost/register.php?");
		string userid(uid);
		string password(pwd);
		url += strid + userid + strpwd + password;

		HttpClient* client = HttpClient::getInstance();
		HttpRequest* req = new HttpRequest();

		req->setUrl(url.c_str());
		req->setRequestType(HttpRequest::Type::GET);
		req->setResponseCallback(CC_CALLBACK_2(CLoginScene::httpResponse2,this));
		client->send(req);
		req->release();
}


//注册
void CLoginScene::httpResponse2(HttpClient* client, HttpResponse* response)
{
	if (!response->isSucceed())
	{
		log("Receive from server error and the error code is %s\n", response->getErrorBuffer());
		return;
	}
	else
	{
		vector<char>* buffer = response->getResponseData();    //...获得返回数据的信息
		char* strtmp = (char*)malloc(sizeof(char) * buffer->size());
		//通过返回值判断是否登录成功
		for (int i = 0; i < buffer->size(); i++)
		{
			strtmp[i] = (*buffer)[i];
			log((*buffer)[i]);
		}
		string analys(strtmp);
		free(strtmp);
		strtmp = NULL;
		if (analys.find("status:ok") < analys.length())
		{
			//MessageBox(NULL, (LPCTSTR)TEXT("success"), (LPCTSTR)TEXT("弹窗测试"), MB_OK);   //弹出对话框
			simulatePop("register success");
		}
		else
		{
			//登录失败，数据库中查找不到信息
			//提示：密码或账户错误
			//MessageBox("注册失败", "注册失败！");
			//log("注册失败");
			simulatePop("register failed!");
		}
	}
}

void CLoginScene::simulatePop(string str)
{
	Label* note_txt = Label::createWithTTF(str, "fonts/arial.ttf", 30);
	note_txt->setPosition(Vec2(220, 540));
	this->addChild(note_txt,99,"note");
	//定义动画效果
	Action* action = Sequence::create(
		DelayTime::create(0.5f), FadeOut::create(0.2f),
		CallFuncN::create(CC_CALLBACK_1(CLoginScene::onShowDone, this)),
		NULL);

	note_txt->runAction(action);
}

void CLoginScene::onShowDone(Ref* pRef)
{
	this->getChildByName("note")->removeFromParentAndCleanup(true);
}

void CLoginScene::addEventTouch()
{
	auto pLogin = Rect(144, 343, 128, 53);
	auto pResign = Rect(144, 283, 128, 53);
	EventListenerTouchOneByOne* eventListner = EventListenerTouchOneByOne::create();
	eventListner->onTouchBegan = [=](Touch* touch, Event* event)
	{
		auto location = touch->getLocationInView();
		location = Director::getInstance()->convertToGL(location);
		if (pLogin.containsPoint(location))
		{
			login_btn->setScale(0.7);
		}
		else if (pResign.containsPoint(location))
		{
			register_btn->setScale(0.7);
		}
		return true; // if you are consuming it
	};

	eventListner->onTouchMoved = [=](Touch* touch, Event* event) {

		/*auto location = touch->getLocationInView();
		location = Director::getInstance()->convertToGL(location);
		if (pStart.containsPoint(location))
		{
			pStartGame->setColor(Color3B::RED);
		}
		else if (pSet.containsPoint(location))
		{
			pSetGame->setColor(Color3B::RED);
		}
		else if (pExit.containsPoint(location))
		{
			pExitGame->setColor(Color3B::RED);
		}*/
		//? pStartGame->setColor(Color3B::RED) : nullptr;
	};

	// trigger when you let up
	eventListner->onTouchEnded = [=](Touch* touch, Event* event) {
		auto location = touch->getLocationInView();
		location = Director::getInstance()->convertToGL(location);
		if (pLogin.containsPoint(location))
		{
			login();
		}
		else if (pResign.containsPoint(location))
		{
			regist();
		}
		login_btn->setScale(1);
		register_btn->setScale(1);

		/*auto location = touch->getLocationInView();
		location = Director::getInstance()->convertToGL(location);
		if (pStart.containsPoint(location))
		{
			Director::getInstance()->replaceScene(CGameScene::create());
		}
		else if (pSet.containsPoint(location))
		{
			pSetGame->setColor(Color3B::RED);
		}
		else if (pExit.containsPoint(location))
		{
			pExitGame->setColor(Color3B::RED);*/
		//}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListner, this);
}

