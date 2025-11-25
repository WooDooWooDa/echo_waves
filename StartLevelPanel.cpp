#include "StartLevelPanel.h"
#include "FontManager.h"
#include "gameSettings.h"
#include <format>

void StartLevelPanel::Init()
{
	auto startText = new Text();
	startText->SetText("Press SPACE to clap", FontManager::FONT_SIZE_72);
	startText->SetPosition(vector2(GAME_WINDOW_SIZE / 2));
	texts.push_back(startText);

	auto level = new Text();
	level->SetPosition(vector2(GAME_WINDOW_SIZE / 2, (GAME_WINDOW_SIZE / 2) + 50));
	texts.push_back(level);
}

void StartLevelPanel::Update(Uint64 delta)
{
}

void StartLevelPanel::DrawIn(SDL_Renderer* r) const
{
	for (auto& text : texts) {
		text->Draw(r);
	}
}

void StartLevelPanel::SetLevelNumber(int number)
{
	texts.at(1)->SetText(std::format("Level {}", number), FontManager::FONT_SIZE_48);
}
