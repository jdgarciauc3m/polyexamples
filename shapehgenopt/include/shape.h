#ifndef DSL_SHAPE_H
#define DSL_SHAPE_H

#include <iosfwd>
#include <memory>
#include <cstring>
#include <iostream>

namespace dsl { // Dummy Shapes Library

class shape {
private:
  class shape_base;
  constexpr static int max_shape_size = sizeof(std::unique_ptr<shape_base>);

  template <typename T>
  static constexpr bool is_small() { return sizeof(T) <= max_shape_size; }

  template <typename T>
  using small_shape = typename std::enable_if<is_small<T>(), shape>::type;

  template <typename T>
  using large_shape = typename std::enable_if<(!is_small<T>()), shape>::type;

  shape() {}

public:


  template <typename S>
  shape(S && s,
        small_shape<S> * = nullptr) noexcept
  {
    new (&buffer_) concrete_shape<S>{std::forward<S>(s)};
  }

  template <typename S>
  shape(S && s,
        large_shape<S> * = nullptr) noexcept
  {
    new (&buffer_) dynamic_shape<S>{std::forward<S>(s)};
  }

  shape(const shape &) noexcept = delete;
  shape & operator=(const shape &) noexcept = delete;

  shape(shape && s) noexcept {
    s.self()->moving_clone(buffer_);
  }

  shape & operator=(shape &&) noexcept = delete;

  ~shape() noexcept {
    self()->~shape_base();
  }

  std::string classname() const { return self()->classname(); }
  int area() const noexcept { return self()->area(); }
  void translate(int dx, int dy) noexcept { self()->translate(dx,dy); }
  void enlarge(int k) noexcept {self()->enlarge(k); }

  friend std::ostream & operator<<(std::ostream & os, const shape & s)
    { s.self()->insert(os); return os; }
  friend std::istream & operator>>(std::istream & is, shape & s)
    { s.self()->extract(is); return is; }

private:

  std::aligned_storage<max_shape_size>::type buffer_;

  shape_base * self() noexcept { 
    return reinterpret_cast<shape_base*>(&buffer_); 
  }

  const shape_base * self() const noexcept { 
    return reinterpret_cast<const shape_base*>(&buffer_); 
  }

  class shape_base {
  public:
    shape_base() noexcept {}
    virtual ~shape_base() noexcept = default;

    virtual shape_base * moving_clone(std::aligned_storage<max_shape_size>::type & buf) noexcept = 0;

    virtual std::string classname() const = 0;
    virtual int area() const noexcept = 0;
    virtual void translate(int dx, int dy) noexcept = 0;
    virtual void enlarge(int k) noexcept = 0;
    virtual void insert(std::ostream & os) const noexcept = 0;
    virtual void extract(std::istream & is) noexcept = 0;
  };

  template <typename S>
  class concrete_shape : public shape_base {
  public:
    concrete_shape() noexcept : impl_{} {}
    concrete_shape(S && x) noexcept : impl_{std::forward<S>(x)} {}
    virtual ~concrete_shape() noexcept = default;

    virtual shape_base * moving_clone(std::aligned_storage<max_shape_size>::type & buf) noexcept override {
      return new (&buf) concrete_shape<S>(std::move(impl_));
    }

    std::string classname() const override { return impl_.classname(); }
    int area() const noexcept override { return impl_.area(); }
    void translate(int dx, int dy) noexcept override { impl_.translate(dx,dy); }
    void translate(int k) noexcept override {impl_.enlarge(k); }
    void insert(std::ostream & os) const noexcept override { os << impl_; }
    void extract(std::istream & is) noexcept override { is >> impl_; }
  private:
    S impl_;
  };
  
  template <typename S>
  class dynamic_shape : public shape_base {
  public:
    dynamic_shape() noexcept : impl_{std::make_unique<S>()} {}
    dynamic_shape(S && s) noexcept : impl_{std::make_unique<S>(std::forward<S>(s))} {}
    dynamic_shape(std::unique_ptr<S> && p) noexcept : impl_{std::forward<std::unique_ptr<S>>(p)} {}

    virtual ~dynamic_shape() noexcept = default;

    virtual shape_base * moving_clone(std::aligned_storage<max_shape_size>::type & buf) noexcept override {
      return new (&buf) dynamic_shape<S>(std::move(impl_));
    }
  
    std::string classname() const noexcept override { return impl_->classname(); }
    int area() const noexcept override { return impl_->area(); }
    void translate(int dx, int dy) noexcept override { impl_->translate(dx,dy); }
    void enlarge(int k) noexcept override {impl_->enlarge(k); }
    void insert(std::ostream & os) const noexcept override { os << *impl_; }
    void extract(std::istream & is) noexcept override { is >> *impl_; }
  private:
    std::unique_ptr<S> impl_;
  };

public:
  template <typename S>
  friend small_shape<S> make_shape() noexcept;

  template <typename S>
  friend large_shape<S> make_shape() noexcept;
};

template <typename S>
shape::small_shape<S> make_shape() noexcept
{
  shape s;
  new (&s.buffer_) shape::concrete_shape<S>{};
  return s;
}

template <typename S>
shape::large_shape<S> make_shape() noexcept {
  shape s;
  new (&s.buffer_) shape::dynamic_shape<S>{};
  return s;
}

} // namespace dsl

#endif
