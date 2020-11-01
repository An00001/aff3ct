/*!
 * \file
 * \brief Class module::Decoder_repetition_fast.
 */
#ifndef DECODER_REPETITION_FAST
#define DECODER_REPETITION_FAST

#include "Module/Decoder/Repetition/Decoder_repetition.hpp"

namespace aff3ct
{
namespace module
{
template <typename B = int, typename R = float>
class Decoder_repetition_fast : public Decoder_repetition<B,R>
{
public:
	Decoder_repetition_fast(const int& K, const int& N, const bool buffered_encoding = true);
	virtual ~Decoder_repetition_fast() = default;
	virtual Decoder_repetition_fast<B,R>* clone() const;

protected:
	int _decode_siso(const R *sys, const R *par, R *ext, const int frame_id);
};
}
}

#endif /* DECODER_REPETITION_FAST */
