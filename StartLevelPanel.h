#pragma once
#include "MenuPanel.h"

class StartLevelPanel : public MenuPanel
{
public:
	void Init() override;
	void Update(Uint64 delta) override;
	void DrawIn(SDL_Renderer*) const override;

	void SetLevelNumber(int);
};

