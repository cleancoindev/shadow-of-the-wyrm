#pragma once
#ifdef _MSC_VER
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif
#include "MenuWrapper.hpp"
#include "Prompt.hpp"
#include "PromptProcessor.hpp"
#include "SDLCursorLocation.hpp"
#include "SDLRender.hpp"

// Handles prompts on a given sdl window.
class SDLPromptProcessor : public PromptProcessor
{
  public:
    bool operator==(const SDLPromptProcessor& cpp) const;

    int get_prompt(SDL_Window* window);
    std::string get_prompt(const SDLDisplayParameters& display_params, SDLCursorLocation& cursor_location, SDLRender& render, SDL_Renderer* sdl_renderer, SDL_Texture* spritesheet, SDL_Texture* screen, const MenuWrapper& menu_wrapper, PromptPtr prompt);
    void show_prompt(const SDLDisplayParameters& display_params, SDLCursorLocation& cursor_location, SDLRender& render, SDL_Renderer* sdl_renderer, SDL_Texture* spritesheet, SDL_Texture* screen, PromptPtr prompt, int row, int col, int TERMINAL_MAX_ROWS, int TERMINAL_MAX_COLS);
    std::string get_user_string(const SDLDisplayParameters& display_params, SDLCursorLocation& cursor_location, SDLRender& render, SDL_Renderer* sdl_renderer, SDL_Texture* spritesheet, SDL_Texture* screen, bool allow_nonalphanumeric = false);
};
