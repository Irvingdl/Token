#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <filesystem> // Necesario para listar archivos en un directorio

namespace fs = std::filesystem;

bool open_file(const std::string& filename) {
    std::ifstream file(filename);
    return file.is_open();
}

int main() {
    std::string directory = "Files"; // Carpeta donde están los archivos HTML
    std::ofstream log_file("a1_matricula.txt");
    auto total_start = std::chrono::high_resolution_clock::now();

    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.path().extension() == ".html") { // Filtra solo archivos HTML
            std::string filename = entry.path().string();
            auto start = std::chrono::high_resolution_clock::now();
            bool success = open_file(filename);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;

            log_file << "Archivo: " << filename << " Tiempo de apertura: " << duration.count() << " segundos\n";
            if (!success) {
                log_file << "Error al abrir " << filename << "\n";
            }
        }
    }

    auto total_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> total_duration = total_end - total_start;
    log_file << "Tiempo total: " << total_duration.count() << " segundos\n";

    log_file.close();
    return 0;
}
