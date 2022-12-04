// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "MainWindow.g.h"
#include "ImageFileInfo.h"

using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Search;

namespace winrt::WallpaperPreviewApp::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);


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
			auto info = winrt::make<implementation::ImageFileInfo>(properties, file, file.DisplayName(), file.DisplayType());

			co_return info;
		}
    };
}

namespace winrt::WallpaperPreviewApp::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
