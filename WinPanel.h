#pragma once
#include "MenuPanel.h"

class WinPanel : public MenuPanel
{
public:
	void Init() override;
	void Update(Uint64 delta) override;
	void DrawIn(SDL_Renderer*) const override;
};

