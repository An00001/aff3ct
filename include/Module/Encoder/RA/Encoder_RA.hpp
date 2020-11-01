/*!
 * \file
 * \brief Class module::Encoder_RA.
 */
#ifndef ENCODER_RA_HPP_
#define ENCODER_RA_HPP_

#include <vector>

#include "Module/Interleaver/Interleaver.hpp"
#include "Module/Encoder/Encoder.hpp"

namespace aff3ct
{
namespace module
{
template <typename B = int>
class Encoder_RA : public Encoder<B>
{
protected:
	const int rep_count; // number of repetitions
	std::vector<B> U, tmp_X_N;

	Interleaver<B>& interleaver;

public:
	Encoder_RA(const int& K, const int& N, Interleaver<B>& interleaver);

	virtual ~Encoder_RA() = default;

	virtual Encoder_RA<B>* clone() const;

	virtual void set_n_frames(const int n_frames);

protected:
	void _encode(const B *U_K, B *X_N, const int frame_id);
};
}
}

#endif // ENCODER_RA_HPP_
