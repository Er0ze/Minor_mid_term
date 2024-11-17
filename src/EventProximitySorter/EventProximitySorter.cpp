#include "EventProximitySorter.h"
#include "LocationManager.h"
#include <algorithm> // for std::sort

std::vector<Event> EventProximitySorter::sortEventsByProximity(const User& user, const std::vector<Event>& events) {
    std::vector<Event> sortedEvents = events;

    // Sorting events by proximity to the user's location
    std::sort(sortedEvents.begin(), sortedEvents.end(), [&user](const Event& a, const Event& b) {
        // Accessing event location through getLocation() and then getting latitude and longitude
        double distanceA = LocationManager::calculateDistance(
            user.getLatitude(), user.getLongitude(),  // Use getLatitude and getLongitude from User
            a.getLocation().getLatitude(), a.getLocation().getLongitude()  // Use getLocation(), then get latitude and longitude from Event
        );
        double distanceB = LocationManager::calculateDistance(
            user.getLatitude(), user.getLongitude(),  // Use getLatitude and getLongitude from User
            b.getLocation().getLatitude(), b.getLocation().getLongitude()  // Use getLocation(), then get latitude and longitude from Event
        );
        return distanceA < distanceB;
    });

    return sortedEvents;
}
