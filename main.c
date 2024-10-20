#include "snake.h"

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    
    SDL_Texture* snakeTexture = loadTexture("assets/snake.png", renderer);  // Custom texture: snake
    SDL_Texture* foodTexture = loadTexture("assets/apple.png", renderer);   // Custom texture: apple
    SDL_Texture* grassTexture = loadTexture("assets/grass.png", renderer);  // Custom texture: grass

    Snake snake;
    Point food;

    initSnake(&snake);
    placeFood(&food);

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        // Handle input
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else {
                handleInput(&snake, &e);
            }
        }

       
        moveSnake(&snake);

       
        if (checkCollision(&snake)) {
            quit = true;  // Game over
        }

        
        if (checkFoodCollision(&snake, &food)) {
            growSnake(&snake);
            placeFood(&food);
        }

        // Render everything
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Clear screen
        SDL_RenderClear(renderer);

        // Render background (grass)
        renderTexture(renderer, grassTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);  // Custom texture: grass

        // Render snake and food
        renderSnake(renderer, &snake, snakeTexture);  // Custom texture: snake
        renderFood(renderer, &food, foodTexture);     // Custom texture: apple

        SDL_RenderPresent(renderer);

        SDL_Delay(120);  
    }

    SDL_DestroyTexture(snakeTexture);
    SDL_DestroyTexture(foodTexture);
    SDL_DestroyTexture(grassTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
