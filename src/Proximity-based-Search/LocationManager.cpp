#include "LocationManager.h"
#define M_PI 3.14159265358979323846
#include <cmath>

// Define addUserLocation method
void LocationManager::addUserLocation(const User& user) {
    users.push_back(user);
}

// Define getAllUsers method
std::vector<User> LocationManager::getAllUsers() const {
    return users;  // Return all registered users
}

// Define calculateDistance method
double LocationManager::calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371.0; // Earth radius in kilometers
    double lat1Rad = lat1 * M_PI / 180.0;
    double lon1Rad = lon1 * M_PI / 180.0;
    double lat2Rad = lat2 * M_PI / 180.0;
    double lon2Rad = lon2 * M_PI / 180.0;

    double dLat = lat2Rad - lat1Rad;
    double dLon = lon2Rad - lon1Rad;

    double a = sin(dLat / 2) * sin(dLat / 2) + cos(lat1Rad) * cos(lat2Rad) * sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return R * c; // Return distance in kilometers
}

// Define findUsersNearby method
std::vector<User> LocationManager::findUsersNearby(const User& currentUser, double maxDistance) const {
    std::vector<User> nearbyUsers;
    for (const auto& user : users) {
        double distance = calculateDistance(currentUser.getLatitude(), currentUser.getLongitude(),
                                            user.getLatitude(), user.getLongitude());
        if (distance <= maxDistance) {
            nearbyUsers.push_back(user);
        }
    }
    return nearbyUsers;
}
