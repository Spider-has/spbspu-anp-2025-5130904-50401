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
    rectangle_t rect;

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

  void isotropicScaling(IShape &shape, point_t scale_pt, double scale);

  point_t getRightTop(rectangle_t frame);

  point_t operator-(point_t p_t1, point_t p_t2);
  point_t operator+(point_t p_t1, point_t p_t2);
  point_t operator*(point_t p_t1, double k);
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
    shapes[size++] = new Rectangle({0, 0}, 2, 2);

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

    for (size_t i = 0; i < size; i++)
    {
      isotropicScaling(*shapes[i], scale_pt, scale);
    }
    std::cout << "\nafter figures scaling: \n";
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
    rect({w, h, pos})
{
  if (w <= 0.0 || h <= 0.0)
  {
    throw std::invalid_argument("incorrect rectangle creation: width and height must be positive");
  }
}

double khasnulin::Rectangle::getArea() const
{
  return rect.width * rect.height;
}

khasnulin::rectangle_t khasnulin::Rectangle::getFrameRect() const
{
  return rect;
}

void khasnulin::Rectangle::move(double dx, double dy)
{
  rect.pos.x += dx;
  rect.pos.y += dy;
}

void khasnulin::Rectangle::move(point_t to)
{
  rect.pos = to;
}

void khasnulin::Rectangle::scale(double k)
{
  if (k <= 0.0)
  {
    throw std::invalid_argument("incorrect rectangle scaling: scale coefficient must be positive");
  }
  rect.width *= k;
  rect.height *= k;
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

khasnulin::point_t khasnulin::operator-(point_t p_t1, point_t p_t2)
{
  return {p_t1.x - p_t2.x, p_t1.y - p_t2.y};
}

khasnulin::point_t khasnulin::operator+(point_t p_t1, point_t p_t2)
{
  return {p_t1.x + p_t2.x, p_t1.y + p_t2.y};
}

khasnulin::point_t khasnulin::operator*(point_t p_t1, double k)
{
  return {p_t1.x * k, p_t1.y * k};
}

void khasnulin::isotropicScaling(IShape &shape, point_t scale_pt, double scale)
{
  rectangle_t base_frame = shape.getFrameRect();
  point_t old_right_top = getRightTop(base_frame);

  shape.move(scale_pt);

  rectangle_t new_frame = shape.getFrameRect();
  point_t new_right_top = getRightTop(new_frame);

  shape.scale(scale);

  point_t delta = (old_right_top - new_right_top) * scale;

  shape.move(delta.x, delta.y);
}

khasnulin::point_t khasnulin::getRightTop(rectangle_t frame)
{
  return frame.pos + point_t{frame.width / 2, frame.height / 2};
}