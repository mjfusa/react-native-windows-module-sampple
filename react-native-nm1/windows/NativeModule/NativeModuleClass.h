#pragma once
#include "NativeModules.h"

namespace NAMESPACE {

	REACT_MODULE(MODULE);
	struct MODULE {

		REACT_METHOD(DeviceModel, L"deviceModel");
		winrt::hstring MODULE::DeviceModel() noexcept;
	
	};


} // namespace MODULE
