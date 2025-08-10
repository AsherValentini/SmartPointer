#pragma once
#include <cstddef>  // for std::size_t

template<typename T>
class SharedPtr {
public:
	using element_type = T;

	SharedPtr () noexcept : ptr_(nullptr), refcnt_(nullptr) {}
	explicit SharedPtr (T* p) : ptr_(p), refcnt_(nullptr) {
		if(ptr_) {
			refcnt_= new std::size_t(1);
		}
	}

	T* get() const noexcept {return ptr_; }

private:
	T* ptr_;
	std::size_t* refcnt_;

};