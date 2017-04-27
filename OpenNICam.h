#ifndef DYNCAM_OPENNICAM_H
#define DYNCAM_OPENNICAM_H

#include <thread>
#include <opencv2/core/mat.hpp>

#include "OpenNI.h"


// Basic connection listener that prints the camera's name and event description
class DeviceConnectListener : public openni::OpenNI::DeviceConnectedListener
        , public openni::OpenNI::DeviceDisconnectedListener, public openni::OpenNI::DeviceStateChangedListener
{
public:

    virtual void onDeviceConnected( const openni::DeviceInfo* device )
    {
        printf("onDeviceConnected : %s \n", device->getName());
    }

    virtual void onDeviceDisconnected( const openni::DeviceInfo* device )
    {
        printf("onDeviceDisconnected : %s \n", device->getName());
    }

    virtual void onDeviceStateChanged(const openni::DeviceInfo* device, openni::DeviceState state)
    {
        printf("onDeviceChanged : %s code: %d  \n", device->getName(), state);
    }
};

// Basic camera wrapper. Most likely only works for one OpenNI camera at a time
class OpenNICam  : public DeviceConnectListener {
public:
    OpenNICam();
    virtual ~OpenNICam();

protected:
    // Called after a camera has successfully been opened
    void onDeviceOpened();

    // Device events reported by OpenNI
    virtual void onDeviceConnected( const openni::DeviceInfo* device );
    virtual void onDeviceDisconnected( const openni::DeviceInfo* device );
    virtual void onDeviceStateChanged(const openni::DeviceInfo* device, openni::DeviceState state);

    // handles for our device
    openni::Device m_device;
};


#endif //DYNCAM_OPENNICAM_H
