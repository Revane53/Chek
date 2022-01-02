#include <iostream>
#include <string>

using namespace std;

enum products { apples = 1, oranges, pineapples, pears };
struct product
{
	double price;
	int count;
};
product apple{ 50.65,120 }, orange{ 70,24 }, pineapple{ 150,99 }, pear{ 23.84,3 };


int InputValidation(int productcount);
int CopyingArray(int*& array, int size);
int CopyingArray(double*& array, int size);
int ProductSelection(int const i, int const& apple, int const& orange, int const& pineapple, int const& pears);
int IsThereProduct(int const& userinput, int const& apple, int const& orange, int const& pineapple, int const& pear);
double OrderCost(int*& nameproduct, int*& count, int length);
void DichotomousQuestion(int& answer, string& question);
double DailyEarnings(double*& array, int length);
void ResetArray(double*& array);
void ResetArray(int*& array);

int main()
{
	setlocale(LC_ALL, "ru");

	int i = 0, j = 0, user_product, user_product_count = 0, productcount, length = 1, endproduct = 0;
	string ChangeOfBuyer = "\t\t\tПерейти к следующему покупателю ? \n";
	string IncomeRequest = "\t\t\tПросмотр дневной выручки\n";
	string DiscountCard = "\t\t\tЕсть ли фирменная дисконтная карта (7%) ? \n";
	int* count = new int[length];
	int* nameproduct = new int[length];
	double* proceeds = new double[length];

	do
	{

		int k = 1;

		do
		{
			system("cls");
			cout << "\t\t\t\t Клиент № " << j + 1 << endl;
			cout << "\t\t\tДоступные товары для покупки\n";
			if (apple.count > 0)
				cout << "\t 1 -- Яблоки   в колличестве  " << apple.count << " штук   " << apple.price << " рублей за штуку\n";
			else
				cout << "\t 1 -- Яблоки закончились\n";
			if (orange.count > 0)
				cout << "\t 2 -- Апельсины   в колличестве  " << orange.count << " штук   " << orange.price << " рублей за штуку\n";
			else
				cout << "\t 2 -- Апельсины закончились\n";
			if (pineapple.count > 0)
				cout << "\t 3 -- Ананасы   в колличестве  " << pineapple.count << " штук   " << pineapple.price << " рублей за штуку\n";
			else
				cout << "\t 3 -- Ананасы закончились\n";
			if (pear.count > 0)
				cout << "\t 4 -- Груши   в колличестве  " << pear.count << " штук   " << pear.price << " рублей за штуку\n";
			else
				cout << "\t 4 -- Груши закончились\n";
			cout << "\t 5 -- Закончить обслуживание клиента \n\n\n";




			user_product = ProductSelection(k, apple.count, orange.count, pineapple.count, pear.count);

			if (user_product == 5)
			{
				int answer;
				DichotomousQuestion(answer, DiscountCard);
				if (answer == 1)
					proceeds[j] = OrderCost(nameproduct, count, length) * 0.93;
				else
					proceeds[j] = OrderCost(nameproduct, count, length);
				ResetArray(count);
				ResetArray(nameproduct);
				system("cls");
				cout << "\tИТОГО: " << proceeds[j] << " рублей" << endl;
				system("pause");
				break;
			}
			else
			{
				length = i + 1;

				if (i != 0)
				{
					CopyingArray(count, length);
					CopyingArray(nameproduct, length);
				}
				nameproduct[i] = user_product;
			}


			switch (user_product)
			{
			case apples:
				productcount = apple.count;
				count[i] = InputValidation(productcount);
				apple.count -= count[i];
				break;
			case oranges:
				productcount = orange.count;
				count[i] = InputValidation(productcount);
				orange.count -= count[i];
				break;
			case pineapples:
				productcount = pineapple.count;
				count[i] = InputValidation(productcount);
				pineapple.count -= count[i];
				break;
			case pears:
				productcount = pear.count;
				count[i] = InputValidation(productcount);
				pear.count -= count[i];
				break;
			}
			system("cls");

			i++;
			k++;

			if (apple.count == 0 && orange.count == 0 && pineapple.count == 0 && pear.count == 0)
			{
				int answer;
				DichotomousQuestion(answer, DiscountCard);
				if (answer == 1)
					proceeds[j] = OrderCost(nameproduct, count, length) * 0.93;
				else
					proceeds[j] = OrderCost(nameproduct, count, length);
				endproduct = 1;
				system("cls");
				cout << "\tИТОГО: " << proceeds[j] << " рублей" << endl;
				system("pause");
				break;
			}

		} while (true);


		if (endproduct == 1)
		{
			cout << "\tДневная выручка составляет  " << proceeds[j] << " рублей\n";
			system("pause");
			return 0;
		}


		int answer = 0;
		DichotomousQuestion(answer, ChangeOfBuyer);

		if (answer == 1)
		{
			j++;
			CopyingArray(proceeds, j + 1);
		}
		else
		{
			DichotomousQuestion(answer, IncomeRequest);
			if (answer == 1)
			{
				cout << "\tДневная выручка составляет  " << DailyEarnings(proceeds, j + 1) << " рублей\n";
				system("pause");
			}
			break;
		}

	} while (true);
}


int InputValidation(int productcount)
{
	do
	{
		int userinput;
		cout << "\tВведите количество товара которое хотят купить\n";
		cin >> userinput;
		if (userinput > productcount)
			cout << "В наличии товара меньше чем нужно\n"
			<< "В наличии " << productcount << " штук  а запрашиваете  " << userinput << endl;
		else if (userinput < 0)
			cout << "\tКолличество товара не может быть отрицательным\n\n";
		else if (userinput == 0)
			cout << "\tКолличество покупаемого товара не может быть равно 0\n\n";
		else
			return userinput;
	} while (true);
}
int CopyingArray(int*& array, int size)
{
	int* newarray = new int[size];
	for (int i = 0; i < size; i++)
		newarray[i] = array[i];
	delete[] array;
	array = newarray;
	return 0;
}
int CopyingArray(double*& array, int size)
{
	double* newarray = new double[size];
	for (int i = 0; i < size; i++)
		newarray[i] = array[i];
	delete[] array;
	array = newarray;
	return 0;
}
int ProductSelection(int const i, int const& apple, int const& orange, int const& pineapple, int const& pears)
{
	do
	{
		int userinput;
		cout << "\t" << i << " позиция\n";
		cout << "\tВыберете товар от 1 до 4\n";
		cin >> userinput;
		if (userinput == 5)
			return 5;
		else if (userinput >= 1 && userinput < 5)
		{
			if (IsThereProduct(userinput, apple, orange, pineapple, pears) == 1)
				return userinput;
			else
				cout << "\tТовар закончился\n\n";
		}
		else
			cout << "Не существующий товар, попробуйте снова\n";
	} while (true);
}
int IsThereProduct(int const& userinput, int const& apple, int const& orange, int const& pineapple, int const& pear)
{
	switch (userinput)
	{
	case apples:
		if (apple > 0)
			return 1;
		else
			return 0;
	case oranges:
		if (orange > 0)
			return 1;
		else
			return 0;
	case pineapples:
		if (pineapple > 0)
			return 1;
		else
			return 0;
	case pears:
		if (pear > 0)
			return 1;
		else
			return 0;
	}
}
double OrderCost(int*& nameproduct, int*& count, int length)
{
	double sum = 0;
	for (int i = 0; i < length; i++)
	{
		switch (nameproduct[i])
		{
		case apples:
			sum += count[i] * apple.price;
			break;
		case oranges:
			sum += count[i] * orange.price;
			break;
		case pineapples:
			sum += count[i] * pineapple.price;
			break;
		case pears:
			sum += count[i] * pear.price;
			break;
		}
	}
	return sum;
}
void DichotomousQuestion(int& answer, string& question)
{
	do
	{
		system("cls");
		cout << question;
		cout << "\t\t\t\t1 -- ДА         2 -- НЕТ\n";
		cin >> answer;
	} while (answer < 1 || answer > 2);

}
double DailyEarnings(double*& array, int length)
{
	double sum = 0;
	for (int i = 0; i < length; i++)
	{
		sum += array[i];
	}
	return sum;
}
void ResetArray(int*& array)
{
	delete[] array;
	array = new int[1];
}
void ResetArray(double*& array)
{
	delete[] array;
	array = new double[1];
}
