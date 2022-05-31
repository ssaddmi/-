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

void qsort(string *words, int first, int N);
void squeeze(string &n);
int test(char i);
bool rus(char x);
void counter(vector <string> words, vector<int>& an, char alp[32]);
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
    
	ifstream file;
	string n;
    string a;
	cout << "Введите название файла по типу: '13.txt'" << endl;
	cin >> a;
	file.open(a);
    //file.open("13.txt");
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
        squeeze(n);
        words.push_back(n);
        
	}
    file.close();
    
    for (int i = 0; i < words.size(); i++)
    {
        cout << words[i] << '\n';
    }

    for (int i = 0; i < words.size(); i++)
    {
        
        auto it = words.begin();
        if (words[i][0] >= '0' && words[i][0] <= '9')
        {
            numbers.push_back(words[i]);
            words.erase(it + i);
            i--;
            
        }
        else if (words[i][0] == '\0')
        {
            words.erase(it + i);
            i--;
        }
        else if (rus(words[i][0]) == false)
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
        convert(words[i]);
        lower.push_back(words[i]);
    }
    counter(lower, an, alp);

    
    string b = "Analysis";
    b += a;
    ofstream analysis(b);
    if (analysis.is_open())
    {
        analysis << "Вариант 5: кириллица, по алфавиту, по возрастанию, учитывать числа, быстрая сортировка" << endl << "Количество слов: " << words.size() << endl << /*"Время сортировки: " << (((float)time) / CLOCKS_PER_SEC) << " сек." << endl << */ "Статистика (кол-во слов по первой букве):" << endl;
        for (int i = 0; i < 33; i++)
        {
            analysis << endl << alp[i] << " - " << an[i];
        }
        if (numbers.size() > 0)
        {
            analysis << endl << "Также имеются числа: " << endl;
            for (int i = 0; i < numbers.size(); i++)
            {
                analysis << endl << numbers[i];
            }
        }
        if (different.size() > 0)
        {
            analysis << endl << "Также имеются неопределенные элементы: " << endl;
            for (int i = 0; i < different.size(); i++)
            {
                analysis << endl << different[i];
            }
        }
            
        // слова передаются в конверт, заполняются в вектор, после выполняется быстрая сортировка, затем результат записывается в файл
    }
    analysis.close();



    count = 0;
    count += words.size();
    int first = 0;
    

    string *S = new string[count];
    for (int i = 0; i < words.size(); i++)
    {
        S[i] = lower[i];
    }

    sort(S, count - 1);
    string c = "Test";
    c += a;
    ofstream Test(c);
    for (int i = 0; i < words.size(); i++)
    {
        Test << endl << S[i];
    }
    Test.close();
    delete[] S;
}

void squeeze(string &n)
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
int test(char i)
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
void counter(vector<string> words, vector<int>& an, char alp[32])
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
void convert(string& s)
{
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = tolower(s[i]);
    }
}

/*ФУНКЦИЯ СОРТИРОВКИ СТРОК*/
//void qsort(string *words, int first, int N)
//{
//    
//    int left = first, right = N;
//    int mid = (left+right)/2;
//    do
//    {
//        while (words[left][0] < words[mid][0]) left++;
//        while (words[right][0] > words[mid][0]) right--;
//
//        if (left <= right)
//        {
//            swap(words[left], words[right]);
//            
//            left++;
//            right--;
//        }
//    } while (left < right);
//
//    if (right > 0) qsort(words, first, right);
//    if (N > left) qsort(words + left,left, N);
//}



void sort(string* S, int N)
{
    long i = 0, j = N;
    string temp1, p;
    p = S[N >> 1];
    do
    {
        while (S[i] < p) i++;
        while (S[j] > p) j--;
        if (i <= j)
        {
            temp1 = S[i];
            S[i] = S[j];
            S[j] = temp1;
            i++;
            j--;
        }
    } while (i <= j);

    if (j > 0) sort(S, j);
    if (N > i) sort(S + i, N - i);
}