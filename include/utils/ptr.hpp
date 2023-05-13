#pragma once

#include <concepts>
#include <memory>

namespace ll::utils::ptr {

template<typename D, typename B>
requires(std::derived_from<D, B>)
  std::unique_ptr<D> uniquePtrBaseToDerived(std::unique_ptr<B>& p) {
  return std::unique_ptr<D>(static_cast<D*>(p.release()));
}

}// namespace ll::utils::ptr
