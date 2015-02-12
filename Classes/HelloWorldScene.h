#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

//���ƣ�ָʾ��ǰҪ���еĲ���
#define WHITE_CHESS_CHO0SE	1	//ѡ�а���
#define WHITE_CHESS_DEST	2	//�ƶ�����
#define BLACK_CHESS_CHOOSE	3	//ѡ�к���
#define BLACK_CHESS_DEST	4	//�ƶ�����
#define GAMEOVER			0	//��Ϸ����

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

	//"restart"��ť�ص�����
	void menuRestartCallback(CCObject* pSender);

    // a selector callback
    void menuCloseCallback(CCObject* pSender);

	//���ƣ���¼�����еĲ���
	int operationToDo;

	//��¼��ǰ�����ϵ�ȫ������
	CCArray* chess_Array;

	//����ѡ�е�����
	Chess* activeChess;
	//ѡ�����ӵĺ�����λ��
	int activeChess_x;
	//ѡ�����ӵ�������λ��
	int activeChess_y;
	//���־��飬��ʾ�����߻��Ǻ�����
	CCLabelTTF* promptInfo;
	//���ְ�ť�������ʼ��һ��
	CCMenu* restartMenu;

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif  // __HELLOWORLD_SCENE_H__
