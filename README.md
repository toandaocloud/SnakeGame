# Trò Chơi Rắn - Dự án môn Lập Trình Nâng Cao

Đây là trò chơi Rắn kinh điển được phát triển bằng C++ và thư viện SDL2 cho môn Lập Trình Nâng Cao.

## Giới thiệu

Trò chơi Rắn là một trò chơi kinh điển, nơi người chơi điều khiển một con rắn di chuyển trên màn hình để ăn thức ăn, giúp rắn dài hơn và ghi điểm. Mục tiêu là tránh để rắn va vào tường hoặc chính thân mình. Trò chơi bao gồm hiệu ứng âm thanh, hiển thị điểm số và màn hình kết thúc khi thua.

## Cách tải và cài đặt

Để chơi trò chơi, bạn cần thực hiện các bước sau:

1. **Cài đặt thư viện SDL2**: Tải và cài đặt SDL2 cùng các thư viện liên quan như SDL2_image, SDL2_mixer, SDL2_ttf. Bạn có thể tham khảo tài liệu của môn học hoặc hướng dẫn trực tuyến để cấu hình các thư viện này trong môi trường phát triển của bạn.

2. **Tải mã nguồn**: Clone hoặc tải xuống mã nguồn từ kho lưu trữ GitHub:

   
   git clone https://github.com/toandaocloud/SnakeGame.git
   


3. **Biên dịch và chạy trò chơi**: Mở dự án trong môi trường phát triển của bạn (như Code::Blocks), biên dịch và chạy trò chơi.

## Cách chơi

- **Điều khiển rắn**: Sử dụng các phím mũi tên để điều khiển hướng di chuyển của rắn. Lưu ý rằng bạn chỉ có thể chuyển hướng từ ngang sang dọc và ngược lại; không thể quay ngược lại hướng đang di chuyển.

- **Mục tiêu**: Ăn thức ăn xuất hiện ngẫu nhiên trên màn hình để tăng chiều dài của rắn và ghi điểm.

- **Tránh va chạm**: Tránh để rắn va vào tường hoặc chính thân mình, nếu không trò chơi sẽ kết thúc.

## Thông tin sinh viên

- **Họ và tên**: Đào Văn Toàn
- **Mã sinh viên**: 24020325

## Demo Video

[Xem video demo tại đây](<https://drive.google.com/file/d/1NV3WAtu_KGEDxJiF6AlQqZL_SFKQDcUt/view?usp=sharing>)

## Thư viện sử dụng

- **SDL2**: Thư viện chính để phát triển trò chơi.
- **SDL2_image**: Hỗ trợ xử lý hình ảnh.
- **SDL2_mixer**: Hỗ trợ âm thanh và hiệu ứng.
- **SDL2_ttf**: Hỗ trợ hiển thị văn bản với font chữ TrueType.

## Cấu trúc mã nguồn

Dưới đây là mô tả ngắn gọn về các tệp chính trong dự án:

- **main.cpp**: Tệp chính, khởi tạo trò chơi và vòng lặp chính.
- **mainwindow.h/cpp**: Lớp quản lý cửa sổ chính và vòng lặp sự kiện.
- **snake.h/cpp**: Lớp đại diện cho con rắn, bao gồm logic di chuyển và va chạm.
- **field.h/cpp**: Lớp quản lý sân chơi, bao gồm vị trí thức ăn và kiểm tra va chạm.
- **texture.h/cpp**: Lớp hỗ trợ tải và hiển thị hình ảnh.
- **music.h/cpp**: Lớp quản lý âm thanh và hiệu ứng.
- **font.h/cpp**: Lớp hỗ trợ hiển thị văn bản trong trò chơi.
- **exception.h/cpp**: Xử lý các ngoại lệ và lỗi trong quá trình chạy.
