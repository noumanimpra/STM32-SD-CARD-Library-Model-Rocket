#include "usr_fat_sd.h"
#include "fatfs_sd.h"

int cnt = 0;
char tempBuf[50];

SPI_HandleTypeDef hspi1;
UART_HandleTypeDef huart3;

int main()
{
    usr_Sd_FatfsInitial();
    usr_Sd_MountProc();
    usr_Sd_TransmitString_txtFormat("DATA SET\n");//writest to flightRecorder.txt file
    
    while(1)
    {
        sprintf(tempBuf, "counter: %d\n", cnt);
        usr_Sd_TransmitString_txtFormat(tempBuf);
        for (int i = 0; i < 2024; i++)
		    tempBuf[i] = 0;
    }
}
