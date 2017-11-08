#include "SDL_wsg.h"

wsg::Thread::Thread(Runnable *_runnable)
	:runnable(_runnable),hascb(false)
{

}

wsg::Thread::Thread(CallBack _callback)
	:callback(_callback),hascb(true)
{

}

void wsg::Thread::start()
{
	if(hascb) SDL_CreateThread(cb,this);
	else SDL_CreateThread(run,runnable);
}

void wsg::Thread::stop()
{

}

int wsg::Thread::run(void *runnable)
{
	reinterpret_cast<Runnable *>(runnable)->run();
	return 0;
}

int wsg::Thread::cb(void *thread)
{
	reinterpret_cast<Thread *>(thread)->callback();
	return 0;
}

wsg::Thread::~Thread()
{

}