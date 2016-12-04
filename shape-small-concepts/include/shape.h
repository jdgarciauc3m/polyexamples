#ifndef DSL_SHAPE_H
#define DSL_SHAPE_H

#include <iosfwd>
#include <memory>
#include <cstring>
#include <iostream>

namespace dsl { // Dummy Shapes Library

static constexpr int small_object_threshold = 32;

template <typename T>
constexpr concept bool small_object() {
  return sizeof(T) <= small_object_threshold;
}

template <typename T>
constexpr concept bool large_object() {
  return sizeof(T) > small_object_threshold;
}

class shape {
private:

  using internal_buffer = char[small_object_threshold];

  class shape_base {
  public:
    shape_base() noexcept {}
    virtual ~shape_base() noexcept = default;

    virtual void placement_move(internal_buffer & buf) noexcept = 0;

    virtual std::string tagname() const = 0;
    virtual int area() const noexcept = 0;
    virtual void translate(int dx, int dy) noexcept = 0;
    virtual void enlarge(int k) noexcept = 0;
    virtual void insert(std::ostream & os) const noexcept = 0;
    virtual void extract(std::istream & is) noexcept = 0;
  };

  template <typename S>
  class local_shape final : public shape_base {
  public:
    local_shape() noexcept : impl_{} {}
    local_shape(S && x) noexcept : impl_{std::forward<S>(x)} {}
    virtual ~local_shape() noexcept = default;

    virtual void placement_move(internal_buffer & buf) noexcept override; 

    std::string tagname() const override { return impl_.tagname(); }
    int area() const noexcept override { return impl_.area(); }
    void translate(int dx, int dy) noexcept override { impl_.translate(dx,dy); }
    void enlarge(int k) noexcept override {impl_.enlarge(k); }
    void insert(std::ostream & os) const noexcept override { os << impl_; }
    void extract(std::istream & is) noexcept override { is >> impl_; }
  private:
    S impl_;
  };
  
  template <typename S>
  class dynamic_shape final : public shape_base {
  public:
    dynamic_shape() : impl_{std::make_unique<S>()} {}
    dynamic_shape(S && s) : impl_{std::make_unique<S>(std::forward<S>(s))} {}
    dynamic_shape(std::unique_ptr<S> && p) noexcept : impl_{std::forward<std::unique_ptr<S>>(p)} {}
    virtual ~dynamic_shape() noexcept = default;

    virtual void placement_move(internal_buffer & buf) noexcept override; 
  
    std::string tagname() const noexcept override { return impl_->tagname(); }
    int area() const noexcept override { return impl_->area(); }
    void translate(int dx, int dy) noexcept override { impl_->translate(dx,dy); }
    void enlarge(int k) noexcept override {impl_->enlarge(k); }
    void insert(std::ostream & os) const noexcept override { os << *impl_; }
    void extract(std::istream & is) noexcept override { is >> *impl_; }
  private:
    std::unique_ptr<S> impl_;
  };

private:
  internal_buffer buffer_;

  shape_base * self() noexcept { 
    return reinterpret_cast<shape_base*>(&buffer_); 
  }

  const shape_base * self() const noexcept { 
    return reinterpret_cast<const shape_base*>(&buffer_); 
  }

  shape() {}

public:

  template <small_object S>
  shape(S && s) noexcept {
    new (&buffer_) local_shape<S>{std::forward<S>(s)};
  }

  template <large_object S> 
  shape(S && s) noexcept {
    new (&buffer_) dynamic_shape<S>{std::forward<S>(s)};
  }

  template <small_object S>
  friend shape make_shape() noexcept;

  template <large_object S>
  friend shape make_shape() noexcept;

  shape(const shape &) noexcept = delete;
  shape & operator=(const shape &) noexcept = delete;

  shape(shape && s) noexcept {
    s.self()->placement_move(buffer_);
  }

  shape & operator=(shape &&) noexcept = delete;

  ~shape() noexcept {
    self()->~shape_base();
  }

  std::string tagname() const { return self()->tagname(); }
  int area() const noexcept { return self()->area(); }
  void translate(int dx, int dy) noexcept { self()->translate(dx,dy); }
  void enlarge(int k) noexcept {self()->enlarge(k); }

  friend std::ostream & operator<<(std::ostream & os, const shape & s)
    { s.self()->insert(os); return os; }
  friend std::istream & operator>>(std::istream & is, shape & s)
    { s.self()->extract(is); return is; }

};

template <typename S>
void shape::local_shape<S>::placement_move(internal_buffer & buf) noexcept {
  new (&buf) local_shape<S>(std::move(impl_));
}

template <typename S>
void shape::dynamic_shape<S>::placement_move(internal_buffer & buf) noexcept {
  new (&buf) dynamic_shape<S>(std::move(impl_));
}

template <small_object S>
shape make_shape() noexcept {
  shape s;
  new (&s.buffer_) shape::local_shape<S>{};
  return s;
}

template <large_object S>
shape make_shape() noexcept {
  shape s;
  new (&s.buffer_) shape::dynamic_shape<S>{};
  return s;
}

} // namespace dsl

#endif
