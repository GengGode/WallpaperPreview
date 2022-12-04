#pragma once
#include <winrt/Microsoft.UI.Xaml.Media.Imaging.h>
#include <winrt/Windows.UI.Xaml.Data.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.FileProperties.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.System.Threading.h>

using namespace winrt::Microsoft::UI::Xaml::Media::Imaging;
using namespace winrt::Windows::UI::Xaml::Data;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::FileProperties;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Foundation;


namespace winrt::WallpaperPreviewApp::implementation
{
	class ImageFileInfo : public winrt::implements<ImageFileInfo, winrt::Windows::UI::Xaml::Data::INotifyPropertyChanged>
	{
	public:
		ImageFileInfo(ImageProperties const& properties, StorageFile const& imageFile, winrt::hstring  const& name, winrt::hstring const& type);
	public:
		StorageFile ImageFile();
		ImageProperties Properties();	
	public:
		// C#: public async Task<BitmapImage> GetImageSourceAsync()
		// C++: winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::UI::Xaml::Media::Imaging::BitmapImage> GetImageSourceAsync();
		IAsyncOperation<BitmapImage> GetImageSourceAsync();
	public:
		// C#: public async Task<BitmapImage> GetImageThumbnailAsync()
		// C++: winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::UI::Xaml::Media::Imaging::BitmapImage> GetImageThumbnailAsync();
		IAsyncOperation<BitmapImage> GetImageThumbnailAsync();
	public:
		winrt::hstring ImageName();
		winrt::hstring ImageFileType();
	public:	
		// C#: public string ImageDimensions => $"{ImageProperties.Width} x {ImageProperties.Height}";
		// C++: winrt::hstring ImageDimensions() { return winrt::to_hstring(m_imageProperties.Width()) + L" x " + winrt::to_hstring(m_imageProperties.Height()); }
		winrt::hstring ImageDimensions() { return winrt::to_hstring(m_imageProperties.Width()) + L" x " + winrt::to_hstring(m_imageProperties.Height()); }
	public:
		winrt::hstring ImageTitle();
		void ImageTitle(winrt::hstring const& value);
	public:
		int ImageRating();
		void ImageRating(int const& value);
	public:
		// C#: public event PropertyChangedEventHandler PropertyChanged;
		// C++: winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& value);
		winrt::event_token PropertyChanged(PropertyChangedEventHandler const& value);
		void PropertyChanged(winrt::event_token const& token);
			

	protected:
		// C#: protected void OnPropertyChanged([CallerMemberName] string propertyName = null) = >PropertyChanged ? .Invoke(this, new PropertyChangedEventArgs(propertyName));
		// C++: void OnPropertyChanged(winrt::hstring const& propertyName) { PropertyChanged(*this, PropertyChangedEventArgs(propertyName)); }
		void OnPropertyChanged(winrt::hstring const& propertyName = L"");


	private:
		StorageFile m_imageFile{ nullptr };
		ImageProperties m_imageProperties{ nullptr };
		winrt::hstring m_iamgeName;
		winrt::hstring m_imageFileType;
		winrt::event<PropertyChangedEventHandler> m_propertyChanged;
	};
}