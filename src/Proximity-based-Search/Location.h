// Location.h
#ifndef LOCATION_H
#define LOCATION_H

class Location {
public:
    Location(double latitude, double longitude)
        : latitude(latitude), longitude(longitude) {}

    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }

private:
    double latitude;
    double longitude;
};

#endif // LOCATION_H
