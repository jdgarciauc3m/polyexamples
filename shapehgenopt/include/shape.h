#ifndef DSL_SHAPE_H
#define DSL_SHAPE_H

#include <iosfwd>
#include <memory>
#include <cstring>

namespace dsl { // Dummy Shapes Library

class shape {
private:
  constexpr static int max_shape_size = 32;

  template <typename T>
  static constexpr bool is_small() { return sizeof(T) <= max_shape_size; }

  template <typename T>
  using is_small_t = typename std::enable_if<is_small<T>()>::type;

  template <typename T>
  using is_not_small_t = typename std::enable_if<(!is_small<T>())>::type;

  class shape_base;

public:

  shape() { std::memset(&buffer_, 0, sizeof(buffer_)); }

  template <typename S>
  shape(S && s,
        is_small_t<S> * = nullptr) noexcept
  {
    new (&buffer_) concrete_shape<S>{std::move(s)};
  }

  template <typename S>
  shape(S && s,
        is_not_small_t<S> * = nullptr) noexcept
  {
    new (&buffer_) dynamic_shape<S>{std::move(s)};
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
  void move(int dx, int dy) noexcept { self()->move(dx,dy); }
  void resize(int k) noexcept {self()->resize(k); }

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
    virtual void move(int dx, int dy) noexcept = 0;
    virtual void resize(int k) noexcept = 0;
    virtual void insert(std::ostream & os) const noexcept = 0;
    virtual void extract(std::istream & is) noexcept = 0;
  };

  template <typename S>
  class concrete_shape : public shape_base {
  public:
    concrete_shape() noexcept : impl_{} {}
    concrete_shape(S && x) noexcept : impl_{std::move(x)} {}
    virtual ~concrete_shape() noexcept = default;

    virtual shape_base * moving_clone(std::aligned_storage<max_shape_size>::type & buf) noexcept override {
      return new (&buf) concrete_shape<S>(std::move(impl_));
    }

    std::string classname() const override { return impl_.classname(); }
    int area() const noexcept override { return impl_.area(); }
    void move(int dx, int dy) noexcept override { impl_.move(dx,dy); }
    void resize(int k) noexcept override {impl_.resize(k); }
    void insert(std::ostream & os) const noexcept override { os << impl_; }
    void extract(std::istream & is) noexcept override { is >> impl_; }
  private:
    S impl_;
  };
  
  template <typename S>
  class dynamic_shape : public shape_base {
  public:
    dynamic_shape() noexcept : impl_{std::make_unique<S>()} {}
    dynamic_shape(S && s) noexcept : impl_{std::make_unique<S>(std::move(s))} {}

    virtual ~dynamic_shape() noexcept = default;

    virtual shape_base * moving_clone(std::aligned_storage<max_shape_size>::type & buf) noexcept override {
      return new (&buf) dynamic_shape<S>(std::move(impl_));
    }
  
    std::string classname() const override { return impl_->classname(); }
    int area() const override { return impl_->area(); }
    void move(int dx, int dy) override { impl_->move(dx,dy); }
    void resize(int k) override {impl_->resize(k); }
    void insert(std::ostream & os) const override { os << *impl_; }
    void extract(std::istream & is) override { is >> *impl_; }
  private:
    std::unique_ptr<S> impl_;
  };



public:
  template<typename S>
  static shape make(is_small_t<S> * = nullptr) noexcept {
    shape s;
    shape::concrete_shape<S> & cs = static_cast<shape::concrete_shape<S>&>(*s.self());
    new (&s.buffer_) shape::concrete_shape<S>{std::move(cs)};
    return s;
  }

  template<typename S>
  static shape make(is_not_small_t<S> * = nullptr) noexcept {
    shape s;
    new (&s.buffer_) shape::dynamic_shape<S>{std::move(s)};
    return s;
  }

};


} // namespace dsl

#endif
