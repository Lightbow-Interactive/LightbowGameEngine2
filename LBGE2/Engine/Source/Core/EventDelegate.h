#ifndef LBGE2_EVENTDELEGATE_H
#define LBGE2_EVENTDELEGATE_H


class EventDelegate
{
public:
    void Invoke();
    void Bind(void (*_func)());

private:
    void (*func)();

};


#endif //LBGE2_EVENTDELEGATE_H
