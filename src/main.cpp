#include "include/CommandLine.hpp"

int main(int argc, char **argv)
{
    // thiết kế command line có câu lệnh dạng :
    // command 1: main.exe -cprs [file cần nén(input)] [tên file sau khi nén(compression)]
    // command 2: main.exe -decprs [file sau khi nén(compression)] [file sau khi giải nén(ouput)]

    // ví dụ cách sử dụng
    // khởi tạo các biến đã yêu cầu
    // string input = "input.txt";           // file ban đầu
    // string compressed = "compressed.bin"; // file sau khi nén
    // string output = "output.txt";         // file sau khi giải nén

    // // gọi hàm truyền vào là xong
    // compressFile(input, compressed);
    // decompressFile(compressed, output);

    // g++ algorithm/*.cpp main.cpp -o main.exe
    // Build
    // Cmd1: ./main.exe -c input.txt output.txt --bwt
    // Cmd2: ./main.exe -c input.txt output.txt
    // Cmd3: ./main.exe -p paragraph.txt patterns.txt output.txt
    // Cmd4: ./main.exe -cprs input.txt output.bin
    // Cmd5: ./main.exe -decprs output.bin output.txt
    executeWithCommandLine(argc, argv);

    return 0;
}
