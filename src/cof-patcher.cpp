#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void moveFile(const fs::path& source, const fs::path& destination) {
    std::ifstream src(source, std::ios::binary);
    std::ofstream dest(destination, std::ios::binary);
    dest << src.rdbuf();
}

void mainFunction() {
    std::cout << "[~] Enter your FULL path (should begin with /home/) to Cry of Fear installation: ";
    std::string path;
    std::getline(std::cin, path);

    std::cout << "[~] Checking provided directory..." << std::endl;
    if (fs::exists(path)) {
        std::cout << "[+] Directory check passed" << std::endl;
    } else {
        std::cout << "[!] Provided directory does not exist, exiting..." << std::endl;
        exit(1);
    }

    std::cout << "[~] Moving files..." << std::endl;
    std::cout << "[~] Replacing cof.exe..." << std::endl;
    moveFile("patches/cof.exe", path + "/cof.exe");
    std::cout << "[+] cof.exe replaced!" << std::endl;

    std::cout << "[~] Deleting opengl32.dll in the OG directory..." << std::endl;
    fs::remove(path + "/opengl32.dll");
    std::cout << "[+] opengl32.dll removed!" << std::endl;

    std::cout << "[~] Moving opengp32.dll..." << std::endl;
    moveFile("patches/opengp32.dll", path + "/opengp32.dll");
    std::cout << "[+] opengp32.dll moved!" << std::endl;

    std::cout << "[~] Replacing hw.dll..." << std::endl;
    moveFile("patches/hw.dll", path + "/hw.dll");
    std::cout << "[+] hw.dll replaced!" << std::endl;

    std::cout << "[~] Replacing client.dll..." << std::endl;
    moveFile("patches/client.dll", path + "/cryoffear/cl_dlls/client.dll");
    std::cout << "[+] client.dll replaced!" << std::endl;

    std::cout << "[+] Everything done. Have fun!" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc > 1 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")) {
        std::cout << "Cry of Fear Linux patcher v0.0.1\n\nDescription: Replaces game and engine libraries to patched ones. Fixes most of the Cry of Fear bugs for Linux.\n\nUsage: ./cof-patcher\n\nOptional arguments:\n    -h, --help\t\tShow this help message and exit.\n    -v, --version\tDisplay the version of the build and exit.\n\n";
    } else if (argc > 1 && (std::string(argv[1]) == "-v" || std::string(argv[1]) == "--version")) {
        std::cout << "0.0.1" << std::endl;
    } else {
        mainFunction();
    }

    return 0;
}
