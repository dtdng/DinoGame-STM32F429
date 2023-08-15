#include <gui/screen3_screen/Screen3View.hpp>

Screen3View::Screen3View()
{
	score = 0;
}

void Screen3View::setupScreen()
{
    Screen3ViewBase::setupScreen();
    score = presenter->getScore();

    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%d", score);
}

void Screen3View::tearDownScreen()
{
    Screen3ViewBase::tearDownScreen();
}
