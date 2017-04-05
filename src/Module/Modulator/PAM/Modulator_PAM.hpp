#ifndef MODULATOR_PAM_HPP_
#define MODULATOR_PAM_HPP_

#include <vector>
#include "Tools/Perf/MIPP/mipp.h"
#include "Tools/Math/max.h"

#include "../Modulator.hpp"

namespace aff3ct
{
namespace module
{
template <typename B = int, typename R = float, typename Q = R, tools::proto_max<Q> MAX = tools::max_star>
class Modulator_PAM : public Modulator<B,R,Q>
{
private:
	const int bits_per_symbol;
	const int nbr_symbols;
	const R sigma;
	const R sqrt_es;
	const bool disable_sig2;
	mipp::vector<R> constellation;

public:
	Modulator_PAM(const int N, const R sigma, const int bits_per_symbol = 1, const bool disable_sig2 = false,
	              const int n_frames = 1, const std::string name = "Modulator_PAM");
	virtual ~Modulator_PAM();

	int get_buffer_size_after_modulation(const int N);

	void   _modulate           (const mipp::vector<B>& X_N1,                                                          mipp::vector<R>& X_N2);
	void _demodulate           (const mipp::vector<Q>& Y_N1,                                                          mipp::vector<Q>& Y_N2);
	void _demodulate_with_gains(const mipp::vector<Q>& Y_N1, const mipp::vector<R>& H_N,                              mipp::vector<Q>& Y_N2);
	void _demodulate           (const mipp::vector<Q>& Y_N1,                             const mipp::vector<Q>& Y_N2, mipp::vector<Q>& Y_N3);
	void _demodulate_with_gains(const mipp::vector<Q>& Y_N1, const mipp::vector<R>& H_N, const mipp::vector<Q>& Y_N2, mipp::vector<Q>& Y_N3);

private:
	inline R bits_to_symbol(const B* bits) const;
};
}
}

#include "Modulator_PAM.hxx"

#endif // MODULATOR_PAM_HPP_
