#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <fstream>


struct discipline {

    std::string item;
    int grade;

};

struct student {

    std::string SNP;

    std::vector<discipline> dis{
            {"математика",  0},
            {"физика",      0},
            {"химия",       0},
            {"информатика", 0}
    };

};

std::ostream &operator<<(std::ostream &os, std::vector<student> &data) {

    for (size_t i = 0; i < data.size(); ++i) {
        os << data[i].SNP << std::endl;

        for (int j = 0; j < 4; ++j) {
            os << "\t" << data[i].dis[j].item << " " << data[i].dis[j].grade << '\n';
        }
        os << "\n";
    }

    return os;
}


std::istream &operator>>(std::istream &is, std::vector<student> &data) {
    while (!is.eof()) {
        student s;
        std::getline(is, s.SNP);
        for (int j = 0; j < 4; ++j) {
            std::string str;
            std::getline(is, str);
            size_t i = 0;
            while (str[i] > '9' || str[i] < '0') {
                ++i;
            }
            s.dis[j].grade = str[i] - '0';
        }
        if (is.eof()) {
            return is;
        }
        data.push_back(s);
        std::getline(is, s.SNP);
    }

    return is;
}


int main() {

    student a1, a2, a3, a4, a5;

    std::vector<student> data = {a1, a2, a3, a4, a5};

    int number_of_students = 5;

    for (int i = 0; i < number_of_students; ++i) {

        std::cout << "Введите ФИО студентов : \n";
        std::getline(std::cin, data[i].SNP);
    }

    std::cout << "\n";

    int number_of_items = 4;

    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << "\t\t\tстудент : " << data[i].SNP << std::endl << std::endl;

        for (int j = 0; j < number_of_items; ++j) {
            std::cout << "введите оценку за сессию по предмету : " << data[j].dis[j].item << std::endl;
            std::cin >> data[i].dis[j].grade;
        }
    }

    std::sort(data.begin(), data.end(), [](const student &all, const student &all2) {
        return all.SNP < all2.SNP;
    });

    std::cout << "отсортированная группа студентов : " << std::endl;
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << data[i].SNP << std::endl;
    }
    std::cout << std::endl;

    int sum_m = 0;
    int sum_ph = 0;
    int sum_ch = 0;
    int sum_cs = 0;

    for (int i = 0; i < number_of_students; ++i) {
        sum_m += data[i].dis[0].grade;
        sum_ph += data[i].dis[1].grade;
        sum_ch += data[i].dis[2].grade;
        sum_cs += data[i].dis[3].grade;
    }

    double average_m = static_cast<double>(sum_m) / number_of_students;
    double average_ph = static_cast<double>(sum_ph) / number_of_students;
    double average_ch = static_cast<double>(sum_ch) / number_of_students;
    double average_cs = static_cast<double>(sum_cs) / number_of_students;

    std::array<double, 4> arr{average_m, average_ph, average_ch, average_cs};
    auto b = std::max_element(arr.begin(), arr.end());

    if (*b == average_m) {
        std::cout << "группой сдана лучше всего : Математика = " << average_m << std::endl;
    }
    if (*b == average_ph) {
        std::cout << "группой сдана лучше всего : Физика = " << average_ph << std::endl;
    }
    if (*b == average_ch) {
        std::cout << "группой сдана лучше всего : Химия = " << average_ch << std::endl;
    }
    if (*b == average_cs) {
        std::cout << "группой сдана лучше всего : Информатика = " << average_cs << std::endl;
    }

    std::cout << "\n\n";

    std::cout << "Средние баллы по предметам : \n\n";
    std::cout << "Математика = " << average_m << std::endl;
    std::cout << "Физика = " << average_ph << std::endl;
    std::cout << "Химия = " << average_ch << std::endl;
    std::cout << "Информатика = " << average_cs << std::endl;

    std::cout << "\n\n";

    std::ofstream fout;
    fout.open("myFile.txt");
    if (fout.is_open()) {
        std::cout << "файл открыт" << std::endl;
        fout << data;
    } else {
        std::cout << "ошибка открытия файла" << std::endl;
    }
    fout.close();

    std::ifstream fin;
    fin.open("myFile.txt");
    std::vector<student> data2;
    if (fin.is_open()) {
        fin >> data2;
    } else {
        std::cout << "ошибка открытия файла" << std::endl;
    }
    fin.close();

    std::ofstream fout1;
    fout1.open("myFile1.txt");
    fout1 << data2;
    fout1.close();
}


