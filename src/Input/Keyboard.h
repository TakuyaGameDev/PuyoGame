#pragma once
#include "Input.h"

class Keyboard : public Input {
public:
	Keyboard();
	~Keyboard();
	void Update(void);
	const bool GetInputTrigger(const COMMANDS& com);
private:
	std::array<char, 256> keyData;
	void SetInputMap(void);
};