#include "allegro5\allegro.h"
#include "ctime"
#include "allegro5\allegro_native_dialog.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"
#include "allegro5\allegro_image.h"
#include "allegro5\keyboard.h"
#include "allegro5\timer.h"

enum KEYS { SPACE, S, A, D };
int main()
{
	ALLEGRO_DISPLAY *okno = NULL;
	ALLEGRO_TIMER *timer = NULL;
	al_set_window_title(okno, "Co mu zrobisz jak mnie z³apiesz");

	const int FPS = 50;
	const int width = 1100;
	const int height = 760;

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


	okno = al_create_display(width, height);
	timer = al_create_timer(1.0 / FPS);

	ALLEGRO_BITMAP *bit2;
	bit2 = al_load_bitmap("wiezien.png");
	if (!bit2)
		return 1;
	ALLEGRO_BITMAP *bit1;
	bit1 = al_load_bitmap("police.png");
	if (!bit1)
		return 1;
	ALLEGRO_BITMAP *level;
	level = al_load_bitmap("level.png");
	if (!level)
		return 1;
	ALLEGRO_BITMAP *back;
	back = al_load_bitmap("tlo.png");
	if (!back)
		return 1;
	ALLEGRO_BITMAP *money;
	money = al_load_bitmap("monety.png");
	if (!money)
		return 1;
	ALLEGRO_BITMAP *przeszkoda1;
	przeszkoda1 = al_load_bitmap("przeszkoda1.png");
	if (!przeszkoda1)
		return 1;
	ALLEGRO_FONT *font24 = al_create_builtin_font();
	if (!font24)
		return 1;
	ALLEGRO_FONT *font2 = al_create_builtin_font();
	if (!font2)
		return 1;
	ALLEGRO_FONT *font3 = al_create_builtin_font();
	if (!font3)
		return 1;
	ALLEGRO_FONT *font4 = al_create_builtin_font();
	if (!font4)
		return 1;

	al_convert_mask_to_alpha(bit2, al_map_rgb(237,28,36));
	al_convert_mask_to_alpha(bit1, al_map_rgb(255,255,255));
	al_convert_mask_to_alpha(money, al_map_rgb(237, 28, 36));
	al_convert_mask_to_alpha(przeszkoda1, al_map_rgb(237, 28, 36));
	srand(time(NULL));
	int bit1_x=0, bit1_y=0;
	int bit2_x =5, bit2_y = 440;
	int money_x;
	int money_y[10];
	int przeszkoda1_x=0;
	int przeszkoda1_y = 495;
	int ilosc_monet = 0;
	float czas;
	int test = 0;
	int back_x=0;
	int tab[20] = { 0 };
	int tab1[20] = { 0 };

	
	
	


	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	

	bool close = false;
	bool accident = false;
	bool ilosc_monet2 = false;
	bool dodaj_monete = false;
	bool wynik=false;
	bool rysujmonete = false;
	bool rysujprzeszkode1 = false;



	for (int i = 1;i < 10;i++)
	{
		
		money_x = (i*400)+60;
		tab[i] = money_x;
		money_y[i] = rand() % 400 + 150;
		
		
	}
	for (int i = 1;i < 10;i++)
	{

		przeszkoda1_x = (i * 500) + 60;
		tab1[i] = przeszkoda1_x;
		


	}

	al_start_timer(timer);
	while (!close)


	{
			czas = al_get_time();
		
			back_x--;
		
			al_draw_bitmap(back, back_x, 0, 0);
			al_draw_bitmap(back, back_x + 4000, 0, 0);
			if (back_x == 3000)
			{
				break;
			}
			wynik = ilosc_monet*czas;
		al_draw_bitmap(level, 390, 670, 0);
		al_draw_textf(font2, al_map_rgb(0,0, 760),900, 665, 0, "Ilosc monet: %d", ilosc_monet);
		al_draw_textf(font3, al_map_rgb(0, 0, 760), 900, 675, 0, "Wynik: %d", wynik);
		al_draw_textf(font4, al_map_rgb(0, 0, 760), 0, 665, 0, "Czas: %.2f sek", czas);
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
				bit2_y += 100;
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
			
				bit2_y -= keys[SPACE] * 5;
				bit2_y += keys[S] * 5;
				bit2_x -= keys[A] * 5;
				bit2_x += keys[D]*1;
			
		}
		if (rysujprzeszkode1 != false)
		{
			for (int i = 0;i < 10;i++)

			{
				tab1[i]--;

				al_draw_bitmap(przeszkoda1, tab1[i], przeszkoda1_y, 0);
			}

		}

		for (int j = 0;j <10;j++)
		{
			if (rand() % 2 == 1)
			{
				rysujprzeszkode1 = true;
			}
			
		}

		for (int k=3;k < 10;k++)
		{
			if ((bit2_x <= tab1[k] + 100) && (bit2_x >= tab1[k] - 100) && (bit2_y <= przeszkoda1_y + 200) && (bit2_y >= przeszkoda1_y - 200))
			{
				bit2_x -= 5;
			}
		}
		
		if (rysujmonete != false)
		{
			for (int i = 0;i < 10;i++)

			{
				tab[i]--;
			
				al_draw_bitmap(money, tab[i], money_y[i], 0);
			}
			
		}
	
		for (int j = 0;j <10;j++)
		{
			if (rand() % 2 == 1)
			{
				rysujmonete = true;
			}
		}
	
		for (int k = 0;k < 10;k++)
		{
			if ((bit2_x <= tab[k]) && (bit2_x >= tab[k]) && (bit2_y <= money_y[k] + 100) && (bit2_y >= money_y[k] - 100))
			{
				ilosc_monet2 = true;
			}
			if (ilosc_monet2 == true)
			{
				ilosc_monet++;
				ilosc_monet2 = false;
				

			}
		}
		if ((bit2_x <= bit1_x + 100) && (bit2_x >= bit1_x - 100) && (bit2_y <= bit1_y + 100) && (bit2_y >= bit1_y - 100))
			accident = true;

		if (!accident)
		{
			if (bit1_x < 0)
				bit1_x = 0;
			else if (bit1_x > al_get_display_width(okno) - al_get_bitmap_width(bit1))
				bit1_x = al_get_display_width(okno) - al_get_bitmap_width(bit1);
			if (bit1_y < 0)
				bit1_y = 0;
			else if (bit1_y > al_get_display_height(okno) - al_get_bitmap_height(bit1))
				bit1_y = al_get_display_height(okno) - al_get_bitmap_height(bit1);
		
		

			if (bit2_x < 0)
				bit2_x = 0;
			else if (bit2_x > al_get_display_width(okno) - al_get_bitmap_width(bit2))
				bit1_x = al_get_display_width(okno) - al_get_bitmap_width(bit2);
			if (bit2_y < 0)
				bit2_y = 0;
			else if (bit2_y > al_get_display_height(okno) - al_get_bitmap_height(bit2))
				bit2_y = al_get_display_height(okno) - al_get_bitmap_height(bit2);
			al_draw_bitmap(bit2, bit2_x, bit2_y, 0);
			
		}
		
		else
			al_draw_text
			(
				font24, al_map_rgb(255, 255, 255), al_get_display_width(okno) / 2,
				al_get_display_height(okno) / 2,
				ALLEGRO_ALIGN_CENTRE, "GAME OVER-press esc to close the window"
				);
	
		
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	al_destroy_bitmap(bit1);
	al_destroy_bitmap(bit2);
	al_destroy_font(font24);
	al_destroy_display(okno);
	return 0;
	
}