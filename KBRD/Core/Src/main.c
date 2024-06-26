/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 Astrolate.
  * All rights reserved.
  *
  * Astrolate Starling Keyboard
  *
  * This software is "licensed" under CC BY-NC 4.0
  *
  ******************************************************************************
						⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
						⣿⣿⣿⣿⠟⠛⠛⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⢋⣩⣉⢻⣿⣿⣿⣿
						⣿⣿⣿⣿⠀⣿⣶⣕⣈⠹⠿⠿⠿⠿⠟⠛⣛⢋⣰⠣⣿⣷⠀⣿⣿⣿⣿
						⣿⣿⣿⣿⡀⣿⣿⣿⣧⢻⣿⣶⣷⣿⣿⣿⣿⣿⣿⠿⠶ ⠀⣿⣿⣿⣿
						⣿⣿⣿⣿⣷⠘⣿⣿⣿⢸⣿⣿⣋⣀⣈⣻⣿⣿⣷⣤⣤⣿ ⢿⣿⣿⣿
						⣿⣿⣿⣿⣿⣆⢩⣰⣫⣾⣿⣿⣿⣿⡟⠿⠿⠦⠀⠸⠿⣻⣿⡄⢻⣿⣿
						⣿⣿⣿⣿⣿⣿⡄⢻⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣾⣿⣿⣿⣿ ⣼⣿⣿
						⣿⣿⣿⣿⣿⣿⣿⡄⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⣰⣿⣿⣿
						⣿⣿⣿⣿⣿⣿⣿⠇⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢀⣿⣿⣿⣿
						⣿⣿⣿⣿⣿⣿⠋⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢸⣿⣿⣿⣿
						⣿⣿⣿⣿⣿⠟⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⣿⣿⣿⣿
						⣿⣿⣿⣿⠋⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⣿⣿⣿⣿
						⣿⣿⣿⠋⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⣿
						⣿⣿ ⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢸⣿⣿⣿
  ******************************************************************************
**/
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ssd1306.h"
#include "ARGB.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//#define BitSet(byte,nbit)   ((byte) |=  (1<<(nbit)))
//#define BitClear(byte,nbit) ((byte) &= ~(1<<(nbit)))
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

I2C_HandleTypeDef hi2c1;
DMA_HandleTypeDef hdma_i2c1_tx;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
DMA_HandleTypeDef hdma_tim1_ch2;

/* USER CODE BEGIN PV */
extern USBD_HandleTypeDef hUsbDeviceFS;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
const uint8_t StartLogo[] = {								// Start-up bitmap logo
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xD0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x4F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x03, 0xFE, 0x47, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0xC4, 0x07, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x1C, 0x83, 0x7F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x1E, 0x8F, 0xC1, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xEF, 0xE3, 0x03, 0x80, 0x00, 0x40, 0x00, 0x08, 0x00, 0x00, 0x30, 0x00, 0x30, 0x00, 0x00,
	0x03, 0xE0, 0xBA, 0x87, 0x00, 0x00, 0xE0, 0x00, 0x08, 0x00, 0x00, 0x30, 0x00, 0x30, 0x00, 0x00,
	0x03, 0x80, 0x86, 0x8A, 0x00, 0x01, 0xB0, 0x00, 0x1E, 0x18, 0xFE, 0x30, 0x3E, 0x7C, 0x7E, 0x00,
	0x01, 0x60, 0x0F, 0xD4, 0x00, 0x01, 0x10, 0x7C, 0x1E, 0x39, 0xFF, 0x30, 0x03, 0x7D, 0xFF, 0x80,
	0x00, 0x99, 0x32, 0xE4, 0x00, 0x02, 0x08, 0x40, 0x08, 0x63, 0x83, 0xB3, 0xFF, 0x31, 0x01, 0x80,
	0x00, 0xC7, 0xC0, 0x7C, 0x00, 0x06, 0x0C, 0x7F, 0x88, 0x63, 0x01, 0xB7, 0xFF, 0x31, 0xFF, 0x80,
	0x00, 0xE3, 0x84, 0xBC, 0x00, 0x07, 0xFC, 0x1F, 0xC8, 0x63, 0x01, 0xB6, 0x03, 0x31, 0xFF, 0x80,
	0x01, 0x2D, 0x65, 0x16, 0x00, 0x0C, 0x06, 0x00, 0x48, 0x63, 0x83, 0xB6, 0x03, 0x31, 0x00, 0x00,
	0x02, 0x31, 0x1E, 0x0B, 0x00, 0x18, 0x03, 0x7F, 0xC8, 0x61, 0xFF, 0x37, 0xFF, 0x31, 0xF0, 0x00,
	0x02, 0x41, 0x0E, 0x0E, 0x00, 0x10, 0x01, 0x7F, 0x08, 0x60, 0xFE, 0x33, 0xFE, 0x30, 0xF0, 0x00,
	0x05, 0x08, 0x1D, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0E, 0x0A, 0x34, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x07, 0xFA, 0x40, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x06, 0x9F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x07, 0xE9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x4C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

uint8_t EncRotRig, EncRotLft, FnBtnState;					// Encoder processing values
uint8_t keycodes[10] = {};									// Array for key press report
uint8_t MediaReport[2] = {};								// Array for media report
uint8_t DisplayText[8];										// Display value
uint8_t Red, Green, Blue, LedBrightness, ArgbMode, SwitchMode;
// Menu support values
uint8_t MenuOpenFlag, MenuDeniedFlag, RedMenu, GreenMenu, BlueMenu, BrMenu, SubMenu, SubMenuDeniedFlag;
int8_t MenuEncCounter, SubMenuEncCounter;

const uint8_t HEX_Map[97] =									// Array of keys according to schematic
{
//MUX0
	0x29,	// ESC
	0x3A,	// F1
	0x3B,	// F2
	0x3C,	// F3
	0x3D,	// F4
	0x3E,	// F5
	0x3F,	// F6
	0x40,	// F7
	0x41,	// F8
	0x42,	// F9
	0x43,	// F10
	0x44, 	// F11
	0x45,	// F12
	0x46,	// PrtScr
	0x4C,	// Del
	0x55,	// Keypad *
//MUX1
	0x35,	// ~
    0x1E,   // 1
    0x1F,   // 2
    0x20,   // 3
    0x21,   // 4
    0x22,   // 5
    0x23,   // 6
    0x24,   // 7
    0x25,   // 8
    0x26,   // 9
    0x27,   // 0
	0x2D,	// - and _
	0x2E,	// = and +
    0x2A,   // Backspace
	0x53,	// Num Lock
	0x54,	// Keypad /
//MUX2
    0x2B,   // Tab
	0x14,   // Q
	0x1A,   // W
	0x08,   // E
	0x15,   // R
	0x17,   // T
	0x1C,   // Y
	0x18,   // U
	0x0C,   // I
    0x12,   // O
    0x13,   // P
	0x2F,	// [ and {
	0x30,	// ] and }
	0x31,   // \ and |
	0x5F,	// Keypad 7
	0x60,	// Keypad 8
//MUX3
	0x39,	// Caps Lock
    0x04,   // A
    0x16,   // S
    0x07,   // D
    0x09,   // F
    0x0A,   // G
    0x0B,   // H
    0x0D,   // J
    0x0E,   // K
    0x0F,   // L
	0x33, 	// ; and :
	0x34,	// ' and "
    0x28,   // Enter
	0x5C,	// Keypad 4
	0x5D,	// Keypad 5
	0x5E,	// Keypad 6
//MUX4
	0x02,	// Left Shift
    0x1D,   // Z
    0x1B,   // X
    0x06,   // C
    0x19,   // V
    0x05,   // B
    0x11,   // N
    0x10,   // M
	0x36,	// , and <
	0x37,	// . and >
	0x38,	// / and ?
	0x20,	// Right Shift
	0x52,	// Arrow Up
	0x59,	// Keypad 1
	0x5A,	// Keypad 2
	0x5B,	// Keypad 3
//MUX5
	0x01,	// Left Ctrl
	0x08,	// Left Win(Super)
	0x04,	// Left Alt
	0x2C,	// Spacebar
	0x40,	// Right Alt
	0x00,	// Fn - Undefined(Released)
	0x10,	// Right Ctrl
	0x50,	// Arrow Left
	0x51,	// Arrow Down
	0x4F,	// Arrow Right
	0x62,	// Keypad 0
	0x63,	// Keypad Del
	0x58,	// Keypad Enter
	0x61,	// Keypad 9
	0x57,	// Keypad +
	0x56	// Keypad -
};

/*
 * Lock keys indication pre-init
*/
volatile struct HID_Leds_t HID_Leds;

#define L_NUMLOCK          0
#define L_CAPSLOCK         1
#define L_SCROLLLOCK       2

struct HID_Leds_t {
uint8_t NUMLOCK;
uint8_t CAPSLOCK;
uint8_t SCROLLLOCK;
};

void HID_LedsInit(void){
	HID_Leds.NUMLOCK = 0;
	HID_Leds.CAPSLOCK = 0;
	HID_Leds.SCROLLLOCK = 0;
}

/*
 * Simple FLASH read
*/
uint8_t READ_FLASH(uint32_t address) {
    return (*(__IO uint8_t*)address);
}

/*
 * FLASH memory write func for 1 sector
*/
void WRITE_FLASH(uint32_t address, uint8_t data) {

    uint8_t OldData[20];
    for (uint32_t addr = 0x0807FFF0, i = 0; addr <= 0x0807FFFF; addr++, i++) {
    	OldData[i] = READ_FLASH(addr);
	}

	HAL_FLASH_Unlock();                                                             		// Unlock Flash

    FLASH_EraseInitTypeDef eraseInitStruct;
    eraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
    eraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    eraseInitStruct.Sector = FLASH_SECTOR_7;
    eraseInitStruct.NbSectors = 1;

    if (HAL_FLASHEx_Erase(&eraseInitStruct, 0) != HAL_OK) {
    	//HAL_FLASH_Lock();
        Error_Handler();
        //return;
    }

    for (uint32_t addr = 0x0807FFF0, i = 0; addr <= 0x0807FFFF; addr++, i++) {
    	if (addr == address){
            if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, data) != HAL_OK) {
                Error_Handler();
            }
    	}
    	if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, OldData[i]) != HAL_OK) {
        	//HAL_FLASH_Lock();
            Error_Handler();
            //return;
        }
	}
    HAL_FLASH_Lock();

/*
    HAL_FLASH_Unlock();																// Unlock Flash

    FLASH_EraseInitTypeDef eraseInitStruct;
    eraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
    eraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    eraseInitStruct.Sector = FLASH_SECTOR_7; 									    // Get sector via address
    eraseInitStruct.NbSectors = 1; 													// 1 its enough for projects needs

    uint32_t sectorError = 0;
    if (HAL_FLASHEx_Erase(&eraseInitStruct, &sectorError) != HAL_OK) {				// Delete sector where address located(No sense here)
    	Error_Handler();
    }

    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, address, data) != HAL_OK) {		// Write new value in FLASH cell
    	Error_Handler();
    }
    HAL_FLASH_Lock();																// Lock FLASH for sure
*/
}

/*
 * Selecting input pin of MUX output for ADC processing
*/
void ADC_SELECTOR(uint8_t Channel){
	ADC_ChannelConfTypeDef cConfig = {0};
	cConfig.Channel = Channel;
	cConfig.Rank = 1;
	cConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1, &cConfig) != HAL_OK)
	{
		Error_Handler();
	}
}

/*
 * Receiving ADC values
*/
uint32_t ADC_GET_VALUE(void){
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 1);
	return HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
}

/*
 * Selecting 0-15 channel of MUX
*/
void SELECT_MUX_CH(uint8_t MUX_CH) {
	HAL_GPIO_WritePin(GPIOB, SELECT0_Pin, (GPIO_PinState)((MUX_CH >> 0) & 0x01));
	HAL_GPIO_WritePin(GPIOB, SELECT1_Pin, (GPIO_PinState)((MUX_CH >> 1) & 0x01));
	HAL_GPIO_WritePin(GPIOB, SELECT2_Pin, (GPIO_PinState)((MUX_CH >> 2) & 0x01));
	HAL_GPIO_WritePin(GPIOB, SELECT3_Pin, (GPIO_PinState)((MUX_CH >> 3) & 0x01));
}

/*
 * Simultaneously keys press processing
 *
 * 0-ID;
 * 1-MODIFIER;
 * 2-RESERVED;
 * 3-8KEYCODE[6]
*/
void KEY_PRESS(uint32_t ADC_Value, uint8_t Key_Identifier, uint8_t IsMod, uint8_t SwMod){
	/*
	 * In progress
	*/
/*
    uint32_t AdcPrev;
    uint16_t adcThreshold = 500;
	if (SwMod == 0) {																	// Rapid trigger

		if (ADC_Value > AdcPrev + adcThreshold) {
			keycodes[0] = 0x01;
			if (IsMod) {
				keycodes[1] ^= Key_Identifier;
			} else {
				for (uint8_t ByteCounter = 3; ByteCounter <= 9; ByteCounter++) {
					if (keycodes[ByteCounter] == 0) {
						keycodes[ByteCounter] = Key_Identifier;
						break;
					}
				}
			}
		}

		else if (ADC_Value < AdcPrev + adcThreshold) {
			for (uint8_t ByteCounter = 1; ByteCounter <= 9; ByteCounter++) {
				if (keycodes[ByteCounter] != 0){
					keycodes[ByteCounter] = 0x00;										// Clear every byte
				}
			}
		}

	}
	else{*/
		//if (ADC_Value <= 1200 || ADC_Value >= 4000) {									// If switch have different magnet polarity also led power changes less dependent
		if (ADC_Value >= 3500){
			keycodes[0] = 0x01;															// ID(1)
			if(IsMod) {																	// If pressed modifier keys
				keycodes[1] ^= Key_Identifier;											// Accumulating Modifiers values in bits for first byte
			}
			else{
				for (uint8_t ByteCounter = 3; ByteCounter <= 9; ByteCounter++) {		// (MAX pressed keys == not enough)
					if (keycodes[ByteCounter] == 0) {
						keycodes[ByteCounter] = Key_Identifier;
						break;
					}
				}
			}
		}
	//}
	//AdcPrev = ADC_Value;
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_USB_DEVICE_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  SSD1306_Init();														// OLED 128*32
  ARGB_Init();															// SK6812
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);						// Encoder mode start
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  //Menu_SetGenericWriteCallback(Generic_Write);
/*
* Starting Up Logo Astrolate
*/
  SSD1306_DrawBitmap(0, 0, StartLogo, 128, 32, SSD1306_COLOR_WHITE);	// Display logo
  SSD1306_UpdateScreen();												// Show image
  HAL_Delay(1000);														// Wait
  SSD1306_Fill(SSD1306_COLOR_BLACK);									// Clear for next info


  ARGB_Clear();															// Pre clearing of ARGB

/*
 * Read data from previous set-up
*/
  Red = READ_FLASH(0x0807FFF0);
  Green = READ_FLASH(0x0807FFF1);
  Blue = READ_FLASH(0x0807FFF2);
  LedBrightness = READ_FLASH(0x0807FFF3);
  ArgbMode = READ_FLASH(0x0807FFF4);
  SwitchMode = READ_FLASH(0x0807FFF5);

  uint16_t PositionLast = (int16_t)__HAL_TIM_GET_COUNTER(&htim3) / 4;
  while (1)
  {
/*
* Encoder Handler Section
*/
	uint32_t Counter = __HAL_TIM_GET_COUNTER(&htim3);
	uint16_t Position = (int16_t)Counter / 4;
	if(Position == PositionLast){										// No change, (reset & screensaver)
		EncRotRig = 0;
		EncRotLft = 0;
	}
	if(Position > PositionLast){										// Counter has increased, diff is positive
		EncRotRig = 1;
	}
	if(PositionLast > Position){										// Counter has decreased, diff is negative
		EncRotLft = 1;
	}
	// Exceptions for logic issue
	if (Position == 0 && PositionLast == 65535) {
		EncRotRig = 1;
		EncRotLft = 0;
	}
	if (PositionLast == 0 && Position == 65535) {
		EncRotRig = 0;
		EncRotLft = 1;
	}
	PositionLast = Position;
/*
* MUXs-ADC Section
*/
	for(uint8_t MUX = 0; MUX < 6; MUX++){																			// Selecting MUX
	  switch(MUX){
		  case(0):																									// MUX_0
			  ADC_SELECTOR(5);
			  for(uint8_t MuxChannel = 0; MuxChannel <16; MuxChannel++){
				  SELECT_MUX_CH(MuxChannel);
				  KEY_PRESS(ADC_GET_VALUE(), HEX_Map[MuxChannel], 0, SwitchMode);
			  }
		  break;
		  case(1):																									// MUX_1
			  ADC_SELECTOR(4);
			  for(uint8_t MuxChannel = 0; MuxChannel <16; MuxChannel++){
				  SELECT_MUX_CH(MuxChannel);
				  KEY_PRESS(ADC_GET_VALUE(), HEX_Map[16 + MuxChannel], 0, SwitchMode);
			  }
		  break;
		  case(2):																									// MUX_2
			  ADC_SELECTOR(3);
			  for(uint8_t MuxChannel = 0; MuxChannel <16; MuxChannel++){
				  SELECT_MUX_CH(MuxChannel);
				  KEY_PRESS(ADC_GET_VALUE(), HEX_Map[32 + MuxChannel], 0, SwitchMode);
			  }
		  break;
		  case(3):																									// MUX_3
			  ADC_SELECTOR(2);
			  for(uint8_t MuxChannel = 0; MuxChannel <16; MuxChannel++){
				  SELECT_MUX_CH(MuxChannel);
				  KEY_PRESS(ADC_GET_VALUE(), HEX_Map[48 + MuxChannel], 0, SwitchMode);
			  }
		  break;
		  case(4):																									// MUX_4
			  ADC_SELECTOR(1);
			  for(uint8_t MuxChannel = 0; MuxChannel <16; MuxChannel++){
				  SELECT_MUX_CH(MuxChannel);
				  if(MuxChannel == 0) KEY_PRESS(ADC_GET_VALUE(), HEX_Map[64 + MuxChannel], 1, SwitchMode);			// Exception for Left Shift
				  else if(MuxChannel == 11) KEY_PRESS(ADC_GET_VALUE(), HEX_Map[64 + MuxChannel], 1, SwitchMode);	// Exception for Right Shift
				  else KEY_PRESS(ADC_GET_VALUE(), HEX_Map[64 + MuxChannel], 0, SwitchMode);
			  }
		  break;
		  case(5):																									// MUX_5
			  ADC_SELECTOR(0);
			  for(uint8_t MuxChannel = 0; MuxChannel <16; MuxChannel++){
				  SELECT_MUX_CH(MuxChannel);
				  if(MuxChannel == 0) KEY_PRESS(ADC_GET_VALUE(), HEX_Map[80 + MuxChannel], 1, SwitchMode);			// Exception for Left Ctrl
				  else if(MuxChannel == 1) KEY_PRESS(ADC_GET_VALUE(), HEX_Map[80 + MuxChannel], 1, SwitchMode);		// Exception for Left Win
				  else if(MuxChannel == 2) KEY_PRESS(ADC_GET_VALUE(), HEX_Map[80 + MuxChannel], 1, SwitchMode);		// Exception for Left Alt
				  else if(MuxChannel == 4) KEY_PRESS(ADC_GET_VALUE(), HEX_Map[80 + MuxChannel], 1, SwitchMode);		// Exception for Right Alt
				  else if(MuxChannel == 5){
					  if(ADC_GET_VALUE() >= 3500) FnBtnState = 1;													// Fn key press
					  /*SSD1306_GotoXY(0, 10);
					  sprintf(DisplayText, "%d", ADC_GET_VALUE());													// temporary info
					  SSD1306_Puts(DisplayText, &Font_7x10, SSD1306_COLOR_WHITE);*/
				  }
				  else if(MuxChannel == 6) KEY_PRESS(ADC_GET_VALUE(), HEX_Map[80 + MuxChannel], 1, SwitchMode);		// Exception for Right Ctrl
				  else KEY_PRESS(ADC_GET_VALUE(), HEX_Map[80 + MuxChannel], 0, SwitchMode);
			  }
		  break;
	  }
	}
/*
 * Send Key Report
*/
	USBD_HID_SendReport(&hUsbDeviceFS, &keycodes, 9);							// Send keys report
	//if (SwitchMode == 1) {
		for (uint8_t ByteCounter = 1; ByteCounter <= 9; ByteCounter++) {
			if (keycodes[ByteCounter] != 0){
				keycodes[ByteCounter] = 0x00;										// Clear every byte
			}
		}
	//}
	//else if(SwitchMode == 0){}

/*
 * Main Menu
*/
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET && MenuOpenFlag == 0){
		while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET);
		MenuOpenFlag = 1;
	}
	if(MenuOpenFlag){
		SSD1306_GotoXY(0, 0);
		SSD1306_Puts("SETTINGS:", &Font_7x10, SSD1306_COLOR_WHITE);

		SSD1306_GotoXY(90, 0);
		SSD1306_Puts("EXIT", &Font_7x10, SSD1306_COLOR_WHITE);
		//---------------------
		SSD1306_GotoXY(0, 10);
		SSD1306_Puts("ARGB:", &Font_7x10, SSD1306_COLOR_WHITE);

		SSD1306_GotoXY(45, 10);
		SSD1306_Puts("Solid", &Font_7x10, SSD1306_COLOR_WHITE);
		SSD1306_GotoXY(90, 10);
		SSD1306_Puts("Efct", &Font_7x10, SSD1306_COLOR_WHITE);
		//---------------------
		SSD1306_GotoXY(0, 20);
		SSD1306_Puts("Btns:", &Font_7x10, SSD1306_COLOR_WHITE);

		SSD1306_GotoXY(45, 20);
		SSD1306_Puts("Norm", &Font_7x10, SSD1306_COLOR_WHITE);

		SSD1306_GotoXY(90, 20);
		SSD1306_Puts("Rapid", &Font_7x10, SSD1306_COLOR_WHITE);
		//---------------------
		SSD1306_DrawLine(0, 9, 128, 9, SSD1306_COLOR_WHITE);
		SSD1306_DrawLine(0, 19, 128, 19, SSD1306_COLOR_WHITE);
		SSD1306_DrawLine(85, 0, 85, 32, SSD1306_COLOR_WHITE);
		SSD1306_DrawLine(40, 9, 40, 32, SSD1306_COLOR_WHITE);

		if(!MenuDeniedFlag){
			if(EncRotRig == 1)MenuEncCounter++;
			if(EncRotLft == 1)MenuEncCounter--;
			if(MenuEncCounter > 4)MenuEncCounter = 0;
			if(MenuEncCounter < 0)MenuEncCounter = 4;
		}
		switch(MenuEncCounter){
		  case(0):
			SSD1306_GotoXY(90, 0);
			SSD1306_Puts("EXIT", &Font_7x10, SSD1306_COLOR_BLACK);

			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET && MenuOpenFlag == 1){
				while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET);
				MenuOpenFlag = !MenuOpenFlag;
			}
		  break;
		  case(1):
			SSD1306_GotoXY(45, 10);
			SSD1306_Puts("Solid", &Font_7x10, SSD1306_COLOR_BLACK);

			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET && SubMenu == 0){
				while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET);
				SubMenu = 1;
			}
			if(SubMenu){
				MenuDeniedFlag = 1;
				SSD1306_Fill(SSD1306_COLOR_BLACK);

			    SSD1306_GotoXY(8, 0);
				SSD1306_Puts("R", &Font_7x10, SSD1306_COLOR_WHITE);
				sprintf(DisplayText, "%d", Red);
				SSD1306_GotoXY(0, 10);
				SSD1306_Puts(DisplayText, &Font_7x10, SSD1306_COLOR_WHITE);

				SSD1306_GotoXY(32, 0);
				SSD1306_Puts("G", &Font_7x10, SSD1306_COLOR_WHITE);
				sprintf(DisplayText, "%d", Green);
				SSD1306_GotoXY(25, 10);
				SSD1306_Puts(DisplayText, &Font_7x10, SSD1306_COLOR_WHITE);

				SSD1306_GotoXY(64, 0);
				SSD1306_Puts("B", &Font_7x10, SSD1306_COLOR_WHITE);
				sprintf(DisplayText, "%d", Blue);
				SSD1306_GotoXY(56, 10);
				SSD1306_Puts(DisplayText, &Font_7x10, SSD1306_COLOR_WHITE);

				SSD1306_GotoXY(96, 0);
				SSD1306_Puts("BR", &Font_7x10, SSD1306_COLOR_WHITE);
				sprintf(DisplayText, "%d", LedBrightness);
				SSD1306_GotoXY(92, 10);
				SSD1306_Puts(DisplayText, &Font_7x10, SSD1306_COLOR_WHITE);

				SSD1306_GotoXY(90, 20);
				SSD1306_Puts("BACK", &Font_7x10, SSD1306_COLOR_WHITE);
				//---------------------
				SSD1306_DrawLine(0, 9, 128, 9, SSD1306_COLOR_WHITE);
				SSD1306_DrawLine(22, 0, 22, 20, SSD1306_COLOR_WHITE);
				SSD1306_DrawLine(50, 0, 50, 20, SSD1306_COLOR_WHITE);
				SSD1306_DrawLine(85, 0, 85, 20, SSD1306_COLOR_WHITE);

				if(!SubMenuDeniedFlag){
					if(EncRotRig == 1)SubMenuEncCounter++;
					if(EncRotLft == 1)SubMenuEncCounter--;
					if(SubMenuEncCounter > 4)SubMenuEncCounter = 0;
					if(SubMenuEncCounter < 0)SubMenuEncCounter = 4;
				}
				switch(SubMenuEncCounter){
				  case(0):
					sprintf(DisplayText, "%d", Red);
					SSD1306_GotoXY(0, 10);
					SSD1306_Puts(DisplayText, &Font_7x10, SSD1306_COLOR_BLACK);

					if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET && RedMenu == 0){
					while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET);
						RedMenu = 1;
					}
					if(RedMenu){
						SubMenuDeniedFlag = 1;
						if(EncRotRig == 1)Red++;
						if(EncRotLft == 1)Red--;
						if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET && RedMenu == 1){
							while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET);
							WRITE_FLASH(0x0807FFF0, Red);
							RedMenu = 0;
							SubMenuDeniedFlag = 0;
						}
					}
				  break;
				  case(1):
						sprintf(DisplayText, "%d", Green);
						SSD1306_GotoXY(25, 10);
						SSD1306_Puts(DisplayText, &Font_7x10, SSD1306_COLOR_BLACK);

					  //uint8_t GreenMenu = 0;
					  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET && GreenMenu == 0){
						while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET);
						GreenMenu = 1;
					  }
					  if(GreenMenu){
						SubMenuDeniedFlag = 1;
						if(EncRotRig == 1)Green++;
						if(EncRotLft == 1)Green--;
						if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET && GreenMenu == 1){
						  while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET);
						  WRITE_FLASH(0x0807FFF1, Green);
						  GreenMenu = 0;
						  SubMenuDeniedFlag = 0;
						}
					  }

				  break;
				  case(2):
						sprintf(DisplayText, "%d", Blue);
						SSD1306_GotoXY(56, 10);
						SSD1306_Puts(DisplayText, &Font_7x10, SSD1306_COLOR_BLACK);

					  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET && BlueMenu == 0){
						while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET);
						BlueMenu = 1;
					  }
					  if(BlueMenu){
						SubMenuDeniedFlag = 1;
						if(EncRotRig == 1)Blue++;
						if(EncRotLft == 1)Blue--;
						if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET && BlueMenu == 1){
						  while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET);
						  WRITE_FLASH(0x0807FFF2, Blue);
						  BlueMenu = 0;
						  SubMenuDeniedFlag = 0;
						}
					  }

				  break;
				  case(3):
						sprintf(DisplayText, "%d", LedBrightness);
						SSD1306_GotoXY(92, 10);
						SSD1306_Puts(DisplayText, &Font_7x10, SSD1306_COLOR_BLACK);

					  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET && BrMenu == 0){
						while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET);
						BrMenu = 1;
					  }
					  if(BrMenu){
						SubMenuDeniedFlag = 1;
						if(EncRotRig == 1)LedBrightness++;
						if(EncRotLft == 1)LedBrightness--;
						if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET && BrMenu == 1){
						  while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET);
						  WRITE_FLASH(0x0807FFF3, LedBrightness);
						  BrMenu = 0;
						  SubMenuDeniedFlag = 0;
						}
					  }
				  break;
				  case(4):
						SSD1306_GotoXY(90, 20);
						SSD1306_Puts("BACK", &Font_7x10, SSD1306_COLOR_BLACK);
						if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET && SubMenu == 1){
							while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET);
							ArgbMode = 1;
							WRITE_FLASH(0x0807FFF4, ArgbMode);
							SubMenu = !SubMenu;
							MenuDeniedFlag = 0;
						}
				  break;
				}
			}
		  break;
		  case(2):
			SSD1306_GotoXY(90, 10);
			SSD1306_Puts("Efct", &Font_7x10, SSD1306_COLOR_BLACK);
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET){
				while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET);
				ArgbMode = 0;
				WRITE_FLASH(0x0807FFF4, ArgbMode);
			}
		  break;
		  case(3):
			SSD1306_GotoXY(45, 20);
			SSD1306_Puts("Norm", &Font_7x10, SSD1306_COLOR_BLACK);
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET){
				while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET);
				SwitchMode = 1;
				WRITE_FLASH(0x0807FFF5, SwitchMode);
			}
		  break;
		  case(4):
			SSD1306_GotoXY(90, 20);
			SSD1306_Puts("Rapid", &Font_7x10, SSD1306_COLOR_BLACK);
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET){
				while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET);
				SwitchMode = 0;
				WRITE_FLASH(0x0807FFF5, SwitchMode);
			}
		  break;
		}
	}
/*
 * Main Screen Data
*/
	else{
/*
 * Lock keys indication
*/
		uint8_t *getData = USBD_HID_GetData();
		if((getData[0] & (uint8_t)(1<<L_NUMLOCK)) == (1<<L_NUMLOCK)){
			SSD1306_GotoXY(0, 0);
			SSD1306_Puts("Num-ON", &Font_7x10, SSD1306_COLOR_WHITE);
		}
		else{
			SSD1306_GotoXY(0, 0);
			SSD1306_Puts("Num-OFF", &Font_7x10, SSD1306_COLOR_WHITE);
		}
		if((getData[0] & (uint8_t)(1<<L_CAPSLOCK)) == (1<<L_CAPSLOCK)){
			SSD1306_GotoXY(64, 0);
			SSD1306_Puts("Caps-ON", &Font_7x10, SSD1306_COLOR_WHITE);
		}
		else{
			SSD1306_GotoXY(64, 0);
			SSD1306_Puts("Caps-OFF", &Font_7x10, SSD1306_COLOR_WHITE);
		}
/*
 * Volume Up/Down
*/
		if(EncRotRig == 1){
			MediaReport[0] = 0x02;// Report Custom Media ID
			MediaReport[1] = 0x04;//40;//81;
		}
		if(EncRotLft == 1){
			MediaReport[0] = 0x02;
			MediaReport[1] = 0x08;//80;
		}
/*
* Brightness Increment/Decrement (Only for main selected screen)
*/
		if(FnBtnState == 1 && EncRotRig == 1){
			MediaReport[0] = 0x02;
			MediaReport[1] = 0x01;//E9;
		}
		if(FnBtnState == 1 && EncRotLft == 1){
			MediaReport[0] = 0x02;
			MediaReport[1] = 0x02;//EA;
		}
	}

/*
 * Send Media Report
*/
	HAL_Delay(USBD_HID_GetPollingInterval());									// Wait some interval to avoid reports overlapping
	USBD_HID_SendReport(&hUsbDeviceFS, &MediaReport, 2);						// Send report
	MediaReport[1] = 0x00;														// Clear Media Report

    FnBtnState = 0;																// Reset Fn state

	SSD1306_UpdateScreen();														// Show data
	SSD1306_Fill(SSD1306_COLOR_BLACK);											// Clear display for next info

/*
 * ARGB handling
*/
	ARGB_SetBrightness(LedBrightness);
	if(ArgbMode == 1){
		// Solid color
		ARGB_FillRGB(Red, Green, Blue);
	}
	else if(ArgbMode == 0){
		// Some LGTVCOMMUNITY effect
		//In progress
	}
	ARGB_Show();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
/*  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }*/
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 90-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_FALLING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 5;
  sConfig.IC2Polarity = TIM_ICPOLARITY_FALLING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 5;
  if (HAL_TIM_Encoder_Init(&htim3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
  /* DMA2_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
  /* DMA2_Stream4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream4_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SELECT3_Pin|SELECT2_Pin|SELECT1_Pin|SELECT0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : SELECT3_Pin SELECT2_Pin SELECT1_Pin SELECT0_Pin */
  GPIO_InitStruct.Pin = SELECT3_Pin|SELECT2_Pin|SELECT1_Pin|SELECT0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : ENC_SW_Pin */
  GPIO_InitStruct.Pin = ENC_SW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(ENC_SW_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
