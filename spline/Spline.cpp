#include "spline/Spline.h"
#include "spline/SplBase.h"
namespace msd {

Scalar Spline::operator()(Scalar x, size_t order) const
{
    return (*m_impl)(x, order);
}

} // end namespace msd