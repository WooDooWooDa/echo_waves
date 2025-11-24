#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_blendmode.h>
#include "WaveGame.h"
#include "gameSettings.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "SpriteManager.h"
#include "SoundManager.h"
#include "FontManager.h"

std::unique_ptr<SpriteManager> spriteManager;
std::unique_ptr<SoundManager> soundManager;
std::unique_ptr<FontManager> fontManager;

typedef struct
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    WaveGame wave_game;
    Uint64 last_step;
} AppState;

static SDL_AppResult handle_key_event_(WaveGame* game, SDL_Event* event, SDL_Scancode key_code)
{
    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (key_code) {
        case SDL_SCANCODE_Q:
            return SDL_APP_SUCCESS;
        default:
            break;
        }
    }

    game->HandleInputs(event, key_code);
    
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    AppState* as = (AppState*)appstate;
    WaveGame* ctx = &as->wave_game;
    const Uint64 now = SDL_GetTicks();

    // Update
    while ((now - as->last_step) >= TARGET_MS_PER_FRAME) {
        ctx->Update((now - as->last_step) / TARGET_MS_PER_FRAME);
        as->last_step += TARGET_MS_PER_FRAME;
    }

    //Reset window
    SDL_SetRenderDrawColor(as->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(as->renderer);

    // Draw
    ctx->Draw(as->renderer);

    //Render to screen
    SDL_RenderPresent(as->renderer);

    return SDL_APP_CONTINUE;
}

static const struct
{
    const char* key;
    const char* value;
} extended_metadata[] =
{
    { SDL_PROP_APP_METADATA_CREATOR_STRING, "Yuii" },
    { SDL_PROP_APP_METADATA_TYPE_STRING, "game" }
};

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    size_t i;

    if (!SDL_SetAppMetadata("Game Off 2025 - Echo Waves", "1.0", "com.gamejam.wave")) {
        return SDL_APP_FAILURE;
    }

    for (i = 0; i < SDL_arraysize(extended_metadata); i++) {
        if (!SDL_SetAppMetadataProperty(extended_metadata[i].key, extended_metadata[i].value)) {
            return SDL_APP_FAILURE;
        }
    }

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) || !TTF_Init()) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    AppState* as = (AppState*)SDL_calloc(1, sizeof(AppState));
    if (!as) {
        return SDL_APP_FAILURE;
    }

    *appstate = as;
    //as->wave_game = WaveGame();

    if (!SDL_CreateWindowAndRenderer("Echo Waves", GAME_WINDOW_SIZE, GAME_WINDOW_SIZE, SDL_WINDOW_RESIZABLE, &as->window, &as->renderer)) {
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(as->renderer, GAME_WINDOW_SIZE, GAME_WINDOW_SIZE, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    SDL_SetRenderDrawBlendMode(as->renderer, SDL_BLENDMODE_BLEND);

    // INIT GAME
    //Wait for file system to be loaded
#ifdef __EMSCRIPTEN__
    EM_ASM(
        FS.syncfs(true, function(err) {
        if (err) console.error("FS sync failed", err);
    });
    );
#endif

    spriteManager = make_unique<SpriteManager>();
    spriteManager->LoadAllTextures(as->renderer);

    soundManager = make_unique<SoundManager>();
    soundManager->LoadAllSounds();

    fontManager = make_unique<FontManager>();
    fontManager->LoadFont();

    (&as->wave_game)->InitGame();

    as->last_step = SDL_GetTicks();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    WaveGame* game = &((AppState*)appstate)->wave_game;
    switch (event->type) {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    default:
        return handle_key_event_(game, event, event->key.scancode);
        break;
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    if (appstate != NULL) {
        AppState* as = (AppState*)appstate;
        SDL_DestroyRenderer(as->renderer);
        SDL_DestroyWindow(as->window);
        SDL_free(as);
    }
    TTF_Quit();
}