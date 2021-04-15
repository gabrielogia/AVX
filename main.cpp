#include "maskWithOperation.h"
#include "data.h"

int main(int argc, char** argv) {

	int n = atoi(argv[1]);
	std::vector<int> N = { 2 * 1048576, 3 * 1048576, 4 * 1048576, 5 * 1048576, 6 * 1048576, 7 * 1048576, 8 * 1048576 };

	std::vector<data> dataVec;
	std::vector<int> x;
	std::vector<double> resultTsimd, resultSTD, resultAVX;
		
	for (auto i = 0; i < N.size(); i++) //numero de pontos
	{
		for (auto j = 0; j < n; j++) //numero de rodadas
		{
			dataVec.resize(N[i]);
			x.resize(N[i]);
			resultTsimd.resize(N[i]);
			resultSTD.resize(N[i]);
			resultAVX.resize(N[i]);

			for (auto k = 0; k < N[i]; k++)
			{
				x[k] = (k);
				dataVec[k].A[0] = &x[k];
			}

			std::cout << std::endl << "Execution " << j+1 << " with " << N[i] << " points:" << std::endl;
			maskWithOperation::start(x, resultTsimd, resultSTD, resultAVX, dataVec);

			dataVec.clear();
			x.clear();
			resultTsimd.clear();
			resultAVX.clear();
			resultSTD.clear();
		}
		
		std::cout << std::endl;
	}

	return 0;
}