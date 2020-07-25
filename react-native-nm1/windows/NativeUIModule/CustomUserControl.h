//
// CustomUserControl.h
// Declaration of the CustomUserControl class.
//

#pragma once
#include "pch.h"
#include INCLUDE_FILE_X(CONTROL.g.h)

namespace winrt::NAMESPACE::implementation
{
	struct CONTROL : PPCAT(CONTROL, T)<CONTROL> {
		CONTROL();

		static Windows::UI::Xaml::DependencyProperty LabelProperty();

		hstring Label();
		void Label(hstring const& value);

		static void OnLabelChanged(
			Windows::UI::Xaml::DependencyObject const& d,
			Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e);

	private:
		static Windows::UI::Xaml::DependencyProperty m_labelProperty;
	};
}

namespace winrt::NAMESPACE::factory_implementation {
	struct CONTROL : PPCAT(CONTROL,T)<CONTROL, implementation::CONTROL> {};
} //

