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

void Engine::MovementController(SDL_Renderer* renderer, Actor* target, const uint8_t* keyboard, int currentframe)
{
    //This one moves the player
    target->renderquad.x += target->xspeed;
    target->renderquad.y += target->yspeed;

    target->hitbox.x = target->renderquad.x + target->renderquad.w/4;
    target->hitbox.y = target->renderquad.y + target->renderquad.h/4;

    target->bone_gun.x = target->renderquad.x + 45;
    target->bone_gun.y = target->renderquad.y + 45;

    if (keyboard[SDL_SCANCODE_W])
    {
        if (target->renderquad.y >= 100)
            target->yspeed = -5;
        else
            target->yspeed = 0;
    }
    if (keyboard[SDL_SCANCODE_S])
    {
        if (target->renderquad.y <= HEIGHT - 150)
            target->yspeed = 5;
        else
            target->yspeed = 0;
    }
    if ((!keyboard[SDL_SCANCODE_W]) && (!keyboard[SDL_SCANCODE_S]))
    {
        target->yspeed = 0;
    }

    if (keyboard[SDL_SCANCODE_D])
    {
        if (target->renderquad.x <= (WIDTH*7)/10)
            target->xspeed = 5;
        else
            target->xspeed = 0;
    }
    if (keyboard[SDL_SCANCODE_A])
    {
        if (target->renderquad.x >= 0)
            target->xspeed = -5;
        else
            target->xspeed = 0;
    }
    if ((!keyboard[SDL_SCANCODE_D]) && (!keyboard[SDL_SCANCODE_A]))
    {
        target->xspeed = 0;
    }

    if (keyboard[SDL_SCANCODE_SPACE])
    {
        if (currentframe >= target->lockedOnFrame + target->lockout)
        {
            Shoot(renderer, target, currentframe);
            target->lockedOnFrame = currentframe;
        }
    }
}

void Engine::MovementController(Actor* target, Actor* enemy, int currentframe)
{
    enemy->renderquad.x += enemy->xspeed;
    enemy->renderquad.y += enemy->yspeed;

    enemy->hitbox.x = enemy->renderquad.x;
    enemy->hitbox.y = enemy->renderquad.y;

    if (currentframe % 4 == 0)
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

            if ((target->renderquad.y < enemy->renderquad.y) && (enemy->yspeed > -5))
            {
                enemy->yspeed -= 1;
            }
            else if ((target->renderquad.y > enemy->renderquad.y) && (enemy->yspeed < 5))
            {
                enemy->yspeed += 1;
            }
            break;
        case KAMIKAZE:
            //An enemy type that just dives onto the player.
            //Ideally, should not call more than three of them at once

            if (target->renderquad.y < enemy->renderquad.y)
            {
                if (enemy->yspeed > -8)
                {
                    enemy->yspeed -= 1;
                }
            }
            else if (target->renderquad.y > enemy->renderquad.y)
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

void Engine::MovementController(Actor* bullet, int currentframe)
{
    bullet->renderquad.x += bullet->xspeed;
    bullet->renderquad.y += bullet->yspeed;

    bullet->hitbox.x = bullet->renderquad.x;
    bullet->hitbox.y = bullet->renderquad.y;

    if (bullet->renderquad.x > WIDTH + 5)
        bullet->state = DESTROYED;
}
