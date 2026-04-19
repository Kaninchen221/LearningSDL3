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
	SDL_FPoint sizePerEntity{ 2, 4 };
	float dropTimeCost = 0.2;

	void init();

	void update(float deltaSeconds);

	void draw(auto* renderer);

private:

	SDL_FPoint randPointWithinBounds();

	std::vector<SDL_FRect> entities;
	float timePool = 0.f;
};

void Rain::init()
{
	entities.reserve(count);
}

void Rain::update(float deltaSeconds)
{
	if (entities.size() < entities.capacity())
	{
		timePool += deltaSeconds;
		while (timePool > dropTimeCost)
		{
			timePool -= dropTimeCost;
			auto point = randPointWithinBounds();
			entities.push_back(SDL_FRect{ point.x, point.y, sizePerEntity.x, sizePerEntity.y });
		}
	}

	// Update position
	for (auto& entity : entities)
	{
		entity.y += deltaSeconds * speed;

		if (entity.y > bounds.x + bounds.h)
		{
			auto newPosition = randPointWithinBounds();
			entity.x = newPosition.x;
			entity.y = newPosition.y;
		}
	}
}

void Rain::draw(auto* renderer)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	for (const auto& entity : entities)
	{
		// TODO: Could be heavy because of a possible alloc on the heap
		// TODO: Not filled rect, handle It
		SDL_RenderRect(renderer, &entity);
	}
	
	// It has just a render rect inside
	//SDL_RenderRects(renderer, entities.data(), entities.size());
}

inline SDL_FPoint Rain::randPointWithinBounds()
{
	return { SDL_randf() * bounds.w + bounds.x, bounds.y /* SDL_randf() * bounds.h + bounds.y */ };
}
