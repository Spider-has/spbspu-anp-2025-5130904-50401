#include <iostream>

namespace khasnulin
{
  struct point_t
  {
    double x, y;
  };

  struct rectangle_t
  {
    double width, height;
    point_t pos;
  };

  class IShape
  {
  public:
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(point_t to) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double k) = 0;

    virtual ~IShape() = default;
  };

  class Rectangle : public IShape
  {
    double w_, h_;
    point_t pos_;

  public:
    Rectangle(point_t pos, double w, double h);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t to) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
  };
}

int main()
{
}

khasnulin::Rectangle::Rectangle(point_t pos, double w, double h):
    w_(w),
    h_(h),
    pos_(pos)
{
  if (w <= 0.0 || h <= 0.0)
  {
    throw std::invalid_argument("width and height must be positive or zero");
  }
}

double khasnulin::Rectangle::getArea() const
{
  return w_ * h_;
}

khasnulin::rectangle_t khasnulin::Rectangle::getFrameRect() const
{
  return rectangle_t{w_, h_, pos_};
}

void khasnulin::Rectangle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void khasnulin::Rectangle::move(point_t to)
{
  pos_ = to;
}

void khasnulin::Rectangle::scale(double k)
{
  if (k <= 0.0)
  {
    throw std::invalid_argument("scale coefficient must be positive or zero");
  }
  w_ *= k;
  h_ *= k;
}