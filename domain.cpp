#include "domain.h"

namespace domain
{
	Bus::Bus(std::string name, std::vector<Stop*>&& stops, bool is_round)
		: _bus_name(move(name))
		, _stops(move(stops))
		, _total_stops(_stops.size())
		, _is_round_route(is_round)
	{
		_total_unique_stops = std::set<Stop*>(_stops.begin(), _stops.end()).size();
		_route_length_straight = 0;
		_route_length_normal = 0;
		for (size_t i = 0; i < _stops.size() - 1; i++)
		{
			_route_length_straight += ComputeDistance(_stops[i]->GetCoordinates(),
				_stops[i + 1]->GetCoordinates());

			std::string_view cur_stop = _stops[i]->GetName();
			std::string_view next_stop = _stops[i + 1]->GetName();

			std::optional<double> dist_to = _stops[i]->GetDistanceToOtherStop(static_cast<std::string>(next_stop));
			if (dist_to.has_value())
			{
				_route_length_normal += dist_to.value();
			}
			else
			{
				_route_length_normal += _stops[i + 1]->GetDistanceToOtherStop(static_cast<std::string>(cur_stop)).value();
			}
		}
	}

	std::string_view Bus::GetName()
	{
		return _bus_name;
	}

	int Bus::GetTotalStops()
	{
		return _total_stops;
	}

	int Bus::GetTotalUniqueStopst()
	{
		return _total_unique_stops;
	}

	double Bus::GetRouteLength()
	{
		return _route_length_normal;
	}

	double Bus::GetRouteLengthStraight()
	{
		return _route_length_straight;
	}

	double Bus::GetCurvature()
	{
		return GetRouteLength() / GetRouteLengthStraight();
	}

	Stop::Stop(StopParams&& stop)
		: _stop_name(std::move(std::get<0>(stop))),
		_coordinates(std::move(std::get<1>(stop))),
		_distance_to_other_stop(std::move(std::get<2>(stop)))
	{
	}

	std::string_view Stop::GetName()
	{
		return _stop_name;
	}

	void Stop::AddBus(std::string bus_name)
	{
		_buses.insert(bus_name);
	}

	geo::Coordinates Stop::GetCoordinates()
	{
		return _coordinates;
	}

	std::set<std::string> Stop::GetBuses()
	{
		return _buses;
	}

	void Stop::AddDistToOthStop(std::string stop, long distance)
	{
		_distance_to_other_stop[stop] = distance;
	}

	std::optional<double> Stop::GetDistanceToOtherStop(std::string other_stop)
	{
		if (_distance_to_other_stop.count(other_stop))
		{
			return { _distance_to_other_stop[other_stop] };
		}
		else
		{
			return std::nullopt;
		}
	}
}