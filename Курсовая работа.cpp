#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

void qsort(int* mas, int size);
void sravn();


char k[] = {'а','б','в','г','д','е','ё'};
int main()
{
	setlocale(LC_ALL, "Rus");
    int count = 0;
    vector <string> words;
	ifstream file;
	string n;
	cout << "Введите название файла по типу: '13.txt'" << endl;
	cin >> n;
	file.open(n);
	if (file.is_open())
	{
		cout << "Файл открыт!";
	}
	else
	{
		cout << "Не удалось открыть файл";
	}
	while (!file.eof())
	{
		n.clear();
		file >> n;
        words.push_back(n);
        count++;
		//cout << n << endl;
	}
    for (int i = 0; i < count; i++)
    {
        cout << words[i] << endl;
    }
    cout << words.size();

	file.close();
    
}

void qsort(int* mas, int size) {
    //Указатели в начало и в конец массива
    int i = 0;
    int j = size - 1;

    //Центральный элемент массива
    int mid = mas[size / 2];

    //Делим массив
    do {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
        while (mas[i] < mid) {
            i++;
        }
        //В правой части пропускаем элементы, которые больше центрального
        while (mas[j] > mid) {
            j--;
        }

        //Меняем элементы местами
        if (i <= j) {
            int tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);


    //Рекурсивные вызовы, если осталось, что сортировать
    if (j > 0) {
        //"Левый кусок"
        qsort(mas, j + 1);
    }
    if (i < size) {
        //"Првый кусок"
        qsort(&mas[i], size - i);
    }
}

void sravn()
{

}