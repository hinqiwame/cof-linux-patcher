require "dir"
require "file_utils"

def main
	puts "[~] Enter your FULL path (should begin with /home/) to Cry of Fear installation: "
	path = gets

	puts "[~] Checking provided directory..."
	if Dir.exists?("#{path}")
		puts "[+] Directory check passed"
	else
		puts "[!] Provided directory does not exist, exiting..."
		exit(1)
	end

	puts "[~] Moving files..."
	puts "[~] Replacing cof.exe..."
	FileUtils.cp("patches/cof.exe", "#{path}/")
	puts "[+] cof.exe replaced!"
	puts "[~] Deleting opengl32.dll in the OG directory..."
	FileUtils.rm("#{path}/opengl32.dll")
	puts "[+] opengl32.dll removed!"
	puts "[~] Moving opengp32.dll..."
	FileUtils.cp("patches/opengp32.dll", "#{path}/")
	puts "[+] opengp32.dll moved!"
	puts "[~] Replacing hw.dll..."
	FileUtils.cp("patches/hw.dll", "#{path}/")
	puts "[+] hw.dll replaced!"
	puts "[~] Replacing client.dll..."
	FileUtils.cp("patches/client.dll", "#{path}/cryoffear/cl_dlls")
	puts "[+] client.dll replaced!"
	puts "[+] Everything done. Have fun!"
end

# check for arguments
if ARGV.size > 0 && (ARGV[0] == "-h" || ARGV[0] == "--help")
	puts "Cry of Fear Linux patcher v0.0.0\n\nDescription: Replaces game and engine dll files to patched ones. Fixes most of the Cry of Fear bugs for Linux.\n\nUsage: cof-patcher\n\nOptional arguments:\n    -h, --help		Show this help message and exit.\n    -v, --version	Display the version of the build and exit.\n"
elsif ARGV.size > 0 && (ARGV[0] == "-v" || ARGV[0] == "--version")
	puts "0.0.0"
else
	main
end

