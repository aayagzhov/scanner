#include <scanner.h>
#include <core.h>

#include <iostream>
#include <string>
#include <filesystem>

int main(int argc, char* argv[]) {
    scanner::Stat stat;
    if (argc != 7) {
        std::cerr << "Not all options are set:" << std::endl;
        std::cerr << "------------------------" << std::endl;
        std::cerr << "Usage: app --base <*.cvs> --log <*.log> --path <path_to_folder>" << std::endl;
        return 1;
    }

    std::string base_file;
    std::string log_file;
    std::string folder;

    int options_count{0};
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--base") {
            ++options_count;
            base_file = std::filesystem::absolute(argv[++i]).string();
            continue;
        }
        if (arg == "--log") {
            ++options_count;
            log_file = std::filesystem::absolute(argv[++i]).string();
            continue;
        }
        if (arg == "--path") {
            ++options_count;
            folder = std::filesystem::absolute(argv[++i]).string();
            continue;
        }
    }

    if (options_count != 3) {
        std::cerr << "Not all options are set" << std::endl;
        std::cerr << "Usage: app --base <*.cvs> --log <*.log> --path <path_to_folder>" << std::endl;
        return 1;
    }
    stat.folder_path = std::filesystem::absolute(folder).string();
    stat.base_file = std::filesystem::absolute(base_file).string();
    stat.log_file  = std::filesystem::absolute(log_file).string();

    try {
        scanner::Scanner scanner;
        scanner.set_base(base_file);
        scanner.set_log(log_file);
        scanner.set_stat(stat);
        scanner.scan(folder);
        stat.drop();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
