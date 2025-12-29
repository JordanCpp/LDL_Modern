
import SDL1;
import std;

class Canvas
{
public:
    Canvas(SDL_Surface* screen) :
        _screen(screen)
    {
    }

    ~Canvas()
    {
        SDL_Quit();
    }
private:
    SDL_Surface* _screen;
};

std::expected<std::unique_ptr<Canvas>, const char*> CanvasNew(int width, int height)
{
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

int main()
{
    SDL_Loader loader;

    auto canvas = CanvasNew(800, 600);

    if (!canvas)
    {
        return -1;
    }

    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }
    }

    return 0;
}
