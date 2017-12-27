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
with, but I'll see what the collision detection function has to say about perf issues. -L
*/

void Engine::TheAlmightyController(Actor* player)
{
    player->renderquad.x += player->xspeed;
    player->renderquad.y += player->yspeed;
}
