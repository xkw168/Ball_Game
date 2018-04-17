#include "stdafx.h"

Ball::Ball(int x1, int y1)
{
	init(x1, y1);
}


Ball::~Ball()
{

}

void Ball::init(int x1, int y1)
{
	x = x1;
	y = y1;
	r = 20;
	score = 0;
	olddirection = LEFT;
	step = 10;
}

void Ball::draw()
{
	fillcircle(x, y, r);
}

void Ball::move()
{
	switch (olddirection)
	{
	case UP://��������
		y -= step;
		break;
	case DOWN:
		y += step;
		break;
	case LEFT:
		x -= step;
		break;
	case RIGHT:
		x += step;
	}
}

void Ball::changeDirection(int newdirection)
{
	if (((olddirection == UP) && (newdirection == DOWN)) ||
		((olddirection == DOWN) && (newdirection == UP)) ||
		((olddirection == RIGHT) && (newdirection == LEFT)) ||
		((olddirection == LEFT) && (newdirection == RIGHT)))
	{
		// do nothing
	}
	else
	{
		olddirection = newdirection;
	}
}

int Ball::checkState(Ball *ball, Dot *dot)
{
	double distance;
	//��͹��ӵľ���
	distance = sqrt((x - dot->getX())*(x - dot->getX()) + (y - dot->getY())*(y - dot->getY()));
	if (distance <= r + dot->getR())//�Ե�����
	{
		return EAT;
	}
	//������֮��ľ���
	distance = sqrt((x - ball->getX())*(x - ball->getX()) + (y - ball->getY())*(y - ball->getY()));
	if (distance <= r + ball->getR())//ײ����һ����
	{
		return HIT_BALL;
	}
	if (x < r || x > GRAPH_WIDE - r || y < r || y > GRAPH_HIGH - r)//ײǽ
	{
		return HIT_WALL;
	}
	return KEEP;//ʲô��û�з���
}

int Ball::getX()
{
	return x;
}

int Ball::getY()
{
	return y;
}

int Ball::getR()
{
	return r;
}

int Ball::getScore()
{
	return score;
}

void Ball::eat(int dot)
{
	score += dot;//��������
	r += dot;//����
}