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

template <class _InputIterator, class _Predicate, class _IterTag>
[[__nodiscard__]] inline _LIBCPP_HIDE_FROM_ABI _LIBCPP_CONSTEXPR_SINCE_CXX20 _InputIterator
__find_if_impl(_InputIterator __first, _InputIterator __last, _Predicate __pred, _IterTag) {
  for (; __first != __last; ++__first)
    if (__pred(*__first))
      break;
  return __first;
}

template <class _RandomAccessIterator, class _Predicate>
[[__nodiscard__]] inline _LIBCPP_HIDE_FROM_ABI _LIBCPP_CONSTEXPR_SINCE_CXX20 _RandomAccessIterator __find_if_impl(
    _RandomAccessIterator __first, _RandomAccessIterator __last, _Predicate __pred, random_access_iterator_tag) {
  using diff_t = __iter_diff_t<_RandomAccessIterator>;

  for (diff_t __n = (__last - __first) >> 2; __n > 0; --__n) {
    if (__pred(*__first))
      return __first;
    ++__first;

    if (__pred(*__first))
      return __first;
    ++__first;

    if (__pred(*__first))
      return __first;
    ++__first;

    if (__pred(*__first))
      return __first;
    ++__first;
  }

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
