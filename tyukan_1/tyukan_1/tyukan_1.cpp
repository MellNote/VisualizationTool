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

	//iniファイルのパラメータ取得

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

	//構造体設定
	list AKITA, KAGAWA;
	AKITA.DAY;
	KAGAWA.DAY;

	FILE* fp;
	char s[BUFFSIZE];
	double tmp;//変換後の取得地
	char* p1;
	char delim[] = ", ";
	char* ctx;
	int i = 0;
	int count = 0;
	errno_t error;

	//平均雲量
	double avg_akita[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	double avg_kagawa[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };

	//日数カウント
	int days_akita[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	int days_kagawa[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };

	//---------------------------------------画面準備-------------------------------------------//

	// 端末の準備
	initscr();

	/* 特殊キーを受け取る */
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	int key;

	// 色の準備
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLUE);	// 色1 は青文字
	init_pair(2, COLOR_GREEN, COLOR_GREEN);	// 色2 は緑文字
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);	// 色3 は黄文字
	init_pair(10, COLOR_WHITE, COLOR_BLACK);	// 色10 は白文字
	bkgd(COLOR_PAIR(10));			// 背景は色10


	//---------------------------------------秋田データ読み込み-------------------------------------------//

	error = fopen_s(&fp, akita, "r");//第一引数に入れたアドレスに第二引数に入れたファイルのアドレスを入れる

	if (error != 0) {
		fprintf_s(stderr, "秋田データ読み込み失敗");//エラーメッセージ
	}
	else {
		while (fgets(s, BUFFSIZE, fp) != NULL) {//fpの内容をsに入れていく
			p1 = strtok_s(s, delim, &ctx);//sの内容をdelimで区切って入れる
			while (p1 != NULL) {//１日分が取れる
				if (count != 0) {
					tmp = atof(p1);
					AKITA.DAY[i] = tmp;

				}
				p1 = strtok_s(NULL, delim, &ctx);	// 2個目以降の部分文字列取得
				count = 1;
			}
			i++;
			count = 0;
		}
		fclose(fp);
	}
	i = 0;
	count = 0;

	//---------------------------------------秋田データ書き込み-------------------------------------------//

	int a = 1;
	error = fopen_s(&fp, akita_output, "w");

	if (error != 0) {
		fprintf_s(stderr, "秋田ファイル書き込み失敗");
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

	//---------------------------------------香川データ読み込み-------------------------------------------//

	error = fopen_s(&fp, kagawa, "r");//第一引数に入れたアドレスに第二引数に入れたファイルのアドレスを入れる

	if (error != 0) {
		fprintf_s(stderr, "香川データ読み込み失敗");//標準出力でエラーメッセージを書いてくれる
	}
	else {
		while (fgets(s, BUFFSIZE, fp) != NULL) {//fpの内容をsに入れていく
			p1 = strtok_s(s, delim, &ctx);//sの内容をdelimで区切って入れていく
			while (p1 != NULL) {//１日分が取れる
				if (count != 0) {
					tmp = atof(p1);
					KAGAWA.DAY[i] = tmp;

				}
				p1 = strtok_s(NULL, delim, &ctx);	// 2個目以降の部分文字列取得
				count = 1;
			}
			i++;
			count = 0;
		}
		fclose(fp);
	}

	//---------------------------------------香川データ書き込み-------------------------------------------//

	int b = 1;
	error = fopen_s(&fp, kagawa_output, "w");

	if (error != 0) {
		fprintf_s(stderr, "香川ファイル書き込み失敗");
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

	//---------------------------------------平均雲量割合-------------------------------------------//


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


	//---------------------------------------グラフ描画-------------------------------------------//


	while ((key = getch()) != KEY_UP) {

		attrset(COLOR_PAIR(10));			// 色10 を使う

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

			mvaddstr(0, 1, "(10分比)");

			mvaddstr(2, 1, "10");
			mvaddstr(6, 0, "7.5");
			mvaddstr(11, 1, "5");
			mvaddstr(16, 0, "2.5");
			mvaddstr(21, 0, " 0");

			mvaddstr(22, 40, " (月)");
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

			mvaddstr(24, 11, "秋田県の各月の雲量割合");

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

			mvaddstr(0, 1, "(10分比)");

			mvaddstr(2, 1, "10");
			mvaddstr(6, 0, "7.5");
			mvaddstr(11, 1, "5");
			mvaddstr(16, 0, "2.5");
			mvaddstr(21, 0, " 0");

			mvaddstr(22, 40, " (月)");
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

			mvaddstr(24, 11, "香川県の各月の雲量割合");

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


	//端末制御の終了
	endwin();

	return(0);

}


//月ごとの日数をカウントする関数

void CountDay(const char* fileName, int days[12]) {

	FILE *fp;
	char d[BUFFSIZE];
	char slash[] = "/";	//スラッシュで区切る
	char *ctx;			//strtok_s関数で用いる位置情報を格納
	char *p2;			//スラッシュ区切り単語
	int cnt = 0;		//日数をカウントする
	int tmp2;

	//ファイルを開く
	errno_t error;
	error = fopen_s(&fp, fileName, "r");

	//読み込み時のエラー確認
	if (error != 0) {
		fprintf_s(stderr, "ファイル読み込みに失敗しました。");
	}
	//ファイルの読み込み
	else {

		while (fgets(d, BUFFSIZE, fp) != NULL) {	//fp(ファイル)を一行ずつdに格納する
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


//配列を初期化する関数
void SyokikaDay(int days[12]) {
	for (int i = 0; i < 12; i++) {
		days[i] = 0;
	}
}
