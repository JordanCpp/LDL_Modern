// Copyright 2025-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

module;

export module Graphics;

import std;
import SDL1;

export namespace Graphics
{
    class Canvas
    {
    public:
        Canvas(SDL_Surface* screen) :
            _running(true),
            _screen(screen)
        {
        }

        ~Canvas()
        {
            SDL_Quit();
        }

        bool GetEvent()
        {
            if (_running)
            {
                SDL_Event event = {};

                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_QUIT)
                    {
                        _running = false;
                    }
                }
            }

            return _running;
        }
    private:
        bool         _running;
        SDL_Surface* _screen;
    };

    std::expected<std::unique_ptr<Canvas>, const char*> CanvasNew(int width, int height)
    {
        SDL_Loader::Init();

        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            return std::unexpected(SDL_GetError());
        }

        auto screen = SDL_SetVideoMode(width, height, 24, SDL_HWSURFACE);

        if (!screen)
        {
            SDL_Quit();
            return std::unexpected(SDL_GetError());
        }

        return std::make_unique<Canvas>(screen);
    }
}
