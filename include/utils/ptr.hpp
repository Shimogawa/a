#pragma once

#include <concepts>
#include <memory>

namespace ll::utils::ptr {

template<typename D, typename B>
std::unique_ptr<D> uniquePtrBaseToDerived(std::unique_ptr<B>& p) requires(std::derived_from<D, B>) {
  return std::unique_ptr<D>(static_cast<D*>(p.release()));
}

}// namespace ll::utils::ptr
