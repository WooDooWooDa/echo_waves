#include "WinPanel.h"
#include "FontManager.h"
#include "gameSettings.h"

void WinPanel::Init()
{
	auto winText = new Text();
	winText->SetText("You escaped the maze", FontManager::FONT_SIZE_72);
	winText->SetPosition(vector2(GAME_WINDOW_SIZE / 2));
	texts.push_back(winText);

	auto thxText = new Text();
	thxText->SetText("Thank you for playing my game", FontManager::FONT_SIZE_36);
	thxText->SetPosition(vector2(GAME_WINDOW_SIZE / 2, (GAME_WINDOW_SIZE / 2) + 50));
	texts.push_back(thxText);
}

void WinPanel::Update(Uint64 delta) { }

void WinPanel::DrawIn(SDL_Renderer* r) const
{
	for (auto& text : texts) {
		text->Draw(r);
	}
}
