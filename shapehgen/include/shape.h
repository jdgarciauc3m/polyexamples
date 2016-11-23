#ifndef DSL_SHAPE_H
#define DSL_SHAPE_H

#include <iosfwd>
#include <memory>

namespace dsl { // Dummy Shapes Library

class shape {
public:

  shape() : self_{nullptr} {}

  template<typename T>
  shape(T x);

  shape(const shape &) = delete;
  shape & operator=(const shape &) = delete;

  shape(shape &&) noexcept = default;
  shape & operator=(shape &&) = default;

  std::string tagname() const { return self_->tagname(); }
  int area() const { return self_->area(); }
  void translate(int dx, int dy) { self_->translate(dx,dy); }
  void enlarge(int k) {self_->enlarge(k); }

  friend std::ostream & operator<<(std::ostream & os, const shape & s)
    { s.self_->insert(os); return os; }
  friend std::istream & operator>>(std::istream & is, const shape & s)
    { s.self_->extract(is); return is; }

private:

  class shape_base {
  public:
    shape_base() {}
    virtual ~shape_base() = default;
    virtual std::string tagname() const = 0;
    virtual int area() const = 0;
    virtual void translate(int dx, int dy) = 0;
    virtual void enlarge(int k) = 0;
    virtual void insert(std::ostream & os) const = 0;
    virtual void extract(std::istream & is) = 0;
  };

  template <typename T>
  class concrete_shape : public shape_base {
  public:
    concrete_shape() : impl_{} {}
    concrete_shape(T && x) : impl_{std::move(x)} {}
    virtual ~concrete_shape() = default;
    std::string tagname() const override { return impl_.tagname(); }
    int area() const override { return impl_.area(); }
    void translate(int dx, int dy) override { impl_.translate(dx,dy); }
    void enlarge(int k) override {impl_.enlarge(k); }
    void insert(std::ostream & os) const override { os << impl_; }
    void extract(std::istream & is) override { is >> impl_; }
  private:
    T impl_;
  };

  std::unique_ptr<shape_base> self_;

  template <typename U> friend shape make_shape();
};

template <typename T>
shape::shape(T x) :
  self_{std::make_unique<concrete_shape<T>>(std::move(x))}
{}

template<typename T>
shape make_shape() {
  shape s;
  s.self_ = std::make_unique<shape::concrete_shape<T>>();
  return s;
}

} // namespace dsl

#endif
