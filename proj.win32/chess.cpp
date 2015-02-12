#include "chess.h"


Chess::Chess(void)
{
	chessColor = CHESS_COLOR_BLACK;
	location_x = 0;
	location_y = 0;
}

//参数：black_or_white	限定为CHESS_COLOR_BLACK 或 CHESS_COLOR_WHITE，表示黑棋或白旗
//		x				表示横向第几个棋子
//		y				表示纵向第几个棋子（遵循openGL坐标系规则）
Chess::Chess(int black_or_white,int x,int y)
{
	this->chessColor = black_or_white;
	this->location_x = x;
	this->location_y = y;

	//设定棋子的位置
	int realLocat_x = (FRAMESIZE_WIDTH - CHESS_DISTANCE*3)/2 + (this->location_x - 1)*CHESS_DISTANCE;
	int realLocat_y = (FRAMESIZE_HEIGHT - CHESS_DISTANCE*3)/2 + (this->location_y - 1)*CHESS_DISTANCE;
	this->setPosition(ccp((float)realLocat_x,(float)realLocat_y));

	//添加棋子贴图
	if(black_or_white == CHESS_COLOR_BLACK)
	{

		this->initWithFile("black_chess.png",CCRectMake(0, 0, CHESS_WIDTH, CHESS_HEIGHT));
	}
	else if(black_or_white == CHESS_COLOR_WHITE)
	{
		this->initWithFile("white_chess.png",CCRectMake(0, 0, CHESS_WIDTH, CHESS_HEIGHT));
	}
}

bool Chess::addChess(CCLayer* layer,CCArray* chessArray,int black_or_white,int x,int y)
{
	if(isChessExist(chessArray,x,y))
		return false;
	Chess* pChess = new Chess(black_or_white,x,y);
	if(!pChess)return false;
	//将创建的棋子对象加入棋子数组里面
	chessArray->addObject(pChess);
	//将棋子添加到图层中
	layer->addChild(pChess, 0);
	return true;
}

bool Chess::deleteChess(CCLayer* layer,CCArray* chessArray,int x,int y)
{
	if(!isChessExist(chessArray,x,y))
		return false;
	Chess* chessToDelete = getChess(chessArray,x,y);
	chessArray->removeObject(chessToDelete);
	layer->removeChild(chessToDelete);
	return true;
}

Chess* Chess::getChess(CCArray* chessArray,int x,int y)
{
	Chess* pChess = NULL;
	for(unsigned int i = 0;i<chessArray->count();i++)
	{
		Chess* pChessN = (Chess*)chessArray->objectAtIndex(i);
		if(pChessN->getLocation_x() == x && pChessN->getLocation_y() == y)
		{
			pChess = pChessN;
			break;
		}
	}
	return pChess;
}

bool Chess::isChessExist(CCArray* chessArray,int x,int y)
{
	for(unsigned int i = 0;i<chessArray->count();i++)
	{
		Chess* pChessN = (Chess*)chessArray->objectAtIndex(i);
		if(pChessN->getLocation_x() == x && pChessN->getLocation_y() == y)
			return true;
	}
	return false;
}

bool Chess::moveChess(CCLayer* layer,CCArray* chessArray,int x_from,int y_from,int x_to,int y_to)
{
	if(!isChessExist(chessArray,x_from,y_from))
		return false;
	if(isChessExist(chessArray,x_to,y_to))
		return false;
	Chess* chessToMove = getChess(chessArray,x_from,y_from);

	//画面上棋子精灵的移动
	int destX = (FRAMESIZE_WIDTH - CHESS_DISTANCE*3)/2 + (x_to - 1)*CHESS_DISTANCE;
	int destY = (FRAMESIZE_HEIGHT - CHESS_DISTANCE*3)/2 + (y_to - 1)*CHESS_DISTANCE;

	CCFiniteTimeAction* actionMove = CCMoveTo::create((float)CHESS_MOVE_DURING_TIME, ccp(destX, destY));
	chessToMove->runAction(CCSequence::create(actionMove,NULL));
	
	//更新棋子对象信息
	chessToMove->setLocation_x(x_to);
	chessToMove->setLocation_y(y_to);
	return true;
}

bool Chess::touchChess(const CCPoint touchPoint,int &x,int &y)
{
	int touch_x = touchPoint.x;
	int touch_y = touchPoint.y;
	for(int i=1;i<5;i++)
	{
		for(int j=1;j<5;j++)
		{
			int chess_x = (FRAMESIZE_WIDTH - CHESS_DISTANCE*3)/2 + (i - 1)*CHESS_DISTANCE;
			int chess_y = (FRAMESIZE_HEIGHT - CHESS_DISTANCE*3)/2 + (j - 1)*CHESS_DISTANCE;
			if((touch_x - chess_x)*(touch_x - chess_x) + (touch_y - chess_y)*(touch_y - chess_y) < CHESS_RADIUS*CHESS_RADIUS)
			{
				x = i;
				y = j;
				return true;
			}
		}
	}
	return false;
}

//查看某一格是否能放置棋子：如果该位置超出范围或已有棋子，则不能放置新的棋子，返回false
bool canPutChess(CCArray* chessArray,int x,int y)
{
	if(x<1 || x>4 || y<1 || y>4)
		return false;
	if(Chess::isChessExist(chessArray,x,y))
		return false;
	return true;
}

//如果有至少一个黑子存在且可以移动，那么白棋就没有赢
bool Chess::isWhiteWin(CCArray* chessArray)
{
	for(unsigned int i = 0;i<chessArray->count();i++)
	{
		Chess* pChessN = (Chess*)chessArray->objectAtIndex(i);
		if(pChessN->getChessColor()==CHESS_COLOR_BLACK)
		{
			int loc_x = pChessN->getLocation_x();
			int loc_y = pChessN->getLocation_y();
			if(canPutChess(chessArray,loc_x-1,loc_y) || canPutChess(chessArray,loc_x+1,loc_y) || canPutChess(chessArray,loc_x,loc_y-1) || canPutChess(chessArray,loc_x,loc_y+1))
				return false;
		}
	}
	return true;
}

bool  Chess::chessChose(CCArray* chessArray,int x,int y)
{
	if(!isChessExist(chessArray,x,y)) return false;
	Chess* chess = getChess(chessArray,x,y);
	if(chess->getChessColor() == CHESS_COLOR_BLACK)
	{
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("black_chess_chose.png");
		chess->setTexture(texture);
	}
	else if(chess->getChessColor() == CHESS_COLOR_WHITE)
	{
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("white_chess_chose.png");
		chess->setTexture(texture);
	}
	return true;
}

bool  Chess::chessNoChose(CCArray* chessArray,int x,int y)
{
	if(!isChessExist(chessArray,x,y)) return false;
	Chess* chess = getChess(chessArray,x,y);
	if(chess->getChessColor() == CHESS_COLOR_BLACK)
	{
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("black_chess.png");
		chess->setTexture(texture);
	}
	else if(chess->getChessColor() == CHESS_COLOR_WHITE)
	{
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("white_chess.png");
		chess->setTexture(texture);
	}
	return true;
}

bool Chess::isBlackWin(CCArray* chessArray)
{
	for(unsigned int i = 0;i<chessArray->count();i++)
	{
		Chess* pChessN = (Chess*)chessArray->objectAtIndex(i);
		if(pChessN->getChessColor()==CHESS_COLOR_WHITE)
		{
			int loc_x = pChessN->getLocation_x();
			int loc_y = pChessN->getLocation_y();
			if(canPutChess(chessArray,loc_x-1,loc_y) || canPutChess(chessArray,loc_x+1,loc_y) || canPutChess(chessArray,loc_x,loc_y-1) || canPutChess(chessArray,loc_x,loc_y+1))
				return false;
		}
	}
	return true;
}

int Chess::getChessColor(void)
{
	return chessColor;
}

int Chess::getLocation_x(void)
{
	return location_x;
}

int Chess::getLocation_y(void)
{
	return location_y;
}

void Chess::setChessColor(int black_or_white)
{
	chessColor = black_or_white;
}

void Chess::setLocation_x(int x)
{
	location_x = x;
}

void Chess::setLocation_y(int y)
{
	location_y = y;
}

Chess::~Chess(void)
{
}