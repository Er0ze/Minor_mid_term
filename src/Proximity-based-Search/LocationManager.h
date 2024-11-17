#ifndef LOCATION_MANAGER_H
#define LOCATION_MANAGER_H

#include "User.h"
#include <vector>

class LocationManager {
public:
    void addUserLocation(const User& user);  // Method to add user location
    std::vector<User> findUsersNearby(const User& user, double maxDistance) const;  // Method to find nearby users
    std::vector<User> getAllUsers() const;  // New method to get all users
    static double calculateDistance(double lat1, double lon1, double lat2, double lon2);  // Static method to calculate distance

private:
    std::vector<User> users;  // Stores all users
};

#endif // LOCATION_MANAGER_H
