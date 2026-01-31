/* Declare the C functions useful for (preprocessor instruction and) maping */
#include <iostream>
#include <fstream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <cstring>
#include <ctime>

/* Store data into a C++ variable and return a text file */
int main() {
    std::array<char, 128> buffer;
    std::string result;

    // run curl, read output
    // std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("curl -I https://LeaKeller.github.io | findstr /l 'Server Last-Modified Date'", "r"), pclose); // Trial with findstr
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("curl -I https://LeaKeller.github.io", "r"), pclose);
    if (!pipe) {
        std::cerr << "Failed to run curl\n";
        return 1;
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // Allocate to pointer
    char* info = new char[result.length() + 1];
    std::strcpy(info, result.c_str());

    // Get the times for logging
    std::time_t current_time = std::time(nullptr);
    std::tm* locate_time = std::localtime(&current_time);
 
    // Open the log file in append mode
    std::ofstream log_file("ip_log.txt", std::ios::app);
    if (!log_file) {
        std::cerr << "Failed to open log file\n";
        delete[] info;
        return 1;
    }

    // Log the Info with the timestamp
    log_file << "Info: " << info << "\n";
    // Return all the Infoes
    std::cout << "Logged Info: " << info << std::endl;

    // Cleanup
    delete[] info;
    return 0;
}