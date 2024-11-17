#include <iostream>
#include <vector>
#include "User.h"
#include "UserAccountManagement/UserAccountManager.h"
#include "EventManager/Event.h"
#include "EventManager/EventManager.h"
#include "Proximity-based-Search/LocationManager.h"
#include "EventProximitySorter/EventProximitySorter.h"
#include "RecommendationEngine/RecommendationEngine.h"
#include "AlphabeticalSorting/AlphabeticalSorter.h"
#define M_PI 3.14159265358979323846
#include <cmath>


class User {
private:
    int id;
    std::string username;
    std::string name;
    std::string email;
    double latitude;
    double longitude;

public:
    // Constructor with matching types
    User(int id, const std::string& username, const std::string& name, const std::string& email,
         double latitude, double longitude)
        : id(id), username(username), name(name), email(email), latitude(latitude), longitude(longitude) {}

    // Getter methods
    int getId() const { return id; }
    std::string getUsername() const { return username; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
};

class LocationManager {
public:
    // Haversine formula to calculate distance between two points
    double getDistance(double lat1, double lon1, double lat2, double lon2) const {
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

    // Find nearby users within a given distance
    std::vector<User> findUsersNearby(const User& currentUser, double maxDistance) {
        std::vector<User> nearbyUsers;
        // Loop through the list of all users (assumed to be stored somewhere)
        for (const auto& user : allUsers) {
            double distance = getDistance(currentUser.getLatitude(), currentUser.getLongitude(),
                                          user.getLatitude(), user.getLongitude());
            if (distance <= maxDistance) {
                nearbyUsers.push_back(user);
            }
        }
        return nearbyUsers;
    }

private:
    std::vector<User> allUsers; // List of all users, assumed to be managed elsewhere
};

int main() {
    // Create instances of necessary managers
    LocationManager locationManager;
    EventManager eventManager;
    UserAccountManager userAccountManager;
    EventProximitySorter eventSorter;
    RecommendationEngine recommendationEngine;

    // User registration
    std::cout << "Welcome to Sports Buddy!\n";
    std::cout << "Please register users.\n";

    int userId = 1; // Example unique ID generator for users
    while (true) {
        std::string username, name, email;
        double latitude, longitude;

        std::cout << "Enter username (or type 'exit' to finish): ";
        std::getline(std::cin, username);
        if (username == "exit") break;

        std::cout << "Enter name: ";
        std::getline(std::cin, name);

        std::cout << "Enter email: ";
        std::getline(std::cin, email);

        std::cout << "Enter latitude: ";
        std::cin >> latitude;

        std::cout << "Enter longitude: ";
        std::cin >> longitude;
        std::cin.ignore(); // Clear newline from input buffer

        User newUser(userId++, username, name, email, latitude, longitude);
        locationManager.addUserLocation(newUser);
        std::cout << "User registered successfully!\n\n";
    }

    // Event creation
    std::cout << "Now let's create some events.\n";
    while (true) {
        int eventId;
        std::string eventName;
        double eventLatitude, eventLongitude;

        std::cout << "Enter event ID (or type '-1' to finish): ";
        std::cin >> eventId;
        if (eventId == -1) break;

        std::cout << "Enter event name: ";
        std::cin.ignore(); // Clear newline from input buffer
        std::getline(std::cin, eventName);

        std::cout << "Enter event latitude: ";
        std::cin >> eventLatitude;

        std::cout << "Enter event longitude: ";
        std::cin >> eventLongitude;
        std::cin.ignore(); // Clear newline from input buffer

        Location eventLocation(eventLatitude, eventLongitude);
        Event newEvent(eventId, eventName, eventLocation);
        eventManager.addEvent(newEvent);
        std::cout << "Event created successfully!\n\n";
    }

    // User registration for events
    std::cout << "Register users for events.\n";
    while (true) {
        int eventId;
        std::string username;

        std::cout << "Enter event ID to register (or type '-1' to finish): ";
        std::cin >> eventId;
        if (eventId == -1) break;

        std::cout << "Enter username of the user to register: ";
        std::cin.ignore(); // Clear newline from input buffer
        std::getline(std::cin, username);

        // Assuming User is uniquely identified by username
        User userToRegister(0, username, "", "", 0.0, 0.0); // Dummy user object
        eventManager.registerUserForEvent(eventId, userToRegister);
        std::cout << "User registered for event successfully!\n\n";
    }

    // Example of finding nearby users
    std::cout << "Find nearby users.\n";
    std::string currentUserUsername;
    std::cout << "Enter your username to find nearby users: ";
    std::getline(std::cin, currentUserUsername);

    // Find the current user by username
    std::vector<User> nearbyUsers = locationManager.findUsersNearby(User(0, currentUserUsername, "", "", 0.0, 0.0), 0);
    if (!nearbyUsers.empty()) {
        User currentUser = nearbyUsers.at(0);
        
        double maxDistance;
        std::cout << "Enter maximum distance to find nearby users (in km): ";
        std::cin >> maxDistance;

        std::cout << "Nearby Users to " << currentUser.getUsername() << ":\n";
        nearbyUsers = locationManager.findUsersNearby(currentUser, maxDistance);
        for (const auto& user : nearbyUsers) {
            std::cout << user.getUsername() << " - " << user.getName() << "\n";
        }

        // Example of sorting events by proximity
        std::vector<Event> events = eventManager.getEventsForUser(currentUser);
        std::vector<Event> sortedEvents = eventSorter.sortEventsByProximity(currentUser, events);

        std::cout << "Events sorted by proximity to " << currentUser.getUsername() << ":\n";
        for (const auto& event : sortedEvents) {
            std::cout << event.getId() << ": " << event.getName() << "\n";
        }

        // Example of using the recommendation engine (if applicable)
        std::vector<User> recommendedUsers = recommendationEngine.getRecommendations(currentUser, 10.0); // Using a range of 10 for now
        std::cout << "Recommended Users for " << currentUser.getUsername() << ":\n";

        // Display recommended users
        for (const auto& user : recommendedUsers) {
            std::cout << user.getUsername() << " - " << user.getName() << "\n";
        }

        // Now, filter or process events based on the recommended users' proximity
        std::vector<Event> recommendedEvents;  // We'll populate this with events linked to recommended users
        for (const auto& user : recommendedUsers) {
            // Assuming you have a function in EventManager or elsewhere that returns events based on proximity
            std::vector<Event> userEvents = eventManager.getEventsForUser(user);  // Get events for the recommended user

            // Optionally filter the events based on proximity or other criteria
            for (const auto& event : userEvents) {
                // You could apply any further logic to filter events based on currentUser's proximity
                if (locationManager.getDistance(currentUser.getLatitude(), currentUser.getLongitude(),
                        event.getLocation().getLatitude(), event.getLocation().getLongitude()) <= maxDistance) {
                    recommendedEvents.push_back(event);  // Add to the recommended events list
                }
            }
        }

        std::cout << "Recommended Events for " << currentUser.getUsername() << ":\n";
        for (const auto& event : recommendedEvents) {
            std::cout << event.getId() << ": " << event.getName() << "\n";
        }
    } else {
        std::cout << "No user found with the given username.\n";
    }

    return ;

}