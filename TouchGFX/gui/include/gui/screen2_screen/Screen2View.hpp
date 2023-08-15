#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
    virtual void handleClickEvent(const ClickEvent& event);
    virtual void handleGestureEvent(const GestureEvent& event);
    virtual void handleBtnEvent(uint32_t count);
    virtual void checkScore();
    virtual void dinoJump();
    virtual bool checkCollision();
    virtual int16_t rand();
    virtual void writeHighestScore(int);
    virtual int readHighestScore();
    uint32_t tick;
    uint32_t Rx_Data[5];
    int counter; // score
    int horizontal; // horizontal position of enemies, from -50(out of screen) to 320(start appearing)
    uint currentObs; // current enemy type, 0 is cactus, 1 is bird
    int seed; // seed for random enemy
    int jumpDis; // distance for dino to jump for each tick, negative means going up, positive means going down
    bool isJumping; // flag to detect jump
    int BASE_HEIGHT; // original Y pos of dino
    int MAX_HEIGHT; // maximum Y pos of dino when jumping
    int currentHeight; // amount of deviation from BASE_HEIGHT
    int enemySpeed; // number of pixels each enemy will move per tick
    uint32_t obsNumber; // number of enemies, used to increase enemy speed
    int BASE_BIRD_HEIGHT; // base height of bird, used to add variation to bird's Y position
    int timeJump; // check time jump
    int highestScore;
protected:
};

#endif // SCREEN2VIEW_HPP
