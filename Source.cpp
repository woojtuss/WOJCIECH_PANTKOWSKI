#include "allegro5\allegro.h"
#include "ctime"
#include "allegro5\allegro_native_dialog.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"
#include "allegro5\allegro_image.h"
#include "allegro5\keyboard.h"
#include "allegro5/timer.h"
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <cmath>
#include <fstream>
#include <algorithm>
#define ScreenWidth 1100
#define ScreenHeiht 760
void CameraUpdate(float *cameraPosition, float x, float y, int width, int height)
{
	cameraPosition[0] = -(ScreenWidth / 2) + (x + width / 2);
	cameraPosition[2] = -(ScreenHeiht / 2) + (y + height / 2);
	if (cameraPosition[0] < 0)
		cameraPosition[0] = 0;
	if (cameraPosition[1] < 0)
		cameraPosition[1] = 0;
}



enum KEYS { SPACE, S, A, D };
int main()
{
	ALLEGRO_DISPLAY *okno = NULL;
	ALLEGRO_TIMER *timer = NULL;
	al_set_window_title(okno, "Co mu zrobisz jak mnie z³apiesz");

	const int FPS = 50;
	

	bool keys[8] = { false, false, false, false, false, false, false, false };

	if (!al_init())
		al_show_native_message_box(NULL, NULL, NULL, "ALLEGRO INIT FAIL", NULL, NULL);
	if (!al_init_native_dialog_addon())
		al_show_native_message_box(NULL, NULL, NULL, "ALLEGRO NATIVE DIALOG INIT FAIL", NULL, NULL);
	if (!al_init_image_addon())
		al_show_native_message_box(NULL, NULL, NULL, "ALLEGRO IMAGE INIT FAIL", NULL, NULL);
	if (!al_install_keyboard())
		al_show_native_message_box(NULL, NULL, NULL, "ALLEGRO KEYBOARD INIT FAIL", NULL, NULL);
	if (!al_init_font_addon())
		al_show_native_message_box(NULL, NULL, NULL, "ALLEGRO FONT INIT FAIL", NULL, NULL);
	al_install_audio();
	al_init_acodec_addon();

	

	okno = al_create_display(ScreenWidth, ScreenHeiht);
	timer = al_create_timer(1.0 / FPS);

	ALLEGRO_BITMAP *czarny;
	czarny = al_load_bitmap("czarny.png");
	ALLEGRO_BITMAP *level2;
	level2 = al_load_bitmap("l2.jpg");
	ALLEGRO_BITMAP *over;
	over = al_load_bitmap("over.jpg");
	ALLEGRO_BITMAP *bit1;
	bit1 = al_load_bitmap("police.png");
	ALLEGRO_BITMAP *level;
	level = al_load_bitmap("level.png");
	ALLEGRO_BITMAP *back;
	back = al_load_bitmap("tloo.png");
	ALLEGRO_BITMAP *money;
	money = al_load_bitmap("monety.png");
	ALLEGRO_BITMAP *przeszkoda1;
	przeszkoda1 = al_load_bitmap("przeszkoda1.png");
	ALLEGRO_BITMAP *przeszkoda2;
	przeszkoda2 = al_load_bitmap("przeszkoda2.png");
	ALLEGRO_BITMAP *przeszkoda3;
	przeszkoda3 = al_load_bitmap("przeszkoda3.png");
	ALLEGRO_BITMAP *przeszkoda4;
	przeszkoda4 = al_load_bitmap("przeszkoda4.png");
	ALLEGRO_BITMAP *przeszkoda5;
	przeszkoda5 = al_load_bitmap("przeszkoda5.png");
	ALLEGRO_BITMAP *przeszkoda6;
	przeszkoda6 = al_load_bitmap("przeszkoda6.bmp");
	ALLEGRO_BITMAP *bit2;
	bit2 = al_load_bitmap("run.png");
	ALLEGRO_BITMAP *bit3;
	bit3 = al_load_bitmap("run2.png");
	ALLEGRO_BITMAP *bit4;
	bit4 = al_load_bitmap("run3.png");
	ALLEGRO_BITMAP *bit5;
	bit5 = al_load_bitmap("run4.png");
	ALLEGRO_BITMAP *bit6;
	bit6 = al_load_bitmap("run5.png");
	ALLEGRO_BITMAP *bit7;
	bit7 = al_load_bitmap("run6.png");
	ALLEGRO_BITMAP *bit8;
	bit8 = al_load_bitmap("run7.png");
	ALLEGRO_BITMAP *bit9;
	bit9 = al_load_bitmap("run8.png");
	ALLEGRO_BITMAP *bit10;
	bit10 = al_load_bitmap("run9.png");
	ALLEGRO_BITMAP *bit2l;
	bit2l = al_load_bitmap("runK.png");
	ALLEGRO_BITMAP *bit3l;
	bit3l = al_load_bitmap("run2K.png");
	ALLEGRO_BITMAP *bit4l;
	bit4l = al_load_bitmap("run3K.png");
	ALLEGRO_BITMAP *bit5l;
	bit5l = al_load_bitmap("run4K.png");
	ALLEGRO_BITMAP *bit6l;
	bit6l = al_load_bitmap("run5K.png");
	ALLEGRO_BITMAP *bit7l;
	bit7l = al_load_bitmap("run6K.png");
	ALLEGRO_BITMAP *bit8l;
	bit8l = al_load_bitmap("run7K.png");
	ALLEGRO_BITMAP *bit9l;
	bit9l = al_load_bitmap("run8K.png");
	ALLEGRO_BITMAP *bit10l;
	bit10l = al_load_bitmap("run9K.png");
	ALLEGRO_BITMAP *klocek;
	klocek = al_load_bitmap("klocek.bmp");
	ALLEGRO_BITMAP *monety2;
	monety2 = al_load_bitmap("monety2.png");
	ALLEGRO_BITMAP *pies;
	pies = al_load_bitmap("pies.png");
	ALLEGRO_BITMAP *pies2;
	pies2 = al_load_bitmap("pies2.png");
	ALLEGRO_BITMAP *bonus2;
	bonus2 = al_load_bitmap("bonus.bmp");
	ALLEGRO_BITMAP *bonus;
	bonus = al_load_bitmap("bonus2.bmp");
	ALLEGRO_BITMAP *plussto;
	plussto = al_load_bitmap("+100.png");

	al_reserve_samples(2);
	ALLEGRO_SAMPLE *muza;
	muza= al_load_sample("music.wav");
	ALLEGRO_SAMPLE *szczekanie;
	szczekanie = al_load_sample("szczekanie.wav");
	
	ALLEGRO_FONT *font24 = al_create_builtin_font();
	ALLEGRO_FONT *font2 = al_create_builtin_font();
	ALLEGRO_FONT *font3 = al_create_builtin_font();
	ALLEGRO_FONT *font4 = al_create_builtin_font();
	ALLEGRO_FONT *font5 = al_create_builtin_font();
	ALLEGRO_FONT *font6 = al_create_builtin_font();
	ALLEGRO_FONT *font7 = al_create_builtin_font();
	ALLEGRO_FONT *font8 = al_create_builtin_font();

	
	al_convert_mask_to_alpha(bit1, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(money, al_map_rgb(237, 28, 36));
	al_convert_mask_to_alpha(przeszkoda1, al_map_rgb(237, 28, 36));
	al_convert_mask_to_alpha(przeszkoda6, al_map_rgb(237, 28, 36));
	al_convert_mask_to_alpha(przeszkoda1, al_map_rgb(92, 148, 252));
	al_convert_mask_to_alpha(przeszkoda2, al_map_rgb(92, 148, 252));
	al_convert_mask_to_alpha(przeszkoda3, al_map_rgb(92, 148, 252));
	al_convert_mask_to_alpha(przeszkoda4, al_map_rgb(92, 148, 252));
	al_convert_mask_to_alpha(przeszkoda5, al_map_rgb(92, 148, 252));
	al_convert_mask_to_alpha(pies, al_map_rgb(98, 148, 252));
	al_convert_mask_to_alpha(pies2, al_map_rgb(98, 148, 252));
	al_convert_mask_to_alpha(klocek, al_map_rgb(92, 148, 252));
	al_convert_mask_to_alpha(bit2, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(bit3, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(bit4, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(bit5, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(bit6, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(bit7, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(bit8, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(bit9, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(bit10, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(bit2l, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(bit3l, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(bit4l, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(bit5l, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(bit6l, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(bit7l, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(bit8l, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(bit9l, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(bit10l, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(monety2, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(plussto, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(level2, al_map_rgb(255, 255, 255));
	
	const float gravity = 1;


	srand(time(NULL));
	
	float camraPosition[2] = { 0,0 };
	float velx, vely;
	velx = vely = 0;
	int bit1_x;
	int bit1_y = 420;
	int bit2_x = 5, bit2_y = 520;
	int klocek_y1;
	int klocek_y2;
	int ilosc_monet = 0;
	int test = 0;
	int back_x = 0;
	int przeszkoda2_x = 890, przeszkoda3_x = 1200, przeszkoda4_x = 1468, przeszkoda5_x = 1820;
	int przeszkoda2_y = 490, przeszkoda3_y = 440, przeszkoda4_y = 400, przeszkoda5_y = 397;
	float czas;
	int money_x;
	int money_y[20];
	int monety2_x;
	int monety2_y[20];
	int tab[20],tab2[20];
	int pies_x = 2000;
	int pies_y = 518;
	int pies2_x = 2000;
	int pies2_y = 518;
	int tab3[40];
	int tab4[15];
	int tab5[5],przeszkoda6_y=445;
	int bonus2_y, bonus_y;
	int tab6[10];
	
	int s = 6;
	int los;
	float level_x=390, level_y=670, czas_x=0, czas_y=665, ilosc_monet_x=900, ilosc_monet_y=665, wynik_x=900, wynik_y=675;
	int plusstoo_s=3580 ;
	int czas1;
	


	ALLEGRO_TRANSFORM camera;
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	
	bool last_buton = { 1 };
	bool close = false;
	bool accident = false;
	bool ilosc_monet2 = false;
	bool dodaj_monete = false;
	int  wynik=0;
	bool rysujmonete[21] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	bool rysujmonete2[5] = { 1,1,1,1,1 };
	bool rysujprzeszkode1 = false;
	bool jump = false;
	float jumpSpeed = 15;
	bool w_prawo = true;
	bool w_prawo2 = true;
	bool w_prawo3 = true;
	int movespeed=6;
	
	
	

	
	for (int i = 0;i <30;i++)
	{

			
			tab3[0] = 650;
			tab3[1] = 680;
			tab3[2] = 710;
			tab3[3] = 740;
			tab3[4] = 770;
			tab3[5] = 2465;
			tab3[6] = 2495;
			tab3[7] = 2520;
			tab3[8] = 3005;
			tab3[9] = 3200;
			tab3[10] = 3230;
			tab3[11] = 3775;
			tab3[12] = 4125;
			tab3[13] = 4135;
			tab3[14] = 5375;
			tab3[15] = 5405;
			tab3[16] = 5470;
			tab3[17] = 2560;
			tab3[18] = 2590;
			tab3[19] = 2620;
			tab3[20] = 2650;
			tab3[21] = 2680;
			tab3[22] = 2710;
			tab3[23] = 2740;
			tab3[24] = 2910;
			tab3[25] = 2940;
			tab3[26] = 2970;
			tab3[27] = 3230;
			tab3[28] = 3775;
			tab3[29] = 3870;
			tab3[30] = 3900;
			tab3[31] = 3930;
			tab3[32] = 4095;
			tab3[33] = 4190;

			klocek_y1 =410;
			klocek_y2 = 235;


	}
	for (int l = 0;l < 5;l++)
	{
		tab5[0] = 4260;
		tab5[1] = 4735;
		tab5[2] = 5900;
		tab5[3] = 4445;
		tab5[4] = 4920;


	}
	for (int i = 0;i < 10;i++)
	{
		tab4[0] = 515;
		tab4[1] = 3390;
		tab4[2] = 3490;
		tab4[3] = 3580;
		tab4[4] = 3005;
		tab4[5] = 3490;
		tab4[6] = 4125;
		tab4[7] = 4160;
		tab4[8] = 705;
		bonus_y = 410;
		bonus2_y = 235;
	}
	for (int i = 1;i < 20;i++)
	{

		money_x = (i * 400) + 60;
		tab[i] = money_x;
		money_y[i] = rand() % 400 + 150;

		monety2_x = (i * 400) + 780;
		tab2[i] = monety2_x;
		monety2_y[i] = rand() % 400 + 150;
		

	}
	for (int i = 0;i < 10;i++)
	{
		tab6[0] = 1940;
		tab6[1] = 3190;
		tab6[2] = 5826;
	}

	bit1_x = 6400;
	al_start_timer(timer);
	while (!close)


	{
		CameraUpdate(camraPosition, bit2_x, bit2_y, 50, 50);
		al_identity_transform(&camera);
		al_translate_transform(&camera, -camraPosition[0], -camraPosition[1]);
		al_use_transform(&camera);
		czas = al_get_time();
		czas1 = al_get_time();
		al_play_sample(muza, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		al_draw_bitmap(back, back_x, 0, 0);
		wynik = ilosc_monet*czas;
		al_draw_bitmap(level, level_x, level_y, 0);
		al_draw_bitmap(przeszkoda2, przeszkoda2_x, przeszkoda2_y, 0);
		al_draw_bitmap(przeszkoda3, przeszkoda3_x, przeszkoda3_y, 0);
		al_draw_bitmap(przeszkoda4, przeszkoda4_x, przeszkoda4_y, 0);
		al_draw_bitmap(przeszkoda5, przeszkoda5_x, przeszkoda5_y, 0);
		al_draw_bitmap(bit1,bit1_x, bit1_y, 0);
		
		//for (int i = 0;i < 10;i++)
		//{
		//	al_draw_bitmap(pies, tab6[i], pies_y, 0);
		//}
		
		
		for (int j = 0;j <16;j++)
		{
			al_draw_bitmap(klocek, tab3[j], klocek_y1, 0);
			
		}
		for (int j = 16;j <34;j++)
		{
			al_draw_bitmap(klocek, tab3[j], klocek_y2, 0);

		}
		for (int k = 0;k < 4;k++)
		{
			if (czas1 % (3) == 0.0)
			{
				al_draw_bitmap(bonus, tab4[k], bonus_y, 0);
			}
			else
			{
				al_draw_bitmap(bonus2, tab4[k], bonus_y, 0);
			}
		}
		for (int l = 4;l < 9;l++)
		{
			if (czas1 % (3) == 0.0)
			{
				al_draw_bitmap(bonus, tab4[l], bonus2_y, 0);

			}
			else
			{
				al_draw_bitmap(bonus2, tab4[l], bonus2_y, 0);
			}
	
		}
		for (int l = 0;l < 3;l++)
		{
			al_draw_bitmap(przeszkoda1, tab5[l], przeszkoda6_y, 0);
		}
		for (int l = 3;l < 5;l++)
		{
			al_draw_bitmap(przeszkoda6, tab5[l], przeszkoda6_y, 0);
		}


		al_draw_textf(font2, al_map_rgb(0, 0, 760), ilosc_monet_x, ilosc_monet_y, 0, "Ilosc monet: %d", ilosc_monet);
		al_draw_textf(font3, al_map_rgb(0, 0, 760), wynik_x, wynik_y, 0, "Wynik: %d", wynik);
		al_draw_textf(font4, al_map_rgb(0, 0, 760), czas_x, czas_y, 0, "Czas: %.2f sek", czas);
		al_draw_textf(font4, al_map_rgb(0, 0, 760), czas_x, czas_y+10, 0, "Czas: %d sek", bit2_x);
		al_draw_textf(font4, al_map_rgb(0, 0, 760), czas_x, czas_y+20, 0, "Czas: %d sek", bit1_x);
		if (camraPosition[0])
		{
			wynik_x = bit2_x + 445;
			czas_x = bit2_x - 520;
			ilosc_monet_x = bit2_x + 445;
			level_x = bit2_x-130;
		}
			
			
	

	
	

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{

			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				break;
			case ALLEGRO_KEY_S:
				keys[S] = true;
				break;
			case ALLEGRO_KEY_A:
				keys[A] = true;
				break;
			case ALLEGRO_KEY_D:
				keys[D] = true;
				break;
			case ALLEGRO_KEY_ESCAPE:
				close = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{

			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			case ALLEGRO_KEY_S:
				keys[S] = false;
				break;
			case ALLEGRO_KEY_A:
				keys[A] = false;
				break;
			case ALLEGRO_KEY_D:
				keys[D] = false;
				break;
			case ALLEGRO_KEY_ESCAPE:
				close = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			

			if (bit2_y >= 250.0 && bit2_y <= 520.0)
			{
				if (keys[SPACE] && jump)
					vely = -jumpSpeed;
				jump = false;
			}

			{
				bit2_y += keys[S] * s;
			}

			if (keys[A] == true)

			{
				bit2_x -= keys[A] * s;
				{

					if (bit2_x % 10 < 10 && bit2_x % 10 > 0)
					{
						test = 1;
					}
					if (bit2_x % 20 < 20 && bit2_x % 20 > 10)
					{
						test = 2;
					}
					if (bit2_x % 30 < 30 && bit2_x % 30 > 20)
					{
						test = 3;
					}
					if (bit2_x % 40 < 40 && bit2_x % 40 > 30)
					{
						test = 4;
					}

					if (bit2_x % 50 < 50 && bit2_x % 50 > 40)
					{
						test = 5;
					}
					if (bit2_x % 60 < 60 && bit2_x % 60 > 50)
					{
						test = 6;
					}
					if (bit2_x % 70 < 70 && bit2_x % 70 > 60)
					{
						test = 7;
					}
					if (bit2_x % 80 < 80 && bit2_x % 80 > 70)
					{
						test = 8;
					}
					if (bit2_x % 90 < 90 && bit2_x % 90 > 80)
					{
						test = 9;
					}

					if (test == 9)
					{
						al_draw_bitmap(bit3l, bit2_x, bit2_y, 0);
					}
					if (test == 8)
					{
						al_draw_bitmap(bit4l, bit2_x, bit2_y, 0);
					}
					if (test == 7)
					{
						al_draw_bitmap(bit5l, bit2_x, bit2_y, 0);
					}
					if (test == 6)
					{
						al_draw_bitmap(bit6l, bit2_x, bit2_y, 0);
					}
					if (test == 5)
					{
						al_draw_bitmap(bit7l, bit2_x, bit2_y, 0);
					}
					if (test == 4)
					{
						al_draw_bitmap(bit8l, bit2_x, bit2_y, 0);
					}
					if (test == 3)
					{
						al_draw_bitmap(bit9l, bit2_x, bit2_y, 0);
					}
					if (test == 2)
					{
						al_draw_bitmap(bit10l, bit2_x, bit2_y, 0);
					}
					if (test == 1)
					{
						al_draw_bitmap(bit2l, bit2_x, bit2_y, 0);
					}

				}
			}

			if (keys[D] == true)
			{
				bit2_x += keys[D] * s;


				{
					if (bit2_x % 10 < 10 && bit2_x % 10 > 0)
					{
						test = 1;
					}
					if (bit2_x % 20 < 20 && bit2_x % 20 > 10)
					{
						test = 2;
					}
					if (bit2_x % 30 < 30 && bit2_x % 30 > 20)
					{
						test = 3;
					}
					if (bit2_x % 40 < 40 && bit2_x % 40 > 30)
					{
						test = 4;
					}

					if (bit2_x % 50 < 50 && bit2_x % 50 > 40)
					{
						test = 5;
					}
					if (bit2_x % 60 < 60 && bit2_x % 60 > 50)
					{
						test = 6;
					}
					if (bit2_x % 70 < 70 && bit2_x % 70 > 60)
					{
						test = 7;
					}
					if (bit2_x % 80 < 80 && bit2_x % 80 > 70)
					{
						test = 8;
					}
					if (bit2_x % 90 < 90 && bit2_x % 90 > 80)
					{
						test = 9;

					}

					if (test == 1)
					{
						al_draw_bitmap(bit3, bit2_x, bit2_y, 0);
					}
					if (test == 2)
					{
						al_draw_bitmap(bit4, bit2_x, bit2_y, 0);
					}
					if (test == 3)
					{
						al_draw_bitmap(bit5, bit2_x, bit2_y, 0);
					}
					if (test == 4)
					{
						al_draw_bitmap(bit6, bit2_x, bit2_y, 0);
					}
					if (test == 5)
					{
						al_draw_bitmap(bit7, bit2_x, bit2_y, 0);
					}
					if (test == 6)
					{
						al_draw_bitmap(bit8, bit2_x, bit2_y, 0);
					}
					if (test == 7)
					{
						al_draw_bitmap(bit9, bit2_x, bit2_y, 0);
					}
					if (test == 8)
					{
						al_draw_bitmap(bit10, bit2_x, bit2_y, 0);
					}
					if (test == 9)
					{
						al_draw_bitmap(bit2, bit2_x, bit2_y, 0);
					}
				}

			}
			else if (!keys[A] && !keys[D] && !keys[S] && !keys[SPACE])
			{
				al_draw_bitmap(bit2, bit2_x, bit2_y, 0);
			}


			if (!jump)
			{
				vely += gravity;

			}
			else
				vely = 0;
			bit2_y += vely;

			jump = (bit2_y + 32 >= 540);
			if (jump)
			{
				bit2_y = 540 - 32;
			}

			for (int i = 0;i < 20;i++)
				if (rysujmonete[i] == true)
				{
					{

						al_draw_bitmap(money, tab[i], money_y[i], 0);

						if ((bit2_x <= tab[i] + 10) && (bit2_x >= tab[i] - 10) && (bit2_y <= money_y[i] + 100) && (bit2_y >= money_y[i] - 100))
						{
							ilosc_monet += 3;
							rysujmonete[i] = false;
						}
						ilosc_monet2 = false;
					}
				}



			for (int i = 0;i < 10;i++)
				if ((bit2_x <= tab6[i] + 10) && (bit2_x >= tab6[i] - 10) && (bit2_y <= pies_y + 10) && (bit2_y >= pies_y - 10))
				{

					ilosc_monet -= 3;
				}

			if ((bit2_x < przeszkoda2_x + 64) && (bit2_x + 51> przeszkoda2_x) && (bit2_y < przeszkoda2_y + 91) && (bit2_y + 74 >przeszkoda2_y))
			{
				for (int i = przeszkoda2_y;i < bit2_y + 91;i++)
				{
					for (int j = przeszkoda2_x;j < bit2_y + 51;j++)
					{
						if (keys[S] || keys[SPACE])
						{
							s = (i - bit2_y);
							bit2_y += keys[S] * s;
							bit2_y -= keys[SPACE] * s;

						}
						else if (keys[D] || keys[A])
						{
							s = (j - bit2_x);
							bit2_x += keys[D] * s;
							bit2_x -= keys[A] * s;

						}
					}
				}
			}
		}
		
		
		if (tab6[0] == 2100)
		{
			w_prawo = false;
		}
		else if (tab6[0] == 1877)
		{
			w_prawo = true;
		}

		if (w_prawo == true)
		{
			al_draw_bitmap(pies2, tab6[0], pies_y, 0);
			tab6[0]++;
			
		}
		else
		{
			al_draw_bitmap(pies, tab6[0], pies_y, 0);
			tab6[0]--;
		}
		if (tab6[1] == 4169)
		{
			w_prawo2 = false;
		}
		else if (tab6[1] == 2843)
		{
			w_prawo2 = true;
		}

		if (w_prawo2 == true)
		{
			al_draw_bitmap(pies2, tab6[1], pies_y, 0);
			tab6[1]++;

		}
		else
		{
			al_draw_bitmap(pies, tab6[1], pies_y, 0);
			tab6[1]--;
		}
		if (tab6[2] == 5800)
		{
			w_prawo3 = false;
		}
		else if (tab6[2] == 5069)
		{
			w_prawo3 = true;
		}

		if (w_prawo3 == true)
		{
			al_draw_bitmap(pies2, tab6[2], pies_y, 0);
			tab6[2]++;

		}
		else
		{
			al_draw_bitmap(pies, tab6[2], pies_y, 0);
			tab6[2]--;
		}

		
		{
			if ((bit2_x <= tab4[0] + 25) && (bit2_x >= tab4[0] - 25) && (bit2_y <= bonus_y + 25) && (bit2_y >= bonus_y - 25))
			{
				los = 1;
			}
			if ((bit2_x <= tab4[1] + 25) && (bit2_x >= tab4[1] - 25) && (bit2_y <= bonus_y + 25) && (bit2_y >= bonus_y - 25))
			{
				los = 2;
			}
			if ((bit2_x <= tab4[2] + 25) && (bit2_x >= tab4[2] - 25) && (bit2_y <= bonus_y + 25) && (bit2_y >= bonus_y - 25))
			{
				los = 3;
			}
			if ((bit2_x <= tab4[3] + 25) && (bit2_x >= tab4[3] - 25) && (bit2_y <= bonus_y + 25) && (bit2_y >= bonus_y - 25))
			{
				los = 4;
			}

			{


				if (los == 2)
				{

					if (rysujmonete2[2] == true)
					{
						al_draw_bitmap(money, tab4[1], bonus_y, 0);

						if ((bit2_x <= tab4[1] + 10) && (bit2_x >= tab4[1] - 10) && (bit2_y <= bonus_y + 10) && (bit2_y >= bonus_y - 10))
						{
							ilosc_monet += 3;
							rysujmonete2[2] = false;
						}
						ilosc_monet2 = false;
					}
				}

				else if (los == 1)
				{
					
					wynik = wynik - 100;

				}
				else if (los == 3)
				{

					if (rysujmonete2[3] == true)
					{
						al_draw_bitmap(money, tab4[2], bonus_y, 0);

						if ((bit2_x <= tab4[2] + 10) && (bit2_x >= tab4[2] - 10) && (bit2_y <= bonus_y + 10) && (bit2_y >= bonus_y - 10))
						{
							ilosc_monet += 15;
							rysujmonete2[3] = false;
						}
						ilosc_monet2 = false;
					}
				}
				else if (los == 4)
				{
					
					
					if (rysujmonete2[4] == true)
					{
						al_draw_bitmap(plussto, plusstoo_s, bonus_y, 0);

						if ((bit2_x <= plusstoo_s + 10) && (bit2_x >= plusstoo_s - 10) && (bit2_y <= bonus_y + 10) && (bit2_y >= bonus_y - 10))
						{
							ilosc_monet += 100;
							rysujmonete2[4] = false;
						}
						ilosc_monet2 = false;
					}
				}
				

			}}

		if ((bit2_x <= bit1_x+ 500) && (bit2_x >= bit1_x - 100) && (bit2_y <= bit1_y + 100) && (bit2_y >= bit1_y - 100))
		{
			
			if (bit2_x >= bit1_x - 100)
			{
				s = 0;
				if (ilosc_monet < 120)
				{
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_draw_bitmap(over, 6170, 150, 0);
				}
				else
				{
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_draw_bitmap(level2, 6180, 250, 0);
					

				}
			}

		}
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
			
		}
		
	

		
		return 0;

	
}