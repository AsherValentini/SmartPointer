#pragma once
#include <cstddef>  // for std::size_t

template<typename T>
class SharedPtr {
public:
	using element_type = T;

	// default ctr
	SharedPtr () noexcept : ptr_(nullptr), refcnt_(nullptr) {}
	explicit SharedPtr (T* p) : ptr_(p), refcnt_(nullptr) {
		if(ptr_) {
			refcnt_= new std::size_t(1);
		}
	}
	// default dtr
	~SharedPtr () {
		release_();
	}

	// cpy ctr
	SharedPtr (const SharedPtr& other)
		: ptr_(other.ptr_), refcnt_(other.refcnt_) {
			if(refcnt_){
				++(*refcnt_);
			}
		}

	// cpy assignment operator
	SharedPtr& operator =(const SharedPtr& other) noexcept {
		if (this == &other) return *this;

		release_();

		this->ptr_ = other.ptr_;
		this->refcnt_ = other.refcnt_;
		if (refcnt_) {
			++(*refcnt_);
		}

		return *this;
	}

	// mv ctr
	SharedPtr (SharedPtr&& other) noexcept
		: ptr_(other.ptr_), refcnt_(other.refcnt_)
	{
		other.ptr_ = nullptr;
		other.refcnt_ = nullptr;
	}

	// mv assignment operator
	SharedPtr& operator=(SharedPtr&& other) noexcept {

		if (this == &other) return *this;

		release_();

		this->ptr_= other.ptr_;
		this->refcnt_ = other.refcnt_;

		other.ptr_ = nullptr;
		other.refcnt_ = nullptr;

		return *this;

	}

	// operational overloads
	T* operator->() {
		return ptr_;
	}

	T& operator*() {
		return *ptr_;
	}

	// reset a pointer
	void release () {
		release_(); // just drop
	}

	void release (T* p) {

		// drop and aquire new memory
		release_();
		if (p) {
			ptr_ = p;
			refcnt_ = new std::size_t(1);
		}
	}

	T* get() const noexcept {return ptr_; }

	std::size_t use_count() const noexcept {
		return (refcnt_)? *refcnt_ : 0;
	}

	explicit operator bool() const noexcept {
		return ptr_ != nullptr;
	}

private:
	T* ptr_;
	std::size_t* refcnt_;

	void release_ () {
		if(!refcnt_)
			return;
		--(*refcnt_);
		if(refcnt_ == 0) {
			delete ptr_;
			delete refcnt_;
		}
		ptr_ = nullptr;
		refcnt_ = nullptr;
	}

};