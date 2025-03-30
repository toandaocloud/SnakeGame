#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <chrono>
#include <string>
#include "mainwindow.h"
#include "font.h"
#include "texture.h"
#include "field.h"
#include "snake.h"
#include "music.h"

constexpr static int WIDTH = 640;  // Chiều rộng cửa sổ trò chơi
constexpr static int HEIGHT = 480; // Chiều cao cửa sổ trò chơi

int main(int argc, char* argv[]) {
    using namespace std::chrono;

    // Khởi tạo SDL và các thư viện liên quan
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL_Init that bai: " << SDL_GetError() << std::endl;
        return 1;
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "IMG_Init that bai: " << IMG_GetError() << std::endl;
        return 1;
    }
    if (TTF_Init() < 0) {
        std::cerr << "TTF_Init that bai: " << TTF_GetError() << std::endl;
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Mix_OpenAudio that bai: " << Mix_GetError() << std::endl;
        return 1;
    }

    // Tạo cửa sổ chính của trò chơi
    MainWindow win(WIDTH, HEIGHT, "Snakegame");
    win.set_icon("./snaky_assets/apple.png");

    // Tạo tiêu đề trò chơi
    Font font("./snaky_assets/lazy.ttf", 18);
    Texture title(win);
    title.loadFromRenderedText("an nhieu tao nhat co the.", font, SDL_Color{0xFF, 0, 0, 0xFF});

    // Tạo khu vực chơi game
    auto avail_height = win.get_height() - (title.get_height() * 2);
    Field field(WIDTH, avail_height, win);

    // Tạo rắn
    Snake snake(&field, 6);

    // Thêm 2 quả táo
    field.add_random_fruit();
    field.add_random_fruit();

    // Phát nhạc nền
    Music music("./snaky_assets/chpn_op66.mp3");
    music.play();

    // Vòng lặp chính của trò chơi
    auto t1 = steady_clock::now();
    SDL_Event e;
    auto score1 = snake.score();
    bool quit = false;
    while (!quit) {

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            snake.handle_event(e);
        }

        // Thêm gạch sau mỗi 10s
        auto s2 = steady_clock::now();
        auto duration2 = duration_cast<seconds>(s2 - t1).count();
        if (duration2 > 10) {
            field.add_random_obstacle(snake.get_coordinate());
            t1 = s2;
        }

        // Cập nhật tiêu đề nếu điểm số thay đổi
        auto score2 = snake.score();
        if (score2 > score1) {
            title.loadFromRenderedText("an nhieu tao nhat co the. score: " + std::to_string(snake.score()), font, SDL_Color{0xFF, 0, 0, 0xFF});
            score1 = score2;
        }

        // Kiểm tra xem rắn có di chuyển hợp lệ không
        if (!snake.make_move()) { // Nếu thua
            Texture t(win);
            t.loadFromRenderedText("ban da thua cuoc! score: " + std::to_string(snake.score()), font, SDL_Color{0xFF, 0, 0, 0xFF});
            win.clear();
            t.render((win.get_width() - t.get_width()) / 2, (win.get_height() - t.get_height()) / 2);
            win.update();

            SDL_Delay(5000); // Dừng màn hình trong 5 giây trước khi thoát
            break;
        }

        // Vẽ lại màn hình
        win.clear();
        title.render((win.get_width() - title.get_width()) / 2, (title.get_height()) / 2);
        field.render(0, title.get_height() * 2, &snake);
        win.update();

        SDL_Delay(100);
    }

    // Giải phóng tài nguyên trước khi thoát game
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
