// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include <winrt/Windows.UI.Xaml.Media.h>

#include INCLUDE_FILE_X(VIEWMANAGER.h)
#include "JSValueReader.h"
#include "JSValueXaml.h"
#include "NativeModules.h"

#include INCLUDE_FILE_X(CONTROL.h)


using namespace winrt;
using namespace Microsoft::ReactNative;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Controls;

namespace winrt::NAMESPACE::implementation {

    VIEWMANAGER::VIEWMANAGER() {}

    // IViewManager
    hstring VIEWMANAGER::Name() noexcept {
        return CLASS_NAME(CONTROL);
    }

    FrameworkElement VIEWMANAGER::CreateView() noexcept {
        auto const& view = winrt::NAMESPACE::CONTROL();

        view.RegisterPropertyChangedCallback(
            winrt::NAMESPACE::CONTROL::LabelProperty(),
            [this](
                winrt::Windows::UI::Xaml::DependencyObject obj, winrt::Windows::UI::Xaml::DependencyProperty prop) noexcept {
                    if (auto c = obj.try_as<winrt::NAMESPACE::CONTROL>()) {
                        ReactContext().DispatchEvent(
                            c,
                            L"topLabelChanged",
                            [this, c](winrt::Microsoft::ReactNative::IJSValueWriter const& eventDataWriter) noexcept {
                                eventDataWriter.WriteString(c.Label());
                            });
                    }
            });

        return view;
    }

    // IViewManagerWithReactContext
    IReactContext VIEWMANAGER::ReactContext() noexcept {
        return m_reactContext;
    }

    void VIEWMANAGER::ReactContext(IReactContext reactContext) noexcept {
        m_reactContext = reactContext;
    }

    // IViewManagerWithNativeProperties
    IMapView<hstring, ViewManagerPropertyType> VIEWMANAGER::NativeProps() noexcept {
        auto nativeProps = winrt::single_threaded_map<hstring, ViewManagerPropertyType>();

        nativeProps.Insert(L"label", ViewManagerPropertyType::String);
        nativeProps.Insert(L"color", ViewManagerPropertyType::Color);
        nativeProps.Insert(L"backgroundColor", ViewManagerPropertyType::Color);

        return nativeProps.GetView();
    }

    void VIEWMANAGER::UpdateProperties(
        FrameworkElement const& view,
        IJSValueReader const& propertyMapReader) noexcept {
        if (auto control = view.try_as<winrt::NAMESPACE::CONTROL>()) {
            JSValueObject propertyMap = JSValueObject::ReadFrom(propertyMapReader);

            for (auto const& pair : propertyMap) {
                auto const& propertyName = pair.first;
                auto const& propertyValue = pair.second;

                if (propertyName == "label") {
                    if (!propertyValue.IsNull()) {
                        auto value = winrt::box_value(winrt::to_hstring(propertyValue.AsString()));
                        control.SetValue(winrt::NAMESPACE::CONTROL::LabelProperty(), value);
                    }
                    else {
                        control.ClearValue(winrt::NAMESPACE::CONTROL::LabelProperty());
                    }
                }
                else if (propertyName == "color") {
                    if (auto value = propertyValue.To<Brush>()) {
                        control.SetValue(Control::ForegroundProperty(), value);
                    }
                    else {
                        control.ClearValue(Control::ForegroundProperty());
                    }
                }
                else if (propertyName == "backgroundColor") {
                    if (auto value = propertyValue.To<Brush>()) {
                        control.SetValue(Control::BackgroundProperty(), value);
                    }
                    else {
                        control.ClearValue(Control::BackgroundProperty());
                    }
                }
            }
        }
    }

    // IViewManagerWithCommands
    IVectorView<hstring> VIEWMANAGER::Commands() noexcept {
        auto commands = winrt::single_threaded_vector<hstring>();
        commands.Append(L"CustomCommand");
        return commands.GetView();
    }

    void VIEWMANAGER::DispatchCommand(
        FrameworkElement const& view,
        winrt::hstring const& commandId,
        IJSValueReader const& commandArgsReader) noexcept {
        if (auto control = view.try_as<winrt::NAMESPACE::CONTROL>()) {
            if (commandId == L"CustomCommand") {
                std::string arg = std::to_string(winrt::unbox_value<int64_t>(view.Tag()));
                arg.append(", \"");
                arg.append(winrt::to_string(commandArgsReader.GetString()));
                arg.append("\"");
                //::NAMESPACE::DebugWriteLine(to_string(Name()), "CustomCommand", arg);
            }
        }
    }

    // IViewManagerWithExportedEventTypeConstants
    ConstantProviderDelegate VIEWMANAGER::ExportedCustomBubblingEventTypeConstants() noexcept {
        return nullptr;
    }

    ConstantProviderDelegate VIEWMANAGER::ExportedCustomDirectEventTypeConstants() noexcept {
        return [](winrt::Microsoft::ReactNative::IJSValueWriter const& constantWriter) {
            constantWriter.WritePropertyName(L"topLabelChanged");
            constantWriter.WriteObjectBegin();
            WriteProperty(constantWriter, L"registrationName", L"onLabelChanged");
            constantWriter.WriteObjectEnd();
        };
    }

} // namespace winrt::NAMESPACE::implementation
