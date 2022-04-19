#pragma once
#include "transport_catalogue.h"

#include <string_view>

namespace request_handler
{
	void GetRequest(tc::TransportCatalogue& transp_cat);
}
