#include "allegro5\allegro.h"
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
	al_set_window_title(okno, "Efekt kolizji");

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


	okno = al_create_display(1100, 660);
	timer = al_create_timer(1.0 / FPS);

	ALLEGRO_BITMAP *bit2;
	bit2 = al_load_bitmap("wiezien.png");
	if (!bit2)
		return 1;
	ALLEGRO_BITMAP *bit1;
	bit1 = al_load_bitmap("police.png");
	if (!bit1)
		return 1;
	ALLEGRO_BITMAP *back;
	back = al_load_bitmap("tlo.png");
	if (!back)
		return 1;
	ALLEGRO_FONT *font24 = al_create_builtin_font();
	if (!font24)
		return 1;

	al_convert_mask_to_alpha(bit2, al_map_rgb(24, 34, 46));
	al_convert_mask_to_alpha(bit1, al_map_rgb(255,255,255));

	int bit1_x = 0, bit1_y = 550;
	int bit2_x = 110, bit2_y = 540;

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	bool close = false;
	bool accident = false;

	al_start_timer(timer);
	while (!close)
	{
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

			bit2_y -= keys[SPACE] * 5;
			bit2_y += keys[S] * 5;
			bit2_x -= keys[A] * 5;
			bit2_x += keys[D] * 5;
			al_draw_bitmap(back, 0, 0, 0);

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
			al_draw_bitmap(bit1, bit1_x, bit1_y, 0);

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