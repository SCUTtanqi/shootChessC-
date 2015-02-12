#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

//令牌，指示当前要进行的操作
#define WHITE_CHESS_CHO0SE	1	//选中白棋
#define WHITE_CHESS_DEST	2	//移动白棋
#define BLACK_CHESS_CHOOSE	3	//选中黑棋
#define BLACK_CHESS_DEST	4	//移动黑棋
#define GAMEOVER			0	//游戏结束

#define PROMPT_FONT_SIZE (22)

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

#include "chess.h"
	
class HelloWorld : public cocos2d::CCLayerColor
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
	virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);

	//"restart"按钮回调函数
	void menuRestartCallback(CCObject* pSender);

    // a selector callback
    void menuCloseCallback(CCObject* pSender);

	//令牌，记录待进行的操作
	int operationToDo;

	//记录当前棋盘上的全部棋子
	CCArray* chess_Array;

	//触屏选中的棋子
	Chess* activeChess;
	//选中棋子的横坐标位置
	int activeChess_x;
	//选中棋子的纵坐标位置
	int activeChess_y;
	//文字精灵，显示白棋走还是黑棋走
	CCLabelTTF* promptInfo;
	//文字按钮，点击开始新一局
	CCMenu* restartMenu;

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif  // __HELLOWORLD_SCENE_H__
