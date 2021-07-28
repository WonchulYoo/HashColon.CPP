#ifndef EIGEN_INITIALIZE_MATRICES_BY_ZERO
#define EIGEN_INITIALIZE_MATRICES_BY_ZERO
#endif

#include <algorithm>
#include <numeric>
#include <Eigen/Eigen>
#include <HashColon/Statistics/SimpleStatisticalAnalysis.hpp>

using namespace std;
using namespace Eigen;
using namespace HashColon;

namespace HashColon::Statistics
{
	void SimpleStatisticsAnalysisResults::NewAll()	
	{
		Min = make_shared<Real>();
		Max = make_shared<Real>();
		Mean = make_shared<Real>();
		Median = make_shared<Real>();
		Variance = make_shared<Real>();
		StdDeviation = make_shared<Real>();
	}

	Real Min(const vector<Real>& samples) { return *(min_element(samples.begin(), samples.end())); }

	Real Min(const vector<Real>& samples, size_t& idx) 
	{ 
		auto minPtr = min_element(samples.begin(), samples.end());
		idx = (size_t)(minPtr - samples.begin());
		return *minPtr; 
	}

	Real Min(const MatrixXR& samples) { return samples.minCoeff(); }

	Real Max(const vector<Real>& samples) { return *(max_element(samples.begin(), samples.end())); }

	Real Max(const vector<Real>& samples, size_t& idx)
	{
		auto maxPtr = max_element(samples.begin(), samples.end());
		idx = (size_t)(maxPtr - samples.begin());
		return *maxPtr;
	}

	Real Max(const MatrixXR& samples) { return samples.maxCoeff(); }

	Real Mean(const vector<Real>& samples)
	{
		using namespace HashColon;
		return (accumulate(samples.begin(), samples.end(), 0.0) / (Real)samples.size());
	}

	Real Mean(const MatrixXR& samples) { return samples.mean(); }

	Real Median(const vector<Real>& samples)
	{		
		size_t medianIdx = samples.size() / 2;
		vector<size_t> idxs(samples.size());
		iota(idxs.begin(), idxs.end(), 0);
		nth_element(idxs.begin(), idxs.begin() + medianIdx, idxs.end(),
			[&](size_t lhs, size_t rhs)
			{
				return samples[lhs] < samples[rhs];
			}
		);
		return samples[idxs[medianIdx]];
	}

	Real Median(const vector<Real>& samples, size_t& idx)
	{
		size_t medianIdx = samples.size() / 2;
		vector<size_t> idxs(samples.size());
		iota(idxs.begin(), idxs.end(), 0);
		nth_element(idxs.begin(), idxs.begin() + medianIdx, idxs.end(),
			[&](size_t lhs, size_t rhs)
			{
				return samples[lhs] < samples[rhs];
			}
		);
		idx = idxs[medianIdx];
		return samples[idx];
	}

	Real Median(const MatrixXR& samples)
	{
		int size = (int)(samples.cols() * samples.rows());
		vector<Real> _samples;
		copy(samples.data(), samples.data() + size, back_inserter(_samples));
		sort(_samples.begin(), _samples.end());
		size_t medianIdx = samples.size() / 2;
		return _samples[medianIdx];
	}

	Real Variance(const vector<Real>& samples)
	{
		using namespace HashColon;
		const Real mean = Mean(samples);
		Real sqrdSum = 0.0;
		for (const auto& s : samples)
		{
			sqrdSum += (s - mean) * (s - mean);
		}
		return sqrdSum / (Real)samples.size();
	}

	Real Variance(const MatrixXR& samples)
	{
		int size = (int)(samples.cols() * samples.rows());
		const Real mean = Mean(samples);
		Real sqrdSum = 0.0;
		for_each(samples.data(), samples.data() + samples.rows() * samples.cols(),
			[&mean, &sqrdSum](Real s) {
				sqrdSum += (s - mean) * (s - mean);
			}
		);
		return sqrdSum / (Real)size;
	}

	Real StdDeviation(const vector<Real>& samples)
	{
		return sqrt(Variance(samples));
	}

	Real StdDeviation(const MatrixXR& samples)
	{
		return sqrt(Variance(samples));
	}
}
