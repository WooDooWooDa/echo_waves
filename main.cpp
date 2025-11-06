#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_blendmode.h>
#include "WaveGame.h"
#include "gameSettings.h"


typedef struct
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    WaveGame wave_ctx;
    Uint64 last_step;
} AppState;

static SDL_AppResult handle_key_event_(WaveGame* ctx, SDL_Event* event, SDL_Scancode key_code)
{
    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (key_code) {
            /* Quit. */
        case SDL_SCANCODE_ESCAPE:
        case SDL_SCANCODE_Q:
            return SDL_APP_SUCCESS;
            /* Restart the game as if the program was launched. */
        case SDL_SCANCODE_R:
            ctx->InitGame();
            break;
        default:
            break;
        }
    }

    ctx->HandleInputs(event, key_code);
    
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    AppState* as = (AppState*)appstate;
    WaveGame* ctx = &as->wave_ctx;
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

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    AppState* as = (AppState*)SDL_calloc(1, sizeof(AppState));
    if (!as) {
        return SDL_APP_FAILURE;
    }

    *appstate = as;

    if (!SDL_CreateWindowAndRenderer("Echo Waves", GAME_WINDOW_SIZE, GAME_WINDOW_SIZE, SDL_WINDOW_RESIZABLE, &as->window, &as->renderer)) {
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(as->renderer, GAME_WINDOW_SIZE, GAME_WINDOW_SIZE, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    SDL_SetRenderDrawBlendMode(as->renderer, SDL_BLENDMODE_BLEND);

    // INIT GAME
    (&as->wave_ctx)->InitGame();

    as->last_step = SDL_GetTicks();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    WaveGame* ctx = &((AppState*)appstate)->wave_ctx;
    switch (event->type) {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    default:
        handle_key_event_(ctx, event, event->key.scancode);
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
}