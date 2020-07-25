#include "pch.h"
#include INCLUDE_FILE_X(MODULE.h)

#include <winrt/Windows.Security.ExchangeActiveSyncProvisioning.h>

using namespace winrt::Windows::Security::ExchangeActiveSyncProvisioning;
using namespace NAMESPACE;

winrt::hstring MODULE::DeviceModel() noexcept {
  auto info = EasClientDeviceInformation();
  return info.SystemProductName();
}
