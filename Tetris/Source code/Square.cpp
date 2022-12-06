#include "Square.h"
_Square::_Square(float X, float Y, float WIDHT, float LENGHT, int NR)
	: x(X), y(Y), width(WIDHT), length(LENGHT), layout(), nr(NR)
{
	pozicijos[0] = x + length;
	pozicijos[1] = y + width;
	pozicijos[2] = 1.0f;
	pozicijos[3] = 1.0f;
	pozicijos[4] = x - length;
	pozicijos[5] = y - width;
	pozicijos[6] = 0.0f;
	pozicijos[7] = 0.0f;
	pozicijos[8] = x - length;
	pozicijos[9] = y + width;
	pozicijos[10] = 0.0f;
	pozicijos[11] = 1.0f;
	pozicijos[12] = x + length;
	pozicijos[13] = y - width;
	pozicijos[14] = 1.0f;
	pozicijos[15] = 0.0f;
	
	layout.Push<float>(2);
	layout.Push<float>(2);
}

_Square::_Square(const _Square & temp)
	: x(temp.x), y(temp.y), width(temp.width), length(temp.length), layout(temp.layout), nr(temp.nr)
{
	pozicijos[0] = x + length;
	pozicijos[1] = y + width;
	pozicijos[2] = 1.0f;
	pozicijos[3] = 1.0f;
	pozicijos[4] = x - length;
	pozicijos[5] = y - width;
	pozicijos[6] = 0.0f;
	pozicijos[7] = 0.0f;
	pozicijos[8] = x - length;
	pozicijos[9] = y + width;
	pozicijos[10] = 0.0f;
	pozicijos[11] = 1.0f;
	pozicijos[12] = x + length;
	pozicijos[13] = y - width;
	pozicijos[14] = 1.0f;
	pozicijos[15] = 0.0f;
}

void _Square::_Draw(Shader &shader, Renderer &renderer)
{
	VertexArray va;
	VertexBuffer vb(pozicijos, 4 * 4 * sizeof(float));
	va.AddBuffer(vb, layout);
	IndexBuffer ib(indices, 6);
	renderer.Draw(va, ib, shader);
}

void _Square::Move(float x, float y)
{
	pozicijos[0] += x;
	pozicijos[1] += y;
	pozicijos[4] += x;
	pozicijos[5] += y;
	pozicijos[8] += x;
	pozicijos[9] += y;
	pozicijos[12] += x;
	pozicijos[13] += y;
}

void _Square::MoveA(float x, float y)
{
	pozicijos[0] = x + length;
	pozicijos[1] = y + width;
	pozicijos[4] = x - length;
	pozicijos[5] = y - width;
	pozicijos[8] = x - length;
	pozicijos[9] = y + width;
	pozicijos[12] = x + length;
	pozicijos[13] = y - width;
}

unsigned int _Square::indices[] =
{
	0, 2, 3,
	1, 2, 3
};