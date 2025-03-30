#include "snake.h"
#include "field.h"
#include <cmath>

// Khởi tạo rắn
Snake::Snake(Field* f, std::size_t init_size)
    : field{f}, size{init_size}, coordinates{}, next_dir{Directions::Right}
{
    // Lấy vị trí ban đầu
    std::size_t y = field->get_height() / 2;
    std::size_t x = field->get_width() / 2;
    coordinates.emplace_back(y, x);
    (*field)[y][x] = Block::head;

    // Tạo thân rắn
    for (std::size_t i=1; i<size; ++i)
        if ((*field)[y][--x] == Block::empty) {
            coordinates.emplace_back(y, x);
            (*field)[y][x] = Block::body;
        }
        else {break;}
}

//  xử lý di chuyển của rắn
bool Snake::make_move()
{
    auto coord = coordinates.front();
    auto old = coord;

    switch(next_dir) {
        case Directions::Right:
            coord.second++;
            break;
        case Directions::Left:
            coord.second--;
            break;
        case Directions::Up:
            coord.first--;
            break;
        case Directions::Down:
            coord.first++;
            break;
    }

    if ((*field)[coord.first][coord.second] == Block::fruit) { // Ăn trái cây
        increase_size();
        field->eat_fruit();
    }
    else if ((*field)[coord.first][coord.second] != Block::empty) { // Va chạm với vật cản
        return false;
    }

    // Cập nhật vị trí đầu rắn
    (*field)[coord.first][coord.second] = Block::head;
    (*field)[old.first][old.second] = Block::body;
    coordinates.push_front(std::move(coord));

    // Xóa phần đuôi nếu kích thước vượt quá giới hạn
    if (coordinates.size() > size) {
        auto last = coordinates.back();
        (*field)[last.first][last.second] = Block::empty;
        coordinates.pop_back();
    }

    return true;
}

// Hàm tăng kích thước rắn
void Snake::increase_size()
{
    ++size;
}

//  hướng di chuyển của rắn
void Snake::set_direction(Directions dir)
{
    if (std::abs(static_cast<int>(dir) - static_cast<int>(next_dir)) >= 2) {
        next_dir = dir;
    }
}

// Xử lý bàn phím để điều khiển rắn
void Snake::handle_event(SDL_Event& e)
{
    if( e.type == SDL_KEYDOWN ) {
        switch( e.key.keysym.sym ) {
            case SDLK_UP:
            case SDLK_w:
                set_direction(Directions::Up);
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                set_direction(Directions::Right);
                break;
            case SDLK_LEFT:
            case SDLK_a:
                set_direction(Directions::Left);
                break;
            case SDLK_DOWN:
            case SDLK_s:
                set_direction(Directions::Down);
                break;
            default:
                break;
        }
    }
}
