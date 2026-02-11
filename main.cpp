#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>

// RNG state kept local in functions to avoid global side-effects
static uint64_t seed64 = static_cast<uint64_t>(
    std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count());
static std::seed_seq seed_seq{
    static_cast<uint32_t>(seed64 & 0xFFFFFFFFu),
    static_cast<uint32_t>((seed64 >> 32) & 0xFFFFFFFFu)
};
static std::mt19937 gen(seed_seq);
static std::uniform_int_distribution<int> distrib(1, 2);

class Particle {
public:
    char symbol {'*'};
    unsigned short x {50};
    unsigned short y {50};
    char draw[50][50]{}; // zero-initialize

    // Populate draw with a simple snow pattern
    void SnowParticle(char s, unsigned short width, unsigned short height, char out[50][50]) {
        // Fill with spaces first
        for (int r = 0; r < 50; ++r) {
            for (int c = 0; c < 50; ++c) {
                out[r][c] = ' ';
            }
        }

        if (width > 50) width = 50;
        if (height > 50) height = 50;

        // Top row full of snow
        for (unsigned short i = 0; i < width; ++i) {
            out[0][i] = s;
        }
        // Randomly place snow in subsequent rows
        for (unsigned short row = 1; row < height; ++row) {
            for (unsigned short col = 0; col < width; ++col) {
                if (distrib(gen) == 2) {
                    out[row][col] = s;
                }
            }
        }
    }

    // Print the buffer with given dimensions
    void PrintParticleArray(char buf[50][50], unsigned short width, unsigned short height) {
        if (width > 50) width = 50;
        if (height > 50) height = 50;
        for (unsigned short i = 0; i < height; ++i) {
            for (unsigned short j = 0; j < width; ++j) {
                std::cout << buf[i][j];
            }
            std::cout << '\n';
        }
    }
};

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;
    Particle* snow = new Particle();
    snow->symbol = '*';
    snow->x = 50;
    snow->y = 25; // smaller height for terminal readability

    snow->SnowParticle(snow->symbol, snow->x, snow->y, snow->draw);
    snow->PrintParticleArray(snow->draw, snow->x, snow->y);

    return 0;
}
