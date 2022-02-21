#ifndef LBGE2_MAINLEVEL_H
#define LBGE2_MAINLEVEL_H

#include "LBGECore.h"
#include "LBGEUi.h"

class MainLevel : public Level
{
public:
    void Init() override;

private:
    TextBlock* m_textBlock;

};


#endif //LBGE2_MAINLEVEL_H
