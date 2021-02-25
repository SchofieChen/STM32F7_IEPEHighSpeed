#include "Calculate_statistic.h"

extern uint32_t fftSize;
extern float speedans;
extern Sv statistic_value;


//2021/0201/George
//TODO: Reset All parameter
void Initial_AllStatisticValue()
{
	statistic_value.Statistic_max = 0;
	statistic_value.Statistic_min = 0;
	statistic_value.Statistic_var = 0;
	statistic_value.Statistic_rms = 0;
	statistic_value.Statistic_mean = 0;
	statistic_value.Statistic_std = 0;
	statistic_value.Statistic_crestFactor = 0;
	statistic_value.Statistic_kurtosis = 0;
	statistic_value.Statistic_skewness = 0;
	statistic_value.Statistic_FreqOvall = 0;
	statistic_value.Statistic_SpeedOvall = 0;



	statistic_value.Statistic_max_Temp = 0;
	statistic_value.Statistic_min_Temp = 0;
	statistic_value.Statistic_var_Temp = 0;
	statistic_value.Statistic_rms_Temp = 0;
	statistic_value.Statistic_mean_Temp = 0;
	statistic_value.Statistic_std_Temp = 0;
	statistic_value.Statistic_crestFactor_Temp = 0;
	statistic_value.Statistic_kurtosis_Temp = 0;
	statistic_value.Statistic_skewness_Temp = 0;
	statistic_value.Statistic_FreqOvall_Temp = 0;
	statistic_value.Statistic_SpeedOvall_Temp = 0;

}


void Calculate_FreqBandRMS(float *x,  FreqMaxMin * FreqMaxMin , int8_t freq_index)
{
	if(FreqMaxMin->Max != 0)
	{

		int dataRate = 15000;
		float frequencyResolution = dataRate/(float)fftSize;
		float ans = 0;

		float parseRangeMax = FreqMaxMin->Max / frequencyResolution;
		float parseRangeMin = FreqMaxMin->Min / frequencyResolution;
		float ParsevalFftPower = 0;

		for(int i = (int)parseRangeMin; i<(int)parseRangeMax; i++)
		{
			ParsevalFftPower += x[i] * x[i];
		}

		ans = sqrt(ParsevalFftPower * 2)/4096;

		statistic_value.Statistic_FreqPeak[freq_index] = ans;
	}
}



/*
 *
 * Calculate Skewness & kurtosis
 *
 * */
float CalcluateMean(float *x, int n)
{
	float sum = 0;

	for (int i = 0; i < n; i++)
		sum += x[i];

	return sum / n;
}

float CalcluateMoment(float *x, int n, int m)
{
	float mean = CalcluateMean(x, n), sum = 0;

	for (int i = 0; i < n; i++)
		sum += pow(x[i] - mean, m);

	return sum / n;
}

float CalcluateVariance(float *x, int n)
{
	float mean = CalcluateMean(x, n), sumSq = 0;

	for (int i = 0; i < n; i++)
	{
		float delta = x[i] - mean;

		sumSq += delta * delta;
	}

	return sumSq / (n - 1);
}
float CalcluateStandardDeviation(float *x, int n)
{
	return sqrt(CalcluateVariance(x, n));
}

float Calculate_skewness(float *x, int n)
{
	// NIST definition of adjusted Fisher-Pearson
	// coefficient of skewness
	float m3 = CalcluateMoment(x, n, 3);
	float sx = CalcluateStandardDeviation(x, n);
	int n1 = n - 1;
	float Skewness = (sqrt(n * n1) / n1) * m3 / pow(sx, 3);

	return Skewness;
}
float Calculate_kurtosis(float *x, int n)
{
	float m2 = CalcluateMoment(x, n, 2);
	float m4 = CalcluateMoment(x, n, 4);


	float Kurtosis = m4 / (m2 * m2) - 3.0;
    return Kurtosis;
}

float Calculate_FreqOverAll(float *x, int n)
{
	//2021/0209/George
	//Acceleration sin(2πft) integral is Velocity cos(2πft)/2πft
	//Velocity cos(2πft)/2πft integral is cos(2πft)/(2πft)^2
	float ParsevalFftPower = 0;
	float AccelerationRMS = 0;
	float velocityPower = 0;
	float displacementPower = 0;
	float displacementP2p = 0;
	uint32_t displacement_index = 0;

	for(int i = 0; i<n/2; i++)
	{
		ParsevalFftPower += x[i] * x[i];
	}

	int fftSize = 4096;


	/*
	 * 2021/0203/George
	 * Compute Speed Ovall
	 * TODO: Improve compute fftSize to fftSize/2
	 * */
	float32_t sampleCount = 4096;
	float32_t samplingRate = 15000;
	float32_t frequencyScale = samplingRate/sampleCount;
	float SpeedparsevalFftPower = 0;

	//2021/0203/George
	//Calculate Velocity power
	for(uint16_t i = 0; i < fftSize / 2; i++)
	{
			if(i < fftSize/2)
			{
				if(i ==0)
				{
					x[i] = x[i];
				}
				else
				{
					x[i] = (x[i] * 9807) / (2 * 3.1415926 * frequencyScale * i);

				}
				velocityPower += x[i] * x[i];

			}

	}

	//2021/0203/George
	//Calculate displacement power
	for(uint16_t i = 0; i < fftSize / 2; i++)
	{
			if(i < fftSize/2)
			{
				if(i ==0)
				{
					x[i] = x[i];
				}
				else
				{
					x[i] = (x[i]) / (2 * 3.1415926 * frequencyScale * i);

				}
				displacementPower += x[i] * x[i];

			}

	}

	//2021/0203/George2
	//TODO:calculate
	arm_max_f32(x, 2048, &displacementP2p, &displacement_index);


	//2021/0203/George
	//TODO: improve formula from sqrt(ParsevalFftPower)/n to sqrt(2 * ParsevalFftPower)/n;
	AccelerationRMS = sqrt(2 * ParsevalFftPower)/n;

	//2021/0203/George
	//TODO: improve formula from sqrt(velocityPower)/n to sqrt(2 * velocityPower)/n;
	statistic_value.Statistic_SpeedOvall = sqrt(2 * velocityPower)/n; // unit : mm/s
	statistic_value.Statistic_DisplacementOvall = 1000 * sqrt(2 * displacementPower)/n; // unit : um
	return AccelerationRMS;
}





