#pragma once

#include <string>
#include <fstream>

namespace scanner {

/// @brief Find MD-5 hash for input file
class Hasher final {
    public:
        std::string get_hash(const std::string &file) const {

        }

    private:
};

//gcount

} // namespace scanner


/*
int main(int argc, const char** argv) {
    // при неверных аргументах выводим ошибку и выходим с кодом
    if (argc != 3) {
        cerr << "Usage: "s << argv[0] << " <in file> <out file>"s << endl;
        return 1;
    }

    ifstream in_file(argv[1]);
    if (!in_file) {
        cerr << "Can't open input file"s << endl;
        return 2;
    }

    ofstream out_file(argv[2]);
    if (!out_file) {
        cerr << "Can't open output file"s << endl;
        return 2;
    }

    // размер буфера один килобайт
    static const int BUFF_SIZE = 1024;
    std::array<char, BUFF_SIZE> buffer;

    do {
        in_file.read(buffer.data(), BUFF_SIZE);
        out_file.write(buffer.data(), in_file.gcount());
    } while (in_file);
} */



/*//C++ program to get the MD5 Hash of a file
#include <fstream>
#include <iomanip>
#include <iostream>
#include <openssl/md5.h>
using namespace std;

// Function to print the MD5 hash in hexadecimal format
void print_MD5(unsigned char *md, long size = MD5_DIGEST_LENGTH){
    for (int i = 0; i < size; i++){
        cout << hex << setw(2) << setfill('0') << (int)md[i];
    }
    cout << endl;
}

// Function to compute and print MD5 hash of a given string
void computeMD5FromString(const string &str){
    unsigned char result[MD5_DIGEST_LENGTH];
    MD5((unsigned char *)str.c_str(), str.length(), result);

    cout << "MD5 of '" << str << "' : ";
    print_MD5(result);
}

// Function to compute and print MD5 hash of a file
void computeMD5FromFile(const string &filePath){
    ifstream file(filePath, ios::in | ios::binary | ios::ate);

    if (!file.is_open()){
        cerr << "Error: Cannot open file: " << filePath << endl;
        return;
    }

    // Get file size
    long fileSize = file.tellg();
    cout << "File size: " << fileSize << " bytes" << endl;

    // Allocate memory to hold the entire file
    char *memBlock = new char[fileSize];

    // Read the file into memory
    file.seekg(0, ios::beg);
    file.read(memBlock, fileSize);
    file.close();

    // Compute the MD5 hash of the file content
    unsigned char result[MD5_DIGEST_LENGTH];
    MD5((unsigned char *)memBlock, fileSize, result);

    cout << "MD5 of file '" << filePath << "' : ";
    print_MD5(result);

    // Clean up
    delete[] memBlock;
}*/