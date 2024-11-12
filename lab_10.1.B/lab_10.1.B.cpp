#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <string.h>

using namespace std;

#pragma region enums
enum Majors {
	ComputerScience = 1,
	Informatics,
	MathematicsAndEconomics,
	PhysicsAndInformatics,
	LaborTraining
};
enum Subjects {
	Physics = 1,
	Math,
	Prog,
	Num_methods,
	Pedagogika
};
#pragma endregion enums

#pragma region student_struct
#pragma pack(push, 1) //less memory using
struct Student {
	string return_prizv() {
		return this->prizv;
	}
	unsigned short return_course() {
		return this->course;
	}
	string return_major_name() {
		switch (this->major) {
		case ComputerScience:
			return "Комп'ютерні науки";
		case Informatics:
			return "Інформатика";
		case MathematicsAndEconomics:
			return "Математика & Економіка";
		case PhysicsAndInformatics:
			return "Фізика & Інформатика";
		case LaborTraining:
			return "Трудове навчання";
		}
	}
	Majors return_major() {
		return this->major;
	}
	unsigned short return_physics() {
		return this->physics;
	}
	unsigned short return_math() {
		return this->math;
	}
	unsigned short return_prog() {
		return this->prog;
	}
	unsigned short return_num_methods() {
		return this->num_methods;
	}
	unsigned short return_pedagogika() {
		return this->pedagogika;
	}
	unsigned short return_third() {
		switch (this->major) {
		case ComputerScience:
			return this->prog;
		case Informatics:
			return this->num_methods;
		default:
			return this->pedagogika;
		}
	}
	void fill_struct(int i) {
		int temp;
		cout << "Студент №" << i + 1 << endl;
		cout << "Прізвище: "; cin >> this->prizv;
		cout << "Курс: "; cin >> this->course;
		cout << "Спеціальність \n\n(Комп'ютерні науки = 1, \nІнформатика = 2, \nМатематика & Економіка = 3, \nФізика & Інформатика = 4, \nТрудове навчання = 5)\n\n: "; cin >> temp;
		this->major = (Majors)temp;
		cout << "Оцінка з фізики: "; cin >> this->physics;
		cout << "Оцінка з математики: "; cin >> this->math;
		switch (this->major) {
		case ComputerScience:
			cout << "Оцінка з програмування: "; cin >> this->prog;
			break;
		case Informatics:
			cout << "Оцінка з чисельних методів: "; cin >> this->num_methods;
			break;
		case MathematicsAndEconomics:
			cout << "Оцінка з педагогіки: "; cin >> this->pedagogika;
			break;
		case PhysicsAndInformatics:
			cout << "Оцінка з педагогіки: "; cin >> this->pedagogika;
			break;
		case LaborTraining:
			cout << "Оцінка з педагогіки: "; cin >> this->pedagogika;
			break;
		}
	}
private:
	string prizv;
	unsigned short course;
	Majors major;
	unsigned short physics;
	unsigned short math;
	union {
		unsigned short prog;
		unsigned short num_methods;
		unsigned short pedagogika;
	};
};
#pragma pack(pop)    // return old config 
#pragma endregion student_struct

#pragma region functions
void fill_arr(Student* arr, int n) {
	for (int i = 0; i < n; i++) {
		arr[i] = Student();
		arr[i].fill_struct(i);
		cout << endl;
	}
}

int calc_n(int n) {
	int res = 0;
	while (n != 0) {
		n /= 10;
		res++;
	}
	return res;
}

int lenOfLongestPrizv(Student* arr, int n) {
	int res = -1;
	for (int i = 0; i < n; i++) {
		if (static_cast<int>(arr[i].return_prizv().length()) > res) {
			res = static_cast<int>(arr[i].return_prizv().length());
		}
	}
	return res;
}

void printHeader(Student* arr, int n) {
	int width = lenOfLongestPrizv(arr, n);
	(width <= 8) ? (width = 8) : (NULL);
	int maxDigits = calc_n(n);

	for (int i = 0; i < (maxDigits - 1) + (width - 8) + 111; i++) {
		cout << "=";
	}
	cout << endl;

	cout << "|" << setw(maxDigits) << right << "№";
	cout << "|" << setw(width) << left << "Прізвище" << "| Курс |     Спеціальність    | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |" << endl;

	for (int i = 0; i < (maxDigits - 1) + (width - 8) + 111; i++) {
		cout << "-";
	}
	cout << endl;

	for (int i = 0; i < n; i++) {
		cout << "|" << setw(maxDigits) << right << i + 1;
		cout << "|" << setw(width) << left << arr[i].return_prizv();
		cout << "|" << setw(6) << left << arr[i].return_course();
		cout << "|" << setw(22) << left << arr[i].return_major_name();
		cout << "|" << setw(8) << left << arr[i].return_physics();
		cout << "|" << setw(12) << left << arr[i].return_math();
		cout << "|" << setw(15) << left; 
		(arr[i].return_major() == ComputerScience ? cout << arr[i].return_prog() : cout << "-");
		cout << "|" << setw(17) << left;
		(arr[i].return_major() == Informatics ? cout << arr[i].return_num_methods() : cout << "-");
		cout << "|" << setw(12) << left;
		(arr[i].return_major() != ComputerScience && arr[i].return_major() != Informatics ? cout << arr[i].return_pedagogika() : cout << "-");
		cout << setw(13) << "|" << endl;
	}

	for (int i = 0; i < (maxDigits - 1) + (width - 8) + 111; i++) {
		cout << "-";
	}
	cout << endl;
}

int counter(Student* arr, int n) {
	int result = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i].return_physics() == 4 || arr[i].return_physics() == 5) {
			result++;
		}
	}
	return result;
}

float average(Student* arr, int n, Subjects subject) {
	unsigned short sum = 0;
	int counter = 0;

	for (int i = 0; i < n; i++) {
		switch (subject) {
		case Physics:
			sum += arr[i].return_physics();
			counter++;
			break;

		case Math:
			sum += arr[i].return_math();
			counter++;
			break;

		case Prog:
			if (arr[i].return_third() == ComputerScience) {
				sum += arr[i].return_third();
				counter++;
			}
			break;

		case Num_methods:
			if (arr[i].return_third() == Informatics) {
				sum += arr[i].return_third();
				counter++;
			}
			break;

		case Pedagogika:
			if (arr[i].return_third() != ComputerScience && arr[i].return_third() != Informatics) {
				sum += arr[i].return_third();
				counter++;
			}
			break;

		default:
			cout << "Wrong subject" << endl;

			return -1;
		}
	}

	return sum / (float)counter;
}
#pragma endregion functions

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n;
	cout << "Введіть кількість студентів: "; cin >> n;

	Student* arr = new Student[n];
	fill_arr(arr, n);

	printHeader(arr, n);

	cout << "Середнє арифметичне з фізики: " << average(arr, n, Physics) << endl;
	cout << "Середнє арифметичне з математики: " << average(arr, n, Math) << endl;
	cout << "Середнє арифметичне з програмування: " << average(arr, n, Prog) << endl;
	cout << "Середнє арифметичне з чисельних методів: " << average(arr, n, Num_methods) << endl;
	cout << "Середнє арифметичне з педагогіки: " << average(arr, n, Pedagogika) << endl << endl;

	cout << "Кількість студентів, які отримали 4 або 5 з фізики: " << counter(arr, n) << endl;
	delete[] arr;
}