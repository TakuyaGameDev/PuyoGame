#pragma once
#include "Vector2.h"

#define SCREEN_X 640
#define SCREEN_Y 540
#define TITLE "PuyoGame"

class Application
{
public:
	static Application& GetInstance(void)
	{
		static Application sInstance_;
		return sInstance_;
	}

	void Run(void);

	void Terminate(void);

	const Vector2 GetScreenSize(void) const 
	{
		return this->screenSize;
	}

private:
	Application() = default;
	Application(const Application&) = delete;
	void operator=(const Application&) = delete;

	bool SysInit(void);

	Vector2 screenSize;

	void SetScreenSize(const Vector2& size)
	{
		this->screenSize.x = size.x;
		this->screenSize.y = size.y;
	}
};