#include "composite_figure.hpp"

#include <algorithm>
#include <cstddef>
#include <stdexcept>

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
  clear();
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

void ComFig::ShapeVector::insert(IShape *figure, size_t pos)
{
  if (pos > size_)
  {
    throw std::out_of_range("trying to insert element over array boundary");
  }
  ensureCapacity(size_ + 1);
  for (size_t i = size_; i > pos; --i)
  {
    figures_[i] = figures_[i - 1];
  }
  figures_[pos] = figure;
  ++size_;
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

bool ComFig::ShapeVector::empty() const
{
  return !size_;
}

void ComFig::ShapeVector::erase(size_t pos)
{
  if (pos >= size_)
  {
    throw std::out_of_range("trying to delete element over array boundary");
  }
  delete figures_[pos];
  copyShapes(&figures_[pos + 1], &figures_[pos], size_ - pos - 1);
  figures_[size_ - 1] = nullptr;
  --size_;
}

void ComFig::ShapeVector::clear()
{
  for (size_t i = 0; i < size_; i++)
  {
    delete figures_[i];
  }
  size_ = 0;
}

void ComFig::ShapeVector::changeCapacity(size_t newCapacity)
{
  capacity_ = newCapacity > size_ ? newCapacity : size_;
}

size_t ComFig::ShapeVector::getCapacity() const
{
  return capacity_;
}

void ComFig::preappend(IShape *figure)
{
  figures.insert(figure, 0);
}

void ComFig::append(IShape *figure)
{
  figures.insert(figure, figures.size());
}

void ComFig::add(IShape *figure, size_t pos)
{
  figures.insert(figure, pos);
}

khasnulin::IShape &ComFig::last()
{
  if (figures.empty())
  {
    throw std::runtime_error("can't get last element, array is empty");
  }
  return *figures[figures.size() - 1];
}

khasnulin::IShape &ComFig::first()
{
  if (figures.empty())
  {
    throw std::runtime_error("can't get first element, array is empty");
  }
  return *figures[0];
}

const khasnulin::IShape &ComFig::last() const
{
  if (figures.empty())
  {
    throw std::runtime_error("can't get last element, array is empty");
  }
  return *figures[figures.size() - 1];
}

const khasnulin::IShape &ComFig::first() const
{
  if (figures.empty())
  {
    throw std::runtime_error("can't get first element, array is empty");
  }
  return *figures[0];
}

khasnulin::IShape &ComFig::at(size_t index)
{
  if (index >= figures.size())
  {
    throw std::out_of_range("index out of array boundaries");
  }
  return *figures[index];
}

khasnulin::IShape &ComFig::get(size_t index)
{
  return *figures[index];
}

const khasnulin::IShape &ComFig::at(size_t index) const
{
  if (index >= figures.size())
  {
    throw std::out_of_range("index out of array boundaries");
  }
  return *figures[index];
}

const khasnulin::IShape &ComFig::get(size_t index) const
{
  return *figures[index];
}

void ComFig::remove(size_t index)
{
  figures.erase(index);
}

void ComFig::dropFirst()
{
  figures.erase(0);
}

void ComFig::dropLast()
{
  figures.erase(figures.size() > 0 ? figures.size() - 1 : 0);
}

void ComFig::clear()
{
  figures.clear();
}

size_t ComFig::size() const
{
  return figures.size();
}

bool ComFig::empty() const
{
  return figures.empty();
}

void ComFig::reserve(size_t newCapacity)
{
  figures.changeCapacity(newCapacity);
}

void ComFig::shrink()
{
  figures.changeCapacity(figures.size());
}

size_t ComFig::capacity() const
{
  return figures.getCapacity();
}