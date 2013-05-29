//=================================================================================================
// Copyright 2013 Dirk Lemstra <http://magick.codeplex.com/>
//
// Licensed under the ImageMagick License (the "License"); you may not use this file except in 
// compliance with the License. You may obtain a copy of the License at
//
//   http://www.imagemagick.org/script/license.php
//
// Unless required by applicable law or agreed to in writing, software distributed under the
// License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
// express or implied. See the License for the specific language governing permissions and
// limitations under the License.
//=================================================================================================
#pragma once

#include "Base\MagickWrapper.h"
#include "Colors\MagickColor.h"
#include "Drawables\DrawableAffine.h"
#include "Drawables\Base\DrawableBase.h"
#include "Enums\Channels.h"
#include "Enums\ClassType.h"
#include "Enums\ColorSpace.h"
#include "Enums\ColorType.h"
#include "Enums\CompositeOperator.h"
#include "Enums\DistortMethod.h"
#include "Enums\Endian.h"
#include "Enums\EvaluateOperator.h"
#include "Enums\FillRule.h"
#include "Enums\FilterType.h"
#include "Enums\GifDisposeMethod.h"
#include "Enums\Gravity.h"
#include "Enums\MagickFormat.h"
#include "Enums\NoiseType.h"
#include "Enums\OrientationType.h"
#include "Enums\PaintMethod.h"
#include "Enums\Resolution.h"
#include "Enums\RenderingIntent.h"
#include "Enums\SparseColorMethod.h"
#include "Enums\VirtualPixelMethod.h"
#include "Exceptions\Base\MagickException.h"
#include "Helpers\EnumHelper.h"
#include "Helpers\MagickErrorInfo.h"
#include "Helpers\MagickReader.h"
#include "Helpers\MagickReadSettings.h"
#include "Helpers\MagickWriter.h"
#include "Helpers\Percentage.h"
#include "Helpers\TypeMetric.h"
#include "MagickGeometry.h"
#include "MagickImageStatistics.h"
#include "Matrices\MatrixColor.h"
#include "Matrices\MatrixConvolve.h"
#include "Pixels\PixelCollection.h"
#include "Pixels\WritablePixelCollection.h"

using namespace System::Collections::Generic;
using namespace System::Drawing::Imaging;
using namespace System::Text;

namespace ImageMagick
{
	///=============================================================================================
	///<summary>
	/// Encapsulation of the ImageMagick image object.
	///</summary>
	public ref class MagickImage sealed : MagickWrapper<Magick::Image>,
		IEquatable<MagickImage^>, IComparable<MagickImage^>
	{
		//===========================================================================================
	private:
		//===========================================================================================
		static initonly MagickGeometry^ _DefaultFrameGeometry = gcnew MagickGeometry(25, 25, 6, 6);
		MagickWarningException^ _ReadWarning;
		//===========================================================================================
		String^ FormatedFileSize();
		//===========================================================================================
		static bool IsSupportedImageFormat(ImageFormat^ format);
		//===========================================================================================
		void RaiseOrLower(int size, bool raiseFlag);
		//===========================================================================================
		void RandomThreshold(Magick::Quantum low, Magick::Quantum high, bool isPercentage);
		//===========================================================================================
		void RandomThreshold(Magick::Quantum low, Magick::Quantum high, Channels channels, bool isPercentage);
		//===========================================================================================
		void Resize(int width, int height, bool isPercentage);
		//===========================================================================================
		void Sample(int width, int height, bool isPercentage);
		//===========================================================================================
		void Scale(int width, int height, bool isPercentage);
		//===========================================================================================
		void SetFormat(ImageFormat^ format);
		//===========================================================================================
		void SetProfile(String^ name, Magick::Blob &blob);
		//===========================================================================================
		void Zoom(int width, int height, bool isPercentage);
		//===========================================================================================
	internal:
		//===========================================================================================
		MagickImage(const Magick::Image& image);
		//===========================================================================================
		Magick::Image* ReuseImage();
		//===========================================================================================
	public:
		///==========================================================================================
		///<summary>
		/// Initializes a new instance of the MagickImage class.
		///</summary>
		MagickImage();
		///==========================================================================================
		///<summary>
		/// Initializes a new instance of the MagickImage class using the specified byte array.
		///</summary>
		///<param name="data">The byte array to read the image data from.</param>
		///<exception cref="MagickException"/>
		MagickImage(array<Byte>^ data);
		///==========================================================================================
		///<summary>
		/// Initializes a new instance of the MagickImage class using the specified byte array.
		///</summary>
		///<param name="data">The byte array to read the image data from.</param>
		///<param name="readSettings">The settings to use when reading the image.</param>
		///<exception cref="MagickException"/>
		MagickImage(array<Byte>^ data, MagickReadSettings^ readSettings);
		///==========================================================================================
		///<summary>
		/// Initializes a new instance of the MagickImage class using the specified bitmap.
		///</summary>
		///<param name="bitmap">The bitmap to use.</param>
		///<exception cref="MagickException"/>
		MagickImage(Bitmap^ bitmap);
		///==========================================================================================
		///<summary>
		/// Initializes a new instance of the MagickImage class using the specified width, height
		/// and color.
		///</summary>
		///<param name="color">The color to fill the image with.</param>
		///<param name="width">The width.</param>
		///<param name="height">The height.</param>
		MagickImage(MagickColor^ color, int width, int height);
		///==========================================================================================
		///<summary>
		/// Initializes a new instance of the MagickImage class using the specified filename.
		///</summary>
		///<param name="fileName">The fully qualified name of the image file, or the relative image file name.</param>
		///<exception cref="MagickException"/>
		MagickImage(String^ fileName);
		///==========================================================================================
		///<summary>
		/// Initializes a new instance of the MagickImage class using the specified filename
		///</summary>
		///<param name="fileName">The fully qualified name of the image file, or the relative image file name.</param>
		///<param name="readSettings">The settings to use when reading the image.</param>
		///<exception cref="MagickException"/>
		MagickImage(String^ fileName, MagickReadSettings^ readSettings);
		///==========================================================================================
		///<summary>
		/// Initializes a new instance of the MagickImage class using the specified stream.
		///</summary>
		///<param name="stream">The stream to read the image data from.</param>
		///<exception cref="MagickException"/>
		MagickImage(Stream^ stream);
		///==========================================================================================
		///<summary>
		/// Initializes a new instance of the MagickImage class using the specified stream.
		///</summary>
		///<param name="stream">The stream to read the image data from.</param>
		///<param name="readSettings">The settings to use when reading the image.</param>
		///<exception cref="MagickException"/>
		MagickImage(Stream^ stream, MagickReadSettings^ readSettings);
		///==========================================================================================
		///<summary>
		/// Join images into a single multi-image file.
		///</summary>
		property bool Adjoin
		{
			bool get()
			{
				return Value->adjoin();
			}
			void set(bool value)
			{
				Value->adjoin(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Time in 1/100ths of a second which must expire before splaying the next image in an
		/// animated sequence.
		///</summary>
		property int AnimationDelay
		{
			int get()
			{
				return Convert::ToInt32(Value->animationDelay());
			}
			void set(int value)
			{
				Value->animationDelay(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Number of iterations to loop an animation (e.g. Netscape loop extension) for.
		///</summary>
		property int AnimationIterations
		{
			int get()
			{
				return Convert::ToInt32(Value->animationIterations());
			}
			void set(int value)
			{
				Value->animationIterations(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Anti-alias Postscript and TrueType fonts (default true).
		///</summary>
		property bool AntiAlias
		{
			bool get()
			{
				return Value->antiAlias();
			}
			void set(bool value)
			{
				Value->antiAlias(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Background color of the image.
		///</summary>
		property MagickColor^ BackgroundColor
		{
			MagickColor^ get()
			{
				return gcnew MagickColor(Value->backgroundColor());
			}
			void set(MagickColor^ value)
			{
				Magick::Color* color = ReferenceEquals(value, nullptr) ? new Magick::Color() : value->CreateColor();
				Value->backgroundColor(*color);
				delete color;
			}
		}
		///==========================================================================================
		///<summary>
		/// Height of the image before transformations.
		///</summary>
		property int BaseHeight
		{
			int get()
			{
				return Convert::ToInt32(Value->baseRows());
			}
		}
		///==========================================================================================
		///<summary>
		/// Width of the image before transformations.
		///</summary>
		property int BaseWidth
		{
			int get()
			{
				return Convert::ToInt32(Value->baseColumns());
			}
		}
		///==========================================================================================
		///<summary>
		/// Return smallest bounding box enclosing non-border pixels. The current fuzz value is used
		/// when discriminating between pixels.
		///</summary>
		property MagickGeometry^ BoundingBox
		{
			MagickGeometry^ get()
			{
				return gcnew MagickGeometry(Value->boundingBox());
			}
		}
		///==========================================================================================
		///<summary>
		/// Border color of the image.
		///</summary>
		property MagickColor^ BorderColor
		{
			MagickColor^ get()
			{
				return gcnew MagickColor(Value->borderColor());
			}
			void set(MagickColor^ value)
			{
				Magick::Color* color = ReferenceEquals(value, nullptr) ? new Magick::Color() : value->CreateColor();
				Value->borderColor(*color);
				delete color;
			}
		}
		///==========================================================================================
		///<summary>
		/// Image class (DirectClass or PseudoClass)
		/// NOTE: Setting a DirectClass image to PseudoClass will result in the loss of color information
		/// if the number of colors in the image is greater than the maximum palette size (either 256 (Q8)
		/// or 65536 (Q16).
		///</summary>
		property ClassType ClassType
		{
			ImageMagick::ClassType get()
			{
				return (ImageMagick::ClassType)Value->classType();
			}
			void set(ImageMagick::ClassType value)
			{
				return Value->classType((MagickCore::ClassType)value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Associate a clip mask with the image. The clip mask must be the same dimensions as the
		/// image. Pass null to unset an existing clip mask.
		///</summary>
		property MagickImage^ ClipMask
		{
			MagickImage^ get()
			{
				return gcnew MagickImage(Magick::Image(Value->clipMask()));
			}
			void set(MagickImage^ value)
			{
				if (value == nullptr)
				{
					Magick::Image* image = new Magick::Image();
					Value->clipMask(*image);
					delete image;
				}
				else
				{
					Value->clipMask(*value->Value);
				}
			}
		}
		///==========================================================================================
		///<summary>
		/// Colors within this distance are considered equal.
		///</summary>
		property double ColorFuzz
		{
			double get()
			{
				return Value->colorFuzz();
			}
			Void set(double value)
			{
				Value->colorFuzz(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Colormap size (number of colormap entries).
		///</summary>
		property int ColorMapSize
		{
			int get()
			{
				return Convert::ToInt32(Value->colorMapSize());
			}
			void set(int value)
			{
				Value->colorMapSize(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Color space of the image.
		///</summary>
		property ColorSpace ColorSpace
		{
			ImageMagick::ColorSpace get()
			{
				return (ImageMagick::ColorSpace)Value->colorSpace();
			}
			void set(ImageMagick::ColorSpace value)
			{
				return Value->colorSpace((MagickCore::ColorspaceType)value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Color type of the image.
		///</summary>
		property ColorType ColorType
		{
			ImageMagick::ColorType get()
			{
				return (ImageMagick::ColorType)Value->type();
			}
			void set(ImageMagick::ColorType value)
			{
				return Value->type((MagickCore::ImageType)value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Comment text of the image.
		///</summary>
		property String^ Comment
		{
			String^ get()
			{
				return Marshaller::Marshal(Value->comment());
			}
			void set(String^ value)
			{
				std::string comment; 
				Value->comment(Marshaller::Marshal(value, comment));
			}
		}
		///==========================================================================================
		///<summary>
		/// Composition operator to be used when composition is implicitly used (such as for image flattening).
		///</summary>
		property CompositeOperator Compose
		{
			CompositeOperator get()
			{
				return (CompositeOperator)Value->compose();
			}
			void set(CompositeOperator value)
			{
				Value->compose((Magick::CompositeOperator)value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Vertical and horizontal resolution in pixels of the image.
		///</summary>
		property MagickGeometry^ Density
		{
			MagickGeometry^ get()
			{
				return gcnew MagickGeometry(Value->density());
			}
			void set(MagickGeometry^ value)
			{
				if (value == nullptr)
					return;

				Value->density(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Endianness (little like Intel or big like SPARC) for image formats which support
		/// endian-specific options.
		///</summary>
		//===========================================================================================
		property Endian Endian
		{
			ImageMagick::Endian get()
			{
				return (ImageMagick::Endian)Value->endian();
			}
			void set(ImageMagick::Endian value)
			{
				Value->endian((MagickCore::EndianType)value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Image file size.
		///</summary>
		property int FileSize
		{
			int get()
			{
				return Value->fileSize();
			}
		}
		///==========================================================================================
		///<summary>
		/// Original file name of the image (only available if read from disk).
		///</summary>
		property String^ FileName
		{
			String^ get()
			{
				return Marshaller::Marshal(Value->baseFilename());
			}
		}
		///==========================================================================================
		///<summary>
		/// Color to use when drawing inside an object.
		///</summary>
		property MagickColor^ FillColor
		{
			MagickColor^ get()
			{
				return gcnew MagickColor(Value->fillColor());
			}
			void set(MagickColor^ value)
			{
				Magick::Color* color = ReferenceEquals(value, nullptr) ? new Magick::Color() : value->CreateColor();
				Value->fillColor(*color);
				delete color;
			}
		}
		///==========================================================================================
		///<summary>
		/// Pattern to use while filling drawn objects.
		///</summary>
		property MagickImage^ FillPattern
		{
			MagickImage^ get()
			{
				return gcnew MagickImage(Magick::Image(Value->fillPattern()));
			}
			void set(MagickImage^ value)
			{
				if (value == nullptr)
				{
					Magick::Image* image = new Magick::Image();
					Value->fillPattern(*image);
					delete image;
				}
				else
				{
					Value->fillPattern(*value->Value);
				}
			}
		}
		///==========================================================================================
		///<summary>
		/// Rule to use when filling drawn objects.
		///</summary>
		property FillRule FillRule
		{
			ImageMagick::FillRule get()
			{
				return (ImageMagick::FillRule)Value->fillRule();
			}
			void set(ImageMagick::FillRule value)
			{
				Value->fillRule((Magick::FillRule)value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Filter to use when resizing image.
		///</summary>
		property FilterType FilterType
		{
			ImageMagick::FilterType get()
			{
				return (ImageMagick::FilterType)Value->filterType();
			}
			void set(ImageMagick::FilterType value)
			{
				Value->filterType((Magick::FilterTypes)value);
			}
		}
		///==========================================================================================
		///<summary>
		/// FlashPix viewing parameters.
		///</summary>
		property String^ FlashPixView
		{
			String^ get()
			{
				return Marshaller::Marshal(Value->view());
			}
			void set(String^ value)
			{
				std::string view;
				Value->view(Marshaller::Marshal(value, view));
			}
		}
		///==========================================================================================
		///<summary>
		/// Text rendering font.
		///</summary>
		property String^ Font
		{
			String^ get()
			{
				return Marshaller::Marshal(Value->font());
			}
			void set(String^ value)
			{
				std::string font;
				Value->font(Marshaller::Marshal(value, font));
			}
		}
		///==========================================================================================
		///<summary>
		/// Font point size.
		///</summary>
		property double FontPointsize
		{
			double get()
			{
				return Value->fontPointsize();
			}
			void set(double value)
			{
				Value->fontPointsize(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// The format of the image.
		///</summary>
		property MagickFormat Format
		{
			MagickFormat get()
			{
				return EnumHelper::Parse<MagickFormat>(Marshaller::Marshal(Value->magick()), MagickFormat::Unknown);
			}
			void set(MagickFormat value)
			{
				if (value == MagickFormat::Unknown)
					return;

				std::string name;

				Marshaller::Marshal(Enum::GetName(value.GetType(), value), name);
				Value->magick(name);
			}
		}
		///==========================================================================================
		///<summary>
		/// Gif disposal method.
		///</summary>
		property GifDisposeMethod GifDisposeMethod
		{
			ImageMagick::GifDisposeMethod get()
			{
				return (ImageMagick::GifDisposeMethod)Value->gifDisposeMethod();
			}
			void set(ImageMagick::GifDisposeMethod value)
			{
				Value->gifDisposeMethod((int)value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Image supports transparency (matte channel).
		///</summary>
		property bool HasMatte
		{
			bool get()
			{
				return Value->matte();
			}
			void set(bool value)
			{
				Value->matte(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Height of the image.
		///</summary>
		property int Height
		{
			int get()
			{
				return Convert::ToInt32(Value->size().height());
			}
		}
		///==========================================================================================
		///<summary>
		/// Transform image to black and white.
		///</summary>
		property bool IsMonochrome
		{
			bool get()
			{
				return Value->monochrome();
			}
			void set(bool value)
			{
				return Value->monochrome(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// The label of the image.
		///</summary>
		property String^ Label
		{
			String^ get()
			{
				std::string label = Value->label();
				if (label.length() == 0)
					return nullptr;

				return Marshaller::Marshal(label);
			}
			void set(String^ value)
			{
				if (value == nullptr)
					value = "";

				std::string label;
				Marshaller::Marshal(value, label);
				Value->label(label);
			}
		}
		///==========================================================================================
		///<summary>
		/// Transparent color.
		///</summary>
		property MagickColor^ MatteColor
		{
			MagickColor^ get()
			{
				return gcnew MagickColor(Value->matteColor());
			}
			void set(MagickColor^ value)
			{
				Magick::Color* color = ReferenceEquals(value, nullptr) ? new Magick::Color() : value->CreateColor();
				Value->matteColor(*color);
				delete color;
			}
		}
		///==========================================================================================
		///<summary>
		/// Image modulus depth (minimum number of bits required to support red/green/blue components
		/// without loss of accuracy).
		///</summary>
		property int ModulusDepth
		{
			int get()
			{
				return Convert::ToInt32(Value->modulusDepth());
			}
			void set(int value)
			{
				Value->modulusDepth(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Photo orientation of the image.
		///</summary>
		property OrientationType Orientation
		{
			OrientationType get()
			{
				return (OrientationType)Value->orientation();
			}
			void set(OrientationType value)
			{
				Value->orientation((Magick::OrientationType)value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Preferred size and location of an image canvas.
		///</summary>
		property MagickGeometry^ Page
		{
			MagickGeometry^ get()
			{
				return gcnew MagickGeometry(Value->page());
			}
			void set(MagickGeometry^ value)
			{
				Value->page(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// JPEG/MIFF/PNG compression level (default 75).
		///</summary>
		property int Quality
		{
			int get()
			{
				return Convert::ToInt32(Value->quality());
			}
			void set(int value)
			{
				int quality = value < 1 ? 1 : value;
				quality = quality > 100 ? 100 : quality;

				Value->quality(quality);
			}
		}
		///==========================================================================================
		///<summary>
		/// Maximum number of colors to quantize to.
		///</summary>
		property int QuantizeColors
		{
			int get()
			{
				return Convert::ToInt32(Value->quantizeColors());
			}
			void set(int value)
			{
				Value->quantizeColors(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Colorspace to quantize in.
		///</summary>
		property ImageMagick::ColorSpace QuantizeColorSpace
		{
			ImageMagick::ColorSpace get()
			{
				return (ImageMagick::ColorSpace)Value->quantizeColorSpace();
			}
			void set(ImageMagick::ColorSpace value)
			{
				return Value->quantizeColorSpace((MagickCore::ColorspaceType)value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Dither image during quantization (default true).
		///</summary>
		property bool QuantizeDither
		{
			bool get()
			{
				return Value->quantizeDither();
			}
			void set(bool value)
			{
				Value->quantizeDither(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Quantization tree-depth.
		///</summary>
		property int QuantizeTreeDepth
		{
			int get()
			{
				return Convert::ToInt32(Value->quantizeTreeDepth());
			}
			void set(int value)
			{
				Value->quantizeTreeDepth(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Returns the warning that was raised during the read operation.
		///</summary>
		property MagickWarningException^ ReadWarning
		{
			MagickWarningException^ get()
			{
				return _ReadWarning;
			}
		}
		///==========================================================================================
		///<summary>
		/// The type of rendering intent.
		///</summary>
		property RenderingIntent RenderingIntent
		{
			ImageMagick::RenderingIntent get()
			{
				return (ImageMagick::RenderingIntent)Value->renderingIntent();
			}
			void set(ImageMagick::RenderingIntent value)
			{
				return Value->renderingIntent((MagickCore::RenderingIntent)value);
			}
		} 
		///==========================================================================================
		///<summary>
		/// Units of image resolution.
		///</summary>
		property Resolution ResolutionUnits
		{
			Resolution get()
			{
				return (Resolution)Value->resolutionUnits();
			}
			void set(Resolution value)
			{
				return Value->resolutionUnits((MagickCore::ResolutionType)value);
			}
		}
		///==========================================================================================
		///<summary>
		/// The X resolution of the image.
		///</summary>
		property double ResolutionX
		{
			double get()
			{
				return Value->xResolution();
			}
		}
		///==========================================================================================
		///<summary>
		/// The Y resolution of the image.
		///</summary>
		property double ResolutionY
		{
			double get()
			{
				return Value->yResolution();
			}
		}
		///==========================================================================================
		///<summary>
		/// Enabled/disable stroke anti-aliasing.
		///</summary>
		property bool StrokeAntiAlias
		{
			bool get()
			{
				return Value->strokeAntiAlias();
			}
			void set(bool value)
			{
				Value->strokeAntiAlias(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Color to use when drawing object outlines.
		///</summary>
		property MagickColor^ StrokeColor
		{
			MagickColor^ get()
			{
				return gcnew MagickColor(Value->strokeColor());
			}
			void set(MagickColor^ value)
			{
				Magick::Color* color = ReferenceEquals(value, nullptr) ? new Magick::Color() : value->CreateColor();
				Value->strokeColor(*color);
				delete color;
			}
		}
		///==========================================================================================
		///<summary>
		/// Specify the pattern of dashes and gaps used to stroke paths. This represents a
		/// zero-terminated array of numbers that specify the lengths of alternating dashes and gaps
		/// in pixels. If a zero value is not found it will be added. If an odd number of values is
		/// provided, then the list of values is repeated to yield an even number of values.
		///</summary>
		property array<double>^ StrokeDashArray
		{
			array<double>^ get()
			{
				const double* strokeDashArray = Value->strokeDashArray();
				if (strokeDashArray == NULL)
					return nullptr;

				return Marshaller::Marshal(strokeDashArray);
			}
			void set(array<double>^ value)
			{
				double* strokeDashArray = Marshaller::MarshalAndTerminate(value);
				Value->strokeDashArray(strokeDashArray);
				delete[] strokeDashArray;
			}
		}
		///==========================================================================================
		///<summary>
		/// While drawing using a dash pattern, specify distance into the dash pattern to start the
		/// dash (default 0).
		///</summary>
		property double StrokeDashOffset
		{
			double get()
			{
				return Value->strokeDashOffset();
			}
			void set(double value)
			{
				Value->strokeDashOffset(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Specify the shape to be used at the end of open subpaths when they are stroked.
		///</summary>
		property LineCap StrokeLineCap
		{
			LineCap get()
			{
				return (LineCap)Value->strokeLineCap();
			}
			void set(LineCap value)
			{
				Value->strokeLineCap((MagickCore::LineCap)value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Specify the shape to be used at the corners of paths (or other vector shapes) when they
		/// are stroked.
		///</summary>
		property LineJoin StrokeLineJoin
		{
			LineJoin get()
			{
				return (LineJoin)Value->strokeLineJoin();
			}
			void set(LineJoin value)
			{
				Value->strokeLineJoin((MagickCore::LineJoin)value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Specify miter limit. When two line segments meet at a sharp angle and miter joins have
		/// been specified for 'lineJoin', it is possible for the miter to extend far beyond the thickness
		/// of the line stroking the path. The miterLimit' imposes a limit on the ratio of the miter
		/// length to the 'lineWidth'. The default value is 4.
		///</summary>
		property int StrokeMiterLimit
		{
			int get()
			{
				return Convert::ToInt32(Value->strokeMiterLimit());
			}
			void set(int value)
			{
				Value->strokeMiterLimit(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Pattern image to use while stroking object outlines.
		///</summary>
		property MagickImage^ StrokePattern
		{
			MagickImage^ get()
			{
				Magick::Image value = Value->strokePattern();
				if (value == NULL)
					return nullptr;

				return gcnew MagickImage(value);
			}
			void set(MagickImage^ value)
			{
				if (value == nullptr)
					Value->strokePattern(Magick::Image());
				else
					Value->strokePattern(*value->Value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Stroke width for drawing lines, circles, ellipses, etc.
		///</summary>
		property double StrokeWidth
		{
			double get()
			{
				return Value->strokeWidth();
			}
			void set(double value)
			{
				Value->strokeWidth(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Annotation text encoding (e.g. "UTF-16")
		///</summary>
		property Encoding^ TextEncoding
		{
			Encoding^ get()
			{
				String^ encoding = Marshaller::Marshal(Value->textEncoding());

				if (String::IsNullOrEmpty(encoding))
					return nullptr;

				try
				{
					return Encoding::GetEncoding(encoding);
				}
				catch (ArgumentException^)
				{
					return nullptr;
				}
			}
			void set(Encoding^ value)
			{
				String^ name = value != nullptr ? value->WebName : nullptr;

				std::string encoding;
				Value->textEncoding(Marshaller::Marshal(name, encoding));
			}
		}
		///==========================================================================================
		///<summary>
		/// Tile name.
		///</summary>
		property String^ TileName
		{
			String^ get()
			{
				return Marshaller::Marshal(Value->tileName());
			}
			void set(String^ value)
			{
				std::string tileName;
				Value->tileName(Marshaller::Marshal(value, tileName));
			}
		}
		///==========================================================================================
		///<summary>
		/// Number of colors in the image.
		///</summary>
		property int TotalColors
		{
			int get()
			{
				return Convert::ToInt32(Value->totalColors());
			}
		}
		///==========================================================================================
		///<summary>
		/// Turn verbose output on/off.
		///</summary>
		///==========================================================================================
		property bool Verbose 
		{
			bool get() 
			{
				return Value->verbose();
			}
			void set(bool verbose) 
			{
				return Value->verbose(verbose);
			}
		}
		///==========================================================================================
		///<summary>
		/// Virtual pixel method.
		///</summary>
		property VirtualPixelMethod VirtualPixelMethod
		{
			ImageMagick::VirtualPixelMethod get()
			{
				return (ImageMagick::VirtualPixelMethod)Value->virtualPixelMethod();
			}
			void set(ImageMagick::VirtualPixelMethod value)
			{
				Value->virtualPixelMethod((MagickCore::VirtualPixelMethod)value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Width of the image.
		///</summary>
		property int Width
		{
			int get()
			{
				return Convert::ToInt32(Value->size().width());
			}
		}
		//===========================================================================================
		static bool operator == (MagickImage^ left, MagickImage^ right)
		{
			return Object::Equals(left, right);
		}
		//===========================================================================================
		static bool operator != (MagickImage^ left, MagickImage^ right)
		{
			return !Object::Equals(left, right);
		}
		//===========================================================================================
		static bool operator > (MagickImage^ left, MagickImage^ right)
		{
			if (ReferenceEquals(left, nullptr))
				return ReferenceEquals(right, nullptr);

			return left->CompareTo(right) == 1;
		}
		//===========================================================================================
		static bool operator < (MagickImage^ left, MagickImage^ right)
		{
			if (ReferenceEquals(left, nullptr))
				return !ReferenceEquals(right, nullptr);

			return left->CompareTo(right) == -1;
		}
		//===========================================================================================
		static bool operator >= (MagickImage^ left, MagickImage^ right)
		{
			if (ReferenceEquals(left, nullptr))
				return ReferenceEquals(right, nullptr);

			return left->CompareTo(right) >= 0;
		}
		//===========================================================================================
		static bool operator <= (MagickImage^ left, MagickImage^ right)
		{
			if (ReferenceEquals(left, nullptr))
				return !ReferenceEquals(right, nullptr);

			return left->CompareTo(right) <= 0;
		}
		//===========================================================================================
		static explicit operator array<Byte>^ (MagickImage^ image)
		{
			Throw::IfNull("image", image);

			return image->ToByteArray();
		}
		///==========================================================================================
		///<summary>
		/// Adaptive-blur image with the default blur factor (0x1).
		///</summary>
		///<exception cref="MagickException"/>
		void AdaptiveBlur();
		///==========================================================================================
		///<summary>
		/// Adaptive-blur image with specified blur factor.
		///</summary>
		///<param name="radius">The radius of the Gaussian, in pixels, not counting the center pixel.</param>
		///<param name="sigma">The standard deviation of the Laplacian, in pixels.</param>
		///<exception cref="MagickException"/>
		void AdaptiveBlur(double radius, double sigma);
		///==========================================================================================
		///<summary>
		/// Local adaptive threshold image.
		/// http://www.dai.ed.ac.uk/HIPR2/adpthrsh.htm
		///</summary>
		///<param name="width">The width of the pixel neighborhood.</param>
		///<param name="height">The height of the pixel neighborhood.</param>
		///<exception cref="MagickException"/>
		void AdaptiveThreshold(int width, int height);
		///==========================================================================================
		///<summary>
		/// Local adaptive threshold image.
		/// http://www.dai.ed.ac.uk/HIPR2/adpthrsh.htm
		///</summary>
		///<param name="width">The width of the pixel neighborhood.</param>
		///<param name="height">The height of the pixel neighborhood.</param>
		///<param name="offset">Constant to subtract from pixel neighborhood mean.</param>
		///<exception cref="MagickException"/>
		void AdaptiveThreshold(int width, int height, int offset);
		///==========================================================================================
		///<summary>
		/// Add noise to image with the specified noise type.
		///</summary>
		///<param name="noiseType">The type of noise that should be added to the image.</param>
		///<exception cref="MagickException"/>
		void AddNoise(NoiseType noiseType);
		///==========================================================================================
		///<summary>
		/// Add noise to the specified channel of the image with the specified noise type.
		///</summary>
		///<param name="noiseType">The type of noise that should be added to the image.</param>
		///<param name="channels">The channel(s) where the noise should be added.</param>
		///<exception cref="MagickException"/>
		void AddNoise(NoiseType noiseType, Channels channels);
		///==========================================================================================
		///<summary>
		/// Add an ICC iCM profile to an image.
		///</summary>
		///<param name="data">A byte array containing the profile.</param>
		///<exception cref="MagickException"/>
		void AddProfile(array<Byte>^ data);
		///==========================================================================================
		///<summary>
		/// Add a profile to an image.
		///</summary>
		///<param name="profile">The profile.</param>
		///<exception cref="MagickException"/>
		void AddProfile(ColorProfile^ profile);
		///==========================================================================================
		///<summary>
		/// Add an ICC iCM profile to an image.
		///</summary>
		///<param name="stream">A stream containing the profile.</param>
		///<exception cref="MagickException"/>
		void AddProfile(Stream^ stream);
		///==========================================================================================
		///<summary>
		/// Add an ICC iCM profile to an image.
		///</summary>
		///<param name="fileName">The file to read the profile from.</param>
		///<exception cref="MagickException"/>
		void AddProfile(String^ fileName);
		///==========================================================================================
		///<summary>
		/// Add a named profile to an image.
		///</summary>
		///<param name="name">The name of the profile (e.g. "ICM", "IPTC", or a generic profile name).</param>
		///<param name="data">A byte array containing the profile.</param>
		///<exception cref="MagickException"/>
		void AddProfile(String^ name, array<Byte>^ data);
		///==========================================================================================
		///<summary>
		/// Add a named profile to an image.
		///</summary>
		///<param name="name">The name of the profile (e.g. "ICM", "IPTC", or a generic profile name).</param>
		///<param name="stream">A stream containing the profile.</param>
		///<exception cref="MagickException"/>
		void AddProfile(String^ name, Stream^ stream);
		///==========================================================================================
		///<summary>
		/// Add a named profile to an image.
		///</summary>
		///<param name="name">The name of the profile (e.g. "ICM", "IPTC", or a generic profile name).</param>
		///<param name="fileName">The file to read the profile from.</param>
		///<exception cref="MagickException"/>
		void AddProfile(String^ name, String^ fileName);
		///==========================================================================================
		///<summary>
		/// Affine Transform image.
		///</summary>
		///<param name="affineMatrix">The affine matrix to use.</param>
		///<exception cref="MagickException"/>
		void AffineTransform(DrawableAffine^ affineMatrix);
		///==========================================================================================
		///<summary>
		/// Annotate using specified text, and bounding area.
		///</summary>
		///<param name="text">The text to use.</param>
		///<param name="boundingArea">The bounding area.</param>
		///<exception cref="MagickException"/>
		void Annotate(String^ text, MagickGeometry^ boundingArea);
		///==========================================================================================
		///<summary>
		/// Annotate using specified text, bounding area, and placement gravity.
		///</summary>
		///<param name="text">The text to use.</param>
		///<param name="boundingArea">The bounding area.</param>
		///<param name="gravity">The placement gravity.</param>
		///<exception cref="MagickException"/>
		void Annotate(String^ text, MagickGeometry^ boundingArea, Gravity gravity);
		///==========================================================================================
		///<summary>
		/// Annotate using specified text, bounding area, and placement gravity.
		///</summary>
		///<param name="text">The text to use.</param>
		///<param name="boundingArea">The bounding area.</param>
		///<param name="gravity">The placement gravity.</param>
		///<param name="degrees">The rotation.</param>
		///<exception cref="MagickException"/>
		void Annotate(String^ text, MagickGeometry^ boundingArea, Gravity gravity, double degrees);
		///==========================================================================================
		///<summary>
		/// Annotate with text (bounding area is entire image) and placement gravity.
		///</summary>
		///<param name="text">The text to use.</param>
		///<param name="gravity">The placement gravity.</param>
		///<exception cref="MagickException"/>
		void Annotate(String^ text, Gravity gravity);
		///==========================================================================================
		///<summary>
		/// Returns the value of a named image attribute.
		///</summary>
		///<param name="name">The name of the attribute.</param>
		String^ Attribute(String^ name);
		///==========================================================================================
		///<summary>
		/// Sets a named image attribute.
		///</summary>
		///<param name="name">The name of the attribute.</param>
		///<param name="value">The value of the attribute.</param>
		void Attribute(String^ name, String^ value);
		///==========================================================================================
		///<summary>
		/// Blur image with the default blur factor (0x1).
		///</summary>
		///<exception cref="MagickException"/>
		void Blur();
		///==========================================================================================
		///<summary>
		/// Blur image the specified channel of the image with the default blur factor (0x1).
		///</summary>
		///<param name="channels">The channel(s) that should be blurred.</param>
		///<exception cref="MagickException"/>
		void Blur(Channels channels);
		///==========================================================================================
		///<summary>
		/// Blur image with specified blur factor.
		///</summary>
		///<param name="radius">The radius of the Gaussian in pixels, not counting the center pixel.</param>
		///<param name="sigma">The standard deviation of the Laplacian, in pixels.</param>
		///<exception cref="MagickException"/>
		void Blur(double radius, double sigma);
		///==========================================================================================
		///<summary>
		/// Blur image with specified blur factor and channel.
		///</summary>
		///<param name="radius">The radius of the Gaussian in pixels, not counting the center pixel.</param>
		///<param name="sigma">The standard deviation of the Laplacian, in pixels.</param>
		///<param name="channels">The channel(s) that should be blurred.</param>
		///<exception cref="MagickException"/>
		void Blur(double radius, double sigma, Channels channels);
		///==========================================================================================
		///<summary>
		/// Border image (add border to image).
		///</summary>
		///<param name="size">The size of the border.</param>
		///<exception cref="MagickException"/>
		void Border(int size);
		///==========================================================================================
		///<summary>
		/// Border image (add border to image).
		///</summary>
		///<param name="width">The width of the border.</param>
		///<param name="height">The height of the border.</param>
		///<exception cref="MagickException"/>
		void Border(int width, int height);
		///==========================================================================================
		///<summary>
		/// Applies the color decision list from the specified ASC CDL file.
		///</summary>
		///<param name="fileName">The file to read the ASC CDL information from.</param>
		///<exception cref="MagickException"/>
		void CDL(String^ fileName);
		///==========================================================================================
		///<summary>
		/// Charcoal effect image (looks like charcoal sketch).
		///</summary>
		///<exception cref="MagickException"/>
		void Charcoal();
		///==========================================================================================
		///<summary>
		/// Charcoal effect image (looks like charcoal sketch).
		///</summary>
		///<param name="radius">The radius of the Gaussian, in pixels, not counting the center pixel.</param>
		///<param name="sigma">The standard deviation of the Laplacian, in pixels.</param>
		///<exception cref="MagickException"/>
		void Charcoal(double radius, double sigma);
		///==========================================================================================
		///<summary>
		/// Chop image (remove vertical and horizontal subregion of image).
		///</summary>
		///<param name="xOffset">The X offset from origin.</param>
		///<param name="width">The width of the part to chop horizontally.</param>
		///<param name="yOffset">The Y offset from origin.</param>
		///<param name="height">The height of the part to chop vertically.</param>
		///<exception cref="MagickException"/>
		void Chop(int xOffset, int width, int yOffset, int height);
		///==========================================================================================
		///<summary>
		/// Chop image (remove vertical or horizontal subregion of image) using the specified geometry.
		///</summary>
		///<param name="geometry">The geometry to use.</param>
		///<exception cref="MagickException"/>
		void Chop(MagickGeometry^ geometry);
		///==========================================================================================
		///<summary>
		/// Chop image (remove horizontal subregion of image).
		///</summary>
		///<param name="offset">The X offset from origin.</param>
		///<param name="width">The width of the part to chop horizontally.</param>
		///<exception cref="MagickException"/>
		void ChopHorizontal(int offset, int width);
		///==========================================================================================
		///<summary>
		/// Chop image (remove horizontal subregion of image).
		///</summary>
		///<param name="offset">The Y offset from origin.</param>
		///<param name="height">The height of the part to chop vertically.</param>
		///<exception cref="MagickException"/>
		void ChopVertical(int offset, int height);
		///==========================================================================================
		///<summary>
		/// Chromaticity blue primary point.
		///</summary>
		///<param name="x">The X coordinate.</param>
		///<param name="y">The Y coordinate.</param>
		void ChromaBluePrimary(double x, double y);
		///==========================================================================================
		///<summary>
		/// Chromaticity green primary point.
		///</summary>
		///<param name="x">The X coordinate.</param>
		///<param name="y">The Y coordinate.</param>
		void ChromaGreenPrimary(double x, double y);
		///==========================================================================================
		///<summary>
		/// Chromaticity red primary point.
		///</summary>
		///<param name="x">The X coordinate.</param>
		///<param name="y">The Y coordinate.</param>
		void ChromaRedPrimary(double x, double y);
		///==========================================================================================
		///<summary>
		/// Chromaticity red primary point.
		///</summary>
		///<param name="x">The X coordinate.</param>
		///<param name="y">The Y coordinate.</param>
		void ChromaWhitePoint(double x, double y);
		///==========================================================================================
		///<summary>
		/// Colorize image with the specified color, using specified percent alpha.
		///</summary>
		///<param name="color">The color to use.</param>
		///<param name="alpha">The alpha percentage.</param>
		///<exception cref="MagickException"/>
		void Colorize(MagickColor^ color, Percentage alpha);
		///==========================================================================================
		///<summary>
		/// Colorize image with the specified color, using specified percent alpha for red, green,
		/// and blue quantums
		///</summary>
		///<param name="color">The color to use.</param>
		///<param name="alphaRed">The alpha percentage for red.</param>
		///<param name="alphaGreen">The alpha percentage for green.</param>
		///<param name="alphaBlue">The alpha percentage for blue.</param>
		///<exception cref="MagickException"/>
		void Colorize(MagickColor^ color, Percentage alphaRed, Percentage alphaGreen,
			Percentage alphaBlue);
		///==========================================================================================
		///<summary>
		/// Sets the alpha channel to the specified color.
		///</summary>
		///<param name="color">The color to use.</param>
		///<exception cref="MagickException"/>
		void ColorAlpha(MagickColor^ color);
		///==========================================================================================
		///<summary>
		// Get color at colormap position index.
		///</summary>
		///<param name="index">The position index.</param>
		///<exception cref="MagickException"/>
		MagickColor^ ColorMap(int index);
		///==========================================================================================
		///<summary>
		// Set color at colormap position index.
		///</summary>
		///<param name="index">The position index.</param>
		///<exception cref="MagickException"/>
		void ColorMap(int index, MagickColor^ color);
		///==========================================================================================
		///<summary>
		/// Apply a color matrix to the image channels.
		///</summary>
		///<param name="matrixColor">The color matrix to use.</param>
		///<exception cref="MagickException"/>
		void ColorMatrix(MatrixColor^ matrixColor);
		///==========================================================================================
		///<summary>
		/// Compare current image with another image. Returns error information if the images are not
		/// identical.
		///</summary>
		///<param name="image">The other image to compare with this image.</param>
		///<exception cref="MagickException"/>
		MagickErrorInfo^ Compare(MagickImage^ image);
		///==========================================================================================
		///<summary>
		/// Compares the current instance with another object of the same type.
		///</summary>
		///<param name="other">The object to compare this image with.</param>
		virtual int CompareTo(MagickImage^ other);
		//==========================================================================================
		///<summary>
		/// Compose an image onto another at specified offset using the 'In' operator.
		///</summary>
		///<param name="image">The image to composite with this image.</param>
		///<param name="x">The X offset from origin.</param>
		///<param name="y">The Y offset from origin.</param>
		///<exception cref="MagickException"/>
		void Composite(MagickImage^ image, int x, int y);
		//==========================================================================================
		///<summary>
		/// Compose an image onto another at specified offset using the specified algorithm.
		///</summary>
		///<param name="image">The image to composite with this image.</param>
		///<param name="x">The X offset from origin.</param>
		///<param name="y">The Y offset from origin.</param>
		///<param name="compose">The algorithm to use.</param>
		///<exception cref="MagickException"/>
		void Composite(MagickImage^ image, int x, int y, CompositeOperator compose);
		//==========================================================================================
		///<summary>
		/// Compose an image onto another at specified offset using the 'In' operator.
		///</summary>
		///<param name="image">The image to composite with this image.</param>
		///<param name="offset">The offset from origin.</param>
		///<exception cref="MagickException"/>
		void Composite(MagickImage^ image, MagickGeometry^ offset);
		//==========================================================================================
		///<summary>
		/// Compose an image onto another at specified offset using the specified algorithm.
		///</summary>
		///<param name="image">The image to composite with this image.</param>
		///<param name="offset">The offset from origin.</param>
		///<param name="compose">The algorithm to use.</param>
		///<exception cref="MagickException"/>
		void Composite(MagickImage^ image, MagickGeometry^ offset, CompositeOperator compose);
		//==========================================================================================
		///<summary>
		/// Compose an image onto another at specified offset using the 'In' operator.
		///</summary>
		///<param name="image">The image to composite with this image.</param>
		///<param name="gravity">The placement gravity.</param>
		///<exception cref="MagickException"/>
		void Composite(MagickImage^ image, Gravity gravity);
		//==========================================================================================
		///<summary>
		/// Compose an image onto another at specified offset using the specified algorithm.
		///</summary>
		///<param name="image">The image to composite with this image.</param>
		///<param name="gravity">The placement gravity.</param>
		///<param name="compose">The algorithm to use.</param>
		///<exception cref="MagickException"/>
		void Composite(MagickImage^ image, Gravity gravity, CompositeOperator compose);
		//==========================================================================================
		///<summary>
		/// Contrast image (enhance intensity differences in image)
		///</summary>
		///<exception cref="MagickException"/>
		void Contrast();
		//==========================================================================================
		///<summary>
		/// Contrast image (enhance intensity differences in image)
		///</summary>
		///<param name="enhance">Use true to enhance the contrast and false to reduce the contrast.</param>
		///<exception cref="MagickException"/>
		void Contrast(bool enhance);
		//==========================================================================================
		///<summary>
		/// Convolve image. Applies a user-specified convolution to the image.
		///</summary>
		///<exception cref="MagickException"/>
		void Convolve(MatrixConvolve^ convolveMatrix);
		///==========================================================================================
		///<summary>
		/// Creates a copy of the current image.
		///</summary>
		MagickImage^ Copy();
		///==========================================================================================
		///<summary>
		/// Crop image (subregion of original image).
		///</summary>
		///<param name="geometry">The subregion to crop.</param>
		///<exception cref="MagickException"/>
		void Crop(MagickGeometry^ geometry);
		///==========================================================================================
		///<summary>
		/// Crop image (subregion of original image) using CropPosition.Center.
		///</summary>
		///<param name="width">The width of the subregion.</param>
		///<param name="height">The height of the subregion.</param>
		///<exception cref="MagickException"/>
		void Crop(int width, int height);
		///==========================================================================================
		///<summary>
		/// Crop image (subregion of original image).
		///</summary>
		///<param name="width">The width of the subregion.</param>
		///<param name="height">The height of the subregion.</param>
		///<param name="gravity">The position where the cropping should start from.</param>
		///<exception cref="MagickException"/>
		void Crop(int width, int height, Gravity gravity);
		///==========================================================================================
		///<summary>
		/// Displaces an image's colormap by a given number of positions.
		///</summary>
		///<param name="amount">Displace the colormap this amount.</param>
		///<exception cref="MagickException"/>
		void CycleColormap(int amount);
		///==========================================================================================
		///<summary>
		/// Returns the depth (bits allocated to red/green/blue components).
		///</summary>
		///<exception cref="MagickException"/>
		int Depth();
		///==========================================================================================
		///<summary>
		/// Returns the depth (bits allocated to red/green/blue components) of the specified channel.
		///</summary>
		///<param name="channels">The channel to get the depth for.</param>
		///<exception cref="MagickException"/>
		int Depth(Channels channels);
		///==========================================================================================
		///<summary>
		/// Returns the depth (bits allocated to red/green/blue components).
		///</summary>
		///<param name="value">The depth.</param>
		///<exception cref="MagickException"/>
		void Depth(int value);
		///==========================================================================================
		///<summary>
		/// Set the depth (bits allocated to red/green/blue components) of the specified channel.
		///</summary>
		///<param name="value">The depth.</param>
		///<param name="channels">The channel to set the depth for.</param>
		///<exception cref="MagickException"/>
		void Depth(int value, Channels channels);
		///==========================================================================================
		///<summary>
		/// Despeckle image (reduce speckle noise).
		///</summary>
		///<exception cref="MagickException"/>
		void Despeckle();
		///==========================================================================================
		///<summary>
		/// Distorts an image using various distortion methods, by mapping color lookups of the source
		/// image to a new destination image of the same size as the source image.
		///</summary>
		///<param name="method">The distortion method to use.</param>
		///<param name="arguments">An array containing the arguments for the distortion.</param>
		///<exception cref="MagickException"/>
		void Distort(DistortMethod method, array<double>^ arguments);
		///==========================================================================================
		///<summary>
		/// Distorts an image using various distortion methods, by mapping color lookups of the source
		/// image to a new destination image usually of the same size as the source image, unless
		/// 'bestfit' is set to true.
		///</summary>
		///<param name="method">The distortion method to use.</param>
		///<param name="arguments">An array containing the arguments for the distortion.</param>
		///<param name="bestfit">Attempt to 'bestfit' the size of the resulting image.</param>
		///<exception cref="MagickException"/>
		void Distort(DistortMethod method, array<double>^ arguments, bool bestfit);
		///==========================================================================================
		///<summary>
		/// Draw on image using a single drawable.
		///</summary>
		///<param name="drawable">The drawable to draw on the image.</param>
		///<exception cref="MagickException"/>
		void Draw(DrawableBase^ drawable);
		///==========================================================================================
		///<summary>
		/// Draw on image using a collection of drawables.
		///</summary>
		///<param name="drawables">The drawables to draw on the image.</param>
		///<exception cref="MagickException"/>
		void Draw(IEnumerable<DrawableBase^>^ drawables);
		///==========================================================================================
		///<summary>
		/// Determines whether the specified object is equal to the current image.
		///</summary>
		///<param name="obj">The object to compare this image with.</param>
		virtual bool Equals(Object^ obj) override;
		///==========================================================================================
		///<summary>
		/// Determines whether the specified image is equal to the current image.
		///</summary>
		///<param name="other">The image to compare this image with.</param>
		virtual bool Equals(MagickImage^ other);
		///==========================================================================================
		///<summary>
		/// Edge image (hilight edges in image).
		///</summary>
		///<param name="radius">The radius of the pixel neighborhood.</param>
		///<exception cref="MagickException"/>
		void Edge(double radius);
		///==========================================================================================
		///<summary>
		/// Emboss image (hilight edges with 3D effect) with default value (0x1).
		///</summary>
		///<exception cref="MagickException"/>
		void Emboss();
		///==========================================================================================
		///<summary>
		/// Emboss image (hilight edges with 3D effect).
		///</summary>
		///<param name="radius">The radius of the Gaussian, in pixels, not counting the center pixel.</param>
		///<param name="sigma">The standard deviation of the Laplacian, in pixels.</param>
		///<exception cref="MagickException"/>
		void Emboss(double radius, double sigma);
		///==========================================================================================
		///<summary>
		/// Returns the ExifProfile as a byte array,
		///</summary>
		///<exception cref="MagickException"/>
		array<Byte>^ ExifProfile();
		///==========================================================================================
		///<summary>
		/// Loads the ExifProfile from the specified filename.
		///</summary>
		///<param name="data">The byte array to read the exif profile from.</param>
		///<exception cref="MagickException"/>
		void ExifProfile(array<Byte>^ data);
		///==========================================================================================
		///<summary>
		/// Loads the ExifProfile from the specified stream.
		///</summary>
		///<param name="stream">The stream to read the exif profile from.</param>
		///<exception cref="MagickException"/>
		void ExifProfile(Stream^ stream);
		///==========================================================================================
		///<summary>
		/// Loads the ExifProfile from the specified filename.
		///</summary>
		///<param name="fileName">The fully qualified name of the exif profile file, or the relative exif
		/// profile file name.</param>
		///<exception cref="MagickException"/>
		void ExifProfile(String^ fileName);
		///==========================================================================================
		///<summary>
		/// Extend the image as defined by the geometry.
		///</summary>
		///<param name="geometry">The geometry to extend the image to.</param>
		///<exception cref="MagickException"/>
		void Extent(MagickGeometry^ geometry);
		///==========================================================================================
		///<summary>
		/// Extend the image as defined by the geometry.
		///</summary>
		///<param name="geometry">The geometry to extend the image to.</param>
		///<param name="backgroundColor">The background color to use.</param>
		///<exception cref="MagickException"/>
		void Extent(MagickGeometry^ geometry, MagickColor^ backgroundColor);
		///==========================================================================================
		///<summary>
		/// Extend the image as defined by the geometry.
		///</summary>
		///<param name="geometry">The geometry to extend the image to.</param>
		///<param name="gravity">The placement gravity.</param>
		///<exception cref="MagickException"/>
		void Extent(MagickGeometry^ geometry, Gravity gravity);
		///==========================================================================================
		///<summary>
		/// Extend the image as defined by the geometry.
		///</summary>
		///<param name="geometry">The geometry to extend the image to.</param>
		///<param name="gravity">The placement gravity.</param>
		///<param name="backgroundColor">The background color to use.</param>
		///<exception cref="MagickException"/>
		void Extent(MagickGeometry^ geometry, Gravity gravity, MagickColor^ backgroundColor);
		///==========================================================================================
		///<summary>
		/// Flip image (reflect each scanline in the vertical direction).
		///</summary>
		///<exception cref="MagickException"/>
		void Flip();
		///==========================================================================================
		///<summary>
		/// Floodfill pixels matching color (within fuzz factor) of target pixel(x,y) with replacement
		/// alpha value using method.
		///</summary>
		///<param name="alpha">The alpha to use.</param>
		///<param name="x">The X coordinate.</param>
		///<param name="y">The Y coordinate.</param>
		///<param name="paintMethod">The paint method to use.</param>
		///<exception cref="MagickException"/>
		void FloodFill(int alpha, int x, int y, PaintMethod paintMethod);
		///==========================================================================================
		///<summary>
		/// Flood-fill color across pixels that match the color of the  target pixel and are neighbors
		/// of the target pixel. Uses current fuzz setting when determining color match.
		///</summary>
		///<param name="color">The color to use.</param>
		///<param name="x">The X coordinate.</param>
		///<param name="y">The Y coordinate.</param>
		///<exception cref="MagickException"/>
		void FloodFill(MagickColor^ color, int x, int y);
		///==========================================================================================
		///<summary>
		/// Flood-fill color across pixels that match the color of the  target pixel and are neighbors
		/// of the target pixel. Uses current fuzz setting when determining color match.
		///</summary>
		///<param name="color">The color to use.</param>
		///<param name="x">The X coordinate.</param>
		///<param name="y">The Y coordinate.</param>
		///<param name="borderColor">The color of the border.</param>
		///<exception cref="MagickException"/>
		void FloodFill(MagickColor^ color, int x, int y, MagickColor^ borderColor);
		///==========================================================================================
		///<summary>
		/// Flood-fill color across pixels that match the color of the  target pixel and are neighbors
		/// of the target pixel. Uses current fuzz setting when determining color match.
		///</summary>
		///<param name="color">The color to use.</param>
		///<param name="geometry">The position of the pixel.</param>
		///<exception cref="MagickException"/>
		void FloodFill(MagickColor^ color, MagickGeometry^ geometry);
		///==========================================================================================
		///<summary>
		/// Flood-fill color across pixels that match the color of the target pixel and are neighbors
		/// of the target pixel. Uses current fuzz setting when determining color match.
		///</summary>
		///<param name="color">The color to use.</param>
		///<param name="geometry">The position of the pixel.</param>
		///<param name="borderColor">The color of the border.</param>
		///<exception cref="MagickException"/>
		void FloodFill(MagickColor^ color, MagickGeometry^ geometry, MagickColor^ borderColor);
		///==========================================================================================
		///<summary>
		/// Flood-fill texture across pixels that match the color of the target pixel and are neighbors
		/// of the target pixel. Uses current fuzz setting when determining color match.
		///</summary>
		///<param name="image">The image to use.</param>
		///<param name="x">The X coordinate.</param>
		///<param name="y">The Y coordinate.</param>
		///<exception cref="MagickException"/>
		void FloodFill(MagickImage^ image, int x, int y);
		///==========================================================================================
		///<summary>
		/// Flood-fill texture across pixels that match the color of the target pixel and are neighbors
		/// of the target pixel. Uses current fuzz setting when determining color match.
		///</summary>
		///<param name="image">The image to use.</param>
		///<param name="x">The X coordinate.</param>
		///<param name="y">The Y coordinate.</param>
		///<param name="borderColor">The color of the border.</param>
		///<exception cref="MagickException"/>
		void FloodFill(MagickImage^ image, int x, int y, MagickColor^ borderColor);
		///==========================================================================================
		///<summary>
		/// Flood-fill texture across pixels that match the color of the target pixel and are neighbors
		/// of the target pixel. Uses current fuzz setting when determining color match.
		///</summary>
		///<param name="image">The image to use.</param>
		///<param name="geometry">The position of the pixel.</param>
		///<exception cref="MagickException"/>
		void FloodFill(MagickImage^ image, MagickGeometry^ geometry);
		///==========================================================================================
		///<summary>
		/// Flood-fill texture across pixels that match the color of the target pixel and are neighbors
		/// of the target pixel. Uses current fuzz setting when determining color match.
		///</summary>
		///<param name="image">The image to use.</param>
		///<param name="geometry">The position of the pixel.</param>
		///<param name="borderColor">The color of the border.</param>
		///<exception cref="MagickException"/>
		void FloodFill(MagickImage^ image, MagickGeometry^ geometry, MagickColor^ borderColor);
		///==========================================================================================
		///<summary>
		/// Flop image (reflect each scanline in the horizontal direction).
		///</summary>
		///<exception cref="MagickException"/>
		void Flop();
		///==========================================================================================
		///<summary>
		/// Obtain font metrics for text string given current font, pointsize, and density settings.
		///</summary>
		///<exception cref="MagickException"/>
		TypeMetric^ FontTypeMetrics(String^ text);
		///==========================================================================================
		///<summary>
		/// Frame image with the default geometry (25x25+6+6).
		///</summary>
		///<exception cref="MagickException"/>
		void Frame();
		///==========================================================================================
		///<summary>
		/// Frame image with the specified geometry.
		///</summary>
		///<param name="geometry">The geometry of the frame.</param>
		///<exception cref="MagickException"/>
		void Frame(MagickGeometry^ geometry);
		///==========================================================================================
		///<summary>
		/// Frame image with the specified with and height.
		///</summary>
		///<param name="width">The width of the frame.</param>
		///<param name="height">The height of the frame.</param>
		///<exception cref="MagickException"/>
		void Frame(int width, int height);
		///==========================================================================================
		///<summary>
		/// Frame image with the specified with, height, innerBevel and outerBevel.
		///</summary>
		///<param name="width">The width of the frame.</param>
		///<param name="height">The height of the frame.</param>
		///<param name="innerBevel">The inner bevel of the frame.</param>
		///<param name="outerBevel">The outer bevel of the frame.</param>
		///<exception cref="MagickException"/>
		void Frame(int width, int height, int innerBevel, int outerBevel);
		///==========================================================================================
		///<summary>
		/// Initializes a new instance of the MagickImage class using the specified base64 string.
		///</summary>
		///<param name="value">The base64 string to load the image from.</param>
		static MagickImage^ FromBase64(String^ value);
		///==========================================================================================
		///<summary>
		/// Applies a mathematical expression to the image.
		///</summary>
		///<param name="expression">The expression to apply.</param>
		///<exception cref="MagickException"/>
		void Fx(String^ expression);
		///==========================================================================================
		///<summary>
		/// Applies a mathematical expression to the image.
		///</summary>
		///<param name="expression">The expression to apply.</param>
		///<param name="channels">The channel(s) to apply the expression to.</param>
		///<exception cref="MagickException"/>
		void Fx(String^ expression, Channels channels);
		///==========================================================================================
		///<summary>
		/// Gamma level of the image.
		///</summary>
		///<exception cref="MagickException"/>
		double Gamma();
		///==========================================================================================
		///<summary>
		/// Gamma correct image.
		///</summary>
		///<param name="value">The image gamma.</param>
		///<exception cref="MagickException"/>
		void Gamma(double value);
		///==========================================================================================
		///<summary>
		/// Gamma correct image.
		///</summary>
		///<param name="gammeRed">The image gamma for the red channel.</param>
		///<param name="gammeGreen">The image gamma for the green channel.</param>
		///<param name="gammeBlue">The image gamma for the blue channel.</param>
		///<exception cref="MagickException"/>
		void Gamma(double gammeRed, double gammeGreen, double gammeBlue);
		///==========================================================================================
		///<summary>
		/// Gaussian blur image.
		///</summary>
		///<param name="width">The number of neighbor pixels to be included in the convolution.</param>
		///<param name="sigma">The standard deviation of the gaussian bell curve.</param>
		///<exception cref="MagickException"/>
		void GaussianBlur(double width, double sigma);
		///==========================================================================================
		///<summary>
		/// Gaussian blur image.
		///</summary>
		///<param name="width">The number of neighbor pixels to be included in the convolution.</param>
		///<param name="sigma">The standard deviation of the gaussian bell curve.</param>
		///<param name="channels">The channel(s) to blur.</param>
		///<exception cref="MagickException"/>
		void GaussianBlur(double width, double sigma, Channels channels);
		///==========================================================================================
		///<summary>
		/// Servers as a hash of this type.
		///</summary>
		virtual int GetHashCode() override;
		///==========================================================================================
		///<summary>
		/// Preferred size of the image when encoding.
		///</summary>
		///<exception cref="MagickException"/>
		MagickGeometry^ Geometry();
		///==========================================================================================
		///<summary>
		/// Retrieve the ICC ICM profile from the image.
		///</summary>
		///<exception cref="MagickException"/>
		array<Byte>^ GetProfile();
		///==========================================================================================
		///<summary>
		/// Retrieve a named profile from the image.
		///</summary>
		///<param name="name">The name of the profile (e.g. "ICM", "IPTC", or a generic profile name).</param>
		///<exception cref="MagickException"/>
		array<Byte>^ GetProfile(String^ name);
		///==========================================================================================
		///<summary>
		/// Returns an read-only pixel collection that can be used to access the pixels of this image.
		///</summary>
		///<exception cref="MagickException"/>
		PixelCollection^ GetReadOnlyPixels();
		///==========================================================================================
		///<summary>
		/// Returns an read-only pixel collection that can be used to access the pixels of this image.
		///</summary>
		///<param name="x">The X coordinate.</param>
		///<param name="y">The Y coordinate.</param>
		///<param name="width">The width of the pixel area.</param>
		///<param name="height">The height of the pixel area.</param>
		///<exception cref="MagickException"/>
		PixelCollection^ GetReadOnlyPixels(int x, int y, int width, int height);
		///==========================================================================================
		///<summary>
		/// Returns an writable pixel collection that can be used to access the pixels of this image.
		///</summary>
		///<exception cref="MagickException"/>
		WritablePixelCollection^ GetWritablePixels();
		///==========================================================================================
		///<summary>
		/// Returns an writable pixel collection that can be used to access the pixels of this image.
		///</summary>
		///<param name="x">The X coordinate.</param>
		///<param name="y">The Y coordinate.</param>
		///<param name="width">The width of the pixel area.</param>
		///<param name="height">The height of the pixel area.</param>
		///<exception cref="MagickException"/>
		WritablePixelCollection^ GetWritablePixels(int x, int y, int width, int height);
		///==========================================================================================
		///<summary>
		/// Apply a color lookup table (Hald CLUT) to the image.
		///</summary>
		///<param name="image">The image to use.</param>
		///<exception cref="MagickException"/>
		void HaldClut(MagickImage^ image);
		///==========================================================================================
		///<summary>
		/// Implode image (special effect).
		///</summary>
		///<param name="factor">The extent of the implosion.</param>
		///<exception cref="MagickException"/>
		void Implode(double factor);
		///==========================================================================================
		///<summary>
		/// Implements the inverse discrete Fourier transform (DFT) of the image as a magnitude phase.
		///</summary>
		///<param name="image">The image to use.</param>
		///<exception cref="MagickException"/>
		void InverseFourierTransform(MagickImage^ image);
		///==========================================================================================
		///<summary>
		/// Implements the inverse discrete Fourier transform (DFT) of the image either as a magnitude
		/// phase or real / imaginary image pair.
		///</summary>
		///<param name="image">The image to use.</param>
		///<param name="magnitude">Magnitude phase or real / imaginary image pair.</param>
		///<exception cref="MagickException"/>
		void InverseFourierTransform(MagickImage^ image, bool magnitude);
		///==========================================================================================
		///<summary>
		/// Adjust the levels of the image by scaling the colors falling between specified white and
		/// black points to the full available quantum range. Uses a midpoint of 1.0.
		///</summary>
		///<param name="blackPoint">The darkest color in the image. Colors darker are set to zero.</param>
		///<param name="whitePoint">The lightest color in the image. Colors brighter are set to the maximum quantum value.</param>
		///<exception cref="MagickException"/>
		void Level(Magick::Quantum blackPoint, Magick::Quantum whitePoint);
		///==========================================================================================
		///<summary>
		/// Adjust the levels of the image by scaling the colors falling between specified white and
		/// black points to the full available quantum range. Uses a midpoint of 1.0.
		///</summary>
		///<param name="blackPoint">The darkest color in the image. Colors darker are set to zero.</param>
		///<param name="whitePoint">The lightest color in the image. Colors brighter are set to the maximum quantum value.</param>
		///<param name="channels">The channel(s) to level.</param>
		///<exception cref="MagickException"/>
		void Level(Magick::Quantum blackPoint, Magick::Quantum whitePoint, Channels channels);
		///==========================================================================================
		///<summary>
		/// Adjust the levels of the image by scaling the colors falling between specified white and
		/// black points to the full available quantum range.
		///</summary>
		///<param name="blackPoint">The darkest color in the image. Colors darker are set to zero.</param>
		///<param name="whitePoint">The lightest color in the image. Colors brighter are set to the maximum quantum value.</param>
		///<param name="midpoint">The gamma correction to apply to the image. (Useful range of 0 to 10)</param>
		///<exception cref="MagickException"/>
		void Level(Magick::Quantum blackPoint, Magick::Quantum whitePoint, double midpoint);
		///==========================================================================================
		///<summary>
		/// Adjust the levels of the image by scaling the colors falling between specified white and
		/// black points to the full available quantum range.
		///</summary>
		///<param name="blackPoint">The darkest color in the image. Colors darker are set to zero.</param>
		///<param name="whitePoint">The lightest color in the image. Colors brighter are set to the maximum quantum value.</param>
		///<param name="midpoint">The gamma correction to apply to the image. (Useful range of 0 to 10)</param>
		///<param name="channels">The channel(s) to level.</param>
		///<exception cref="MagickException"/>
		void Level(Magick::Quantum blackPoint, Magick::Quantum whitePoint, double midpoint, Channels channels);
		///==========================================================================================
		///<summary>
		/// Lower image (lighten or darken the edges of an image to give a 3-D lowered effect).
		///</summary>
		///<param name="size">The size of the edges.</param>
		///<exception cref="MagickException"/>
		void Lower(int size);
		///==========================================================================================
		///<summary>
		/// Magnify image by integral size.
		///</summary>
		///<exception cref="MagickException"/>
		void Magnify();
		///==========================================================================================
		///<summary>
		/// Remap image colors with closest color from reference image.
		///</summary>
		///<param name="image">The image to use.</param>
		///<exception cref="MagickException"/>
		void Map(MagickImage^ image);
		///==========================================================================================
		///<summary>
		/// Remap image colors with closest color from reference image.
		///</summary>
		///<param name="image">The image to use.</param>
		///<param name="dither">Dither the image.</param>
		///<exception cref="MagickException"/>
		void Map(MagickImage^ image, bool dither);
		///==========================================================================================
		///<summary>
		/// Filter image by replacing each pixel component with the median color in a circular neighborhood.
		///</summary>
		///<exception cref="MagickException"/>
		void MedianFilter();
		///==========================================================================================
		///<summary>
		/// Filter image by replacing each pixel component with the median color in a circular neighborhood.
		///</summary>
		///<param name="radius">The radius of the pixel neighborhood.</param>
		///<exception cref="MagickException"/>
		void MedianFilter(double radius);
		///==========================================================================================
		///<summary>
		/// Reduce image by integral size.
		///</summary>
		///<exception cref="MagickException"/>
		void Minify();
		///==========================================================================================
		///<summary>
		/// Modulate percent hue, saturation, and brightness of an image.
		///</summary>
		///<param name="brightness">The brightness percentage.</param>
		///<param name="saturation">The saturation percentage.</param>
		///<param name="hue">The hue percentage.</param>
		///<exception cref="MagickException"/>
		void Modulate(Percentage brightness, Percentage saturation, Percentage hue);
		///==========================================================================================
		///<summary>
		/// Motion blur image with specified blur factor.
		///</summary>
		///<param name="radius">The radius of the Gaussian, in pixels, not counting the center pixel.</param>
		///<param name="sigma">The standard deviation of the Laplacian, in pixels.</param>
		///<param name="angle">The angle the object appears to be comming from (zero degrees is from the right).</param>
		///<exception cref="MagickException"/>
		void MotionBlur(double radius, double sigma, double angle);
		///==========================================================================================
		///<summary>
		/// Negate colors in image.
		///</summary>
		///<exception cref="MagickException"/>
		void Negate();
		///==========================================================================================
		///<summary>
		/// Negate colors in image.
		///</summary>
		///<param name="onlyGrayscale">Use true to negate only the grayscale colors.</param>
		///<exception cref="MagickException"/>
		void Negate(bool onlyGrayscale);
		///==========================================================================================
		///<summary>
		/// Normalize image (increase contrast by normalizing the pixel values to span the full range
		/// of color values)
		///</summary>
		///<exception cref="MagickException"/>
		void Normalize();
		///==========================================================================================
		///<summary>
		/// Oilpaint image (image looks like oil painting)
		///</summary>
		void OilPaint();
		///==========================================================================================
		///<summary>
		/// Oilpaint image (image looks like oil painting)
		///</summary>
		///<param name="radius">The radius of the circular neighborhood.</param>
		///<exception cref="MagickException"/>
		void OilPaint(double radius);
		///==========================================================================================
		///<summary>
		/// Quantize image (reduce number of colors).
		///</summary>
		///<exception cref="MagickException"/>
		void Quantize();
		///==========================================================================================
		///<summary>
		/// Quantize image (reduce number of colors).
		///</summary>
		///<param name="measureError">When false is specified this method will return null.</param>
		///<exception cref="MagickException"/>
		MagickErrorInfo^ Quantize(bool measureError);
		///==========================================================================================
		///<summary>
		/// Apply an arithmetic or bitwise operator to the image pixel quantums.
		///</summary>
		///<param name="channels">The channel(s) to apply the operator on.</param>
		///<param name="evaluateOperator">The operator.</param>
		///<param name="value">The value.</param>
		///<exception cref="MagickException"/>
		void QuantumOperator(Channels channels, EvaluateOperator evaluateOperator, double value);
		///==========================================================================================
		///<summary>
		/// Apply an arithmetic or bitwise operator to the image pixel quantums.
		///</summary>
		///<param name="channels">The channel(s) to apply the operator on.</param>
		///<param name="geometry">The geometry to use.</param>
		///<param name="evaluateOperator">The operator.</param>
		///<param name="value">The value.</param>
		///<exception cref="MagickException"/>
		void QuantumOperator(Channels channels, MagickGeometry^ geometry, EvaluateOperator evaluateOperator, double value);
		///==========================================================================================
		///<summary>
		/// Raise image (lighten or darken the edges of an image to give a 3-D raised effect).
		///</summary>
		///<param name="size">The size of the edges.</param>
		///<exception cref="MagickException"/>
		void Raise(int size);
		///==========================================================================================
		///<summary>
		/// Changes the value of individual pixels based on the intensity of each pixel compared to a
		/// random threshold. The result is a low-contrast, two color image.
		///</summary>
		///<param name="percentageLow">The low threshold.</param>
		///<param name="percentageHigh">The low threshold.</param>
		///<exception cref="MagickException"/>
		void RandomThreshold(Percentage percentageLow, Percentage percentageHigh);
		///==========================================================================================
		///<summary>
		/// Changes the value of individual pixels based on the intensity of each pixel compared to a
		/// random threshold. The result is a low-contrast, two color image.
		///</summary>
		///<param name="percentageLow">The low threshold.</param>
		///<param name="percentageHigh">The low threshold.</param>
		///<param name="channels">The channel(s) to use.</param>
		///<exception cref="MagickException"/>
		void RandomThreshold(Percentage percentageLow, Percentage percentageHigh, Channels channels);
		///==========================================================================================
		///<summary>
		/// Changes the value of individual pixels based on the intensity of each pixel compared to a
		/// random threshold. The result is a low-contrast, two color image.
		///</summary>
		///<param name="low">The low threshold.</param>
		///<param name="high">The low threshold.</param>
		///<exception cref="MagickException"/>
		void RandomThreshold(Magick::Quantum low, Magick::Quantum high);
		///==========================================================================================
		///<summary>
		/// Changes the value of individual pixels based on the intensity of each pixel compared to a
		/// random threshold. The result is a low-contrast, two color image.
		///</summary>
		///<param name="low">The low threshold.</param>
		///<param name="high">The low threshold.</param>
		///<param name="channels">The channel(s) to use.</param>
		///<exception cref="MagickException"/>
		void RandomThreshold(Magick::Quantum low, Magick::Quantum high, Channels channels);
		///==========================================================================================
		///<summary>
		/// Read single image frame.
		///</summary>
		///<param name="data">The byte array to read the image data from.</param>
		///<returns>If a warning was raised while reading the image that warning will be returned.</returns>
		///<exception cref="MagickException"/>
		MagickWarningException^ Read(array<Byte>^ data);
		///==========================================================================================
		///<summary>
		/// Read single vector image frame.
		///</summary>
		///<param name="data">The byte array to read the image data from.</param>
		///<param name="readSettings">The settings to use when reading the image.</param>
		///<returns>If a warning was raised while reading the image that warning will be returned.</returns>
		///<exception cref="MagickException"/>
		MagickWarningException^ Read(array<Byte>^ data, MagickReadSettings^ readSettings);
		///==========================================================================================
		///<summary>
		/// Read single image frame.
		///</summary>
		///<param name="bitmap">The bitmap to read the image from.</param>
		///<returns>If a warning was raised while reading the image that warning will be returned.</returns>
		///<exception cref="MagickException"/>
		MagickWarningException^ Read(Bitmap^ bitmap);
		///==========================================================================================
		///<summary>
		/// Read single image frame.
		///</summary>
		///<param name="fileName">The fully qualified name of the image file, or the relative image file name.</param>
		///<returns>If a warning was raised while reading the image that warning will be returned.</returns>
		///<exception cref="MagickException"/>
		MagickWarningException^ Read(String^ fileName);
		///==========================================================================================
		///<summary>
		/// Read single vector image frame.
		///</summary>
		///<param name="fileName">The fully qualified name of the image file, or the relative image file name.</param>
		///<param name="readSettings">The settings to use when reading the image.</param>
		///<returns>If a warning was raised while reading the image that warning will be returned.</returns>
		///<exception cref="MagickException"/>
		MagickWarningException^ Read(String^ fileName, MagickReadSettings^ readSettings);
		///==========================================================================================
		///<summary>
		/// Read single image frame.
		///</summary>
		///<param name="stream">The stream to read the image data from.</param>
		///<returns>If a warning was raised while reading the image that warning will be returned.</returns>
		///<exception cref="MagickException"/>
		MagickWarningException^ Read(Stream^ stream);
		///==========================================================================================
		///<summary>
		/// Read single image frame.
		///</summary>
		///<param name="stream">The stream to read the image data from.</param>
		///<param name="readSettings">The settings to use when reading the image.</param>
		///<returns>If a warning was raised while reading the image that warning will be returned.</returns>
		///<exception cref="MagickException"/>
		MagickWarningException^ Read(Stream^ stream, MagickReadSettings^ readSettings);
		///==========================================================================================
		///<summary>
		/// Reduce noise in image using a noise peak elimination filter.
		///</summary>
		///<exception cref="MagickException"/>
		void ReduceNoise();
		///==========================================================================================
		///<summary>
		/// Reduce noise in image using a noise peak elimination filter.
		///</summary>
		///<param name="order">The order to use.</param>
		///<exception cref="MagickException"/>
		void ReduceNoise(int order);
		///==========================================================================================
		///<summary>
		/// Remove a named profile from the image.
		///</summary>
		///<param name="name">The name of the profile (e.g. "ICM", "IPTC", or a generic profile name).</param>
		///<exception cref="MagickException"/>
		void RemoveProfile(String^ name);
		///==========================================================================================
		///<summary>
		/// Resize image to specified size.
		///</summary>
		///<param name="width">The new width.</param>
		///<param name="height">The new height.</param>
		///<exception cref="MagickException"/>
		void Resize(int width, int height);
		///==========================================================================================
		///<summary>
		/// Resize image to specified percentage.
		///</summary>
		///<param name="percentage">The percentage.</param>
		///<exception cref="MagickException"/>
		void Resize(Percentage percentage);
		///==========================================================================================
		///<summary>
		/// Resize image to specified percentage.
		///</summary>
		///<param name="percentageWidth">The percentage of the width.</param>
		///<param name="percentageHeight">The percentage of the height.</param>
		///<exception cref="MagickException"/>
		void Resize(Percentage percentageWidth, Percentage percentageHeight);
		///==========================================================================================
		///<summary>
		/// Roll image (rolls image vertically and horizontally).
		///</summary>
		///<param name="xOffset">The X offset from origin.</param>
		///<param name="yOffset">The Y offset from origin.</param>
		///<exception cref="MagickException"/>
		void Roll(int xOffset, int yOffset);
		///==========================================================================================
		///<summary>
		/// Rotate image counter-clockwise by specified number of degrees.
		///</summary>
		///<param name="degrees">The number of degrees to rotate.</param>
		///<exception cref="MagickException"/>
		void Rotate(double degrees);
		///==========================================================================================
		///<summary>
		/// Resize image by using pixel sampling algorithm.
		///</summary>
		///<param name="width">The new width.</param>
		///<param name="height">The new height.</param>
		void Sample(int width, int height);
		///==========================================================================================
		///<summary>
		/// Resize image by using pixel sampling algorithm to the specified percentage.
		///</summary>
		///<param name="percentage">The percentage.</param>
		///<exception cref="MagickException"/>
		void Sample(Percentage percentage);
		///==========================================================================================
		///<summary>
		/// Resize image by using pixel sampling algorithm to the specified percentage.
		///</summary>
		///<param name="percentageWidth">The percentage of the width.</param>
		///<param name="percentageHeight">The percentage of the height.</param>
		///<exception cref="MagickException"/>
		void Sample(Percentage percentageWidth, Percentage percentageHeight);
		///==========================================================================================
		///<summary>
		/// Resize image by using simple ratio algorithm.
		///</summary>
		///<param name="width">The new width.</param>
		///<param name="height">The new height.</param>
		void Scale(int width, int height);
		///==========================================================================================
		///<summary>
		/// Resize image by using simple ratio algorithm to the specified percentage.
		///</summary>
		///<param name="percentage">The percentage.</param>
		///<exception cref="MagickException"/>
		void Scale(Percentage percentage);
		///==========================================================================================
		///<summary>
		/// Resize image by using simple ratio algorithm to the specified percentage.
		///</summary>
		///<param name="percentageWidth">The percentage of the width.</param>
		///<param name="percentageHeight">The percentage of the height.</param>
		///<exception cref="MagickException"/>
		void Scale(Percentage percentageWidth, Percentage percentageHeight);
		///==========================================================================================
		///<summary>
		/// Segment (coalesce similar image components) by analyzing the histograms of the color
		/// components and identifying units that are homogeneous with the fuzzy c-means technique.
		/// Also uses QuantizeColorSpace and Verbose image attributes.
		///</summary>
		///<exception cref="MagickException"/>
		void Segment();
		///==========================================================================================
		///<summary>
		/// Segment (coalesce similar image components) by analyzing the histograms of the color
		/// components and identifying units that are homogeneous with the fuzzy c-means technique.
		/// Also uses QuantizeColorSpace and Verbose image attributes.
		///</summary>
		///<param name="clusterThreshold">This represents the minimum number of pixels contained in
		/// a hexahedra before it can be considered valid (expressed as a percentage).</param>
		///<param name="smoothingThreshold">The smoothing threshold eliminates noise in the second
		/// derivative of the histogram. As the value is increased, you can expect a smoother second
		/// derivative</param>
		///<exception cref="MagickException"/>
		void Segment(double clusterThreshold, double smoothingThreshold);
		///==========================================================================================
		///<summary>
		/// Separates a channel from the image and makes it a grayscale image.
		///</summary>
		///<param name="channels">The channel(s) to separates.</param>
		///<exception cref="MagickException"/>
		void Separate(Channels channels);
		///==========================================================================================
		///<summary>
		/// Shade image using distant light source.
		///</summary>
		///<exception cref="MagickException"/>
		void Shade();
		///==========================================================================================
		///<summary>
		/// Shade image using distant light source.
		///</summary>
		///<param name="azimuth">The light source direction.</param>
		///<param name="elevation">The light source direction.</param>
		///<param name="colorShading">Specify true to shade the intensity of each pixel.</param>
		///<exception cref="MagickException"/>
		void Shade(double azimuth, double elevation, bool colorShading);
		///==========================================================================================
		///<summary>
		/// Simulate an image shadow.
		///</summary>
		///<exception cref="MagickException"/>
		void Shadow();
		///==========================================================================================
		///<summary>
		/// Simulate an image shadow.
		///</summary>
		///<param name="color">The color of the shadow.</param>
		///<exception cref="MagickException"/>
		void Shadow(MagickColor^ color);
		///==========================================================================================
		///<summary>
		/// Simulate an image shadow.
		///</summary>
		///<param name="x">the shadow x-offset.</param>
		///<param name="y">the shadow y-offset.</param>
		///<param name="sigma">The standard deviation of the Gaussian, in pixels.</param>
		///<param name="alpha">Transparency percentage.</param>
		///<exception cref="MagickException"/>
		void Shadow(int x, int y, double sigma, Percentage alpha);
		///==========================================================================================
		///<summary>
		/// Simulate an image shadow.
		///</summary>
		///<param name="x">the shadow x-offset.</param>
		///<param name="y">the shadow y-offset.</param>
		///<param name="sigma">The standard deviation of the Gaussian, in pixels.</param>
		///<param name="alpha">Transparency percentage.</param>
		///<param name="color">The color of the shadow.</param>
		///<exception cref="MagickException"/>
		void Shadow(int x, int y, double sigma, Percentage alpha, MagickColor^ color);
		///==========================================================================================
		///<summary>
		/// Sharpen pixels in image.
		///</summary>
		///<exception cref="MagickException"/>
		void Sharpen();
		///==========================================================================================
		///<summary>
		/// Sharpen pixels in image.
		///</summary>
		///<param name="channels">The channel(s) that should be sharpened.</param>
		///<exception cref="MagickException"/>
		void Sharpen(Channels channels);
		///==========================================================================================
		///<summary>
		/// Sharpen pixels in image.
		///</summary>
		///<param name="radius">The radius of the Gaussian, in pixels, not counting the center pixel.</param>
		///<param name="sigma">The standard deviation of the Laplacian, in pixels.</param>
		///<exception cref="MagickException"/>
		void Sharpen(double radius, double sigma);
		///==========================================================================================
		///<summary>
		/// Sharpen pixels in image.
		///</summary>
		///<param name="radius">The radius of the Gaussian, in pixels, not counting the center pixel.</param>
		///<param name="sigma">The standard deviation of the Laplacian, in pixels.</param>
		///<param name="channels">The channel(s) that should be sharpened.</param>
		void Sharpen(double radius, double sigma, Channels channels);
		///==========================================================================================
		///<summary>
		/// Shave pixels from image edges.
		///</summary>
		///<param name="leftRight">The number of pixels to shave left and right.</param>
		///<param name="topBottom">The number of pixels to shave top and bottom.</param>
		///<exception cref="MagickException"/>
		void Shave(int leftRight, int topBottom);
		///==========================================================================================
		///<summary>
		/// Shear image (create parallelogram by sliding image by X or Y axis).
		///</summary>
		///<param name="xAngle">Specifies the number of degrees to shear the image.</param>
		///<param name="yAngle">Specifies the number of degrees to shear the image.</param>
		///<exception cref="MagickException"/>
		void Shear(double xAngle, double yAngle);
		///==========================================================================================
		///<summary>
		/// adjust the image contrast with a non-linear sigmoidal contrast algorithm
		///</summary>
		///<param name="sharpen">Specifies if sharpening should be used.</param>
		///<param name="contrast">The contrast</param>
		///<exception cref="MagickException"/>
		void SigmoidalContrast(bool sharpen, double contrast);
		///==========================================================================================
		///<summary>
		/// adjust the image contrast with a non-linear sigmoidal contrast algorithm
		///</summary>
		///<param name="sharpen">Specifies if sharpening should be used.</param>
		///<param name="contrast">The contrast to use.</param>
		///<param name="midpoint">The midpoint to use.</param>
		///<exception cref="MagickException"/>
		void SigmoidalContrast(bool sharpen, double contrast, double midpoint);
		///==========================================================================================
		///<summary>
		/// Solarize image (similar to effect seen when exposing a photographic film to light during
		/// the development process)
		///</summary>
		///<exception cref="MagickException"/>
		void Solarize();
		///==========================================================================================
		///<summary>
		/// Solarize image (similar to effect seen when exposing a photographic film to light during
		/// the development process)
		///</summary>
		///<param name="factor">The factor to use.</param>
		///<exception cref="MagickException"/>
		void Solarize(double factor);
		///==========================================================================================
		///<summary>
		/// Sparse color image, given a set of coordinates, interpolates the colors found at those
		/// coordinates, across the whole image, using various methods.
		///</summary>
		///<param name="channels">The channel(s) to use.</param>
		///<param name="method">The spare color method to use.</param>
		///<param name="coordinates">The coordinates to use.</param>
		///<exception cref="MagickException"/>
		void SparseColor(Channels channels, SparseColorMethod method, array<double>^ coordinates);
		///==========================================================================================
		///<summary>
		/// Returns image statistics.
		///</summary>
		///<exception cref="MagickException"/>
		MagickImageStatistics Statistics();
		///==========================================================================================
		///<summary>
		/// Add a digital watermark to the image (based on second image)
		///</summary>
		///<param name="watermark">The image to use as a watermark.</param>
		///<exception cref="MagickException"/>
		void Stegano(MagickImage^ watermark);
		///==========================================================================================
		///<summary>
		/// Create an image which appears in stereo when viewed with red-blue glasses (Red image on
		/// left, blue on right)
		///</summary>
		///<param name="rightImage">The image to use as the right part of the resulting image.</param>
		///<exception cref="MagickException"/>
		void Stereo(MagickImage^ rightImage);
		///==========================================================================================
		///<summary>
		/// Strips an image of all profiles and comments.
		///</summary>
		///<exception cref="MagickException"/>
		void Strip();
		///==========================================================================================
		///<summary>
		/// Swirl image (image pixels are rotated by degrees).
		///</summary>
		///<param name="degrees">The number of degrees.</param>
		///<exception cref="MagickException"/>
		void Swirl(double degrees);
		///==========================================================================================
		///<summary>
		/// Channel a texture on image background.
		///</summary>
		///<param name="image">The image to use as a texture on image background.</param>
		///<exception cref="MagickException"/>
		void Texture(MagickImage^ image);
		///==========================================================================================
		///<summary>
		/// Threshold image.
		///</summary>
		///<param name="value">The threshold value.</param>
		///<exception cref="MagickException"/>
		void Threshold(double value);
		///==========================================================================================
		///<summary>
		/// Converts this instance to a base64 string.
		///</summary>
		String^ ToBase64();
		///==========================================================================================
		///<summary>
		/// Converts this instance to a bitmap using ImageFormat.Bitmap.
		///</summary>
		Bitmap^ ToBitmap();
		///==========================================================================================
		///<summary>
		/// Converts this instance to a bitmap using the specified ImageFormat. Supported formats are:
		/// Bmp, Gif, Icon, Jpeg, Png, Tiff.
		///</summary>
		Bitmap^ ToBitmap(ImageFormat^ imageFormat);
		///==========================================================================================
		///<summary>
		/// Converts this instance to a byte array.
		///</summary>
		array<Byte>^ ToByteArray();
		///==========================================================================================
		///<summary>
		/// Returns a string that represents the current image.
		///</summary>
		virtual String^ ToString() override;
		///==========================================================================================
		///<summary>
		/// Transform image based on image geometry.
		///</summary>
		///<param name="imageGeometry">The image geometry.</param>
		///<exception cref="MagickException"/>
		void Transform(MagickGeometry^ imageGeometry);
		///==========================================================================================
		///<summary>
		/// Transform image based on image geometry.
		///</summary>
		///<param name="imageGeometry">The image geometry.</param>
		///<param name="cropGeometry">The crop geometry.</param>
		///<exception cref="MagickException"/>
		void Transform(MagickGeometry^ imageGeometry, MagickGeometry^ cropGeometry);
		///==========================================================================================
		///<summary>
		/// Origin of coordinate system to use when annotating with text or drawing.
		///</summary>
		///<param name="x">The X coordinate.</param>
		///<param name="y">The Y coordinate.</param>
		///<exception cref="MagickException"/>
		void TransformOrigin(double x, double y);
		///==========================================================================================
		///<summary>
		/// Rotation to use when annotating with text or drawing.
		///</summary>
		///<param name="angle">The angle.</param>
		///<exception cref="MagickException"/>
		void TransformRotation(double angle);
		///==========================================================================================
		///<summary>
		/// Reset transformation parameters to default.
		///</summary>
		///<exception cref="MagickException"/>
		void TransformReset();
		///==========================================================================================
		///<summary>
		/// Scale to use when annotating with text or drawing.
		///</summary>
		///<param name="scaleX">The X coordinate scaling element.</param>
		///<param name="scaleY">The Y coordinate scaling element.</param>
		///<exception cref="MagickException"/>
		void TransformScale(double scaleX, double scaleY);
		///==========================================================================================
		///<summary>
		/// Skew to use in X axis when annotating with text or drawing.
		///</summary>
		///<param name="skewX">The X skew.</param>
		///<exception cref="MagickException"/>
		void TransformSkewX(double skewX);
		///==========================================================================================
		///<summary>
		/// Skew to use in Y axis when annotating with text or drawing.
		///</summary>
		///<param name="skewY">The Y skew.</param>
		///<exception cref="MagickException"/>
		void TransformSkewY(double skewY);
		///==========================================================================================
		///<summary>
		/// Add matte channel to image, setting pixels matching color to transparent.
		///</summary>
		///<param name="color">The color to make transparent.</param>
		///<exception cref="MagickException"/>
		void Transparent(MagickColor^ color);
		///==========================================================================================
		///<summary>
		/// Add matte image to image, for all the pixels that lies in between the given two colors.
		///</summary>
		///<exception cref="MagickException"/>
		void TransparentChroma(MagickColor^ colorLow, MagickColor^ colorHigh);
		///==========================================================================================
		///<summary>
		/// Trim edges that are the background color from the image.
		///</summary>
		///<exception cref="MagickException"/>
		void Trim();
		///==========================================================================================
		///<summary>
		/// Replace image with a sharpened version of the original image using the unsharp mask algorithm.
		///</summary>
		///<param name="radius">The radius of the Gaussian, in pixels, not counting the center pixel.</param>
		///<param name="sigma">The standard deviation of the Laplacian, in pixels.</param>
		///<param name="amount">The percentage of the difference between the original and the blur image
		/// that is added back into the original.</param>
		///<param name="threshold">The threshold in pixels needed to apply the diffence amount.</param>
		///<exception cref="MagickException"/>
		void Unsharpmask(double radius, double sigma, double amount, double threshold);
		///==========================================================================================
		///<summary>
		/// Replace image with a sharpened version of the original image using the unsharp mask algorithm.
		///</summary>
		///<param name="radius">The radius of the Gaussian, in pixels, not counting the center pixel.</param>
		///<param name="sigma">The standard deviation of the Laplacian, in pixels.</param>
		///<param name="amount">The percentage of the difference between the original and the blur image
		/// that is added back into the original.</param>
		///<param name="threshold">The threshold in pixels needed to apply the diffence amount.</param>
		///<param name="channels">The channel(s) that should be sharpened.</param>
		///<exception cref="MagickException"/>
		void Unsharpmask(double radius, double sigma, double amount, double threshold, Channels channels);
		///==========================================================================================
		///<summary>
		/// Map image pixels to a sine wave.
		///</summary>
		///<exception cref="MagickException"/>
		void Wave();
		///==========================================================================================
		///<summary>
		/// Map image pixels to a sine wave.
		///</summary>
		///<param name="amplitude">The amplitude.</param>
		///<param name="length">The length of the wave.</param>
		///<exception cref="MagickException"/>
		void Wave(double amplitude, double length);
		///==========================================================================================
		///<summary>
		/// Writes the image to the specified stream.
		///</summary>
		///<param name="stream">The stream to write the image data to.</param>
		///<exception cref="MagickException"/>
		void Write(Stream^ stream);
		///==========================================================================================
		///<summary>
		/// Writes the image to the specified file name.
		///</summary>
		///<param name="fileName">The fully qualified name of the image file, or the relative image file name.</param>
		///<exception cref="MagickException"/>
		void Write(String^ fileName);
		///==========================================================================================
		///<summary>
		// Zoom image to specified size.
		///</summary>
		///<param name="width">The new width.</param>
		///<param name="height">The new height.</param>
		///<exception cref="MagickException"/>
		void Zoom(int width, int height);
		///==========================================================================================
		///<summary>
		// Zoom image to specified size.
		///</summary>
		///<param name="percentage">The percentage.</param>
		///<exception cref="MagickException"/>
		void Zoom(Percentage percentage);
		///==========================================================================================
		///<summary>
		/// Zoom image to specified size.
		///</summary>
		///<param name="percentageWidth">The percentage of the width.</param>
		///<param name="percentageHeight">The percentage of the height.</param>
		///<exception cref="MagickException"/>
		void Zoom(Percentage percentageWidth, Percentage percentageHeight);
		};
		//==============================================================================================
	}