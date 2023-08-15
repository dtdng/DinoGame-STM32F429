/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Screen2ViewBase::Screen2ViewBase()
{
    __background.setPosition(0, 0, 320, 240);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    bg.setXY(-7, -4);
    bg.setBitmap(touchgfx::Bitmap(BITMAP_BG_ID));
    add(bg);

    ground.setXY(0, 178);
    ground.setBitmaps(BITMAP_GROUND0_ID, BITMAP_GROUND2_ID);
    ground.setUpdateTicksInterval(15);
    ground.startAnimation(false, true, true);
    add(ground);

    dinoc.setXY(5, 153);
    dinoc.setBitmaps(BITMAP_DINOC0_ID, BITMAP_DINOC1_ID);
    dinoc.setUpdateTicksInterval(1);
    dinoc.startAnimation(false, true, false);
    dinoc.setVisible(false);
    add(dinoc);

    dino.setXY(12, 134);
    dino.setBitmaps(BITMAP_DINO1_ID, BITMAP_DINO3_ID);
    dino.setUpdateTicksInterval(12);
    dino.startAnimation(false, true, true);
    add(dino);

    bird.setXY(241, 124);
    bird.setBitmaps(BITMAP_BIRD0_ID, BITMAP_BIRD1_ID);
    bird.setUpdateTicksInterval(15);
    bird.startAnimation(false, true, true);
    add(bird);

    cacti1.setXY(206, 149);
    cacti1.setBitmap(touchgfx::Bitmap(BITMAP_CACTUS0_ID));
    add(cacti1);

    textAreaPoint.setXY(232, 26);
    textAreaPoint.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textAreaPoint.setLinespacing(0);
    Unicode::snprintf(textAreaPointBuffer, TEXTAREAPOINT_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_DTA7).getText());
    textAreaPoint.setWildcard(textAreaPointBuffer);
    textAreaPoint.resizeToCurrentText();
    textAreaPoint.setTypedText(touchgfx::TypedText(T___SINGLEUSE_EK8I));
    add(textAreaPoint);

    highestScoreTextArea.setXY(12, 26);
    highestScoreTextArea.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    highestScoreTextArea.setLinespacing(0);
    Unicode::snprintf(highestScoreTextAreaBuffer, HIGHESTSCORETEXTAREA_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_9LM2).getText());
    highestScoreTextArea.setWildcard(highestScoreTextAreaBuffer);
    highestScoreTextArea.resizeToCurrentText();
    highestScoreTextArea.setTypedText(touchgfx::TypedText(T___SINGLEUSE_CZU9));
    add(highestScoreTextArea);
}

Screen2ViewBase::~Screen2ViewBase()
{

}

void Screen2ViewBase::setupScreen()
{

}