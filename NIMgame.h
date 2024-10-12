#pragma once

class Game {
public:
	Game();												//метод-конструктор, вызывающий последовательно init(), generate() и start()
private:
	int take(int, int);									//изъятие из N кучки M предметов
	void show();										//вывод в консоль оставшихся кучек
	void generate();									//создание заданного количества кучек со случайным количеством предметов
	int gamemode();										//выбор режима игры
	void init(int);										//создание двух объектов-Игроков в зависимости от режима игры
	void start();										//старт игры

	const int min = 2, max = 12;						//задают минимально и максимально возможное количество предметов в кучках
	int numberOfBunches, notEmpty_iterator, step;		//количество кучек, количество оставашихся непустых кучек, ход
	int* bunches;										//указатель на массив кучек

														//структура для возвращения значений номера кучки и количества предметов из функции move()
	struct pair {
		int bunch, items;
	};
														//виртуальный класс Игрока и его реализации в виде Человека и Компьютера
	class Player {
	public:
		const char* name;
		virtual pair move(int*, int) = 0;
	};
	class Human : public Player {
	public:
		Human(const char* name);
		pair move(int*, int) override;
	};
	class Computer : public Player {
	public:
		Computer(const char*);
		pair move(int*, int) override;
	};
	
	Player* Players[2];									//массив из двух Игроков
};