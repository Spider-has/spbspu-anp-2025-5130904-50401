#include "composite_figure.hpp"

#include <cstddef>

namespace
{
  void copyShapes(khasnulin::IShape **from, khasnulin::IShape **to, size_t size)
  {
    for (size_t i = 0; i < size; i++)
    {
      to[i] = from[i];
    }
  }
}

khasnulin::CompositeFigure::CompositeFigure():
    size(0),
    capacity(0),
    figures(nullptr)
{
}

khasnulin::CompositeFigure::CompositeFigure(const CompositeFigure &cf):
    size(cf.size),
    capacity(cf.capacity),
    figures(new IShape *[cf.size])
{
  copyShapes(cf.figures, figures, size);
}