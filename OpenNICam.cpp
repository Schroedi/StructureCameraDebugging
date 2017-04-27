#include "OpenNICam.h"
#include <iostream>

// helper to quickly check for success on OpenNI calls
// throws an exception with error description if err != STATUS_OK
void checkOpenNiError(openni::Status err) {
    if (err != openni::STATUS_OK)
    {
        throw std::runtime_error("OpenNI2 Error:\n"
                                 + std::string(openni::OpenNI::getExtendedError()));
    }
}

OpenNICam::OpenNICam() {
    std::cout << "Init cam" << std::endl;
    openni::Status err;

    err = openni::OpenNI::initialize();
    checkOpenNiError(err);

    // register ourself for device callbacks
    openni::OpenNI::addDeviceConnectedListener(this);
    openni::OpenNI::addDeviceDisconnectedListener(this);
    openni::OpenNI::addDeviceStateChangedListener(this);

    // list all connected devices
    openni::Array<openni::DeviceInfo> deviceList;
    openni::OpenNI::enumerateDevices(&deviceList);
    for (int i = 0; i < deviceList.getSize(); ++i)
    {
        printf("Device \"%s\" is plugged in\n", deviceList[i].getUri());
    }

    // open any camera
    err = m_device.open(openni::ANY_DEVICE);
    if (err == openni::STATUS_OK)
    {
        // success case if camera has been freshly plugged in during the last ~3 seconds
        onDeviceOpened();
    } else {
        // currently no device is connected
        std::cout << "No device was opened. Waiting for events." << std::endl;
    }
}

OpenNICam::~OpenNICam() {
    m_device.close();
    openni::OpenNI::shutdown();
}

void OpenNICam::onDeviceOpened() {
    std::cout << "Success, device opened." << std::endl;
}

void OpenNICam::onDeviceConnected(const openni::DeviceInfo *device) {
    DeviceConnectListener::onDeviceConnected(device);

    openni::Status err;
    err = m_device.open(device->getUri());
    checkOpenNiError(err);
    onDeviceOpened();
}

void OpenNICam::onDeviceDisconnected(const openni::DeviceInfo *device) {
    DeviceConnectListener::onDeviceDisconnected(device);
    // do not close device here, this will crash
    //m_device.close();
}

void OpenNICam::onDeviceStateChanged(const openni::DeviceInfo *device, openni::DeviceState state) {
    DeviceConnectListener::onDeviceStateChanged(device, state);
}

