//
// CONTROL.cpp
// Implementation of the CONTROL class.
//

#include "pch.h"
#include INCLUDE_FILE_X(CONTROL.h)

#if __has_include(INCLUDE_FILE_X(CONTROL.g.cpp))
#include INCLUDE_FILE_X(CONTROL.g.cpp)
#endif

namespace winrt::NAMESPACE::implementation {

    CONTROL::CONTROL() {
        InitializeComponent();
    }
    
    Windows::UI::Xaml::DependencyProperty CONTROL::m_labelProperty =
        Windows::UI::Xaml::DependencyProperty::Register(
            L"Label",
            winrt::xaml_typename<winrt::hstring>(),
            winrt::xaml_typename<winrt::NAMESPACE::CONTROL>(),
            Windows::UI::Xaml::PropertyMetadata{ winrt::box_value(winrt::hstring()) });


    Windows::UI::Xaml::DependencyProperty CONTROL::LabelProperty() {
        return m_labelProperty;
    }

    hstring CONTROL::Label() {
        return winrt::unbox_value<winrt::hstring>(GetValue(m_labelProperty));
    }

    void CONTROL::Label(hstring const& value) {
        SetValue(m_labelProperty, winrt::box_value(value));
    }

} // namespace winrt::NAMESPACE::implementation
