/*
 * usr_fat_sd.h
 *
 *  Created on: 28 Ağu 2024
 *      Author: numan
 */

#ifndef USR_FAT_SD_H_
#define USR_FAT_SD_H_

#include "stm32f4xx_hal.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#include "bme280.h"
#include "bmi088.h"
#include "algorithms.h"
#include "queternion.h"
#include "lora.h"
#include "usr_gnss_l86_parser.h"
#include "dataPacking.h"
#include "externalPins.h"
#include "configuration.h"
#include "reset_detect.h"


#include "fatfs.h"

#define bool _Bool
#define true 1
#define false 0
#define _io static

int 	usr_Sd_TransmitString_txtFormat(const char *str);
int 	usr_Sd_TransmitString_csvFormat(const char *str);
void 	usr_Sd_FatfsInitial(void);
void 	usr_Sd_MountProc(void);
void 	usr_Sd_TestFunctions(void);
void 	sdDataLogger(BME_280_t *BME_Pack, bmi088_struct_t *BMI_Pack, backup_sram_datas_s *Backup_Pack, S_GPS_L86_DATA *GPS_Pack, power *Power_Pack);

#endif /* USR_FAT_SD_H_ */
