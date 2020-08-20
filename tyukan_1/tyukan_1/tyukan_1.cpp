#include "stdafx.h"
#include <curses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#define BUFFSIZE 1024
void CountDay(const char* fileName, int days[12]);
void SyokikaDay(int days[12]);

struct list {
	double DAY[366];
};

int main() {

	//ini�t�@�C���̃p�����[�^�擾

	DWORD Akita = 0;
	char akita[BUFFSIZE];
	Akita = GetPrivateProfileString("Kumo", "keyword1", "none", akita, sizeof(akita), "C:\\Users\\daich\\Documents\\Visual Studio 2015\\Projects\\tyukan_1\\Release\\.\\Kumo.ini");

	DWORD Kagawa = 0;
	char kagawa[BUFFSIZE];
	Kagawa = GetPrivateProfileString("Kumo", "keyword2", "none", kagawa, sizeof(kagawa), "C:\\Users\\daich\\Documents\\Visual Studio 2015\\Projects\\tyukan_1\\Release\\.\\Kumo.ini");

	DWORD Akita_output = 0;
	char akita_output[BUFFSIZE];
	Akita_output = GetPrivateProfileString("Kumo_output", "keyword3", "none", akita_output, sizeof(akita_output), "C:\\Users\\daich\\Documents\\Visual Studio 2015\\Projects\\tyukan_1\\Release\\.\\Kumo.ini");

	DWORD Kagawa_output = 0;
	char kagawa_output[BUFFSIZE];
	Kagawa_output = GetPrivateProfileString("Kumo_output", "keyword4", "none", kagawa_output, sizeof(kagawa_output), "C:\\Users\\daich\\Documents\\Visual Studio 2015\\Projects\\tyukan_1\\Release\\.\\Kumo.ini");

	//�\���̐ݒ�
	list AKITA, KAGAWA;
	AKITA.DAY;
	KAGAWA.DAY;

	FILE* fp;
	char s[BUFFSIZE];
	double tmp;//�ϊ���̎擾�n
	char* p1;
	char delim[] = ", ";
	char* ctx;
	int i = 0;
	int count = 0;
	errno_t error;

	//���ω_��
	double avg_akita[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	double avg_kagawa[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };

	//�����J�E���g
	int days_akita[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	int days_kagawa[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };

	//---------------------------------------��ʏ���-------------------------------------------//

	// �[���̏���
	initscr();

	/* ����L�[���󂯎�� */
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	int key;

	// �F�̏���
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLUE);	// �F1 �͐���
	init_pair(2, COLOR_GREEN, COLOR_GREEN);	// �F2 �͗Ε���
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);	// �F3 �͉�����
	init_pair(10, COLOR_WHITE, COLOR_BLACK);	// �F10 �͔�����
	bkgd(COLOR_PAIR(10));			// �w�i�͐F10


	//---------------------------------------�H�c�f�[�^�ǂݍ���-------------------------------------------//

	error = fopen_s(&fp, akita, "r");//�������ɓ��ꂽ�A�h���X�ɑ������ɓ��ꂽ�t�@�C���̃A�h���X������

	if (error != 0) {
		fprintf_s(stderr, "�H�c�f�[�^�ǂݍ��ݎ��s");//�G���[���b�Z�[�W
	}
	else {
		while (fgets(s, BUFFSIZE, fp) != NULL) {//fp�̓��e��s�ɓ���Ă���
			p1 = strtok_s(s, delim, &ctx);//s�̓��e��delim�ŋ�؂��ē����
			while (p1 != NULL) {//�P����������
				if (count != 0) {
					tmp = atof(p1);
					AKITA.DAY[i] = tmp;

				}
				p1 = strtok_s(NULL, delim, &ctx);	// 2�ڈȍ~�̕���������擾
				count = 1;
			}
			i++;
			count = 0;
		}
		fclose(fp);
	}
	i = 0;
	count = 0;

	//---------------------------------------�H�c�f�[�^��������-------------------------------------------//

	int a = 1;
	error = fopen_s(&fp, akita_output, "w");

	if (error != 0) {
		fprintf_s(stderr, "�H�c�t�@�C���������ݎ��s");
	}
	else {
		CountDay(akita, days_akita);

		for (int count = 0; count < 12; count++) {
			for (int i = 0; i < days_akita[count]; i++) {
				avg_akita[count] += AKITA.DAY[a];
				a++;

			}
			avg_akita[count] = avg_akita[count] / days_akita[count];
			fprintf(fp, "2018/%d,%lf\n", count + 1, avg_akita[count]);
		}
		a = 1;
	}
	//SyokikaDay(days_akita);
	fclose(fp);

	//---------------------------------------����f�[�^�ǂݍ���-------------------------------------------//

	error = fopen_s(&fp, kagawa, "r");//�������ɓ��ꂽ�A�h���X�ɑ������ɓ��ꂽ�t�@�C���̃A�h���X������

	if (error != 0) {
		fprintf_s(stderr, "����f�[�^�ǂݍ��ݎ��s");//�W���o�͂ŃG���[���b�Z�[�W�������Ă����
	}
	else {
		while (fgets(s, BUFFSIZE, fp) != NULL) {//fp�̓��e��s�ɓ���Ă���
			p1 = strtok_s(s, delim, &ctx);//s�̓��e��delim�ŋ�؂��ē���Ă���
			while (p1 != NULL) {//�P����������
				if (count != 0) {
					tmp = atof(p1);
					KAGAWA.DAY[i] = tmp;

				}
				p1 = strtok_s(NULL, delim, &ctx);	// 2�ڈȍ~�̕���������擾
				count = 1;
			}
			i++;
			count = 0;
		}
		fclose(fp);
	}

	//---------------------------------------����f�[�^��������-------------------------------------------//

	int b = 1;
	error = fopen_s(&fp, kagawa_output, "w");

	if (error != 0) {
		fprintf_s(stderr, "����t�@�C���������ݎ��s");
	}
	else {
		CountDay(kagawa, days_kagawa);

		for (int count = 0; count < 12; count++) {
			for (int i = 0; i < days_kagawa[count]; i++) {
				avg_kagawa[count] += KAGAWA.DAY[b];
				b++;

			}
			avg_kagawa[count] = avg_kagawa[count] / days_kagawa[count];
			fprintf(fp, "2018/%d,%lf\n", count + 1, avg_kagawa[count]);
		}
		b = 1;
	}

	fclose(fp);

	//---------------------------------------���ω_�ʊ���-------------------------------------------//


	a = 1;
	b = 1;

	for (int count = 0; count < 12; count++) {
		for (int i = 0; i < days_akita[count]; i++) {
			avg_akita[count] += AKITA.DAY[a];
			a++;
			
		}
		avg_akita[count] = avg_akita[count] / days_akita[count];
		
	}

	a = 1;

	for (int count = 0; count < 12; count++) {
		for (int i = 0; i < days_kagawa[count]; i++) {
			avg_kagawa[count] += KAGAWA.DAY[b];
			b++;

		}
		avg_kagawa[count] = avg_kagawa[count] / days_kagawa[count];
		
	}

	b = 1;


	//---------------------------------------�O���t�`��-------------------------------------------//


	while ((key = getch()) != KEY_UP) {

		attrset(COLOR_PAIR(10));			// �F10 ���g��

		int y_jiku = 20;


		switch (key) {

		case KEY_LEFT:
			erase();

			for (int i = 0; i < 20; i++) {
				mvaddstr(i + 2, 3, "|");
			}
			for (int i = 0; i < 37; i++) {
				mvaddstr(21, i + 3, "-");
			}

			mvaddstr(0, 1, "(10����)");

			mvaddstr(2, 1, "10");
			mvaddstr(6, 0, "7.5");
			mvaddstr(11, 1, "5");
			mvaddstr(16, 0, "2.5");
			mvaddstr(21, 0, " 0");

			mvaddstr(22, 40, " (��)");
			mvaddstr(22, 4, " 1");
			mvaddstr(22, 7, " 2");
			mvaddstr(22, 10, " 3");
			mvaddstr(22, 13, " 4");
			mvaddstr(22, 16, " 5");
			mvaddstr(22, 19, " 6");
			mvaddstr(22, 22, " 7");
			mvaddstr(22, 25, " 8");
			mvaddstr(22, 28, " 9");
			mvaddstr(22, 31, "10");
			mvaddstr(22, 34, "11");
			mvaddstr(22, 37, "12");

			mvaddstr(24, 11, "�H�c���̊e���̉_�ʊ���");

			for (int i = 0; i < 12; i++) {
				int cnt = (int)(avg_akita[i] * 2);

				for (int a = 0; a < cnt; a++) {

					attrset(COLOR_PAIR(1));
					mvaddstr(y_jiku - a, 4 + (i * 3), "**");
				}
			}break;

		case KEY_RIGHT:
			erase();

			for (int i = 0; i < 20; i++) {
				mvaddstr(i + 2, 3, "|");
			}
			for (int i = 0; i < 37; i++) {
				mvaddstr(21, i + 3, "-");
			}

			mvaddstr(0, 1, "(10����)");

			mvaddstr(2, 1, "10");
			mvaddstr(6, 0, "7.5");
			mvaddstr(11, 1, "5");
			mvaddstr(16, 0, "2.5");
			mvaddstr(21, 0, " 0");

			mvaddstr(22, 40, " (��)");
			mvaddstr(22, 4, " 1");
			mvaddstr(22, 7, " 2");
			mvaddstr(22, 10, " 3");
			mvaddstr(22, 13, " 4");
			mvaddstr(22, 16, " 5");
			mvaddstr(22, 19, " 6");
			mvaddstr(22, 22, " 7");
			mvaddstr(22, 25, " 8");
			mvaddstr(22, 28, " 9");
			mvaddstr(22, 31, "10");
			mvaddstr(22, 34, "11");
			mvaddstr(22, 37, "12");

			mvaddstr(24, 11, "���쌧�̊e���̉_�ʊ���");

			for (int i = 0; i < 12; i++) {
				int cnt = (int)(avg_kagawa[i] * 2);

				for (int a = 0; a < cnt; a++) {

					attrset(COLOR_PAIR(2));
					mvaddstr(y_jiku - a, 4 + (i * 3), "**");
				}
			}break;

		}


	}
	//------------------------------------------------------------------------------------------//


	//�[������̏I��
	endwin();

	return(0);

}


//�����Ƃ̓������J�E���g����֐�

void CountDay(const char* fileName, int days[12]) {

	FILE *fp;
	char d[BUFFSIZE];
	char slash[] = "/";	//�X���b�V���ŋ�؂�
	char *ctx;			//strtok_s�֐��ŗp����ʒu�����i�[
	char *p2;			//�X���b�V����؂�P��
	int cnt = 0;		//�������J�E���g����
	int tmp2;

	//�t�@�C�����J��
	errno_t error;
	error = fopen_s(&fp, fileName, "r");

	//�ǂݍ��ݎ��̃G���[�m�F
	if (error != 0) {
		fprintf_s(stderr, "�t�@�C���ǂݍ��݂Ɏ��s���܂����B");
	}
	//�t�@�C���̓ǂݍ���
	else {

		while (fgets(d, BUFFSIZE, fp) != NULL) {	//fp(�t�@�C��)����s����d�Ɋi�[����
			p2 = strtok_s(d, slash, &ctx);

			while (p2 != NULL) {

				if (cnt == 1) {
					tmp2 = atoi(p2);
					days[tmp2 - 1]++;
				}
				p2 = strtok_s(NULL, slash, &ctx);
				cnt++;
			}
			cnt = 0;
		}

		fclose(fp);
	}
}


//�z�������������֐�
void SyokikaDay(int days[12]) {
	for (int i = 0; i < 12; i++) {
		days[i] = 0;
	}
}
