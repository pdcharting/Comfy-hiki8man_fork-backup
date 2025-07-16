#pragma once

#include <vector>
#include "BeatTick.h"

namespace Comfy::Studio::Editor
{
	using EventID = int64_t;

	enum class EventKind
	{
		None          = 0,
		ChallengeTime = 1,
		ChanceTime    = 2,
		TechnicalZone = 3,
		Lyrics        = 4,
		Count
	};

	/*
	struct LyricsData
	{
		std::string Value = "";
		u32 Color = 0xFFFFFFFF;
	};
	*/

	struct TimedEvent
	{
		EventID ID;
		BeatTick StartTick;
		BeatTick EndTick;
		EventKind Kind;

		TimedEvent()
		{
			ID = 0;
			StartTick = BeatTick::FromTicks(0);
			EndTick = BeatTick::FromTicks(0);
			Kind = EventKind::None;
		}

		TimedEvent(EventKind kind, BeatTick start, BeatTick end) : Kind(kind), StartTick(start), EndTick(end)
		{
			ID = 0;
		} 
	};

	struct SortedEventList
	{
	public:
		TimedEvent& Add(TimedEvent src);
		void Remove(EventID id);
		i32 FindIndex(EventID id) const;
		void Sort();

		inline const std::vector<TimedEvent>& GetRawView() const { return data; }

		auto begin() { return data.begin(); }
		auto end() { return data.end(); }
		auto begin() const { return data.cbegin(); }
		auto end() const { return data.cend(); }

		inline TimedEvent& operator[](i32 index) { return data[index]; }
		void operator=(std::vector<TimedEvent>&& other);

	private:
		std::vector<TimedEvent> data;

		static EventID GetNextUniqueID();
	};
}