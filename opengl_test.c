#include <stdbool.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

int main(int argc, char* args[]) {

    int WINDOW_FLAGS = SDL_WINDOW_OPENGL;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    } 

    SDL_Window *window = SDL_CreateWindow("OpenGL Test", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS);
    if(window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_GLContext Context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);

    bool running = true, fullscreen = false;
    while(running) {
        SDL_Event ev;
        while(SDL_PollEvent(&ev)) { 
            if(ev.type == SDL_KEYDOWN) { 
                switch(ev.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    case 'f':
                        fullscreen = !fullscreen;
                        if(fullscreen) {
                            SDL_SetWindowFullscreen(window, WINDOW_FLAGS | SDL_WINDOW_FULLSCREEN_DESKTOP);
                        }
                        else {
                            SDL_SetWindowFullscreen(window, WINDOW_FLAGS);
                        }
                        break;
                    default:
                        break;
                }
            } else if (ev.type == SDL_QUIT) {
                running = false;
            }
        }

        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        glClearColor(0.f, 1.f, 0.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);

    }
    return 0;
}