SmartPtrPuzzle
Paragraph:

Implement your own basic version of a shared_ptr<T> from scratch.
This smart pointer should manage shared ownership of a dynamically allocated object, with proper reference counting.
When the last SharedPtr<T> pointing to the object is destroyed, the object must be deleted.

You must implement:

    Reference counting (manual or via internal control block)

    Copy and move constructors

    Copy and move assignment

    Proper destructor logic

    operator*() and operator->()

    A use_count() method for inspection

Example:
```
SharedPtr<Foo> a(new Foo(42));
SharedPtr<Foo> b = a;           // shared ownership
SharedPtr<Foo> c = std::move(b); // move ownership

assert(a.use_count() == 2);
assert(b.use_count() == 0);     // b is moved-from
assert(c.use_count() == 2);
```

Clarifications:

    You may not use std::shared_ptr, std::weak_ptr, or std::make_shared.

    You must handle proper cleanup (i.e., object is deleted once all owners go out of scope).

    Use raw new and delete internally, but manage ownership safely.

    SharedPtr<T> must support both copy and move semantics.

    You do not need to handle weak pointers or thread-safety.

    You must avoid double-deletes and leaks (Valgrind clean!).
