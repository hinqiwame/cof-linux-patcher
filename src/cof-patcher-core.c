// NOTE: The patcher applies only base patches to ensure smooth and playable experience for Cry of Fear on Linux.
// Use it on clean installation of Cry of Fear. 
// You can get the idea of how you can modify the code to extend patcher's functionality by checking out the comments.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void movefile(const char* source, const char* destination) 
{
    FILE* src = fopen(source, "rb");
    FILE* dest = fopen(destination, "wb");
    
    if (!src || !dest) {
        printf("[-] Error opening files: %s or %s\n", source, destination);
        if (src) fclose(src);
        if (dest) fclose(dest);
        return;
    }

    char buffer[4096];
    size_t bytesRead;
    
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytesRead, dest);
    }

    fclose(src);
    fclose(dest);
}

void patch(const char* path) 
{
    printf("[*] Checking provided directory...\n");
    struct stat dirStat;

    if (stat(path, &dirStat) == 0) {
        printf("[+] Directory check passed\n");
    } else {
        perror("[-] Provided directory does not exist, exiting...");
        exit(1);
    }

    char fullPath[1024];

    printf("[*] Moving files...\n");
    
    printf("[*] Replacing cof.exe...\n");
    strcpy(fullPath, path);
    strcat(fullPath, "/cof.exe");
    movefile("patches/cof.exe", fullPath);
    printf("[+] cof.exe replaced!\n");

    printf("[~] Deleting opengl32.dll in the OG directory...\n");
    strcpy(fullPath, path);
    strcat(fullPath, "/opengl32.dll");
    if (remove(fullPath) == 0) {
        printf("[+] opengl32.dll removed!\n");
    } else {
        printf("[-] Failed to delete opengl32.dll\n");
    }

    printf("[*] Moving opengp32.dll...\n");
    strcpy(fullPath, path);
    strcat(fullPath, "/opengp32.dll");
    movefile("patches/opengp32.dll", fullPath);
    printf("[+] opengp32.dll moved!\n");

    printf("[*] Replacing hw.dll...\n");
    strcpy(fullPath, path);
    strcat(fullPath, "/hw.dll");
    movefile("patches/hw.dll", fullPath);
    printf("[+] hw.dll replaced!\n");

    printf("[*] Replacing client.dll...\n");
    strcpy(fullPath, path);
    strcat(fullPath, "/cryoffear/cl_dlls/client.dll");
    movefile("patches/client.dll", fullPath);
    printf("[+] client.dll replaced!\n");

    // At this point only base patches would have been applied.
    // If you want to install any additional mods or whatever, place the files you need in "patches" directory and use it like shown below:

    /*
    printf("[*] Patching unlockables...\n");
    strcpy(fullPath, path);
    strcat(fullPath, "/cryoffear/scriptsettings.dat");
    movefile("patches/scriptsettings.dat", fullPath);
    printf("[+] Unlockables patched!\n");
    */

    // Remember to recompile the program if you modified it. You can use compiler script in this directory.

    printf("[*] Everything is done. Happy halloween! :)\n"); // :)
}

int main(int argc, char* argv[]) 
{
    if (argc > 1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        printf("Cry of Fear Linux patcher core v0.0.3\n\nDescription: Replaces game and engine libraries to patched ones. Fixes most of the Cry of Fear bugs for Linux.\n\nUsage: %s /path/to/cof\n\nOptional arguments:\n    -h, --help\t\tShow this help message and exit.\n    -v, --version\tDisplay the version of the build and exit.\n\nGithub: https://github.com/hinqiwame/cof-linux-patcher\n", argv[0]);
    } else if (argc > 1 && (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)) {
        printf("0.0.3\n");
    } else {
        if (argc != 2) {
            printf("You didn't provide enough arguments.\nSee %s --help.\n", argv[0]);
            exit(EXIT_FAILURE);
        }

        const char* path = argv[1];
        patch(path);
    }

    return 0;
}
