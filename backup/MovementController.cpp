#include "Engine.h"

using namespace std;

/*
So you might be wondering "What the fsck am I even looking at ?", and in a way, I totally understand that.
Those things are behavior controllers. Turns out that the Behave() class method I used can't be really used
as is, due to (I think) a language limitation: Containers cannot store derived classes. Object slicing
happens all over the place, which makes calling the derived Behave() methods near impossible.

One solution would have been to make a container of pointers, but that prevents us from instancing
new objects on the fly, so each level would have to preallocate a table of non-respawning enemies,
which doesn't quite work out with the concept of wraparound levels.

A reference wrapper (see header <functional>) runs into a similar problem: you can't create anonymous
objects with the reference wrapper, and thus you end up with the same problem, and the same bad
solution to it.

All in all, the Controllers solution should be less of a hassle to both implement and work
with, but I'll see what the collision detection function has to say about performance issues. -L
*/

void Engine::TheAlmightyController(Actor* player, const uint8_t* keyboard, int currentframe)
{
    player->renderquad.x += player->xspeed;
    player->renderquad.y += player->yspeed;

    player->bone_gun.x = player->renderquad.x + 45;
    player->bone_gun.y = player->renderquad.y + 45;

    if (keyboard[SDL_SCANCODE_W])
    {
        if (player->renderquad.y >= 100)
            player->yspeed = -5;
        else
            player->yspeed = 0;
    }
    if (keyboard[SDL_SCANCODE_S])
    {
        if (player->renderquad.y <= HEIGHT - 150)
            player->yspeed = 5;
        else
            player->yspeed = 0;
    }
    if ((!keyboard[SDL_SCANCODE_W]) && (!keyboard[SDL_SCANCODE_S]))
    {
        player->yspeed = 0;
    }

    if (keyboard[SDL_SCANCODE_D])
    {
        if (player->renderquad.x <= (WIDTH*7)/10)
            player->xspeed = 5;
        else
            player->xspeed = 0;
    }
    if (keyboard[SDL_SCANCODE_A])
    {
        if (player->renderquad.x >= 0)
            player->xspeed = -5;
        else
            player->xspeed = 0;
    }
    if ((!keyboard[SDL_SCANCODE_D]) && (!keyboard[SDL_SCANCODE_A]))
    {
        player->xspeed = 0;
    }
}

void Engine::TheAlmightyController(Actor* player, Actor* enemy, int currentframe)
{
    enemy->renderquad.x += enemy->xspeed;
    enemy->renderquad.y += enemy->yspeed;

    if (currentframe % 2 == 0)
    {
        switch (enemy->subtype)
        {
        case NONE:
            //We shouldn't do anything here, this is just to prevent the compiler
            //from bitching out because one enumeration value is not handled
            //in this switch
            break;
        case REGULAR:
            //Flies in a straight line, right to left, shoots sometimes.
            //Spawns at a randomized height.
            //Clusters of 3-6 recommended, perhaps more in later levels
            break;
        case BOMBER:
            //Hangs on the screen and unloads mines that float up and leftwards.
            //Depending on actual machine perf, can spawn in clusters of
            //anywhere between two and (maybe ?) six.
            if ((enemy->renderquad.x < (WIDTH*4)/10) && (enemy->xspeed < 5))
            {
                enemy->xspeed++;
            }
            else if ((enemy->renderquad.x > WIDTH - 100) && (enemy->xspeed > -5))
            {
                enemy->xspeed--;
            }

            if ((player->renderquad.y < enemy->renderquad.y) && (enemy->yspeed > -5))
            {
                enemy->yspeed -= 1;
            }
            else if ((player->renderquad.y > enemy->renderquad.y) && (enemy->yspeed < 5))
            {
                enemy->yspeed += 1;
            }
            break;
        case KAMIKAZE:
            //An enemy type that just dives onto the player.
            //Ideally, should not call more than three of them at once

            if (player->renderquad.y < enemy->renderquad.y)
            {
                if (enemy->yspeed > -8)
                {
                    enemy->yspeed -= 1;
                }
            }
            else if (player->renderquad.y > enemy->renderquad.y)
            {
                if (enemy->yspeed < 8)
                {
                    enemy->yspeed += 1;
                }
            }
            break;
        case TANK:
            //Slows down when the player is at an high altitude,
            //speeds up when the player dives to bomb it.
            //
            //Maybe make it shoot too ?
            break;
            }
    }

    if ((enemy->renderquad.x < -50) || (currentframe == enemy->createdOnFrame + enemy->timeToLive))
        enemy->state = DESTROYED;
}

void Engine::TheAlmightyController(Actor* bullet, int currentframe)
{
    bullet->renderquad.x += bullet->xspeed;

    if ((bullet->createdOnFrame + bullet->timeToLive >= currentframe) || (bullet->renderquad.x > WIDTH))
        bullet->state = DESTROYED;
}
