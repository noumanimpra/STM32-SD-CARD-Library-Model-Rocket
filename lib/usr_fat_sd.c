/*
 * usr_fat_sd.c
 *
 *  Created on: 28 Ağu 2024
 *      Author: numan
 */

#include "usr_fat_sd.h"

#ifdef GNSS_SD_INTEGRATION_MODE
_io float lat = 0;
_io float lon = 0;
_io float kn = 0;
_io float time = 0;
_io int fixQuality = 0;
_io int satInUse = 0;
_io int hdop = 0;
_io float altitude_M = 0;
_io int test_cnt = 0;
_io float test_fl = 0.2;
#endif
_io float testNum = 0;
_io char fatBuff[1024];
char _aBuf[2048];
_io char _line[] = "\n-----------------------------------\n";
int b_fl = 1;

extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart3;

_io FATFS fs;
_io FIL fil;
_io FRESULT fresult;
_io UINT br, bw;
_io FATFS *pfs;
_io DWORD fre_clust;
_io uint32_t total, free_space;

_io void uart_Sd_Transmit(char *string)
{
	uint8_t len = strlen(string);
	HAL_UART_Transmit(&huart3, (uint8_t *)string, len, 2000); // transmit in blocking mode
}
_io int sdBufSize(char *buf)
{
	int i = 0;
	while (*buf++ != '\0')
		i++;
	return i;
}

_io void sdBufClear(void)
{
	for (int i = 0; i < 1024; i++)
		fatBuff[i] = 0;
}

void usr_SdFatfsInitial(void)
{
	MX_FATFS_Init();
}
void usr_Sd_MountProc(void)
{
	fresult = f_mount(&fs, "/", 1);
	if (fresult != FR_OK)
		uart_Sd_Transmit("error in mount [Check For Fat Response (fresult) in debug mode!!!!]......\n");
	else
		uart_Sd_Transmit("SD CARD MOUNTED CUSSESSFULY..\n");

	/*capacity details*/
	f_getfree("", &fre_clust, &pfs);
	total = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
	sprintf(fatBuff, "SD CARD [Total] Size: \t%lu\n", total);
	uart_Sd_Transmit(fatBuff);
	sdBufClear();
	free_space = (uint32_t)(fre_clust * pfs->csize * 0.5);
	sprintf(fatBuff, "SD CARD [Free] Size: \t%lu\n", free_space);
	uart_Sd_Transmit(fatBuff);
	/*
	fresult = f_open(&fil, "flightRecorder.txt", FA_CREATE_ALWAYS | FA_WRITE); // test
	fresult = f_close(&fil);*/
	fresult = f_open(&fil, "flightRecorder.csv", FA_CREATE_ALWAYS | FA_WRITE); // test
	fresult = f_printf(&fil,"TIME;PRESSURE;HUMIDITY;ALTITUDE;VELOCITY;ACCX;ACCY;ACCZ;GYROX;GYROY;GYROZ;RSTATUS;BACKUP1;BACKUP2;BACKUP3;MAXALTITUDE;LAT;LON;SATINUSE;ALTITUDEINM;VOLTAGE;CURRENT;MWATTS\n");
	fresult = f_close(&fil);
}

void usr_Sd_TestFunctions(void)
{
#ifdef GNSS_SD_INTEGRATION_MODE
	char m_DataBuf[200];
	fresult = f_open(&fil, "testDataLogFile.txt", FA_CREATE_ALWAYS | FA_WRITE);
	fresult = f_puts("\n--------[L86 Data Values]------\n", &fil);
	while (1)
	{
		Usr_GpsL86GetValues(&L86DataParams);
		lat = L86DataParams.lat;
		lon = L86DataParams.lon;
		kn = L86DataParams.speedKN;
		time = L86DataParams.timeDateBuf;

		if (lon > 20)
		{
			// sprintf(m_DataBuf, "counter: %d, float: %f\n", test_cnt, test_fl);
			sprintf(m_DataBuf, "Lat: [%f] Lon: [%f] Speed: [%.2f] Time: [%f]\n", lat, lon, kn, time);
			fresult = f_printf(&fil, m_DataBuf);
			test_cnt++;
			if (test_cnt > 100)
			{
				HAL_Delay(1000);
				uart_Sd_Transmit("[testDataLogFile.txt] GOK-HAN data has been modified.\n");
				fresult = f_close(&fil); // close
				uart_Sd_Transmit("[testDataLogFile.txt] GOK-HAN data log closed.\n");
				break;
			}
		}
	}
#endif

#ifdef FAT_TEST_MODE
	char aBuf[50];
	fresult = f_open(&fil, "testDataLogFile.txt", FA_CREATE_ALWAYS | FA_WRITE); // open to write
	fresult = f_puts("\n--------[Counter Started]------\n", &fil);
	fresult = f_puts("\n--------[saaaa]------\n", &fil);
	while (1)
	{
		// fresult = f_printf(&fil, "sa %d\n",test_cnt);
		sprintf(aBuf, "counter: %d, float: %f\n", test_cnt, test_fl);
		fresult = f_printf(&fil, aBuf);
		test_cnt++;
		test_fl++;
		HAL_Delay(100);
		if (test_cnt > 40)
		{
			uart_Sd_Transmit("[testDataLogFile.txt] GOK-HAN data has been modified.\n");
			break;
		}
	}
	fresult = f_close(&fil); // close
	uart_Sd_Transmit("[testDataLogFile.txt] GOK-HAN data log closed.\n");

#endif
}
int usr_Sd_TransmitString_txtFormat(const char *str)
{
	fresult = f_open(&fil, "flightRecorder.txt", FA_OPEN_APPEND | FA_WRITE);
	fresult = f_printf(&fil, str);
	fresult = f_close(&fil);
	return fresult;
}

int usr_Sd_TransmitString_csvFormat(const char *str)
{
	fresult = f_open(&fil, "flightRecorder.csv", FA_OPEN_APPEND | FA_WRITE);
	sprintf(_aBuf,"--;;; %s ;;;--\n",str);
	fresult = f_printf(&fil, _aBuf);
	fresult = f_close(&fil);
	for (int i = 0; i < 2024; i++)
		_aBuf[i] = 0;
	return fresult;
}
void sdDataLogger(BME_280_t *BME_Pack, bmi088_struct_t *BMI_Pack, backup_sram_datas_s *Backup_Pack, S_GPS_L86_DATA *GPS_Pack, power *Power_Pack)
{
	fresult = f_open(&fil, "flightRecorder.csv", FA_OPEN_APPEND | FA_WRITE);
	sprintf(_aBuf, "%.0f;%.1f;%.1f;%.1f;%.1f;%f;%f;%f;%f;%f;%f;%d;%f;%f;%f;%f;%.1f;%f;%f;%d;%.1f;%.2f;%.2f,%.2f\n", GPS_Pack->timeDateBuf, BME_Pack->pressure, BME_Pack->humidity, BME_Pack->altitude, BME_Pack->velocity, BMI_Pack->acc_x, BMI_Pack->acc_y, BMI_Pack->acc_z, BMI_Pack->gyro_x, BMI_Pack->gyro_y, BMI_Pack->gyro_z, Backup_Pack->r_status, Backup_Pack->q[0], Backup_Pack->q[1], Backup_Pack->q[2], Backup_Pack->q[3], Backup_Pack->max_altitude, GPS_Pack->lat, GPS_Pack->lon, GPS_Pack->satInUse, GPS_Pack->altitudeInMeter, Power_Pack->voltaj, Power_Pack->akim, Power_Pack->mWatt_s);
	fresult = f_printf(&fil, _aBuf);
	fresult = f_close(&fil);
	for (int i = 0; i < 2024; i++)
		_aBuf[i] = 0;
}

