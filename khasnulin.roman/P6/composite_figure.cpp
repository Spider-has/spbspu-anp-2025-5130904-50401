#include "composite_figure.hpp"

#include <algorithm>
#include <cstddef>

namespace
{
  void copyShapes(khasnulin::IShape **from, khasnulin::IShape **to, size_t size) noexcept
  {
    for (size_t i = 0; i < size; i++)
    {
      to[i] = from[i];
    }
  }
}

using ComFig = khasnulin::CompositeFigure;
ComFig::ShapeVector::ShapeVector() noexcept:
    size_(0),
    capacity_(0),
    figures_(nullptr)
{
}

ComFig::ShapeVector::ShapeVector(const ShapeVector &sv):
    size_(sv.size_),
    capacity_(sv.capacity_),
    figures_(new IShape *[sv.capacity_])
{
  copyShapes(sv.figures_, figures_, size_);
}

ComFig::ShapeVector::ShapeVector(ShapeVector &&sv) noexcept:
    size_(sv.size_),
    capacity_(sv.capacity_),
    figures_(sv.figures_)
{
  sv.figures_ = nullptr;
  sv.capacity_ = 0;
  sv.size_ = 0;
}

ComFig::ShapeVector &ComFig::ShapeVector::operator=(const ShapeVector &sv)
{
  if (this == std::addressof(sv))
  {
    return *this;
  }
  IShape **newFigures = new IShape *[sv.capacity_];

  copyShapes(sv.figures_, newFigures, sv.size_);
  delete[] figures_;
  figures_ = newFigures;
  size_ = sv.size_;
  capacity_ = sv.capacity_;
  return *this;
}

ComFig::ShapeVector &ComFig::ShapeVector::operator=(ShapeVector &&sv) noexcept
{
  if (this == std::addressof(sv))
  {
    return *this;
  }
  std::swap(figures_, sv.figures_);
  std::swap(size_, sv.size_);
  std::swap(capacity_, sv.capacity_);
  return *this;
}

ComFig::ShapeVector::~ShapeVector()
{
  for (size_t i = 0; i < size_; i++)
  {
    delete figures_[i];
  }
  delete[] figures_;
}

size_t ComFig::ShapeVector::size() const noexcept
{
  return size_;
}

khasnulin::IShape *ComFig::ShapeVector::operator[](size_t index) const
{
  return figures_[index];
}

void ComFig::ShapeVector::append(IShape *figure)
{
  ensureCapacity(size_ + 1);
  figures_[size_++] = figure;
}

void ComFig::ShapeVector::preappend(IShape *figure)
{
  ensureCapacity(size_ + 1);
  ++size_;
  for (size_t i = size_ - 1; i > 0; --i)
  {
    figures_[i] = figures_[i - 1];
  }
  figures_[0] = figure;
}

void ComFig::ShapeVector::ensureCapacity(size_t newSize)
{
  size_t newCapacity = newSize > capacity_ * 2 ? newSize : capacity_ * 2;
  IShape **newFigures = new IShape *[newCapacity];
  copyShapes(figures_, newFigures, size_);
  delete[] figures_;
  capacity_ = newCapacity;
  figures_ = newFigures;
}