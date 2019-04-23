#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <tuple>
#include <algorithm>

using namespace std;
using Graphic = set<std::pair<int, int>>;

void FillSet(Graphic& g, int n) {//заполняет график значениями, введенными с клавиатуры
	for (int i = 0; i < n; i++) {//
		int first, second;
		cin >> first >> second;//Принимает значение элемента
		g.insert({ first,second });//создает и записывает кортеж в график
	}
}

Graphic Union(const Graphic& first, const Graphic& second) {//операция объединения
	Graphic result;//создаем пустой график С
	for (const auto& x : first) {//берем эдементы графика А
		result.insert(x);//записываем элементы графика А в график С
	}
	for (const auto& y : first) {//берем  элемент графика А
		for (const auto& x : second) {//берем  элемент графика В
			if (x != y) {//сравниваем выбранные элементы графика А и с выбранным элемнтом графика В
				result.insert(x);//если не равен(если равен, то идем в пункт 2), то добавляем в график С, если равен, то переходим в пункт 1 и берем следующий элемент А
			}
		}
	}
	return result;
}

Graphic Intersection(const Graphic& first, const Graphic& second) {//операция пересечения 
	Graphic result;//создаем пустой график
	for (const auto& item_first : first) {//берем  элемент графика А
		for (const auto& item_second : second) {//берем  элемент графика В
			if (item_first == item_second) {//сравниваем выбранный элемент множества А с выбранным элементом множества В
				result.insert(item_first);//если равен(если не равен, то идем в пункт 2), то добавляем в множество С, переходим в пункт 1 и берем следующий элемент А
			}
		}
	}
	return result;
}

Graphic Difference(const Graphic& first, const Graphic& second) {// Операция разности
	Graphic result;//создаем пустой график С
	for (const auto& item_first : first) {// Берем элемент графика А
		auto it = find(second.begin(), second.end(), item_first);//Берем элемент графика В и сравниваем с элементом графика А
		if (it == second.end()) {//Если данного эл-та нету в графкие В, то записываем его в график С
			result.insert(item_first);
		}
	}
	return result;
}



Graphic SymmetryDifference(const Graphic& first, const Graphic& second) {//Операция Симметрической разности
	Graphic result(move(Difference(first, second))); //записываем в график С разность между графиками А и В
	for (const auto& x : Difference(second, first)) {  //Берем элемент разности между графиками В и А
		result.insert(x);//записываем в график С
	}
	return result;
}



Graphic Inversion(const Graphic& graphic) {
	Graphic result;//создаем пустой график С
	for (const auto& [first, second] : graphic) {//берем элемент графика А
		result.insert({ second,first });//записываем инверсированный кортеж элемента из графика А в график С
	}
	return result;
}

Graphic Composition(const Graphic& first_graphic, const Graphic& second_graphic) {
	Graphic result;//создаем пустой график С
	for (const auto& [first, second] : first_graphic) {//берем элемент графика А
		auto it = find_if(second_graphic.begin(), second_graphic.end(), [second](const pair<int, int> & p) {//Если вторая компонента выбранного кортежа графика А 
			return p.first == second;
			});
		if (it != second_graphic.end()) {//равна первой компоненте выбранного кортежа графика В
			result.insert({ first,it->second });//Создаем новый кортеж
					// Первой компонентой нового кортежа является первая компонента выбранного кортежа А.
					//Второй компонентой нового кортежа является вторая компонента выбранного кортежа B.
					//Записываем новый кортеж в график J.
		}
	}
	return result;
}

std::ostream& operator<<(std::ostream& out, const set<std::pair<int, int>>& s) {
	out << "{";
	if (s.size() == 0) {
		out << "}";
		return out;
	}
	for (auto it = s.begin(); it != s.end(); it++) {

		if (it != prev(s.end())) {
			out << "<" << it->first << ", " << it->second << ">, ";
		}
		else {
			out << "<" << it->first << ", " << it->second << ">}";
		}
	}
	return out;
}

void Menu() {//выбор операции
	cout << "1 - выводит объединение графиков" << std::endl << "2 - выводит пересечение графиков" << std::endl
		<< "3 - выводит разность графиков" << std::endl
		<< "4 - выводит симметрическую разность графиков" << std::endl
		<< "5 - выводит инверсию графиков" << std::endl
		<< "6 - выводит композицию графиков" << std::endl
		<< "7 - выйти из программы" << std::endl;
}



int main() {
	setlocale(LC_ALL, "ru");
	Graphic first, second;//создаем пустые графики А и В
	int first_amount, second_amount;
	cout << "Введите размер графикова\n";
	cin >> first_amount >> second_amount;//Вводим размеры графиков А и В
	cout << "Введите элементы первого графика\n";
	FillSet(first, first_amount);
	cout << "Ваш первый график: " << first << endl;
	cout << "Введите элементы второго графика\n";
	FillSet(second, second_amount);
	cout << "Ваш второй график: " << second << endl;

	while (true) {
		Menu();//Перечисление всех операций
		cout << "Введите номер команды\n";
		int number;
		cin >> number;
		switch (number)//Выбор операции
		{
		case 1: {//операция объединения
			cout << "Объединение двух графиков: " << Union(first, second) << std::endl;
			break;
		}
		case 2: {//операция пересечения 
			cout << "Пересечение двух графиков: " << Intersection(first, second) << std::endl;
			break;
		}
		case 3: {//операция разности 
			int k;
			cout << "Введите номер операции\n1. Операция разности между графикамм А и В (А\\В)\n2. Операция разности между графикамм B и A (B\\A)\n";
			cin >> k;
			switch (k)//Выбор операций
			{
			case 1: {
				cout << "Разность  графиков A и B: " << Difference(first, second) << std::endl;
				break;
			}
			case 2: {
				cout << "Разность  графиков B и A: " << Difference(second, first) << std::endl;
				break;
			}
			default:
				break;
			}

			break;
		}
		case 4: {//операция симметрической разности 
			cout << "Симметрическая разность: " << SymmetryDifference(first, second) << std::endl;
			break;
		}

		case 5: {//операция инверсия 
			int k;
			cout << "Введите номер операции\n1 - Инверсия графика А\n2 - Инверсия графика В\n";
			cin >> k;
			switch (k)
			{
			case 1: {
				cout << "Инверсия графика A: " << Inversion(first) << std::endl;
				break;
			}
			case 2: {
				cout << "Инверсия графика B: " << Inversion(second) << std::endl;
				break;
			}
			default:
				break;
			}

			break;
		}
		case 6: {//операция композиция
			int k;
			cout << "Введите номер операции\n1 - Композиция графиков А и В (А x В)\n2 - Композиция графиков B и А (B x A)\n";
			cin >> k;
			switch (k)
			{
			case 1: {
				cout << "Композиция графиков А и В (А x В): " << Composition(first, second) << std::endl;
				break;
			}
			case 2: {
				cout << "Композиция графиков B и А (B x A): " << Composition(second, first) << std::endl;
				break;
			}
			default:
				break;
			}
			break;

		}
		case 7: {//операция выхода
			return 0;
		}
		default: {
			cout << "Вы ввели неправильную команду\n";
			break;
		}
		}
	}
}