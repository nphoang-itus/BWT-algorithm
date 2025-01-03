#include "include\Compression.hpp"

int main()
{
    // thiết kế command line có câu lệnh dạng :
    // command 1: main.exe compression [file cần nén(input)] [tên file sau khi nén(compression)]
    // command 2: main.exe decompression [file sau khi nén(compression)] [file sau khi giải nén(ouput)]

    // ví dụ cách sử dụng
    // khởi tạo các biến đã yêu cầu
    string input = "input.txt";           // file ban đầu
    string compressed = "compressed.bin"; // file sau khi nén
    string output = "output.txt";         // file sau khi giải nén

    // gọi hàm truyền vào là xong
    compressFile(input, compressed);
    decompressFile(compressed, output);

    return 0;
}
