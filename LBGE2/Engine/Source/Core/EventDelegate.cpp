#include "EventDelegate.h"

#include <iostream>

void EventDelegate::Invoke()
{
    if (func) func();
    else std::cout << "Event has no binding" << std::endl;
}

void EventDelegate::Bind(void (*_func)())
{
    func = _func;
}
