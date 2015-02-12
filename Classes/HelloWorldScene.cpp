#include "HelloWorldScene.h"

using namespace cocos2d;


CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
		//°×ÆåÏÈ×ß
		operationToDo = WHITE_CHESS_CHO0SE;

		//³õÊ¼»¯chess_Array
		chess_Array = CCArray::create();
		chess_Array->retain();

		activeChess = NULL;
		activeChess_x = 0;
		activeChess_y = 0;

        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

		//±³¾°ÑÕÉ«
		this->initWithColor(ccc4(255,255,255,255));

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		//Ìí¼ÓÌáÊ¾ÎÄ×Ö
		promptInfo = CCLabelTTF::create("","Artial",PROMPT_FONT_SIZE);
		CC_BREAK_IF(!promptInfo);
		promptInfo->retain();
		promptInfo->setColor(ccc3(0,0,0));
		promptInfo->setPosition(ccp(winSize.width/2,winSize.height-15));
		this->addChild(promptInfo);
		promptInfo->setString("white move");

		//¡°restart¡±°´Å¥
		CCLabelTTF* restart = CCLabelTTF::create("restart","Artial",PROMPT_FONT_SIZE);
		CC_BREAK_IF(!restart);
		restart->retain();
		restart->setColor(ccc3(0,0,0));
		CCMenuItemLabel* restartButtom = CCMenuItemLabel::create(restart,this,menu_selector(HelloWorld::menuRestartCallback));
		CC_BREAK_IF(!restartButtom);
		restartButtom->retain();
		restartMenu = CCMenu::create(restartButtom,NULL);
		restartMenu->setPosition(winSize.width/2,15);
		this->addChild(restartMenu);

		//CCSize size = CCDirector::sharedDirector()->getWinSize();

        //add the white chesses
		Chess::addChess(this,chess_Array,CHESS_COLOR_WHITE,1,1);
		Chess::addChess(this,chess_Array,CHESS_COLOR_WHITE,2,1);
		Chess::addChess(this,chess_Array,CHESS_COLOR_WHITE,3,1);
		Chess::addChess(this,chess_Array,CHESS_COLOR_WHITE,4,1);
		Chess::addChess(this,chess_Array,CHESS_COLOR_WHITE,1,2);
		Chess::addChess(this,chess_Array,CHESS_COLOR_WHITE,4,2);

		//Add the black chesses
		Chess::addChess(this,chess_Array,CHESS_COLOR_BLACK,1,3);
		Chess::addChess(this,chess_Array,CHESS_COLOR_BLACK,4,3);
		Chess::addChess(this,chess_Array,CHESS_COLOR_BLACK,1,4);
		Chess::addChess(this,chess_Array,CHESS_COLOR_BLACK,2,4);
		Chess::addChess(this,chess_Array,CHESS_COLOR_BLACK,3,4);
		Chess::addChess(this,chess_Array,CHESS_COLOR_BLACK,4,4);

		/*Chess::deleteChess(this,chess_Array,1,3);
		Chess::moveChess(this,chess_Array,4,4,1,3);*/

		this->setTouchEnabled(true);

        bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
	if(operationToDo==GAMEOVER)
		return;
	CCTouch *touch = (CCTouch*) touches->anyObject();
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	int chess_x = 0;
	int chess_y = 0;
	if(Chess::touchChess(location,chess_x,chess_y))
	{
		switch(operationToDo) 
		{
		case WHITE_CHESS_CHO0SE:
			if(Chess::isChessExist(chess_Array,chess_x,chess_y))
			{
				activeChess = Chess::getChess(chess_Array,chess_x,chess_y);
				activeChess_x = chess_x;
				activeChess_y = chess_y;
				if(activeChess->getChessColor() == CHESS_COLOR_WHITE)
				{
					Chess::chessChose(chess_Array,chess_x,chess_y);
					operationToDo = WHITE_CHESS_DEST;
				}
			}
			break;
		case WHITE_CHESS_DEST:
			if((abs(chess_x - activeChess_x)==1 && chess_y==activeChess_y) || (chess_x==activeChess_x && abs(chess_y - activeChess_y)==1))
			{
				if(!Chess::isChessExist(chess_Array,chess_x,chess_y))
				{
					Chess::chessNoChose(chess_Array,activeChess_x,activeChess_y);
					Chess::moveChess(this,chess_Array,activeChess_x,activeChess_y,chess_x,chess_y);

					//ÅĞ¶ÏÊÇ·ñÉ±ËÀÒ»¸öºÚ×Ó
					//ºáÏòÅĞ¶Ï
					if(Chess::isChessExist(chess_Array,1,chess_y) && Chess::isChessExist(chess_Array,2,chess_y) && Chess::isChessExist(chess_Array,3,chess_y) && !Chess::isChessExist(chess_Array,4,chess_y))
					{
						if(Chess::getChess(chess_Array,1,chess_y)->getChessColor()==CHESS_COLOR_BLACK && Chess::getChess(chess_Array,2,chess_y)->getChessColor()==CHESS_COLOR_WHITE &&  Chess::getChess(chess_Array,3,chess_y)->getChessColor()==CHESS_COLOR_WHITE)
							Chess::deleteChess(this,chess_Array,1,chess_y);
						else if(Chess::getChess(chess_Array,1,chess_y)->getChessColor()==CHESS_COLOR_WHITE && Chess::getChess(chess_Array,2,chess_y)->getChessColor()==CHESS_COLOR_WHITE &&  Chess::getChess(chess_Array,3,chess_y)->getChessColor()==CHESS_COLOR_BLACK)
							Chess::deleteChess(this,chess_Array,3,chess_y);
					}
					else if(!Chess::isChessExist(chess_Array,1,chess_y) && Chess::isChessExist(chess_Array,2,chess_y) && Chess::isChessExist(chess_Array,3,chess_y) && Chess::isChessExist(chess_Array,4,chess_y))
					{
						if(Chess::getChess(chess_Array,2,chess_y)->getChessColor()==CHESS_COLOR_BLACK && Chess::getChess(chess_Array,3,chess_y)->getChessColor()==CHESS_COLOR_WHITE &&  Chess::getChess(chess_Array,4,chess_y)->getChessColor()==CHESS_COLOR_WHITE)
							Chess::deleteChess(this,chess_Array,2,chess_y);
						else if(Chess::getChess(chess_Array,2,chess_y)->getChessColor()==CHESS_COLOR_WHITE && Chess::getChess(chess_Array,3,chess_y)->getChessColor()==CHESS_COLOR_WHITE &&  Chess::getChess(chess_Array,4,chess_y)->getChessColor()==CHESS_COLOR_BLACK)
							Chess::deleteChess(this,chess_Array,4,chess_y);
					}
					//×İÏòÅĞ¶Ï
					if(Chess::isChessExist(chess_Array,chess_x,1) && Chess::isChessExist(chess_Array,chess_x,2) && Chess::isChessExist(chess_Array,chess_x,3) && !Chess::isChessExist(chess_Array,chess_x,4))
					{
						if(Chess::getChess(chess_Array,chess_x,1)->getChessColor()==CHESS_COLOR_BLACK && Chess::getChess(chess_Array,chess_x,2)->getChessColor()==CHESS_COLOR_WHITE &&  Chess::getChess(chess_Array,chess_x,3)->getChessColor()==CHESS_COLOR_WHITE)
							Chess::deleteChess(this,chess_Array,chess_x,1);
						else if(Chess::getChess(chess_Array,chess_x,1)->getChessColor()==CHESS_COLOR_WHITE && Chess::getChess(chess_Array,chess_x,2)->getChessColor()==CHESS_COLOR_WHITE &&  Chess::getChess(chess_Array,chess_x,3)->getChessColor()==CHESS_COLOR_BLACK)
							Chess::deleteChess(this,chess_Array,chess_x,3);
					}
					else if(!Chess::isChessExist(chess_Array,chess_x,1) && Chess::isChessExist(chess_Array,chess_x,2) && Chess::isChessExist(chess_Array,chess_x,3) && Chess::isChessExist(chess_Array,chess_x,4))
					{
						if(Chess::getChess(chess_Array,chess_x,2)->getChessColor()==CHESS_COLOR_BLACK && Chess::getChess(chess_Array,chess_x,3)->getChessColor()==CHESS_COLOR_WHITE &&  Chess::getChess(chess_Array,chess_x,4)->getChessColor()==CHESS_COLOR_WHITE)
							Chess::deleteChess(this,chess_Array,chess_x,2);
						else if(Chess::getChess(chess_Array,chess_x,2)->getChessColor()==CHESS_COLOR_WHITE && Chess::getChess(chess_Array,chess_x,3)->getChessColor()==CHESS_COLOR_WHITE &&  Chess::getChess(chess_Array,chess_x,4)->getChessColor()==CHESS_COLOR_BLACK)
							Chess::deleteChess(this,chess_Array,chess_x,4);
					}
					
					//ÅĞ¶Ï°×ÆåÊÇ·ñÓ®µÃ±ÈÈü
					if(Chess::isWhiteWin(chess_Array))
					{
						operationToDo = GAMEOVER;
						promptInfo->setString("white win");
					}
					else
					{
						operationToDo = BLACK_CHESS_CHOOSE;
						promptInfo->setString("black move");
					}
				}
			}
			break;
		case BLACK_CHESS_CHOOSE:
			if(Chess::isChessExist(chess_Array,chess_x,chess_y))
			{
				activeChess = Chess::getChess(chess_Array,chess_x,chess_y);
				activeChess_x = chess_x;
				activeChess_y = chess_y;
				if(activeChess->getChessColor() == CHESS_COLOR_BLACK)
				{
					Chess::chessChose(chess_Array,chess_x,chess_y);
					operationToDo = BLACK_CHESS_DEST;
				}
			}
			break;
		case BLACK_CHESS_DEST:
			if((abs(chess_x - activeChess_x)==1 && chess_y==activeChess_y) || (chess_x==activeChess_x && abs(chess_y - activeChess_y)==1))
			{
				if(!Chess::isChessExist(chess_Array,chess_x,chess_y))
				{
					Chess::chessNoChose(chess_Array,activeChess_x,activeChess_y);
					Chess::moveChess(this,chess_Array,activeChess_x,activeChess_y,chess_x,chess_y);

					//ÅĞ¶ÏÊÇ·ñÉ±ËÀÒ»¸ö°××Ó
					//ºáÏòÅĞ¶Ï
					if(Chess::isChessExist(chess_Array,1,chess_y) && Chess::isChessExist(chess_Array,2,chess_y) && Chess::isChessExist(chess_Array,3,chess_y) && !Chess::isChessExist(chess_Array,4,chess_y))
					{
						if(Chess::getChess(chess_Array,1,chess_y)->getChessColor()==CHESS_COLOR_WHITE && Chess::getChess(chess_Array,2,chess_y)->getChessColor()==CHESS_COLOR_BLACK &&  Chess::getChess(chess_Array,3,chess_y)->getChessColor()==CHESS_COLOR_BLACK)
							Chess::deleteChess(this,chess_Array,1,chess_y);
						else if(Chess::getChess(chess_Array,1,chess_y)->getChessColor()==CHESS_COLOR_BLACK && Chess::getChess(chess_Array,2,chess_y)->getChessColor()==CHESS_COLOR_BLACK &&  Chess::getChess(chess_Array,3,chess_y)->getChessColor()==CHESS_COLOR_WHITE)
							Chess::deleteChess(this,chess_Array,3,chess_y);
					}
					else if(!Chess::isChessExist(chess_Array,1,chess_y) && Chess::isChessExist(chess_Array,2,chess_y) && Chess::isChessExist(chess_Array,3,chess_y) && Chess::isChessExist(chess_Array,4,chess_y))
					{
						if(Chess::getChess(chess_Array,2,chess_y)->getChessColor()==CHESS_COLOR_WHITE && Chess::getChess(chess_Array,3,chess_y)->getChessColor()==CHESS_COLOR_BLACK &&  Chess::getChess(chess_Array,4,chess_y)->getChessColor()==CHESS_COLOR_BLACK)
							Chess::deleteChess(this,chess_Array,2,chess_y);
						else if(Chess::getChess(chess_Array,2,chess_y)->getChessColor()==CHESS_COLOR_BLACK && Chess::getChess(chess_Array,3,chess_y)->getChessColor()==CHESS_COLOR_BLACK &&  Chess::getChess(chess_Array,4,chess_y)->getChessColor()==CHESS_COLOR_WHITE)
							Chess::deleteChess(this,chess_Array,4,chess_y);
					}
					//×İÏòÅĞ¶Ï
					if(Chess::isChessExist(chess_Array,chess_x,1) && Chess::isChessExist(chess_Array,chess_x,2) && Chess::isChessExist(chess_Array,chess_x,3) && !Chess::isChessExist(chess_Array,chess_x,4))
					{
						if(Chess::getChess(chess_Array,chess_x,1)->getChessColor()==CHESS_COLOR_WHITE && Chess::getChess(chess_Array,chess_x,2)->getChessColor()==CHESS_COLOR_BLACK &&  Chess::getChess(chess_Array,chess_x,3)->getChessColor()==CHESS_COLOR_BLACK)
							Chess::deleteChess(this,chess_Array,chess_x,1);
						else if(Chess::getChess(chess_Array,chess_x,1)->getChessColor()==CHESS_COLOR_BLACK && Chess::getChess(chess_Array,chess_x,2)->getChessColor()==CHESS_COLOR_BLACK &&  Chess::getChess(chess_Array,chess_x,3)->getChessColor()==CHESS_COLOR_WHITE)
							Chess::deleteChess(this,chess_Array,chess_x,3);
					}
					else if(!Chess::isChessExist(chess_Array,chess_x,1) && Chess::isChessExist(chess_Array,chess_x,2) && Chess::isChessExist(chess_Array,chess_x,3) && Chess::isChessExist(chess_Array,chess_x,4))
					{
						if(Chess::getChess(chess_Array,chess_x,2)->getChessColor()==CHESS_COLOR_WHITE && Chess::getChess(chess_Array,chess_x,3)->getChessColor()==CHESS_COLOR_BLACK &&  Chess::getChess(chess_Array,chess_x,4)->getChessColor()==CHESS_COLOR_BLACK)
							Chess::deleteChess(this,chess_Array,chess_x,2);
						else if(Chess::getChess(chess_Array,chess_x,2)->getChessColor()==CHESS_COLOR_BLACK && Chess::getChess(chess_Array,chess_x,3)->getChessColor()==CHESS_COLOR_BLACK &&  Chess::getChess(chess_Array,chess_x,4)->getChessColor()==CHESS_COLOR_WHITE)
							Chess::deleteChess(this,chess_Array,chess_x,4);
					}

					//ÅĞ¶ÏºÚÆåÊÇ·ñÓ®µÃ±ÈÈü
					if(Chess::isBlackWin(chess_Array))
					{
						operationToDo = GAMEOVER;
						promptInfo->setString("black win");
					}
					else
					{
						operationToDo = WHITE_CHESS_CHO0SE;
						promptInfo->setString("white move");
					}
				}
			}
			break;
		default:
			;
		}
	}

}

void HelloWorld::menuRestartCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

