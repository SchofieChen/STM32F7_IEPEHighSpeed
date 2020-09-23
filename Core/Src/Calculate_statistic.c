#include "Calculate_statistic.h"

extern uint32_t fftSize;
extern float speedans;
extern Sv statistic_value;
float Calculate_rms(float *data, int n)
{
	float32_t rmsAns = 0;
	float32_t * ans = &rmsAns;
	float32_t sum = 0;

	for (int i = 0; i < n; i++)
		sum += data[i]*data[i];

	sum = sum / n;
	arm_sqrt_f32(sum, ans);


	return *ans;
}

float Calculate_max(float *data)
{
	float max= 0;
	float mid= 0;  //
		for(int i = 0;i<4096;i++){
		/*因為arr[i]是固定的 ，所以可以用arr[i]先和max比較，如果大於max 則
			把max的值賦給mid的值，然後把arr[i]賦給max  這樣max肯定比mid大*/
		if(data[i]>max){
		mid = max;
		max =data[i];

			}else if(data[i]>mid){/*  另一種情況 arr[i]處於兩者之間*/
				mid = data[i];//  則吧arr[i]賦給mid
			}


		}
		printf("max=%d,mid=%d\n",max,mid);


		return max;
}
void Calculate_FreqMax(float *x,  FreqMaxMin * FreqMaxMin , int8_t freq_index)
{
	if(FreqMaxMin->Max != 0)
	{

		int DATARE = 15000;
		float frequencyResolution = 15000/(float)fftSize;
		float ans = 0;
		//DRATE_15000 = 15000
		float parseRangeMax = FreqMaxMin->Max / frequencyResolution;
		float parseRangeMin = FreqMaxMin->Min / frequencyResolution;
		float ParsevalFftPower = 0;

		for(int i = (int)parseRangeMin; i<(int)parseRangeMax; i++)
		{
			//FFTRMSArray[i] = (testOutput[i]*2)/4096;
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
	float ParsevalFftPower = 0;
	float ans = 0;
	for(int i = 0; i<n; i++)
	{
		//FFTRMSArray[i] = (testOutput[i]*2)/4096;
		ParsevalFftPower += x[i] * x[i];
	}

	int fftSize = 4096;
	/*
	 * Compute Speed Ovall
	 *
	 * */
	float32_t sampleCount = 4096;
	float32_t samplingRate = 15000;
	float32_t frequencyScale = samplingRate/sampleCount;
	float SpeedparsevalFftPower = 0;

	for(uint16_t i = 1; i < fftSize; i++)
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

		}
		else if(i > fftSize/2)
		{
			x[i] = (x[i] * 9807) / (2 * 3.1415926 * frequencyScale * abs(fftSize-i));
		}
		SpeedparsevalFftPower += x[i] * x[i];
	}



	ans = sqrt(ParsevalFftPower)/n;
	statistic_value.Statistic_SpeedOvall = sqrt(SpeedparsevalFftPower)/n;
	return ans;
}





