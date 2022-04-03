#include "core.h"

void addTestItems(Repository<Event>& eventRepo)
{
	eventRepo.save(-2, Event(0, "Event0", "Description0", DateTime(2022, 12, 1, 0, 0, 0), 10, "www.link0.com"));
	eventRepo.save(-2, Event(0, "Event1", "Description1", DateTime(2022, 12, 1, 0, 0, 0), 11, "www.link1.com"));
	eventRepo.save(-2, Event(0, "Event2", "Description2", DateTime(2022, 12, 2, 0, 0, 0), 12, "www.link2.com"));
	eventRepo.save(-2, Event(0, "Event3", "Description3", DateTime(2022, 12, 3, 0, 0, 0), 13, "www.link3.com"));
	eventRepo.save(-2, Event(0, "Event4", "Description4", DateTime(2022, 12, 4, 0, 0, 0), 14, "www.link4.com"));
	eventRepo.save(-2, Event(0, "Event5", "Description5", DateTime(2022, 12, 5, 0, 0, 0), 15, "www.link5.com"));
	eventRepo.save(-2, Event(0, "Event6", "Description6", DateTime(2022, 12, 6, 0, 0, 0), 16, "www.link6.com"));
	eventRepo.save(-2, Event(0, "Event7", "Description7", DateTime(2022, 12, 7, 0, 0, 0), 17, "www.link7.com"));
	eventRepo.save(-2, Event(0, "Event8", "Description8", DateTime(2022, 12, 8, 0, 0, 0), 18, "www.link8.com"));
	eventRepo.save(-2, Event(0, "Event9", "Description9", DateTime(2022, 12, 9, 0, 0, 0), 19, "www.link9.com"));
}
