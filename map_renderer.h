#pragma once

#include "svg.h"

#include <map>
#include <vector>

namespace map_render
{
	struct MapSettings
	{
		double width = 0.0;
		double height = 0.0;
		double padding = 0.0;
		double line_width = 0.0;
		double stop_radius = 0.0;
		int bus_label_font_size = 0;
		std::pair<double, double> bus_label_offset;
		int stop_label_font_size = 0;
		std::pair<double, double> stop_label_offset;

		svg::Color underlayer_color;
		double underlayer_width = 0.0;
		std::vector<svg::Color> color_palette;
	};

	

	class MapRender
	{
	public:
	private:
	};
}	