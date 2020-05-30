/* 
* BSD 2-Clause License
* 
* Copyright (c) 2020, 143 Software
* All rights reserved.
* 
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
* 
* 1. Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer.
* 
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "input.h"

void handleInput()
{
    switch (gameState)
    {
        case Title:
            if (pad.buttons & SCE_CTRL_CROSS)
            {
                gameState = Playing;
            }
        break;

        case Playing:
            if (pad.buttons & SCE_CTRL_START)
            {
                IS_PAUSED = true;
            }

            if (IS_PAUSED)
            {
                //pauseOption = ResumeGameOption;
                vita2d_draw_rectangle((SCREEN_W/2) - (SCREEN_W/4), (SCREEN_H/2) - (SCREEN_H/4), SCREEN_W/2, SCREEN_H/2, RGBA8(0x0B,0x58,0x7F,0xFF));
                vita2d_draw_rectangle(((SCREEN_W/2) - (SCREEN_W/4)) + 5, ((SCREEN_H/2) - (SCREEN_H/4)) + 5, (SCREEN_W/2) - 10, (SCREEN_H/2) - 10, RGBA8(0x2D,0x84,0xAF,0xFF));
                vita2d_pgf_draw_text(pgf, (SCREEN_W/2) - 50, (SCREEN_H/2) - 90, WHITE, 1.5f, "Paused");
                
                vita2d_pgf_draw_text(pgf, (SCREEN_W/2) - 200, (SCREEN_H/2) - 40, WHITE, 1.0f, "Score");
                vita2d_pgf_draw_text(pgf, (SCREEN_W/2) - 200, (SCREEN_H/2) - 10, WHITE, 1.0f, "000000");

                vita2d_pgf_draw_text(pgf, (SCREEN_W/2) + 150, (SCREEN_H/2) - 40, WHITE, 1.0f, "Lives");
                vita2d_pgf_draw_text(pgf, (SCREEN_W/2) + 150, (SCREEN_H/2) - 10, WHITE, 1.0f, "1");

                if (pauseOption == ResumeGameOption)
                {
                    vita2d_pgf_draw_text(pgf, (SCREEN_W/2) - 60, (SCREEN_H/2) + 80, RGBA8(0xFF,0xD8,0x3A,0xFF), 1.0f, "Resume game");
                    vita2d_pgf_draw_text(pgf, (SCREEN_W/2) - 50, (SCREEN_H/2) + 110, RGBA8(0xFF,0xFF,0xFF,0xFF), 1.0f, "Back to title");
                    
                    if (pad.buttons & SCE_CTRL_DOWN)
                    {
                        pauseOption = TitleScreenOption;
                    }
                    else if (pad.buttons & SCE_CTRL_CROSS)
                    {
                        IS_PAUSED = false;
                    }
                }
                else if (pauseOption == TitleScreenOption)
                {
                    vita2d_pgf_draw_text(pgf, (SCREEN_W/2) - 60, (SCREEN_H/2) + 80, RGBA8(0xFF,0xFF,0xFF,0xFF), 1.0f, "Resume game");
                    vita2d_pgf_draw_text(pgf, (SCREEN_W/2) - 50, (SCREEN_H/2) + 110, RGBA8(0xFF,0xD8,0x3A,0xFF), 1.0f, "Back to title");
                    
                    if (pad.buttons & SCE_CTRL_UP)
                    {
                        pauseOption = ResumeGameOption;
                    }
                    else if (pad.buttons & SCE_CTRL_CROSS)
                    {
                        resetGame();
                        sceKernelDelayThread(100000);
                    }
                }
            }
            else
            {
                if (pad.buttons & SCE_CTRL_LEFT)
                {
                    playerx -= speedVal;
                }
                else if (pad.buttons & SCE_CTRL_RIGHT)
                {
                    playerx += speedVal;
                }

                if (playerx < 0)
                    playerx = 0;

                if (playerx > 839)
                    playerx = 839;
            }
        break;

        default:
        break;
    }
}