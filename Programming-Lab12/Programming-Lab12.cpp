#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>

using namespace std;

const char delimiter = '_';
const int insert_words_count = 2;
string base[] = { "СЬОГОДНІ","ЧИМДУЖ","МОЖЛИВО","ДОЩИТЬ","СТРІЛЯТИ","СИЛЬНО","ДЕРЕВО","ЗМІСТОВНО","ВЕЛИКИЙ","ВОГОНЬ" };
const int base_size = size(base);

void ToUpper(string& s)
{
	int len = s.length();
	for (int i = 0; i < len; i++)
	{
		s[i] = toupper(s[i]);
	}
}

string EncodeMessage(string message)
{
	int delim_pos = -1;
	do
	{
		string to_insert;
		for (int i = 0; i < insert_words_count; i++)
		{
			to_insert += base[rand() % base_size] + delimiter;
		}
		message.insert(delim_pos + 1, to_insert);
		delim_pos = message.find(delimiter, delim_pos + to_insert.length() + 1);
	} while (delim_pos != string::npos);
	return message;
}

string DecodeMessage(string message)
{
	int delim_pos = 0;
	do
	{
		int right_bound = delim_pos;
		for (int i = 0; i < insert_words_count; i++)
		{
			right_bound = message.find(delimiter, right_bound + 1);
		}
		message.erase(delim_pos, right_bound - delim_pos + 1);
		delim_pos = message.find(delimiter, delim_pos + 1);
	} while (delim_pos++ != string::npos);
	return message;
}

int main()
{
	srand(time(0));

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Ukrainian");

	cout << "Введіть речення:\n";
	string message;
	getline(cin, message, '\n');
	ToUpper(message);
	cout << "\nРечення, що шифрується:\n" << message << '\n';

	string encoded_message = EncodeMessage(message);
	cout << "\nЗашифроване речення:\n" << encoded_message << '\n';

	string decoded_message = DecodeMessage(encoded_message);
	cout << "\nДешифроване речення:\n" << decoded_message << '\n';

	cin.get();
}