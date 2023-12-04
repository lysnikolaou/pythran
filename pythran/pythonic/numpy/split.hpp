#ifndef PYTHONIC_NUMPY_SPLIT_HPP
#define PYTHONIC_NUMPY_SPLIT_HPP

#include "pythonic/include/numpy/split.hpp"

#include "pythonic/numpy/array_split.hpp"
#include "pythonic/builtins/ValueError.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T, class pS>
  types::list<types::ndarray<T, types::array<long, std::tuple_size<pS>::value>>>
  split(types::ndarray<T, pS> const &a, long nb_split)
  {
    if (a.flat_size() % nb_split != 0)
      throw types::ValueError("array split does ! result in an equal division");
    return array_split(a, nb_split);
  }

  template <class T, class pS, class I_>
  typename std::enable_if<
      types::is_iterable<I_>::value,
      types::list<types::ndarray<
          T, types::array<long, std::tuple_size<pS>::value>>>>::type
  split(types::ndarray<T, pS> const &a, I_ const &split_mask)
  {
    return array_split(a, split_mask);
  }

  template <class E, class I_>
  types::list<types::ndarray<typename E::dtype, types::array<long, E::value>>>
  split(E const &a, I_ const &)
  {
    throw std::runtime_error("split only partially implemented");
  }
}
PYTHONIC_NS_END

#endif
