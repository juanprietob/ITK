/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkGrayscaleFunctionErodeImageFilter_h
#define itkGrayscaleFunctionErodeImageFilter_h

#include "itkMorphologyImageFilter.h"

namespace itk
{
/** \class GrayscaleFunctionErodeImageFilter
 * \brief gray scale function erosion of an image
 *
 * Erode an image using functional grayscale morphology. Function
 * erosion takes the minimum of all the pixels identified by the
 * structuring element minus the structuring element value.
 *
 * The structuring element can be composed of arbitrary nonnegative
 * values (not restricted to zero or one). Element values greater than
 * zero indicate pixels that will be considered during the dilation.
 * The function erosion operation is defined as the minimum over the
 * elements of the image value MINUS the structuring element value.
 *
 * For the each input image pixel,
 *   - NeighborhoodIterator gives neighbors of the pixel.
 *   - Evaluate() member function returns the minimum value among
 *     the image neighbors minus the kernel value where the kernel has
 *     elements > 0.
 *   - Replace the original value with the min value
 *
 * \sa MorphologyImageFilter, GrayscaleFunctionErodeImageFilter, BinaryErodeImageFilter
 * \ingroup ImageEnhancement  MathematicalMorphologyImageFilters
 * \ingroup ITKMathematicalMorphology
 */
template< typename TInputImage, typename TOutputImage, typename TKernel >
class GrayscaleFunctionErodeImageFilter:
  public MorphologyImageFilter< TInputImage, TOutputImage, TKernel >
{
public:
  /** Standard class typedefs. */
  typedef GrayscaleFunctionErodeImageFilter                           Self;
  typedef MorphologyImageFilter< TInputImage, TOutputImage, TKernel > Superclass;
  typedef SmartPointer< Self >                                        Pointer;
  typedef SmartPointer< const Self >                                  ConstPointer;

  /** Standard New method. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(GrayscaleFunctionErodeImageFilter,
               MorphologyImageFilter);

  /** Declaration of pixel type. */
  typedef typename Superclass::PixelType PixelType;

  /** Kernel (structuring element) iterator. */
  typedef typename Superclass::KernelIteratorType KernelIteratorType;

  /** Neighborhood iterator type. */
  typedef typename Superclass::NeighborhoodIteratorType NeighborhoodIteratorType;

  /** Kernel typedef. */
  typedef typename Superclass::KernelType KernelType;

  /** Default boundary condition type */
  typedef typename Superclass::DefaultBoundaryConditionType DefaultBoundaryConditionType;

  /** ImageDimension constants */
  itkStaticConstMacro(InputImageDimension, unsigned int,
                      TInputImage::ImageDimension);
  itkStaticConstMacro(OutputImageDimension, unsigned int,
                      TOutputImage::ImageDimension);
  itkStaticConstMacro(KernelDimension, unsigned int,
                      TKernel::NeighborhoodDimension);

  /** Type of the pixels in the Kernel. */
  typedef typename TKernel::PixelType KernelPixelType;

#ifdef ITK_USE_CONCEPT_CHECKING
  // Begin concept checking
  itkConceptMacro( SameDimensionCheck1,
                   ( Concept::SameDimension< InputImageDimension, OutputImageDimension > ) );
  itkConceptMacro( SameDimensionCheck2,
                   ( Concept::SameDimension< InputImageDimension, KernelDimension > ) );
  itkConceptMacro( InputConvertibleToOutputCheck,
                   ( Concept::Convertible< PixelType, typename TOutputImage::PixelType > ) );
  itkConceptMacro( KernelConvertibleToInputCheck,
                   ( Concept::Convertible< KernelPixelType, PixelType > ) );
  itkConceptMacro( InputAdditiveOperatorsCheck,
                   ( Concept::AdditiveOperators< PixelType > ) );
  itkConceptMacro( InputLessThanComparableCheck,
                   ( Concept::LessThanComparable< PixelType > ) );
  itkConceptMacro( KernelGreaterThanComparableCheck,
                   ( Concept::GreaterThanComparable< KernelPixelType > ) );
  // End concept checking
#endif

protected:
  GrayscaleFunctionErodeImageFilter();
  ~GrayscaleFunctionErodeImageFilter() {}

  /** Evaluate image neighborhood with kernel to find the new value
   * for the center pixel value
   *
   * It will return the minimum value of the image pixels minus the
   * structuring element values whose corresponding element in the
   * structuring element is positive. This version of Evaluate is used
   * for non-boundary pixels. */
  PixelType Evaluate(const NeighborhoodIteratorType & nit,
                     const KernelIteratorType kernelBegin,
                     const KernelIteratorType kernelEnd) ITK_OVERRIDE;

private:
  GrayscaleFunctionErodeImageFilter(const Self &) ITK_DELETE_FUNCTION;
  void operator=(const Self &) ITK_DELETE_FUNCTION;

  // Default boundary condition for erosion filter, defaults to
  // NumericTraits<PixelType>::max()
  DefaultBoundaryConditionType m_ErodeBoundaryCondition;
}; // end of class
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkGrayscaleFunctionErodeImageFilter.hxx"
#endif

#endif
