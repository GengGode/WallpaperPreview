#pragma once
#include "MainWindow.g.h"
#include "ImageFileInfo.h"
#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.Storage.Search.h>

using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Search;

namespace winrt::WallpaperPreview::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        int32_t MyProperty();
        void MyProperty(int32_t value);

		// C#: public ObservableCollection<ImageFileInfo> Images { get; } = new ObservableCollection<ImageFileInfo>();
		// C++: winrt::Windows::UI::Xaml::Interop::IBindableObservableVector Images() { return m_images; }
		winrt::Windows::UI::Xaml::Interop::IBindableObservableVector Images() { return m_images; }
		winrt::Windows::UI::Xaml::Interop::IBindableObservableVector m_images;
		
		IAsyncAction MainWindow::GetItemsAsync()
		{
			StorageFolder appInstalledFolder = Package::Current().InstalledLocation();
			StorageFolder picturesFolder = co_await appInstalledFolder.GetFolderAsync(L"Assets\\Samples");

			// C#: var result = picturesFolder.CreateFileQueryWithOptions(new QueryOptions());
			// C++: auto result = picturesFolder.CreateFileQueryWithOptions(QueryOptions());
			auto result = picturesFolder.CreateFileQueryWithOptions(QueryOptions());
		
			// C#: IReadOnlyList<StorageFile> imageFiles = await result.GetFilesAsync();
			// C++: auto imageFiles = co_await result.GetFilesAsync();
			auto imageFiles = co_await result.GetFilesAsync();
		
			for (auto imageFile : imageFiles)
			{
				Images().Append(winrt::make<ImageFileInfo>(imageFile));
			}

			// C#: ImageGridView.ItemsSource = Images;
			// C++: ImageGridView().ItemsSource(Images());
			ImageGridView().ItemsSource(Images());
		}

		static IAsyncOperation<ImageFileInfo> LoadImageInfo(StorageFile file)
		{
			// C#: var properties = await file.Properties.GetImagePropertiesAsync();
			// C++: auto properties = co_await file.Properties().GetImagePropertiesAsync();
			auto properties = co_await file.Properties().GetImagePropertiesAsync();
			// C#: ImageFileInfo info = new(properties, file, file.DisplayName, file.DisplayType);
			// C++: auto info = winrt::make<ImageFileInfo>(properties, file, file.DisplayName(), file.DisplayType());
			auto info = winrt::make<ImageFileInfo>(properties, file, file.DisplayName(), file.DisplayType());
			
			co_return info;
		}
    };
	
}

namespace winrt::WallpaperPreview::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}


/* C#:
using System.Threading.Tasks;
using Windows.ApplicationModel;
using Windows.Storage;
using Windows.Storage.Search;
...
private async Task GetItemsAsync()
{
    StorageFolder appInstalledFolder = Package.Current.InstalledLocation;
    StorageFolder picturesFolder = await appInstalledFolder.GetFolderAsync("Assets\\Samples");

    var result = picturesFolder.CreateFileQueryWithOptions(new QueryOptions());

    IReadOnlyList<StorageFile> imageFiles = await result.GetFilesAsync();
    foreach (StorageFile file in imageFiles)
    {
        Images.Add(await LoadImageInfo(file));
    }

    ImageGridView.ItemsSource = Images;
}

public async static Task<ImageFileInfo> LoadImageInfo(StorageFile file)
{
    var properties = await file.Properties.GetImagePropertiesAsync();
    ImageFileInfo info = new(properties,
                             file, file.DisplayName, file.DisplayType);

    return info;
}
*/

/* C++:
#include "pch.h"
#include "MainWindow.xaml.h"
#include "ImageFileInfo.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::Search;

IAsyncOperation<ImageFileInfo> LoadImageInfo(StorageFile file)
{
	ImageProperties properties = co_await file.Properties().GetImagePropertiesAsync();
	ImageFileInfo info = { properties, file, file.DisplayName(), file.DisplayType() };

	co_return info;
}

IAsyncAction MainWindow::GetItemsAsync()
{
	StorageFolder appInstalledFolder = Package::Current().InstalledLocation();
	StorageFolder picturesFolder = co_await appInstalledFolder.GetFolderAsync(L"Assets\\Samples");

	QueryOptions options;
	StorageFileQueryResult result = picturesFolder.CreateFileQueryWithOptions(options);

	IReadOnlyList<StorageFile> imageFiles = co_await result.GetFilesAsync();
	for (StorageFile file : imageFiles)
	{
		Images().Append(co_await LoadImageInfo(file));
	}

	ImageGridView().ItemsSource(Images());
}
*/

