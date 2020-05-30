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

//Testing branch

#include "main.h"

int main()
{
    initVita();

    while (1)
    {
        sceCtrlPeekBufferPositive(0, &pad, 1);

        switch (gameState)
        {
            case Title:
                startFrame();
                
                vita2d_pgf_draw_text(pgf, 20, 30, WHITE, 1.0f, "Title");
                handleInput();

                endFrame();
            
            break;

            case Playing:
                startFrame();

                vita2d_pgf_draw_text(pgf, 20, 30, WHITE, 1.0f, "Playing");
                handleInput();

                endFrame();
            
            break;

            default:
                gameState = Playing;
            break;
        }
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
