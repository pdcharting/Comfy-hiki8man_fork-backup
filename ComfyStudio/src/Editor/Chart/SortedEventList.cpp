#include <algorithm>
#include "SortedEventList.h"

using namespace Comfy::Studio::Editor;

TimedEvent& SortedEventList::Add(TimedEvent src)
{
	if (src.ID == 0)
		src.ID = GetNextUniqueID();

	auto it = data.begin();
	while (it != data.end())
	{
		if (src.StartTick >= it->StartTick)
		{
			it++;
			continue;
		}

		break;
	}

	return *data.emplace(it, src);
}

void SortedEventList::Remove(EventID id)
{
	for (auto it = data.begin(); it != data.end(); it++)
	{
		if (it->ID == id)
		{
			data.erase(it);
			break;
		}
	}
}

i32 SortedEventList::FindIndex(EventID id) const
{
	for (size_t i = 0; i < data.size(); i++)
	{
		if (data[i].ID == id)
			return static_cast<i32>(i);
	}

	return -1;
}

void SortedEventList::Sort()
{
	std::sort(data.begin(), data.end(), [](TimedEvent& ev1, TimedEvent& ev2) { return ev1.StartTick < ev2.StartTick; });
}

void SortedEventList::operator=(std::vector<TimedEvent>&& other)
{
	data = std::move(other);
	Sort();
	for (TimedEvent& event : data)
		event.ID = GetNextUniqueID();

}

EventID SortedEventList::GetNextUniqueID()
{
	static EventID GlobalTimedEventID = 0;
	return ++GlobalTimedEventID;
}