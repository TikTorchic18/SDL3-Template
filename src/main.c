#define SDL_MAIN_USE_CALLBACKS

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

#define WIDTH (640)
#define HEIGHT (360)

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} AppState;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
    *appstate = SDL_malloc(sizeof(AppState));
    SDL_Window* window;
    SDL_Renderer* renderer;

    if (!SDL_SetAppMetadata("Hello SDL", "1.0.0", "com.tiktorchic18.hello-sdl")) {
        SDL_Log("Failed to set app metadata: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Hello SDL", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer)) { 
        SDL_Log("Failed to create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_SetRenderLogicalPresentation(renderer, WIDTH, HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX)) {
        SDL_Log("Failed to set logical presentation: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    *(AppState*)*appstate = (AppState) {
        .window = window,
        .renderer = renderer
    };

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    SDL_Renderer* renderer = ((AppState*)appstate)->renderer;
    
    SDL_SetRenderDrawColor(renderer, 0x1e, 0x1e, 0x2e, SDL_ALPHA_OPAQUE);

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
            break;
        default:
            break;
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    SDL_Window* window = ((AppState*)appstate)->window;
    SDL_Renderer* renderer = ((AppState*)appstate)->renderer;

    SDL_free(appstate);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return;
}
