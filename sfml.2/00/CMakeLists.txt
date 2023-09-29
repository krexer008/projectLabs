# Добавляем исполняемый файл 00
# Он собирается из 1 файла исходного кода: main.cpp
add_executable(00 main.cpp)

# включаем режим C++17 для сборки 00

target_compile_definitions(00 PUBLIC cxx_std_17)