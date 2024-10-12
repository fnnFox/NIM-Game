#pragma once

class Game {
public:
	Game();												//�����-�����������, ���������� ��������������� init(), generate() � start()
private:
	int take(int, int);									//������� �� N ����� M ���������
	void show();										//����� � ������� ���������� �����
	void generate();									//�������� ��������� ���������� ����� �� ��������� ����������� ���������
	int gamemode();										//����� ������ ����
	void init(int);										//�������� ���� ��������-������� � ����������� �� ������ ����
	void start();										//����� ����

	const int min = 2, max = 12;						//������ ���������� � ����������� ��������� ���������� ��������� � ������
	int numberOfBunches, notEmpty_iterator, step;		//���������� �����, ���������� ����������� �������� �����, ���
	int* bunches;										//��������� �� ������ �����

														//��������� ��� ����������� �������� ������ ����� � ���������� ��������� �� ������� move()
	struct pair {
		int bunch, items;
	};
														//����������� ����� ������ � ��� ���������� � ���� �������� � ����������
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
	
	Player* Players[2];									//������ �� ���� �������
};