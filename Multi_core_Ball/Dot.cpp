#include "stdafx.h"

Dot::Dot(int radius)
{
	r = radius;
	x = GRAPH_WIDE - r;//ȡx��ȡֵ��Χ����ֹ������ǽ��
	y = GRAPH_HIGH - r;
	x = rand() % x;
	y = rand() % y;
}

Dot::~Dot()
{
}

void Dot::draw() 
{
	setfillcolor(LIGHTRED);//������ͬ��ɫƻ��
	setlinecolor(LIGHTRED);
	fillcircle(x, y, r);
	setfillcolor(CYAN);//����apple��Ҫ����ɫ�ָ���ԭʼ����
	setlinecolor(CYAN);
}

void Dot::change()
{
	x = GRAPH_WIDE - 3 * r;//����x��ȡֵ��Χ����ֹ��ǽ̫������Ӧ������
	y = GRAPH_HIGH - 3 * r;
	x = rand() % x;
	y = rand() % y;
	r = (rand() % 3) + 5;//ÿһ�ι��ӵĴ�С���
}

int Dot::getX()
{
	return x;
}

int Dot::getY()
{
	return y;
}

int Dot::getR()
{
	return r;
}