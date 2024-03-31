#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <complex>

struct DataStruct {
    std::complex<double> key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;

    friend std::istream& operator>>(std::istream& in, DataStruct& data) {
        std::string line;
        std::getline(in, line);

        // Поиск начала и конца записи в скобках
        size_t start = line.find('(');
        size_t end = line.find(')');
        if (start == std::string::npos || end == std::string::npos) {
            return in; // Пропускаем некорректные данные
        }

        // Извлечение данных из записи в скобках
        std::istringstream iss(line.substr(start + 1, end - start - 1));
        while (iss) {
            std::string field;
            iss >> field;
            if (field == ":key1") {
                char c;
                double re, im;
                iss >> c >> re >> c >> im >> c;
                data.key1 = { re, im };
            }
            else if (field == ":key2") {
                long long n;
                unsigned long long d;
                char c;
                iss >> c >> c >> n >> c >> d >> c;
                data.key2 = { n, d };
            }
            else if (field == ":key3") {
                std::string str;
                iss >> std::quoted(str);
                data.key3 = str;
            }
        }

        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
        out << "(:key1 #c(" << std::fixed << data.key1.real() << " " << data.key1.imag()
            << ") :key2 (:N " << data.key2.first << ":D " << data.key2.second
            << ":) :key3 " << std::quoted(data.key3) << ":)";
        return out;
    }

    bool operator<(const DataStruct& other) const {
        // Реализация сравнения для новых типов данных
        return false; // Замените на корректное сравнение
    }
};

int main() {
    std::vector<DataStruct> dataVec;
    DataStruct temp;

    // Заполнение вектора данными
    while (std::cin >> temp) {
        dataVec.push_back(temp);
    }

    // Сортировка данных
    std::sort(dataVec.begin(), dataVec.end());

    // Вывод отсортированных данных
    for (const auto& data : dataVec) {
        std::cout << data << "\n";
    }

    return 0;
}