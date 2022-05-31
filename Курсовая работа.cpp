#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <locale>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <vector>

using namespace std;

void squeeze(string &n);
int test(char i);
bool rus(char x);
void counter(vector <string> words, vector<int>& an, char alp[33]);
void convert(string& s);
void sort(string* S, int N);

vector <string> different;
vector <string> words;
vector <string> numbers;
vector <string> lower;

int main()
{
	setlocale(LC_ALL, "Rus");
    int count = 0;
    string n;
    string a;
	ifstream file;
	cout << "Введите название файла по типу: '13.txt'" << endl;
	cin >> a;
	file.open(a);
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
        squeeze(n); //функция, которая удаляет лиишние символы(знаки препинания и прочие)
        words.push_back(n);  //добавление всех возможных слов и чисел в массив
        
	}
    file.close();

    for (int i = 0; i < words.size(); i++)
    {
        
        auto it = words.begin();
        if (words[i][0] >= '0' && words[i][0] <= '9') //добавление чисел в отедльный массив и удаление из основного массива слов
        {
            numbers.push_back(words[i]);
            words.erase(it + i);
            i--;
            
        }
        else if (words[i][0] == '\0') //удаление пустых строк
        {
            words.erase(it + i);
            i--;
        }
        else if (rus(words[i][0]) == false) //добавление неопределенных слов в отдельных массив и удаление их из основного элемента
        {
            different.push_back(n);
            words.erase(it + i);
            i--;
        }
        
    }
    
    
    char alp[33] = { 'а','б','в','г','д','е','ё','ж','з','и','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','э','ю','я' };
    vector<int> an(33);
    for (int i = 0; i < words.size(); i++)
    {
        convert(words[i]); //функция, которая конвертирует слова в слова с нижним регистром
        lower.push_back(words[i]); //добавление обработанных слов в отдельный массив
    }
    counter(lower, an, alp); //подсчет статистики количества слов в файле на определенную букву


    count = 0;
    count += words.size();
    int first = 0;


    string* S = new string[count]; 
    for (int i = 0; i < words.size(); i++)
    {
        S[i] = lower[i]; //заполнение динамического массива
    }
    clock_t t; //Вычисляет реальное прошедшее время для процесса.
    t = clock();
    sort(S, count - 1);
    t = clock() - t; 

    string c = "Result";
    c += a;
    ofstream Test(c);
    for (int i = 0; i < words.size(); i++) //запись в файл отсортированных слов
    {
        Test << S[i] << "\n";
    }
    Test.close();
    delete[] S;

    
    string b = "Analysis";
    b += a;
    ofstream analysis(b);
    if (analysis.is_open()) //запись в файл статистики слов, времени работы сортировки и т.д.
    {
        analysis << "Вариант 5: кириллица, по алфавиту, по возрастанию, учитывать числа, быстрая сортировка" << endl << "Количество слов: " << words.size() << endl << "Время сортировки: " << (((float)t) / CLOCKS_PER_SEC) << " сек." << endl <<  "Статистика (кол-во слов по первой букве):" << endl;
        cout << endl << "Вариант 5: кириллица, по алфавиту, по возрастанию, учитывать числа, быстрая сортировка" << endl << "Количество слов: " << words.size() << endl << "Время сортировки: " << (((float)t) / CLOCKS_PER_SEC) << " сек." << endl <<  "Статистика (кол-во слов по первой букве):" << endl;
        for (int i = 0; i < 33; i++)
        {
            analysis << alp[i] << " - " << an[i] << "\n";
            cout << alp[i] << " - " << an[i] << "\n";
        }
        if (numbers.size() > 0)
        {
            analysis << endl << "Также имеются числа: " << "\n";
            cout << endl << "Также имеются числа: " << "\n";
            for (int i = 0; i < numbers.size(); i++)
            {
                analysis <<  numbers[i] << "\n";
                cout << numbers[i] << "\n";
            }
        }
        if (different.size() > 0)
        {
            analysis << endl << "Также имеются неопределенные элементы: " << "\n";
            cout << endl << "Также имеются неопределенные элементы: " << "\n";
            for (int i = 0; i < different.size(); i++)
            {
                analysis << different[i];
                cout << different[i];
            }
        }
            
        // слова передаются в конверт, заполняются в вектор, после выполняется быстрая сортировка, затем результат записывается в файл
    }
    analysis.close();



    
}

void squeeze(string &n) //функция, которая удаляет лишние символы из слов: знаки препинания и прочие
{
    
    for (int i = 0; i < n.length() + 1; i++)
    {
        auto it = n.begin();
 
        while (test(n[i]) == false)
        {
            n.erase(it + i);
        }   
    }
}
int test(char i) //функция, которая проверяет элемент, выводит ложь, если элемент - знак препинания
{
    if (ispunct(i) || i == '№' || i == ' ')
        return false;
    else
        return true;
   
}
bool rus(char x) // Проверка на символ кириллицы
{
    if (x >= 'А' && x <= 'я')
    {
        return true;
    }
    else
    {
        return false;
    }
}
void counter(vector<string> words, vector<int>& an, char alp[33]) //функция, которая подсчиытвает количество слов на определенную букву
{
    int counter = 0;
    for (int i = 0; i < 33; i++)
    {
        for (int j = 0; j < words.size(); j++)
        {
            if (words[j][0] == alp[i])
            {
                counter++;
            }
        }
        an[i] = counter;
        counter = 0;
    }
}
void convert(string& s) //функция, приводящая слова к нижнему регистру 
{
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = tolower(s[i]);
    }
}

void sort(string* S, int N) //функция быстрой сортировки массива строк
{
    long i = 0, j = N; //Указатели в начало и в конец массива
    string mid;
    mid = S[N/2]; //Центральный элемент массива
    //Делим массив
    do
    {
        while (S[i] < mid) i++;//Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
        while (S[j] > mid) j--;//В правой части пропускаем элементы, которые больше центрального
        if (i <= j)
        {
            //Меняем элементы местами
            swap(S[i], S[j]);
            i++;
            j--;
        }
    } while (i <= j);
    //Рекурсивные вызовы, если осталось, что сортировать
    if (j > 0) sort(S, j);//"Левый кусок"
    if (N > i) sort(S + i, N - i);//"Првый кусок"
}