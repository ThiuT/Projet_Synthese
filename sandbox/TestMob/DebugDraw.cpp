/* DebugDraw.cpp

  Copyright (C) 2010 Allen Jordan

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  Allen Jordan allen.jordan@gmail.com
*/

#include "DebugDraw.h"

DebugDraw::DebugDraw(sf::RenderWindow *renderWindow)
{
	window = renderWindow;
    width = window->GetWidth();
    height = window->GetHeight();
}

//convert a Box2D (float 0.0f - 1.0f range) color to a SFML color (uint8 0 - 255 range)
sf::Color DebugDraw::B2SFColor(const b2Color &color)
{
	sf::Color result((sf::Uint8)(color.r*255), (sf::Uint8)(color.g*255), (sf::Uint8)(color.b*255));
	return result;
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape polygon(vertexCount);
	for (int32 i=0; i<vertexCount; i++)
	{
		b2Vec2 vertex = vertices[i];
		sf::Vector2f coord(vertex.x*100,height-vertex.y*100);
		polygon.SetPoint(i,coord);
	}
        polygon.SetFillColor(sf::Color::Red);
	window->Draw(polygon);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape polygon(vertexCount);
	for (int32 i=0; i<vertexCount; i++)
	{
		b2Vec2 vertex = vertices[i];
		sf::Vector2f coord(vertex.x*100,height-vertex.y*100);
		polygon.SetPoint(i,coord);
	}
        polygon.SetFillColor(sf::Color::Red);
	window->Draw(polygon);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	sf::CircleShape circle(radius);
	sf::Vector2f coord(center.x*100,height-center.y*100);
	circle.SetPosition(coord);
        circle.SetFillColor(sf::Color::Red);
	window->Draw(circle);
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	sf::CircleShape circle(radius);
	sf::Vector2f coord(center.x*100,height-center.y*100);
	circle.SetPosition(coord);
        circle.SetFillColor(sf::Color::Red);
	window->Draw(circle);
}

//havn't bothered fleshing these out yet
void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {}
void DebugDraw::DrawTransform(const b2Transform& xf) {}
