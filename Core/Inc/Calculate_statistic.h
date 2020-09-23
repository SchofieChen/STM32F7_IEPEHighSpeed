#include "arm_math.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct FreqMaxMinInstance
{
    int Max;
    int Min;
}FreqMaxMin;

float Calculate_max(float *data);
void Calculate_FreqMax(float *data,  FreqMaxMin * FreqMaxMin , int8_t freq_index);
float Calculate_skewness(float *data, int n);
float Calculate_kurtosis(float *data, int n);
float Calculate_rms(float *data, int n);
float Calculate_FreqOverAll(float *data, int n);
float Calculate_SpeedOverAll(float *x, int n);


typedef struct Statistic_value
{
	float Statistic_max;
	float Statistic_min;
	float Statistic_var;
	float Statistic_rms;
	float Statistic_mean;
	float Statistic_std;
	float Statistic_crestFactor;
	float Statistic_kurtosis;
	float Statistic_skewness;
	float Statistic_FreqOvall;
	float Statistic_SpeedOvall;
	float Statistic_FreqPeak[20];


	float Statistic_max_Temp;
	float Statistic_min_Temp;
	float Statistic_var_Temp;
	float Statistic_rms_Temp;
	float Statistic_mean_Temp;
	float Statistic_std_Temp;
	float Statistic_crestFactor_Temp;
	float Statistic_kurtosis_Temp;
	float Statistic_skewness_Temp;
	float Statistic_FreqOvall_Temp;
	float Statistic_SpeedOvall_Temp;
}Sv;

struct Freq_settingValue
{
	int freq1;
	int freq2;
	int freq3;
	int freq4;
	int freq5;
	int freq6;
	int freq7;
	int freq8;
	int freq9;
	int freq10;
	int freq11;
	int freq12;
	int freq13;
	int freq14;

}freq_settingValue;

typedef struct FreqSettingValueList
{
    FreqMaxMin range1;
    FreqMaxMin range2;
    FreqMaxMin range3;
}FreqSettingValueList;

FreqSettingValueList freqSettingValueList;
Sv statistic_value;
