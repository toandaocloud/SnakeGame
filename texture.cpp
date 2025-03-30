#include "texture.h"
#include "exception.h"

#include <SDL_image.h>
#include <SDL_ttf.h>

// Hàm khởi tạo Texture
Texture::Texture(MainWindow& m)
    : mTexture{nullptr}, gRenderer{m.get_renderer()}, mWidth{0}, mHeight{0} {}

// Hàm hủy Texture, giải phóng tài nguyên
Texture::~Texture()
{
    // Giải phóng bộ nhớ
    free();
}

// Tải ảnh từ tệp
bool Texture::loadFromFile( const std::string& path )
{
    // Giải phóng texture cũ
    free();

    // Texture mới sẽ được tạo
    SDL_Texture* newTexture = nullptr;

    // Tải hình ảnh từ đường dẫn
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == nullptr ) {
        throw SnakeException(std::string("Không thể tải hình ảnh ") + path + " : " + IMG_GetError());
    }

    // Xóa màu nền trắng (0xFF, 0xFF, 0xFF) để làm trong suốt
    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0xFF, 0xFF ) );

    // Tạo texture từ surface
    newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
    if( newTexture == nullptr ) {
        throw SnakeException(std::string("Không thể tạo texture từ ") + path + " : " + SDL_GetError());
    }

    // Lấy kích thước hình ảnh
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;

    // Giải phóng surface sau khi đã tạo texture
    SDL_FreeSurface( loadedSurface );

    // Lưu texture mới
    mTexture = newTexture;
    return mTexture != nullptr;
}

// Tải texture từ văn bản đã render
bool Texture::loadFromRenderedText( const std::string& textureText, Font& f, SDL_Color textColor )
{
    // Giải phóng texture cũ nếu có
    free();

    // Tạo surface từ văn bản
    SDL_Surface* textSurface = TTF_RenderText_Solid( f.get_font(), textureText.c_str(), textColor );
    if( textSurface == nullptr ) {
        throw SnakeException(std::string("Không thể render văn bản! Lỗi SDL_ttf: ") + TTF_GetError());
    }

    // Tạo texture từ surface
    mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
    if( mTexture == nullptr ) {
        throw SnakeException(std::string("Không thể tạo texture từ văn bản :") + SDL_GetError());
    }

    // Lấy kích thước văn bản
    mWidth = textSurface->w;
    mHeight = textSurface->h;

    // Giải phóng surface sau khi đã tạo texture
    SDL_FreeSurface( textSurface );

    return mTexture != nullptr;
}

// Giải phóng texture
void Texture::free()
{
    // Nếu texture tồn tại, giải phóng nó
    if( mTexture != nullptr ) {
        SDL_DestroyTexture( mTexture );
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

// Thiết lập màu sắc cho texture
void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    // Điều chỉnh màu của texture
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void Texture::setBlendMode( SDL_BlendMode blending )
{

    SDL_SetTextureBlendMode( mTexture, blending );
}

// Thiết lập độ trong suốt (alpha) của texture
void Texture::setAlpha( Uint8 alpha )
{

    SDL_SetTextureAlphaMod( mTexture, alpha );
}

// Hiển thị texture lên màn hình
void Texture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    // Xác định vùng hiển thị trên màn hình
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    if( clip != nullptr )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // Render texture lên màn hình
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}
