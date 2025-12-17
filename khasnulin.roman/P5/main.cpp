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

  void printRectInfo(std::ostream &out, rectangle_t rect);
  rectangle_t getCommonRectangleFrame(rectangle_t r1, rectangle_t r2);
  void calculateAndPrintFiguresInfo(std::ostream &out, IShape **shapes, size_t size);
  rectangle_t calculateFiguresGeneralRectangleFrame(IShape **shapes, size_t size);
}

int main()
{
  using namespace khasnulin;
  IShape *shapes[3];
  size_t size = 0;
  size_t code = 0;
  try
  {

    shapes[size++] = new Rectangle({1, 1}, 5, 3);
    shapes[size++] = new Rectangle({-5, -5}, 2, 2);

    double scale;
    point_t scale_pt;

    std::cin >> scale_pt.x >> scale_pt.y;
    std::cin >> scale;
    if (std::cin.fail())
    {
      throw std::runtime_error("incorrect input: fail to read arguments, must be 3 double");
    }
    if (scale <= 0)
    {
      throw std::runtime_error("incorrect input: scale coefficient must be more than zero");
    }

    std::cout << "before figures scaling: \n";
    calculateAndPrintFiguresInfo(std::cout, shapes, size);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << "\n";
    code = 1;
  }
  catch (...)
  {
    std::cerr << "unknown error\n";
    code = 1;
  }

  for (size_t i = 0; i < size; i++)
  {
    delete shapes[i];
  }
  return code;
}

khasnulin::Rectangle::Rectangle(point_t pos, double w, double h):
    w_(w),
    h_(h),
    pos_(pos)
{
  if (w <= 0.0 || h <= 0.0)
  {
    throw std::invalid_argument("incorrect rectangle creation: width and height must be positive");
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
    throw std::invalid_argument("incorrect rectangle scaling: scale coefficient must be positive");
  }
  w_ *= k;
  h_ *= k;
}

void khasnulin::printRectInfo(std::ostream &out, rectangle_t rect)
{
  out << "rectangle center x:" << rect.pos.x << ", y: " << rect.pos.y << ", width: " << rect.width
      << ", height: " << rect.height << "\n";
}

khasnulin::rectangle_t khasnulin::getCommonRectangleFrame(rectangle_t r1, rectangle_t r2)
{
  double left = std::min(r1.pos.x - r1.width / 2, r2.pos.x - r2.width / 2);
  double right = std::max(r1.pos.x + r1.width / 2, r2.pos.x + r2.width / 2);
  double bottom = std::min(r1.pos.y - r1.height / 2, r2.pos.y - r2.height / 2);
  double top = std::max(r1.pos.y + r1.height / 2, r2.pos.y + r2.height / 2);
  return rectangle_t{right - left, top - bottom, {(right + left) / 2, (top + bottom) / 2}};
}

void khasnulin::calculateAndPrintFiguresInfo(std::ostream &out, IShape **shapes, size_t size)
{
  double sum_area = 0;
  rectangle_t general_frame = calculateFiguresGeneralRectangleFrame(shapes, size);
  for (size_t i = 0; i < size; i++)
  {
    double area = shapes[i]->getArea();
    out << "figure " << i << " area: " << shapes[i]->getArea() << "\n";
    rectangle_t rect = shapes[i]->getFrameRect();
    out << "figure " << i << " frame ";
    printRectInfo(out, rect);

    sum_area += area;
  }
  out << "area sum: " << sum_area << "\n";
  out << "general figures frame ";
  printRectInfo(out, general_frame);
}

khasnulin::rectangle_t khasnulin::calculateFiguresGeneralRectangleFrame(IShape **shapes, size_t size)
{
  if (!size)
  {
    throw std::runtime_error("figures general frame: empty shapes array error");
  }
  rectangle_t general_frame = shapes[0]->getFrameRect();
  for (size_t i = 1; i < size; i++)
  {
    general_frame = getCommonRectangleFrame(general_frame, shapes[i]->getFrameRect());
  }
  return general_frame;
}