	// револьвер
	// всего есть 6 позиций, юзер вводит кол-во патронов, в зависимости от этого позиции заполняются
	// юзер "куртит барабан" и патроны попадают в рандомные позиции, сохраняя последовательность

// Добавить ставки 
// 

#include <iostream>
#include <stdlib.h>
#include <ctime> //чтобы rand норм работало
using namespace std;

int NewFillArrBullets(int arrNewBullets[], int RefConsiderBullets, const int SizeDrum) // Сздаёт новый массив с другим расположением патронов
{
	int StartWith, ConsiderBullets;
	StartWith = rand() % 5; // число от которого будем заполнять массив
	ConsiderBullets = RefConsiderBullets; //задаём переменной значение по ссылке, т к это значение должно оставаться неизменным 

	if (StartWith != 5)
	{
		for (int i = StartWith; i < SizeDrum;) // тут заполняем массив 1ами от элемента (переменнаой) а до конца массива, если в ConsiderBullets ещё что-то осталось, то работает следующий if
		{
			if (ConsiderBullets == 0)
			{
				break;
			}
			else
			{
				arrNewBullets[i] = 1;	// добавляем патрон в барабан
				ConsiderBullets--;	
			}
			i++;
		}
	}
	int c = 0;
	if (ConsiderBullets != 0)
	{
		for (int i = c; i < SizeDrum;)  // Всё, что осталось в ConsiderBullets мы закидываем в начало массива с патронами 
		{
			if (ConsiderBullets == 0)
			{
				break;
			}
			arrNewBullets[i] = 1;
			ConsiderBullets--;
			i++;
		}
		return arrNewBullets[SizeDrum]; // возврат из функции нового массива
	}
}

int FillArrBullets(int arrBullets[], const int SizeDrum, int RefConsiderBullets)
{
	int Bullets = 0;
	for (int i = Bullets; i < SizeDrum;) // заполняем массив патронами, 1- патрон есть, 0- патрона нет

	{

		arrBullets[i] = 1; // 0-ой эл массива = 1
		if (i == 5)
		{
			cout << "больше нет места" << endl;
			break;
		}
		else
		{
			cout << "Патрон добавлен!" << endl;
			cout << "(1 - добавить ещё патрон 2 - крутить барабан)\n>>> ";
			int choice1;
			cin >> choice1;
			if (choice1 == 2)
			{
				for (int j = i + 1; j < SizeDrum;) // заполняем нулями остальные элементы массива 
				{
					arrBullets[j] = 0;
					j++;
				}
				break;
			}
		}
		i++;
	}

	for (int i = 0; i < SizeDrum;) // считаем кол-во пуль в барабане 
	{
		if (arrBullets[i] == 1)
		{
			RefConsiderBullets++;
		}
		i++;
	}
	return RefConsiderBullets;
}

// ставки сюда

void SearchWiner(int& RefAmountPlayers, int* ArrDied, int PlayersLeft)
{
	int* ArrWiners = new int[PlayersLeft];

	for (int i = 1, k = 0, j = 0; i < RefAmountPlayers + 1;)
	{
		if (i == ArrDied[j])
		{
			i++;
		}
		else
		{
			while (j < 6)
			{
				if (i == ArrDied[j])
				{
					break;
				}
				else
				{
					j++;
				}
			}
			if (j == 6)
			{
				ArrWiners[k] = i;
				k++;
				j = 0;
			}
			i++;
		}
	}
	//cout << "\nArrWiners ";
	for (int i = 0; i < PlayersLeft; i++)
	{
		cout << "Победил игрок номер: " << ArrWiners[i] << endl;
	}
	delete[] ArrWiners;
}

void Play(int arrNewBullets[], int SizeDrum, int RefConsiderBullets, int PlayerNum) // играем
{
	int& RefPlayerNum = PlayerNum;
	int AmountPlayers = 0;
	int& RefAmountPlayers = AmountPlayers;
	while (true) // узнаём кол-во игроков 
	{
		cout << "\nСколько игроков? (не больше 6)\n>>> ";
		cin >> AmountPlayers;
		if (0 < AmountPlayers && AmountPlayers < 7)
		{
			break;
		}
		else
		{
			cout << "Неверно!" << endl;
		}
	}

	int a = 0, b = 0; //счётчики для работы с массивами
	cout << "\n\tОчередь игрока номер: " << RefPlayerNum + 1 << endl;

	int* ArrDied = new int[SizeDrum]; // создаём массив для выбывших челов и заполняем его нулями 
	for (int k = 0; k < SizeDrum;)
	{
		ArrDied[k] = 0;
		k++;
	}

	for (RefPlayerNum; RefPlayerNum < SizeDrum;)//стреляем
	{
		int choice;
		cout << "\tХотите сдаться? (1 - нет! 2 - я сдаюсь.) \n>>> ";
		cin >> choice;
		if (choice == 2)
		{
			cout << "Игрок номер " << RefPlayerNum + 1 << " выбывает" << endl;
			ArrDied[b] = RefPlayerNum + 1; // закидываем номер выбывшего игрока в массив 
		}
		else if (arrNewBullets[a] == 1)				
		{
			RefConsiderBullets--;	// т к был выстрел патронов в барабане стало на 1 меньше 
			a = 0;	// чтобы после "прокрутки" не продложали идти по массиву с текущего элемента, а начали сначала
			cout << "ВЫСТРЕЛ!!! (Игрок номер " << RefPlayerNum + 1 << " выбывает)" << endl;
			ArrDied[b] = RefPlayerNum + 1; //закидываем номер выбывшего игрока в массив 
			b++;

			//cout << "'Крутим барабан'" << endl;
			for (int i = 0; i < SizeDrum;) 
			{
				arrNewBullets[i] = 0;
				i++;
			}
			NewFillArrBullets(arrNewBullets, RefConsiderBullets, SizeDrum); // "крутим барабан"
		}
		else
		{
			cout << "В холостую!!!" << endl;
			a++;
		}
				
		//=================================================================================================		
		//проверка на то, не победил ли игрок уже
		int AmountDropoutPlayers = 0;
		int& RefADP = AmountDropoutPlayers;
		for (int i = 0; i < SizeDrum;) // считаем кол-во выбывших
		{
			if (ArrDied[i] != 0)
			{
				RefADP++;
				i++;
			}
			else
			{
				i++;
			}
		}
		// теперь мы должны посчитать, сколько ещё участников в игре 
		int PlayersLeft;
		PlayersLeft = RefAmountPlayers - RefADP;
		//выявляем победителя 
		if (PlayersLeft == 1) 
		{
			SearchWiner(RefAmountPlayers, ArrDied, PlayersLeft);
			delete[] ArrDied;
			return;
		}
		if (RefConsiderBullets == 0 && PlayersLeft > 1) //если победителя ещё нет и если все патроны закончились, то несколько победителей
		{
			SearchWiner(RefAmountPlayers, ArrDied, PlayersLeft);
			delete[] ArrDied;
			return;
		}
		//=================================================================================================		
		// если игрок ещё не победил - настраиваем очередь 

		RefPlayerNum++;
		bool d = true;
		bool& Refd = d;

		for (int i = 0; i < AmountPlayers;)
		{
			for (int i = 0; i < SizeDrum;) // этот цикл будет чекать массив выбывших, чтобы участники не повторялись
			{
				if (ArrDied[i] != RefPlayerNum + 1) // если эл массива != номеру текущего игрока 
				{
					// если игрока нет в массиве выбывших, выводим его 
					Refd = true;
					i++;
				}
				else
				{
					//cout << "в массиве выбывших такой чел есть!!!" << endl;
					Refd = false;
					break;
				}
			}

			if (RefPlayerNum + 1 <= AmountPlayers) //если текущий номер игрока <= кол-ву всех участников 
			{
				if (Refd == true)
				{
					cout << "\n\tОчередь игрока номер: " << RefPlayerNum + 1 << endl;
					break;
				}
				else
				{
					RefPlayerNum++;
					i++;
				}
			}
			else
			{
				RefPlayerNum = 0;
				i++;
			}
		}
	}
}

int main()
{
	setlocale(0, "ru");
	srand(time(NULL));

	while (true)
	{
		int choice;
		while (true)
		{
			cout << "Хотите сыграть в русскую рулетку? (1 - да 2 - нет)\n>>> ";
			cin >> choice;
			if (choice == 2)
			{
				cout << "Ладно." << endl;
				exit(1); // завершает выполнение проги? вроде да
			}
			else if (choice == 1)
			{
				int const SizeDrum = 6; //барабан и его размер
				int arrBullets[SizeDrum];
				int ConsiderBullets = 0;
				int& RefConsiderBullets = ConsiderBullets;
				RefConsiderBullets = FillArrBullets(arrBullets, SizeDrum, RefConsiderBullets); //функция заполнения барабана и подсчёта кол-ва пуль 

				int arrNewBullets[SizeDrum];
				for (int i = 0; i < SizeDrum;)
				{
					arrNewBullets[i] = 0;
					i++;
				}

				NewFillArrBullets(arrNewBullets, RefConsiderBullets, SizeDrum); // крутим барабан 

				int PlayerNum = 0;
				Play(arrNewBullets, SizeDrum, RefConsiderBullets, PlayerNum);
				break;
			}
			else
			{
				cout << "Нет такого варианта!" << endl;
			}
		}
		cout << "\n\nПоздразляю! ";
	}
}
