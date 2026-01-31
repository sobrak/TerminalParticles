#include <iostream>
#include <random>
#include <chrono>
#include <thread>

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 gen(seed);
std::uniform_int_distribution<> distrib(1, 2);
int random_num;

class Particle {
public:
    char symbol;
    unsigned short x;
    unsigned short y;
    char draw[50][50];

    Particle() {
        for(int i = 0; i < 50; i++) {
            for(int j = 0; j < 50; j++) {
                draw[i][j] = ' ';
            }
        }
    }
};

void SnowParticle(char symbol, unsigned short x, unsigned short y, char draw[50][50]) {
    int i = 0, j = 0, n = 0;
    for(i = 0; i < x; i++)  {
        draw[0][i] = symbol;
    }
    i = 0;
    for(n; n < y ; n++) {
        j++;
        for(i = 0; i < x; i++) {
            distrib(gen);
            if(distrib(gen) == 2) {draw[j][i] = symbol;}
        }
    }
}

void PrintParticleArray(char draw[50][50], unsigned short width, unsigned short height) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            std::cout << draw[i][j];
        }
        std::cout << std::endl;
    }
}

int main(int argc, char **argv) {
    Particle snow;
    snow.symbol = '*';
    snow.x = 50;
    snow.y = 50;
    SnowParticle(snow.symbol, snow.x, snow.y, snow.draw);
    PrintParticleArray(snow.draw, snow.x, snow.y);
    return 0;
}
