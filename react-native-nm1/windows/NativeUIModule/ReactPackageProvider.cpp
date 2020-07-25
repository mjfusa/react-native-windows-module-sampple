// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "ReactPackageProvider.h"
#if __has_include("ReactPackageProvider.g.cpp")
#include "ReactPackageProvider.g.cpp"
#endif

#ifdef NATIVE_MODULE
#include INCLUDE_FILE_X(MODULE.h)
#endif

#ifdef NATIVE_UI_MODULE
#include INCLUDE_FILE_X(VIEWMANAGER.h)
#endif

using namespace winrt::Microsoft::ReactNative;

namespace winrt::NAMESPACE::implementation {

    void ReactPackageProvider::CreatePackage(IReactPackageBuilder const& packageBuilder) noexcept {

        //AddAttributedModules(packageBuilder);
        
        packageBuilder.AddViewManager(
            CLASS_NAME(VIEWMANAGER) , []() { return winrt::make<VIEWMANAGER>(); });
        
    }

} // namespace winrt::<Namespace>::implementation
