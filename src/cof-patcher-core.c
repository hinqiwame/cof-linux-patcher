// NOTE: The patcher applies only base patches to ensure smooth and playable expirience for Cry of Fear on Linux.
// Use it on clean installation of Cry of Fear. 
// You can get the idea of how you can modify the code to extend patcher's functionality by checking out the comments.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void movefile(const char* source, const char* destination) {
    FILE* src = fopen(source, "rb");
    FILE* dest = fopen(destination, "wb");
    if (src && dest) {
        char buffer[4096];
        size_t bytesRead;
        while ((bytesRead = fread(buffer, 1, sizeof(buffer), src)) > 0) {
            fwrite(buffer, 1, bytesRead, dest);
        }
        fclose(src);
        fclose(dest);
    }
}

void patch(const char* path) {
    printf("[*] Checking provided directory...\n");
    struct stat dirStat;
    if (stat(path, &dirStat) == 0) {
        printf("[+] Directory check passed\n");
    } else {
        printf("[-] Provided directory does not exist, exiting...\n");
        exit(1);
    }

    printf("[*] Moving files...\n");
    printf("[*] Replacing cof.exe...\n");
    movefile("patches/cof.exe", strcat(path, "/cof.exe"));
    printf("[+] cof.exe replaced!\n");

    printf("[~] Deleting opengl32.dll in the OG directory...\n");
    remove(strcat(path, "/opengl32.dll"));
    printf("[+] opengl32.dll removed!\n");

    printf("[*] Moving opengp32.dll...\n");
    movefile("patches/opengp32.dll", strcat(path, "/opengp32.dll"));
    printf("[+] opengp32.dll moved!\n");

    printf("[*] Replacing hw.dll...\n");
    movefile("patches/hw.dll", strcat(path, "/hw.dll"));
    printf("[+] hw.dll replaced!\n");

    printf("[*] Replacing client.dll...\n");
    movefile("patches/client.dll", strcat(path, "/cryoffear/cl_dlls/client.dll"));
    printf("[+] client.dll replaced!\n");

    // At this point only base patches have been applied.
    // If you want to install any additional mods or whatever, place the files you need in "patches" directory and use it like shown below:

    /*
    printf("[*] Patching unlockables...\n");
    movefile("patches/scriptsettings.dat", strcat(path, "/cryoffear/scriptsettings.dat"));
    printf("[+] Unlockables patched!\n");
    */

    // Remember to recompile the program if you modified it. You can use compiler script in this directory. 

    printf("[*] Everything is done. Happy summer!\n"); // :)
}

int main(int argc, char* argv[]) {	
    if (argc > 1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        printf("Cry of Fear Linux patcher core v0.0.2\n\nDescription: Replaces game and engine libraries to patched ones. Fixes most of the Cry of Fear bugs for Linux.\n\nUsage: %s\n\nOptional arguments:\n    -h, --help\t\tShow this help message and exit.\n    -v, --version\tDisplay the version of the build and exit.\n\nGithub: https://github.com/hinqiwame/cof-linux-patcher\n", argv[0]);
    } else if (argc > 1 && (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)) {
        printf("0.0.2\n");
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
