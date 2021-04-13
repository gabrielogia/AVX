#pragma once
#include "tsimd/tsimd/tsimd.h"
#include "data.h"
#include <vector>
#include <chrono>
#include <immintrin.h>

class maskWithOperation
{
	public:
		maskWithOperation();
		~maskWithOperation();

		static void start(const std::vector<int>& x, std::vector<double>& resultTsimd, std::vector<double>& resultSTD, std::vector<double>& resultAVX);

		static void testOperations();
		static void testLoadStore(std::vector<int> &x, std::vector<int> &y);

		static void setOperationTsimd(const std::vector<int> &x, std::vector<double> &result);
		static void oddOrEvenTsimd(const std::vector<int>& x, tsimd::vboold4& evenOrOdd, int i);
		static void trigTsimd(const std::vector<int>& x, tsimd::vboold4& evenOrOdd, std::vector<double>& result, int i);
		static void sumDivideTimesTsimd(std::vector<double>& result, int i);
		
		static void setOperationSTD(const std::vector<int>& x, std::vector<double>& result);
		static void oddOrEvenSTD(const std::vector<int>& x, std::vector<int>& evenOrOdd, int i);
		static void trigSTD(const std::vector<int>& x, const std::vector<int>& evenOrOdd, std::vector<double>& result, int i);
		static void sumDivideTimesSTD(std::vector<double>& result, int i);

		static void setOperationAVX(const std::vector<int>& x, std::vector<double>& result);
		static void oddorEvenAVX(const std::vector<int>& x, __m256d& vec, __m256i& maskCos, __m256i& maskSin, int i);
		static void trigAVX(std::vector<double>& result, __m256d& vec, __m256i& maskCos, __m256i& maskSin, int i);
		static void sumDivideTimesAVX(std::vector<double>& result, __m256d& resultCos, __m256d& resultSin, __m256i& maskCos, __m256i& maskSin, int i);
};

