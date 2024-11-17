#ifndef USER_H
#define USER_H

#include <string>
using namespace std;
class User {
private:
    int id;
    std::string username;
    std::string name;
    std::string email;
    double latitude;
    double longitude;

public:
    // Constructor and other methods

    // Getter for ID
    int getId() const { return id; }

    // Other getters
    std::string getUsername() const { return username; }
    std::string getName() const { return name; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
};

#endif // USER_H
