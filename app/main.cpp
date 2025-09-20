#include <scanner.h>

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    std::string base_file;
    std::string log_file;
    std::string folder;

    if (argc != 7) {
        std::cerr << "Not all options are set" << std::endl;
        std::cerr << "Usage: app --base <*.cvs> --log <*.log> --path <path_to_folder>" << std::endl;
        return 1;
    }

    int options_count{0};
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--base") {
            ++options_count;
            base_file = argv[++i];
            continue;
        }
        if (arg == "--log") {
            ++options_count;
            log_file = argv[++i];
            continue;
        }
        if (arg == "--path") {
            ++options_count;
            folder = argv[++i];
            continue;
        }
    }

    if (options_count != 3) {
        std::cerr << "Not all options are set" << std::endl;
        std::cerr << "Usage: app --base <*.cvs> --log <*.log> --path <path_to_folder>" << std::endl;
        return 1;
    }


    scanner::Scanner scanner;
    scanner.set_base(base_file);
    scanner.set_log(log_file);
    scanner.scan(folder);

    return 0;
}

//./build/app/app --base file.csv --log log.log  --path ./r