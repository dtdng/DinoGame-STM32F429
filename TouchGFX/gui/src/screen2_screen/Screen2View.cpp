#include <gui/screen2_screen/Screen2View.hpp>
#include <gui/screen3_screen/Screen3View.hpp>
#include <cmsis_os.h>
#include "stm32f4xx_hal.h"
#include "string.h"
#include "stdio.h"
//#include <FLASH_SECTOR_F4.h>
//#include <FLASH_SECTOR_F4.c>
#include <math.h>
Screen2View::Screen2View()
{
	tick = 0;
	horizontal = 320;
	currentObs = 0;
	seed = 1;
	jumpDis = -4;
	isJumping = false;
	BASE_HEIGHT = 134;
	MAX_HEIGHT = 70;
	currentHeight = 1;
	counter = 0;
	enemySpeed = 3;
	obsNumber = 0;
	BASE_BIRD_HEIGHT = 124;
	timeJump = 0;
	highestScore = 0;
}

void Screen2View::setupScreen()
{

    Screen2ViewBase::setupScreen();
    dinoc.setVisible(false);
    highestScore = readHighestScore();
    Unicode::snprintf(highestScoreTextAreaBuffer, HIGHESTSCORETEXTAREA_SIZE, "%d", highestScore);
    highestScoreTextArea.invalidate();
    Unicode::snprintf(textAreaPointBuffer, TEXTAREAPOINT_SIZE, "%d", counter);
    textAreaPoint.invalidate();
    // set enemies to be on the right edge of screen
    cacti1.setX(320);
    bird.setX(320);
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}

extern osMessageQueueId_t randomNumberQueueHandle;
int16_t Screen2View::rand(){
	int16_t randomNumber = 0;
	if (osMessageQueueGetCount(randomNumberQueueHandle) > 0){
		osMessageQueueGet(randomNumberQueueHandle, &randomNumber, NULL, osWaitForever);
	}
	return randomNumber;
}

extern osMessageQueueId_t buttonQueueHandle;
void Screen2View::handleTickEvent(){
	Screen2ViewBase::handleTickEvent();
	tick++;

	bool gameOver = checkCollision();
	if (gameOver){
		if(counter > highestScore) highestScore = counter;
		presenter->saveScore(counter);
		presenter->saveHighestScore(highestScore);
		writeHighestScore(highestScore);
		static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen3ScreenNoTransition();;
	}

	// check queue
	uint32_t count = osMessageQueueGetCount(buttonQueueHandle);
	if(count > 0){
		handleBtnEvent(count);
	}

	// set enemy according to random number
	switch (currentObs){
	case 0:
		cacti1.setX(horizontal);
		break;
	case 1:
		bird.setX(horizontal);
		break;
	}

	horizontal -= enemySpeed;

	if (horizontal < -50){
		currentObs = rand() % 2;
		if (currentObs == 1){ // diversify height of bird
			switch (rand() % 3){
				case 0:
					bird.setY(BASE_BIRD_HEIGHT);
					break;
				case 1:
					bird.setY(BASE_BIRD_HEIGHT - 22);
					break;
				case 2:
					bird.setY(BASE_BIRD_HEIGHT + 25);
					break;
			}
		}
		horizontal = 320;

		// increase difficulty, every x enemies, the enemySpeed increases
		obsNumber++;
		if (obsNumber % 10 == 0){
			enemySpeed++;
			// max enemy speed is 7 to limit the game's difficulty
			if (enemySpeed > 7)
				enemySpeed = 7;
		}


	}
	checkScore();

	// Jump logic
	if (isJumping){
		dinoJump();
	}
	invalidate();
}

void Screen2View::dinoJump(){
	dinoc.setVisible(false);
	dino.setVisible(true);
	dino.stopAnimation();
	timeJump++;
	int a = -10; //acceleration
	int v0  = 50; // base spd
	currentHeight = round(BASE_HEIGHT - a*timeJump*timeJump/100 - v0*timeJump/10);//y = a*t*t + v0*t+y0
	dino.setY(currentHeight);

	// reset state after landing
	if (dino.getY() >= BASE_HEIGHT){
		dino.setY(BASE_HEIGHT);
		dino.startAnimation(false, true, true);
		isJumping = false;
		currentHeight = 1;
	}
}

void Screen2View::checkScore(){
	//printout the point
	if(tick % 5 == 0) counter++;
	if(counter < highestScore){
		Unicode::snprintf(textAreaPointBuffer, TEXTAREAPOINT_SIZE, "%d", counter);
		textAreaPoint.invalidate();
		Unicode::snprintf(highestScoreTextAreaBuffer, HIGHESTSCORETEXTAREA_SIZE, "%d", highestScore);
		highestScoreTextArea.invalidate();
	}else{
		textAreaPoint.setVisible(false);
		Unicode::snprintf(highestScoreTextAreaBuffer, HIGHESTSCORETEXTAREA_SIZE, "%d", counter);
		highestScoreTextArea.invalidate();
	}
}


bool Screen2View::checkCollision(){
	int16_t dinoT, dinoR, dinoB, dinoL;
	if (dino.isVisible()){
		int deviation = BASE_HEIGHT - dino.getY(); // amount of deviation of the dino from the ground
		if (deviation > 8) deviation = 8; // max deviation is 8, which reaches dino's legs
		dinoL = dino.getX();
		dinoT = dino.getY() + 10;
		// simulate the skew of the dino's lower body using the deviation value
		dinoR = dino.getX() + dino.getWidth() - 10 - deviation;
		dinoB = dino.getY() + dino.getHeight() - 5;
	} else {
		dinoL = dinoc.getX();
		dinoT = dinoc.getY() + 10;
		dinoR = dinoc.getX() + dinoc.getWidth();
		dinoB = dinoc.getY() + dinoc.getHeight();
	}

	int16_t obsT, obsR, obsB, obsL;
	if (currentObs == 0){
		obsL = cacti1.getX();
		obsT = cacti1.getY();
		obsR = cacti1.getX() + cacti1.getWidth();
		obsB = cacti1.getY() + cacti1.getHeight();
	} else {
		obsL = bird.getX();
		obsT = bird.getY();
		obsR = bird.getX() + bird.getWidth();
		obsB = bird.getY() + bird.getHeight();
	}

	if (dinoR >= obsL && dinoL <= obsR && dinoB >= obsT && dinoT <= obsB){
		return true;
	}

	return false;
}

void Screen2View::handleBtnEvent(uint32_t count){
	uint8_t res = 0;
	osMessageQueueGet(buttonQueueHandle, &res, NULL, osWaitForever);
			if(res == 1 && isJumping == false){
				timeJump = 0;
				isJumping = true;
			}
			if(res == 2){
				dino.setVisible(false);
				dinoc.setVisible(true);
			}
			if(res == 3){
				dino.setVisible(true);
				dinoc.setVisible(false);
	}
}

//TODO: switch to physical button
void Screen2View::handleClickEvent(const ClickEvent& event){
	Screen2ViewBase::handleClickEvent(event);

	// logic for crouching
	if (event.getType() == ClickEvent::PRESSED){
		dino.setVisible(false);
		dinoc.setVisible(true);
	}

	if (event.getType() == ClickEvent::RELEASED){
		dino.setVisible(true);
		dinoc.setVisible(false);
	}

}

//TODO: switch to physical button
void Screen2View::handleGestureEvent(const GestureEvent& event){
	Screen2ViewBase::handleGestureEvent(event);
	// detect jumping
	if (event.getType() == GestureEvent::SWIPE_VERTICAL){
			timeJump = 0;
			isJumping = true;
	}
}


static uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;

  if((Address < 0x08003FFF) && (Address >= 0x08000000))
  {
    sector = FLASH_SECTOR_0;
  }
  else if((Address < 0x08007FFF) && (Address >= 0x08004000))
  {
    sector = FLASH_SECTOR_1;
  }
  else if((Address < 0x0800BFFF) && (Address >= 0x08008000))
  {
    sector = FLASH_SECTOR_2;
  }
  else if((Address < 0x0800FFFF) && (Address >= 0x0800C000))
  {
    sector = FLASH_SECTOR_3;
  }
  else if((Address < 0x0801FFFF) && (Address >= 0x08010000))
  {
    sector = FLASH_SECTOR_4;
  }
  else if((Address < 0x0803FFFF) && (Address >= 0x08020000))
  {
    sector = FLASH_SECTOR_5;
  }
  else if((Address < 0x0805FFFF) && (Address >= 0x08040000))
  {
    sector = FLASH_SECTOR_6;
  }
  else if((Address < 0x0807FFFF) && (Address >= 0x08060000))
  {
    sector = FLASH_SECTOR_7;
  }
  else if((Address < 0x0809FFFF) && (Address >= 0x08080000))
  {
    sector = FLASH_SECTOR_8;
  }
  else if((Address < 0x080BFFFF) && (Address >= 0x080A0000))
  {
    sector = FLASH_SECTOR_9;
  }
  else if((Address < 0x080DFFFF) && (Address >= 0x080C0000))
  {
    sector = FLASH_SECTOR_10;
  }
  else if((Address < 0x080FFFFF) && (Address >= 0x080E0000))
  {
    sector = FLASH_SECTOR_11;
  }
  else if((Address < 0x08103FFF) && (Address >= 0x08100000))
  {
    sector = FLASH_SECTOR_12;
  }
  else if((Address < 0x08107FFF) && (Address >= 0x08104000))
  {
    sector = FLASH_SECTOR_13;
  }
  else if((Address < 0x0810BFFF) && (Address >= 0x08108000))
  {
    sector = FLASH_SECTOR_14;
  }
  else if((Address < 0x0810FFFF) && (Address >= 0x0810C000))
  {
    sector = FLASH_SECTOR_15;
  }
  else if((Address < 0x0811FFFF) && (Address >= 0x08110000))
  {
    sector = FLASH_SECTOR_16;
  }
  else if((Address < 0x0813FFFF) && (Address >= 0x08120000))
  {
    sector = FLASH_SECTOR_17;
  }
  else if((Address < 0x0815FFFF) && (Address >= 0x08140000))
  {
    sector = FLASH_SECTOR_18;
  }
  else if((Address < 0x0817FFFF) && (Address >= 0x08160000))
  {
    sector = FLASH_SECTOR_19;
  }
  else if((Address < 0x0819FFFF) && (Address >= 0x08180000))
  {
    sector = FLASH_SECTOR_20;
  }
  else if((Address < 0x081BFFFF) && (Address >= 0x081A0000))
  {
    sector = FLASH_SECTOR_21;
  }
  else if((Address < 0x081DFFFF) && (Address >= 0x081C0000))
  {
    sector = FLASH_SECTOR_22;
  }
  else if((Address < 0x081FFFFF) && (Address >= 0x081E0000))
  {
    sector = FLASH_SECTOR_23;
  }
  return sector;
}

uint8_t bytes_temp[4];


void float2Bytes(uint8_t * ftoa_bytes_temp,float float_variable)
{
    union {
      float a;
      uint8_t bytes[4];
    } thing;

    thing.a = float_variable;

    for (uint8_t i = 0; i < 4; i++) {
      ftoa_bytes_temp[i] = thing.bytes[i];
    }

}

float Bytes2float(uint8_t * ftoa_bytes_temp)
{
    union {
      float a;
      uint8_t bytes[4];
    } thing;

    for (uint8_t i = 0; i < 4; i++) {
    	thing.bytes[i] = ftoa_bytes_temp[i];
    }

   float float_variable =  thing.a;
   return float_variable;
}


uint32_t Flash_Write_Data (uint32_t StartSectorAddress, uint32_t *Data, uint16_t numberofwords)
{

	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t SECTORError;
	int sofar=0;


	 /* Unlock the Flash to enable the flash control register access *************/
	  HAL_FLASH_Unlock();

	  /* Erase the user Flash area */

	  /* Get the number of sector to erase from 1st sector */

	  uint32_t StartSector = GetSector(StartSectorAddress);
	  uint32_t EndSectorAddress = StartSectorAddress + numberofwords*4;
	  uint32_t EndSector = GetSector(EndSectorAddress);

	  /* Fill EraseInit structure*/
	  EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
	  EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
	  EraseInitStruct.Sector        = StartSector;
	  EraseInitStruct.NbSectors     = (EndSector - StartSector) + 1;

	  /* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
	     you have to make sure that these data are rewritten before they are accessed during code
	     execution. If this cannot be done safely, it is recommended to flush the caches by setting the
	     DCRST and ICRST bits in the FLASH_CR register. */
	  if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
	  {
		  return HAL_FLASH_GetError ();
	  }

	  /* Program the user Flash area word by word
	    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

	   while (sofar<numberofwords)
	   {
	     if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, StartSectorAddress, Data[sofar]) == HAL_OK)
	     {
	    	 StartSectorAddress += 4;  // use StartPageAddress += 2 for half word and 8 for double word
	    	 sofar++;
	     }
	     else
	     {
	       /* Error occurred while writing data in Flash memory*/
	    	 return HAL_FLASH_GetError ();
	     }
	   }

	  /* Lock the Flash to disable the flash control register access (recommended
	     to protect the FLASH memory against possible unwanted operation) *********/
	  HAL_FLASH_Lock();

	   return 0;
}


void Flash_Read_Data (uint32_t StartSectorAddress, uint32_t *RxBuf, uint16_t numberofwords)
{
	while (1)
	{

		*RxBuf = *(__IO uint32_t *)StartSectorAddress;
		StartSectorAddress += 4;
		RxBuf++;
		if (!(numberofwords--)) break;
	}
}

void Convert_To_Str (uint32_t *Data, char *Buf)
{
	int numberofbytes = ((strlen((char *)Data)/4) + ((strlen((char *)Data) % 4) != 0)) *4;

	for (int i=0; i<numberofbytes; i++)
	{
		Buf[i] = Data[i/4]>>(8*(i%4));
	}
}


void Flash_Write_NUM (uint32_t StartSectorAddress, float Num)
{

	float2Bytes(bytes_temp, Num);

	Flash_Write_Data (StartSectorAddress, (uint32_t *)bytes_temp, 1);
}


float Flash_Read_NUM (uint32_t StartSectorAddress)
{
	uint8_t buffer[4];
	float value;

	Flash_Read_Data(StartSectorAddress, (uint32_t *)buffer, 1);
	value = Bytes2float(buffer);
	return value;
}

void Screen2View::writeHighestScore(int score){
	uint32_t data[3];
	data[0] = (uint32_t) score;
	Flash_Write_Data(0x081E0000, data, 3);
}

int Screen2View::readHighestScore(){
	int result;
	uint32_t data[0];
	Flash_Read_Data(0x081E0000, data, 1);
	result = data[0];
	return result;
}

