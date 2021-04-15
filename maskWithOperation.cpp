#include "maskWithOperation.h"

maskWithOperation::maskWithOperation() {

}

void maskWithOperation::trigSTDu(const std::vector<int>& evenOrOdd, std::vector<data>& dataVec, int i) {

	if (evenOrOdd[i] == 0) {
		dataVec[i].C[0] = std::tan(std::sin(*dataVec[i].A[0]));
	}

	else {
		dataVec[i].C[0] = std::tan(std::cos(*dataVec[i].A[0]));
	}
}

void maskWithOperation::oddOrEvenSTDu(std::vector<int>& evenOrOdd, std::vector<data>& dataVec, int i) {

	evenOrOdd[i] = (*dataVec[i].A[0] % 2) == 0;
}

void maskWithOperation::setOperationSTDu(const std::vector<int>& x, std::vector<data>& dataVec) {
	std::vector<int> evenOrOdd(x.size());

	for (auto i = 0; i < x.size(); i++)
	{
		oddOrEvenSTDu(evenOrOdd, dataVec, i);
		trigSTDu(evenOrOdd, dataVec, i);
		//sumDivideTimesSTD(result, i);
		//std::cout << "Resultado STDu " << i << " = " << dataVec[i].C[0] << std::endl;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void maskWithOperation::trigAVX(std::vector<double>& result, __m256d& vec, __m256i& maskCos, __m256i& maskSin, int i) {

	_mm256_maskstore_pd(result.data() + i, maskCos, _mm256_tan_pd(_mm256_cos_pd(vec)));
	_mm256_maskstore_pd(result.data() + i, maskSin, _mm256_tan_pd(_mm256_sin_pd(vec)));
}

void maskWithOperation::oddorEvenAVX(const std::vector<int>& x, __m256d& vec, __m256i& maskCos, __m256i& maskSin, int i) {
	vec = _mm256_setr_pd((double)x[i], (double)x[i + 1], (double)x[i + 2], (double)x[i + 3]);
	maskCos = _mm256_setr_epi64x(-1 * ((x[i + 0] % 2) == 0), -1 * ((x[i + 1] % 2) == 0), -1 * ((x[i + 2] % 2) == 0), -1 * ((x[i + 3] % 2) == 0));
	maskSin = _mm256_setr_epi64x(-1 * ((x[i + 0] % 2) != 0), -1 * ((x[i + 1] % 2) != 0), -1 * ((x[i + 2] % 2) != 0), -1 * ((x[i + 3] % 2) != 0));
}

void maskWithOperation::setOperationAVX(const std::vector<int>& x, std::vector<double>& result) {
	__m256d vec;
	__m256i maskCos, maskSin;

	for (auto i = 0; i < x.size(); i+= 4)
	{
		oddorEvenAVX(x, vec, maskCos, maskSin, i);
		trigAVX(result, vec, maskCos, maskSin, i);
		//sumDivideTimesAVX(result, resultCos, resultSin, maskCos, maskSin, i);
		/*std::cout << "Resultado AVX " << i << " = " << result[i] << std::endl;
		std::cout << "Resultado AVX " << i+1 << " = " << result[i+1] << std::endl;
		std::cout << "Resultado AVX " << i+2 << " = " << result[i+2] << std::endl;
		std::cout << "Resultado AVX " << i+3 << " = " << result[i + 3] << std::endl;*/
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void maskWithOperation::trigTsimd(const std::vector<int>& x, tsimd::vboold4& evenOrOdd, std::vector<double>& result, int i) {
	tsimd::vdouble4 temp;

	temp = tsimd::load<tsimd::vint4>(x.data()+i);
	tsimd::store(tsimd::tan(tsimd::cos(temp)), result.data()+i, evenOrOdd);
	tsimd::store(tsimd::tan(tsimd::sin(temp)), result.data()+i, !evenOrOdd);
}

void maskWithOperation::oddOrEvenTsimd(const std::vector<int> &x, tsimd::vboold4 &evenOrOdd, int i) {
	tsimd::vint4 vec;

	vec = tsimd::load<tsimd::vint4>(x.data() + i);
	evenOrOdd = ((vec % 2) == 0);
}

void maskWithOperation::setOperationTsimd(const std::vector<int>& x, std::vector<double>& result) {
	tsimd::vboold4 evenOrOdd;

	for (auto i = 0; i < x.size(); i += tsimd::vdouble4::static_size)
	{
		oddOrEvenTsimd(x, evenOrOdd, i);
		trigTsimd(x, evenOrOdd, result, i);
		//sumDivideTimesTsimd(result, i);
		/*std::cout << "Resultado TSIMD: " << i << " = " << result[i] << std::endl;
		std::cout << "Resultado TSIMD: " << i+1 << " = " << result[i+1] << std::endl;
		std::cout << "Resultado TSIMD: " << i+2 << " = " << result[i+2] << std::endl;
		std::cout << "Resultado TSIMD: " << i+3 << " = " << result[i + 3] << std::endl;*/
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void maskWithOperation::trigSTD(const std::vector<int>& x, const std::vector<int>& evenOrOdd, std::vector<double>& result, int i) {

	if (evenOrOdd[i] == 0) {
		result[i] = std::tan(std::sin(x[i]));
	}

	else {
		result[i] = std::tan(std::cos(x[i]));
	}
}

void maskWithOperation::oddOrEvenSTD(const std::vector<int>& x, std::vector<int>& evenOrOdd, int i) {

	evenOrOdd[i] = (x[i] % 2) == 0;
}

void maskWithOperation::setOperationSTD(const std::vector<int>& x, std::vector<double>& result) {
	std::vector<int> evenOrOdd(x.size());

	for (auto i = 0; i < x.size(); i++)
	{
		oddOrEvenSTD(x, evenOrOdd, i);
		trigSTD(x, evenOrOdd, result, i);
		//sumDivideTimesSTD(result, i);
		//std::cout << "Resultado STD " << i << " = " << result[i] << std::endl;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void maskWithOperation::start(const std::vector<int>& x, std::vector<double>& resultTsimd, std::vector<double>& resultSTD, std::vector<double>& resultAVX, std::vector<data>& dataVec) {
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double>elapsed_seconds;

	start = std::chrono::system_clock::now();
	maskWithOperation::setOperationTsimd(x, resultTsimd);
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	std::cout << "Set Operation TSIMD: " << elapsed_seconds.count() << std::endl;


	start = std::chrono::system_clock::now();
	maskWithOperation::setOperationSTD(x, resultSTD);
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	std::cout << "Set Operation STD: " << elapsed_seconds.count() << std::endl;

	start = std::chrono::system_clock::now();
	maskWithOperation::setOperationAVX(x, resultAVX);
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	std::cout << "Set Operation AVX: " << elapsed_seconds.count() << std::endl;

	start = std::chrono::system_clock::now();
	maskWithOperation::setOperationSTDu(x, dataVec);
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	std::cout << "Set Operation STDu: " << elapsed_seconds.count() << std::endl;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////