#ifdef CHANNEL_MKL

#include <cmath>
#include <stdexcept>
#include <algorithm>

#include "Tools/Display/bash_tools.h"

#include "Channel_AWGN_MKL_LLR.hpp"

using namespace aff3ct::module;
using namespace aff3ct::tools;

template <typename R>
Channel_AWGN_MKL_LLR<R>
::Channel_AWGN_MKL_LLR(const int N, const R& sigma, const int seed, const int n_frames, const std::string name)
: Channel<R>(N, n_frames, name),
  sigma(sigma)
{
	if (sigma == (R)0)
		throw std::domain_error("aff3ct::module::Channel_AWGN_MKL_LLR: \"sigma\" can't be equal to 0.");

	//vslNewStream(&stream_state, VSL_BRNG_MT2203, seed);
	vslNewStream(&stream_state, VSL_BRNG_SFMT19937, seed);

	if (stream_state == nullptr)
		throw std::runtime_error("aff3ct::module::Channel_AWGN_MKL_LLR: \"stream_state\" can't be null.");
}

template <typename R>
Channel_AWGN_MKL_LLR<R>
::~Channel_AWGN_MKL_LLR()
{
	vslDeleteStream(&stream_state);
}

template <typename R>
void Channel_AWGN_MKL_LLR<R>
::_add_noise(const mipp::vector<R>& X_N, mipp::vector<R>& Y_N)
{
	throw std::runtime_error("aff3ct::module::Channel_AWGN_MKL_LLR: adding white Gaussian noise is impossible on this "
	                         "type of data.");
}

namespace aff3ct
{
namespace module
{
template <>
void Channel_AWGN_MKL_LLR<float>
::_add_noise(const mipp::vector<float>& X_N, mipp::vector<float>& Y_N)
{
	vsRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER2,
	              stream_state,
	              Y_N.size(),
	              Y_N.data(),
	              0.0,
	              sigma);
	/*
	vsRngGaussian(VSL_RNG_METHOD_GAUSSIAN_ICDF,
	              stream_state,
	              Y_N.size(),
	              Y_N.data(),
	              0.0,
	              sigma);
	*/

	auto size = Y_N.size();
	for (unsigned i = 0; i < size; i++)
		Y_N[i] = X_N[i] + Y_N[i];
}
}
}

namespace aff3ct
{
namespace module
{
template <>
void Channel_AWGN_MKL_LLR<double>
::_add_noise(const mipp::vector<double>& X_N, mipp::vector<double>& Y_N)
{
	vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER2,
	              stream_state,
	              Y_N.size(),
	              Y_N.data(),
	              0.0,
	              sigma);
	/*
	vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_ICDF,
	              stream_state,
	              Y_N.size(),
	              Y_N.data(),
	              0.0,
	              sigma);
	*/

	auto size = Y_N.size();
	for (unsigned i = 0; i < size; i++)
		Y_N[i] = X_N[i] + Y_N[i];
}
}
}

// ==================================================================================== explicit template instantiation 
#include "Tools/types.h"
#ifdef MULTI_PREC
template class aff3ct::module::Channel_AWGN_MKL_LLR<R_32>;
template class aff3ct::module::Channel_AWGN_MKL_LLR<R_64>;
#else
template class aff3ct::module::Channel_AWGN_MKL_LLR<R>;
#endif
// ==================================================================================== explicit template instantiation

#endif
