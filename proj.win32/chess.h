#pragma once
#include "cocos2d.h"
using namespace cocos2d;

#define CHESS_COLOR_BLACK 0
#define CHESS_COLOR_WHITE 1
#define CHESS_WIDTH (65)
#define CHESS_HEIGHT (65)
#define CHESS_RADIUS (50)
#define CHESS_DISTANCE (70)//���ӵľ���
#define CHESS_MOVE_DURING_TIME (0.5)//�����ƶ�һ�񻨷ѵ�ʱ��

#define FRAMESIZE_WIDTH (480)
#define	FRAMESIZE_HEIGHT (320)

class Chess :
	public CCSprite
{
public:
	Chess(void);
	Chess(int black_or_white,int x,int y);
	~Chess(void);

	int getChessColor(void);
	int getLocation_x(void);
	int getLocation_y(void);

	void setChessColor(int black_or_white);
	void setLocation_x(int x);
	void setLocation_y(int y);
	
	static bool addChess(CCLayer* layer,CCArray* chessArray,int black_or_white,int x,int y);
	static bool deleteChess(CCLayer* layer,CCArray* chessArray,int x,int y);
	static Chess* getChess(CCArray* chessArray,int x,int y);
	static bool isChessExist(CCArray* chessArray,int x,int y);
	static bool moveChess(CCLayer* layer,CCArray* chessArray,int x_from,int y_from,int x_to,int y_to);

	//�ж��Ƿ����ɰ�������Ӯ��ʤ��
	static bool isWhiteWin(CCArray* chessArray);
	static bool isBlackWin(CCArray* chessArray);
	
	//���CCPoint��Ӧ�ĵ��Ƿ���ĳ�������ڣ�������򷵻�true���������������̵�λ�ø���x��y
	static bool touchChess(const CCPoint touchPoint,int &x,int &y);

	//ѡ��ĳ�����Ӻ��滻������ͼƬ�����������ӱ�ѡ��
	static bool chessChose(CCArray* chessArray,int x,int y);
	static bool chessNoChose(CCArray* chessArray,int x,int y);

private:
	//��־λ�����廹�ǰ���
	int chessColor;
	//�����������꣬���̹��4*4
	int location_x;
	//������������
	int location_y;
};