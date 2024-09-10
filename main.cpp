/*
Структура «компьютер» (поля: тип процессора, тактовая частота, объем оперативной
памяти, размер жесткого диска, тип видеокарты)
*/
#include <iostream>
#include <string>
#include <fstream> // библиотека для работы с файлами
#include <vector>
#include <iosfwd> // библиотека для работы с потоками

struct computer { // Определяем структуру компьютер
	std::string cpu_type;
	std::string clock_frequency;
	std::string ram_value;
	std::string hdd_value;
	std::string gpu_type;
};
int main(int argc, const char* argv[]) {
	setlocale(LC_ALL, "Russian");
	if (argc != 4) { // ошибка, если неверное количество аргументов
		std::cerr << "Ошибка: Используйте четыре параметра :(\n";
		return -1;
	}
	const std::string mode(argv[1]); // Режим записи или чтения из файла
	const std::string open_mode(argv[2]); // Текстовый или двоичный режим
	const std::string file_name(argv[3]); // Название файла
	int n; // Количество компьютеров
	std::vector<computer> computers; // Вектор, содержащий элементы типа структуры компьютер
	if (mode == "write") { // Режим записи в файл
		std::cout << "Введите количество компьютеров: ";
		std::cin >> n;
		computers.resize(n); // Изменения размера вектора под количество компьютеров
		for (size_t i = 0; i < computers.size();++i) {
			std::cout << "Номер компьютера: " << (i + 1) << std::endl;		
			std::cout << "Тип процессора: ";
			if (i == 0) {
				std::cin.ignore();
			}
			std::getline(std::cin, computers[i].cpu_type); // Аналогично с этой строкой далее записываем i-й ввод пользователя в соответствующее поле структуры
			std::cout << "Частота процессора: ";
			std::getline(std::cin, computers[i].clock_frequency);
			std::cout << "Объём ОЗУ: ";
			std::getline(std::cin, computers[i].ram_value);
			std::cout << "Объём HDD: ";
			std::getline(std::cin, computers[i].hdd_value);
			std::cout << "Тип видеокарты: ";
			std::getline(std::cin, computers[i].gpu_type);
		}
		if (open_mode == "text") { // Режим текст
			std::ofstream file_text (file_name); // Файл открываем для записи
			file_text << n << std::endl; // записываем количество компьютеров
			for (auto& pos : computers) { // Используем range based for для прохода по вектору структуры и записываем в файл поля структуры
				file_text << "Тип процессора: " << pos.cpu_type << std::endl << "Частота процессора: " << pos.clock_frequency << std::endl << "Объём ОЗУ: " << pos.ram_value << std::endl << "Объём HDD: " << pos.hdd_value << std::endl << "Тип видеокарты: " << pos.gpu_type << std::endl;
			}
			file_text.close();
		}
		else if (open_mode == "binary") { // Режим двоичный
				std::ofstream file_binary(file_name, std::ios::binary); // открываем файл для записи в двоичном режиме
				file_binary.write((char*)&n, sizeof(n)); // записываем в файл n
				for (auto pos : computers) { // Используем range based for для прохода по вектору структуры и записываем в файл поля структуры
					// ends - вводим нулевой байт в 
					file_binary << "Тип процессора: " << pos.cpu_type << std::ends << "Частота процессора: " << pos.clock_frequency << std::ends << "Объём ОЗУ: " << pos.ram_value << std::ends << "Объём HDD: " << pos.hdd_value << std::ends << "Тип видеокарты: " << pos.gpu_type << std::ends;
				}
				file_binary.close();
			}
	}
	else if (mode == "read") { // Режим чтения из файла
		if (open_mode == "text") { // Режим текст
			std::ifstream file_read(file_name); // открываем файл на чтение
			if (!file_read) { // Ошибка, если файл не найден
				std::cerr << "Файл не найден :(\n";
				return -1;
			}
			file_read >> n; // Записываем в файл количество компьютеров
			computers.resize(n); // Меняем размер вектора 
			bool numm = true;
			for (auto& pos : computers) {
				if (numm == true) {
					file_read.ignore(1, '\n'); // На первом компьютере есть два лишних пустых символа, которые мы пропускаем
					numm = false;
				}
				
				std::getline(file_read, pos.cpu_type); // Записываем в файл характеристики компьютера
				std::getline(file_read, pos.clock_frequency);
				std::getline(file_read, pos.ram_value);
				std::getline(file_read, pos.hdd_value);
				std::getline(file_read, pos.gpu_type);
			}
			file_read.close();
		}
		else if (open_mode == "binary") { // Двоичный режим
			std::ifstream file_bin_read(file_name, std::ios::binary); // Открываем режим на чтение в двоичном режиме
			if (!file_bin_read) { // Ошибка, если файл не найден
				std::cerr << "Файл не найден :(\n";
				return -1;
			}
			file_bin_read.read((char*)&n, sizeof(n)); // считываем в файле n
			computers.resize(n); // Меняем размер вектора
			for (auto& pos : computers) { // range based for по файлу
				std::getline(file_bin_read, pos.cpu_type,'\0'); // Считываем часть файла до нулевого байта в соответствующее поле структуры
				std::getline(file_bin_read, pos.clock_frequency, '\0');
				std::getline(file_bin_read, pos.ram_value, '\0');
				std::getline(file_bin_read, pos.hdd_value, '\0');
				std::getline(file_bin_read, pos.gpu_type, '\0');
			}
			file_bin_read.close();
		}
		int num = 1;
		for (auto& pos : computers) { // range based for выводим характеристики компьютера в консоль
			std::cout << "Номер компьютера: " << num << std::endl;
			std::cout << pos.cpu_type << std::endl; 
			std::cout << pos.clock_frequency << std::endl;
			std::cout << pos.ram_value << std::endl;
			std::cout << pos.hdd_value << std::endl;
			std::cout<< pos.gpu_type << std::endl;
			num++;
			std::cout << std::endl;
		}
	}
	return 0;
}
