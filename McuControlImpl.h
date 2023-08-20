#pragma once

#include <LFramework/COM/ComLibrary.h>
#include <MicroNetwork.Task.MemoryAccess.IStream.IoStreamDescriptor.h>
#include <MicroNetwork/User/Link.h>
#include <McuControl.h>
#include <iostream>
#include <mutex>

namespace McuControl {
    class Impl : public LFramework::ComImplement<Impl, MicroNetwork::User::Link<MicroNetwork::Task::MemoryAccess::IStreamIoStreamDescriptor>, MicroNetwork::Task::MemoryAccess::IDeviceToHost, IMcuControl> {
      public: 
        ~Impl() {
            std::cout << "TestTaskHost::~dtor" << std::endl;
        }
        void setOutputStream(LFramework::ComPtr<MicroNetwork::Task::MemoryAccess::IHostToDevice> outStream) override {
            _outStream = outStream;
        }
    
        //Device to host
        void readResponse(MicroNetwork::Task::MemoryAccess::MemoryBlob response) {
            std::cout  << "readResponse: address = " << response.header.address << " size = " << response.header.size << std::endl;
            const std::uint8_t* data = reinterpret_cast<const std::uint8_t*>(&response.data);
            std::cout  << "data = " << data[0] << ", " << data[1] << " ..."  << std::endl;
    
        }
        void writeResponse(bool success) {
            std::cout  << "writeResponse";
        }
    
    
        //User interface
        void readMemory() {
            std::cout << "Read memory user call" << std::endl;
        }
    
    
        void onUserRelease() override {
            _outStream = nullptr;
            std::cout  << "User release";
        }
        void onNetworkRelease() override {
            Link::onNetworkRelease();
            std::cout  << "Network release";
        }
    protected:
        
    private:
        int _rxPacketId = 0;
        LFramework::ComPtr<MicroNetwork::Task::MemoryAccess::IHostToDevice> _outStream;
        std::mutex _packetsMutex;
    };
}