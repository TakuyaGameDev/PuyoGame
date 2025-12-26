#pragma once
#include "Input.h"

class Keyboard : public Input {
public:
	Keyboard(PLAYERS p);
	~Keyboard();
	void Update(void);
	const bool GetInputTrigger(const COMMANDS& com);
private:
	std::array<char, 256> keyData;
	void SetCommandMap(void);
};