#include "pch.h"
#include "ImageFileInfo.h"

winrt::WallpaperPreview::implementation::ImageFileInfo::ImageFileInfo(ImageProperties const& properties, StorageFile const& imageFile, winrt::hstring const& name, winrt::hstring const& type)
{
	m_imageProperties = properties;
	m_iamgeName = name;
	m_imageFileType = type;
	m_imageFile = imageFile;
}

StorageFile winrt::WallpaperPreview::implementation::ImageFileInfo::ImageFile()
{
	return m_imageFile;
}

ImageProperties winrt::WallpaperPreview::implementation::ImageFileInfo::Properties()
{
	return m_imageProperties;
}

IAsyncOperation<BitmapImage> winrt::WallpaperPreview::implementation::ImageFileInfo::GetImageSourceAsync()
{
	IRandomAccessStream fileStream = co_await m_imageFile.OpenAsync(FileAccessMode::Read);
	
	BitmapImage bitmapImage;
	bitmapImage.SetSource(fileStream);
	co_return bitmapImage;
}

IAsyncOperation<BitmapImage> winrt::WallpaperPreview::implementation::ImageFileInfo::GetImageThumbnailAsync()
{
	StorageItemThumbnail thumbnail = co_await m_imageFile.GetThumbnailAsync(ThumbnailMode::PicturesView, 200);
	
	BitmapImage bitmapImage;
	bitmapImage.SetSource(thumbnail);
	co_return bitmapImage;
}

winrt::hstring winrt::WallpaperPreview::implementation::ImageFileInfo::ImageName()
{
	return m_iamgeName;
}

winrt::hstring winrt::WallpaperPreview::implementation::ImageFileInfo::ImageFileType()
{
	return m_imageFileType;
}

winrt::hstring winrt::WallpaperPreview::implementation::ImageFileInfo::ImageTitle()
{
	return m_imageProperties.Title().empty() ? m_iamgeName : m_imageProperties.Title(); 
}

void winrt::WallpaperPreview::implementation::ImageFileInfo::ImageTitle(winrt::hstring const& value)
{
	if (m_imageProperties.Title() != value)
	{
		m_imageProperties.Title(value);
		m_imageProperties.SavePropertiesAsync();
		OnPropertyChanged();
	}
}

int winrt::WallpaperPreview::implementation::ImageFileInfo::ImageRating()
{
	return (int)m_imageProperties.Rating();
}

void winrt::WallpaperPreview::implementation::ImageFileInfo::ImageRating(int const& value)
{
	if (m_imageProperties.Rating() != (uint32_t)value)
	{
		m_imageProperties.Rating((uint32_t)value);
		m_imageProperties.SavePropertiesAsync();
		OnPropertyChanged();
	}
}

winrt::event_token winrt::WallpaperPreview::implementation::ImageFileInfo::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& value)
{
	return m_propertyChanged.add(value);
}

void winrt::WallpaperPreview::implementation::ImageFileInfo::PropertyChanged(winrt::event_token const& token)
{
	m_propertyChanged.remove(token);
}

void winrt::WallpaperPreview::implementation::ImageFileInfo::OnPropertyChanged(winrt::hstring const& propertyName)
{
	m_propertyChanged(*this, PropertyChangedEventArgs(propertyName));
}
