#pragma once

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>

class Rain
{
public:

	// Config

	SDL_FRect bounds{ 0, 0, 1000, 1000 };
	SDL_Color color{ 0, 0, 255, 255 };
	float speed = 100.f;
	int64_t count = 400;
	SDL_FPoint singleDropSize{ 2, 4 };
	
	float dropTimeCost = 0.2;

	void init();

	void update(float deltaSeconds);

	void draw(auto* renderer);

private:

	SDL_FPoint randPointWithinboundss();

	std::vector<SDL_FPoint> points;
	float timePool = 0.f;
};

void Rain::init()
{
	points.reserve(count);
}

void Rain::update(float deltaSeconds)
{
	if (points.size() < points.capacity())
	{
		timePool += deltaSeconds;
		while (timePool > dropTimeCost)
		{
			timePool -= dropTimeCost;
			auto point = randPointWithinboundss();
			points.push_back(point);
		}
	}

	// Update position
	for (auto& point : points)
	{
		point.y += deltaSeconds * speed;

		if (point.y > bounds.x + bounds.h)
		{
			point = randPointWithinboundss();
		}
	}
}

void Rain::draw(auto* renderer)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_FRect rect{ 0, 0, singleDropSize.x, singleDropSize.y };
	for (const auto& point : points)
	{
		rect.x = point.x;
		rect.y = point.y;

		// TODO: Heavy, could be optimized
		SDL_RenderRect(renderer, &rect);
	}
}

inline SDL_FPoint Rain::randPointWithinboundss()
{
	return { SDL_randf() * bounds.w + bounds.x, bounds.y /* SDL_randf() * bounds.h + bounds.y */ };
}
