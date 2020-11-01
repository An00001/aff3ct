/*!
 * \file
 * \brief Class module::Decoder_RA.
 */
#ifndef DECODER_RA
#define DECODER_RA

#include <vector>
#include <mipp.h>

#include "Module/Interleaver/Interleaver.hpp"
#include "Module/Decoder/Decoder_SIHO.hpp"

namespace aff3ct
{
namespace module
{
template <typename B = int, typename R = float>
class Decoder_RA : public Decoder_SIHO<B,R>
{
protected:
	const int rep_count; // number of repetitions
	int max_iter;        // max number of iterations

	std::vector<R> Fw, Bw;
	std::vector<R> Tu, Td, Wu, Wd, U;
	std::vector<mipp::vector<R>> Xd, Xu;

	Interleaver<R>& interleaver;

public:
	Decoder_RA(const int& K, const int& N, Interleaver<R>& interleaver, int max_iter = 10);
	virtual ~Decoder_RA() = default;
	virtual Decoder_RA<B,R>* clone() const;

	virtual void set_n_frames(const int n_frames);

protected:
	int _decode_siho(const R *Y_N, B *V_K, const int frame_id);

private:
	R check_node(R a, R b);
	int sign(R x);
};
}
}

#endif /* DECODER_RA */
