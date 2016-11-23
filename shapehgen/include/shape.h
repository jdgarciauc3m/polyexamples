#ifndef DSL_SHAPE_H
#define DSL_SHAPE_H

#include <iosfwd>
#include <memory>

namespace dsl { // Dummy Shapes Library

class shape {
public:

  template<typename T>
  shape(T x);

  template<typename T>
  static shape make();

  shape(const shape &) = delete;
  shape & operator=(const shape &) = delete;

  shape(shape &&) noexcept = default;
  shape & operator=(shape &&) = default;

  std::string classname() const { return self_->classname(); }
  int area() const { return self_->area(); }
  void move(int dx, int dy) { self_->move(dx,dy); }
  void resize(int k) {self_->resize(k); }

  friend std::ostream & operator<<(std::ostream & os, const shape & s)
    { s.self_->insert(os); return os; }
  friend std::istream & operator>>(std::istream & is, const shape & s)
    { s.self_->extract(is); return is; }

private:
  shape() : self_{nullptr} {}

  class shape_base {
  public:
    shape_base() {}
    virtual ~shape_base() = default;
    virtual std::string classname() const = 0;
    virtual int area() const = 0;
    virtual void move(int dx, int dy) = 0;
    virtual void resize(int k) = 0;
    virtual void insert(std::ostream & os) const = 0;
    virtual void extract(std::istream & is) = 0;
  };

  template <typename T>
  class concrete_shape : public shape_base {
  public:
    concrete_shape() : impl_{} {}
    concrete_shape(T && x) : impl_{std::move(x)} {}
    virtual ~concrete_shape() = default;
    std::string classname() const override { return impl_.classname(); }
    int area() const override { return impl_.area(); }
    void move(int dx, int dy) override { impl_.move(dx,dy); }
    void resize(int k) override {impl_.resize(k); }
    void insert(std::ostream & os) const override { os << impl_; }
    void extract(std::istream & is) override { is >> impl_; }
  private:
    T impl_;
  };

  std::unique_ptr<shape_base> self_;
};

template <typename T>
shape::shape(T x) :
  self_{std::make_unique<concrete_shape<T>>(std::move(x))}
{}

template <typename T>
shape shape::make() {
  shape s;
  s.self_ = std::make_unique<concrete_shape<T>>();
  return s;
}

} // namespace dsl

#endif
