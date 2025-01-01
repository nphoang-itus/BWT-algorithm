# BWT-algorithm
Research Burrows–Wheeler Transform Algorithm

# Cấu trúc thư mục

`data/`
- Lưu trữ toàn bộ tệp dữ liệu cần thiết (các file dạng .txt).
- Chia thành các thư mục: `input/` và `output/`

`src/`
- Chứa toàn bộ mã nguồn chính của dự án:
    - `algorithms/`: Chứa các file cài đặt cho từng thuật toán
    - `common/`: Chứa các file dùng chung.
    - `include/`: Chứa file header để khai báo các hàm và lớp.
    - `main.cpp`

## Các phần chính:
- `BWT`: Chương trình chuyển từ chuỗi thường sang chuỗi dạng BWT ***(Thái Hoà)***.
- `ReverseBWT`: Chương trình chuyển từ chuỗi dạng BWT sang chuỗi thường ***(Thái Hoà)***..
- `PatternSerch`: Chương trình tìm kiếm mẫu ***(Thượng Đế)***..
- `Compression`: Chương trình nén dữ liệu ***(Thành công)***..
