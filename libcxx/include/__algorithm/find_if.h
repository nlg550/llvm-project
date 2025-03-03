// -*- C++ -*-
//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___ALGORITHM_FIND_IF_H
#define _LIBCPP___ALGORITHM_FIND_IF_H

#include <__algorithm/iterator_operations.h>
#include <__config>
#include <__iterator/concepts.h>
#include <__iterator/iterator_traits.h>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

// General case
template <class _InputIterator, class _Predicate, class IterTag>
[[__nodiscard__]] inline _LIBCPP_HIDE_FROM_ABI _LIBCPP_CONSTEXPR_SINCE_CXX20 _InputIterator
__find_if_impl(_InputIterator __first, _InputIterator __last, _Predicate __pred, IterTag) {
  for (; __first != __last; ++__first)
    if (__pred(*__first))
      break;
  return __first;
}

template <class _RandomAccessIterator, class _Predicate>
[[__nodiscard__]] inline _LIBCPP_HIDE_FROM_ABI _LIBCPP_CONSTEXPR_SINCE_CXX20 _RandomAccessIterator __find_if_impl(
    _RandomAccessIterator __first, _RandomAccessIterator __last, _Predicate __pred, random_access_iterator_tag) {
  using diff_t = __iter_diff_t<_RandomAccessIterator>;

  diff_t __dist = distance(__first, __last);

  diff_t __last_unrolled = __dist - (__dist % 4);
  _RandomAccessIterator __iters[4];
  bool __found[4];

  for (diff_t __i = 0; __i < __last_unrolled; __i += 4) {
    __iters[0] = __first++;
    __iters[1] = __first++;
    __iters[2] = __first++;
    __iters[3] = __first++;

    __found[0] = __pred(*__iters[0]);
    __found[1] = __pred(*__iters[1]);
    __found[2] = __pred(*__iters[2]);
    __found[3] = __pred(*__iters[3]);

    if (__found[0] || __found[1] || __found[2] || __found[3])
      break;
  }

  if (__found[0])
    return __iters[0];
  if (__found[1])
    return __iters[1];
  if (__found[2])
    return __iters[2];
  if (__found[3])
    return __iters[3];

  for (; __first != __last; ++__first)
    if (__pred(*__first))
      break;
  return __first;
}

template <class _InputIterator, class _Predicate>
[[__nodiscard__]] inline _LIBCPP_HIDE_FROM_ABI _LIBCPP_CONSTEXPR_SINCE_CXX20 _InputIterator
find_if(_InputIterator __first, _InputIterator __last, _Predicate __pred) {
  return __find_if_impl(
      std::move(__first), std::move(__last), std::move(__pred), __iterator_category_type<_InputIterator>());
}

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___ALGORITHM_FIND_IF_H
