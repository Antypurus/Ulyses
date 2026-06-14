#include <iostream>

#include <SDL3/SDL.h>

int main() {
    SDL_Init(0);

    std::uint64_t framebufferWidth = 1280;
    std::uint64_t framebufferHeight = 720;

    SDL_Window* window = SDL_CreateWindow("Ulysses", framebufferWidth, framebufferHeight, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, "Ulysses Renderer");
    SDL_Texture* framebuffer = SDL_CreateTexture(renderer, 
        SDL_PIXELFORMAT_ARGB8888, 
        SDL_TEXTUREACCESS_STREAMING, 
        framebufferWidth, 
        framebufferHeight);

    bool running = true;
    while(running) {
        void* framebufferData = nullptr;
        int pitch = 0;
        SDL_LockTexture(framebuffer, nullptr, &framebufferData, &pitch);

        SDL_UnlockTexture(framebuffer);
        SDL_RenderTexture(renderer, framebuffer, nullptr, nullptr);
        SDL_RenderPresent(renderer);

        SDL_Event event;
        SDL_PollEvent(&event);
        if(event.type == SDL_EVENT_QUIT){
            running = false;
        }
    }

    SDL_DestroyTexture(framebuffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}