#pragma once
#include "cocos2d.h"
using namespace cocos2d;

#define CHESS_COLOR_BLACK 0
#define CHESS_COLOR_WHITE 1
#define CHESS_WIDTH (65)
#define CHESS_HEIGHT (65)
#define CHESS_RADIUS (50)
#define CHESS_DISTANCE (70)//棋子的距离
#define CHESS_MOVE_DURING_TIME (0.5)//棋子移动一格花费的时间

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

	//判断是否是由白棋或黑棋赢得胜利
	static bool isWhiteWin(CCArray* chessArray);
	static bool isBlackWin(CCArray* chessArray);
	
	//检测CCPoint对应的点是否在某个棋子内，如果是则返回true，并将棋子在棋盘的位置赋给x和y
	static bool touchChess(const CCPoint touchPoint,int &x,int &y);

	//选中某个棋子后替换该棋子图片，表明该棋子被选中
	static bool chessChose(CCArray* chessArray,int x,int y);
	static bool chessNoChose(CCArray* chessArray,int x,int y);

private:
	//标志位：黑棋还是白旗
	int chessColor;
	//横向棋盘坐标，棋盘规格：4*4
	int location_x;
	//纵向棋盘坐标
	int location_y;
};