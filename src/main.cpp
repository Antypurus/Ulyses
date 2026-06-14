#include <iostream>
#include <array>

#include <SDL3/SDL.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    std::uint64_t framebufferWidth = 1280;
    std::uint64_t framebufferHeight = 720;

    SDL_Window* window = SDL_CreateWindow("Ulysses", framebufferWidth, framebufferHeight, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if(renderer == nullptr) { 
        std::cout << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Texture* framebuffer = SDL_CreateTexture(renderer, 
        SDL_PIXELFORMAT_ARGB8888, 
        SDL_TEXTUREACCESS_STREAMING, 
        framebufferWidth, 
        framebufferHeight);

    bool running = true;
    while(running) {
        void* framebufferData = nullptr;
        int pitch = 0;
        bool result = SDL_LockTexture(framebuffer, nullptr, &framebufferData, &pitch);
        if(!result) { 
            std::cout << "ERROR: failed to lock texture" << std::endl;
            std::cout << SDL_GetError() << std::endl;
            std::cout << framebuffer << std::endl;
            std::cout << renderer << std::endl;
            goto exit;
        }

        uint8_t* dst = static_cast<uint8_t*>(framebufferData);
        auto calcIDX = [&](int x, int y) -> auto {
            return y * (pitch) + x * 4;
        };
        auto setPixel = [&](int x, int y, std::array<std::uint8_t, 4> value) {
            auto idx = calcIDX(x, y);
            SDL_memcpy(dst + idx, value.data(), 4);
        };

        setPixel(0, 0, {255, 255, 255, 255});
        setPixel(0, 1, {255, 255, 255, 255});
        setPixel(0, 2, {255, 255, 255, 255});
        setPixel(1, 0, {255, 255, 255, 255});
        setPixel(1, 1, {255, 255, 255, 255});
        setPixel(1, 2, {255, 255, 255, 255});
        setPixel(2, 0, {255, 255, 255, 255});
        setPixel(2, 1, {255, 255, 255, 255});
        setPixel(2, 2, {255, 255, 255, 255});

        SDL_UnlockTexture(framebuffer);
        SDL_RenderTexture(renderer, framebuffer, nullptr, nullptr);
        SDL_RenderPresent(renderer);

        SDL_Event event;
        SDL_PollEvent(&event);
        if(event.type == SDL_EVENT_QUIT){
            running = false;
        }
    }

exit:
    SDL_DestroyTexture(framebuffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}