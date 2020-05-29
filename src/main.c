#include <psp2/display.h>
#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <stdlib.h>
#include <vita2d.h>

#define SCREEN_W 960
#define SCREEN_H 544

#define BLACK RGBA8(0, 0, 0, 255)
#define GREEN RGBA8(0, 255, 0, 255)
#define RED RGBA8(255, 0, 0, 255)
#define BLUE RGBA8(0, 0, 255, 255)
#define WHITE RGBA8(255, 255, 255, 255)

extern unsigned char _binary_data_Textures_center_png_start;
extern unsigned char _binary_data_Textures_bg_png_start;

int boundaryXLeft = 0;
int boundaryXRight = 839;
int boundaryYUp = 0;
int boundaryYDown = 418;

int randx = 0;

int game_playing;

vita2d_pgf *pgf;
SceCtrlData pad;

typedef struct
{
    int x;
    int y;
    int w;
    int h;
    int speed;
    vita2d_texture *texture;
} Sprite;

#define MAX_ENEMIES 6

Sprite player;
Sprite enemies[MAX_ENEMIES];

uint16_t enemiesLeft = 0;

Sprite* e = enemies;
vita2d_texture *bg;

void debugInfo()
{
                vita2d_pgf_draw_textf(pgf, 10, 30, WHITE, 1.0f, "X: %d", player.x);
                vita2d_pgf_draw_textf(pgf, 10, 50, WHITE, 1.0f, "Y: %d", player.y);
                vita2d_pgf_draw_textf(pgf, 10, 70, WHITE, 1.0f, "speed: %d", player.speed);
                vita2d_pgf_draw_textf(pgf, 10, 90, WHITE, 1.0f, "rand: %d", randx);
}

void playerInit()
{
    player.x = 419;
    player.y = 418;
    player.speed = 13;
    player.texture = vita2d_load_PNG_buffer(&_binary_data_Textures_center_png_start);
}

void playerInput()
{
    sceCtrlPeekBufferPositive(0, &pad, 1);

    if ((pad.buttons & SCE_CTRL_UP) && (player.y > boundaryYUp))
    {
        player.y -= player.speed;
    }
    else if ((pad.buttons & SCE_CTRL_DOWN) && (player.y < boundaryYDown))
    {
        player.y += player.speed;
    }
    else if ((pad.buttons & SCE_CTRL_LEFT) && (player.x > boundaryXLeft))
    {
        player.x -= player.speed;
    }
    else if ((pad.buttons & SCE_CTRL_RIGHT) && (player.x < boundaryXRight))
    {
        player.x += player.speed;
    }

    //Restrict movement so we don't move past left or right of the screen
    if (player.x < boundaryXLeft)
        player.x = boundaryXLeft;

    if (player.x > boundaryXRight)
        player.x = boundaryXRight;

    if (player.y > boundaryYDown)
        player.y = boundaryYDown;

    //Start will quit the scene and bring us back
    if (pad.buttons & SCE_CTRL_START)
    {
        game_playing = 0;
    }

    //Left and right triggers will change out movement speed (debug)
    if (pad.buttons & SCE_CTRL_LTRIGGER)
    {
        player.speed--;
    }
                
    if (pad.buttons & SCE_CTRL_RTRIGGER)
    {
        player.speed++;
    }
}

void draw()
{
    //Draw the background
    vita2d_draw_texture_scale(bg, 0, 0, 1.0f, 1.0f);

    /*e = enemies;
    for (int i = 0; i < 3; i++)
    {
        e->x = i*64;
        e->y = 32;
        e->w = 128;
        e->h = 128;
        e->texture = vita2d_load_PNG_buffer(&_binary_data_Textures_center_png_start);

	    vita2d_draw_texture_scale(e->texture, e->x, e->y, 0.5f, 0.5f);

        enemiesLeft++;
        e++;
    }
    */
    //Draw the player
    vita2d_draw_texture_tint_scale(player.texture, player.x, player.y, 0.5f, 0.5f, RGBA8(255,255,255,255));

}

void update()
{
    playerInput();
}

int main()
{
    vita2d_init();
    vita2d_set_clear_color(BLACK);

    pgf = vita2d_load_default_pgf();
    bg = vita2d_load_PNG_buffer(&_binary_data_Textures_bg_png_start);

    playerInit();

    while (1)
    {
        vita2d_start_drawing();
        vita2d_clear_screen();

        sceCtrlPeekBufferPositive(0, &pad, 1);

        vita2d_pgf_draw_text(pgf, 400, 230, RGBA8(255, 255, 255, 255), 1.0f, "Once upon a time...");

        if (pad.buttons & SCE_CTRL_CROSS)
        {
            vita2d_clear_screen();
            game_playing = 1;
        }

        if (game_playing)
        {
            vita2d_end_drawing();
            vita2d_swap_buffers();
            sceDisplayWaitVblankStart();

            while (game_playing)
            {
		        //Start the frame
                vita2d_start_drawing();
                vita2d_clear_screen();

		        //Do stuff
		        draw();
		        update(); 
                debugInfo();

                //End the frame
                vita2d_end_drawing();
                vita2d_swap_buffers();
            }
        }


        vita2d_end_drawing();
        vita2d_swap_buffers();
        sceDisplayWaitVblankStart();
    }

    //Clean up
    vita2d_fini();
    vita2d_free_pgf(pgf);
    vita2d_free_texture(player.texture);
    sceKernelExitProcess(0);

    return 0;
}

//Collision detection
//int diffX = firstMovingX - secondMovingX;
//if (diffX < 0)
//{
//    diffX = secondMovingX - firstMovingX;
//}

//int diffY = firstMovingY - secondMovingY;
//if (diffY < 0)
//{
//    diffY = secondMovingY - firstMovingY;
//}

//if ((diffX < 100) && (diffY < 100))
//{
//    vita2d_pgf_draw_text(pgf, 400, 50, RED, 1.0f, "COLLISION DETECTED!");
//}
