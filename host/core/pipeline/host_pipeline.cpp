#include <iostream>
#include <memory>
#include <mutex>

#include "host_pipeline.hpp"

#include "../../../shared/timer.hpp"


HostPipeline::HostPipeline()
    : _data_queue_lf(c_data_queue_size)
{}

void HostPipeline::onNewData(
    const StreamInfo& info,
    const StreamData& data
)
{
    Timer t;

    // std::cout << "--- new data from " << info.name << " , size: " << data.size << "\n";
    bool keep_frame = _public_stream_names.empty() ||
            (_public_stream_names.find(info.getName()) != _public_stream_names.end());
    if(!keep_frame)
    {
        std::cout << "Stream " << info.name << "is not in the stream list" << ":\n";
        return;
    }

    if(data.size > info.size)
    {
        keep_frame = false;
    }

    if(keep_frame == false)
    {
        std::cout << "Received frame " << info.name << " is wrong size: " << data.size << ", expected: " << info.size <<":\n";
        return;
    }

    std::shared_ptr<HostDataPacket> host_data(
        new HostDataPacket(
            data.size,
            data.data,
            info.name,
            info.getDimensionsForSize(data.size),
            info.elem_size
            ));
    
    // std::unique_lock<std::mutex> guard(q_lock);
    if (!_data_queue_lf.push(host_data))
    {
        // std::unique_lock<std::mutex> guard(q_lock);
        // _data_queue_lf.pop();
        // if (!_data_queue_lf.push(host_data))
        // {
        //     std::cerr << "Data queue is full " << info.name << ":\n";
        // }
    }
    // guard.unlock();

    // std::cout << "===> onNewData " << t.ellapsed_us() << " us\n";
}

void HostPipeline::onNewDataSubject(const StreamInfo &info)
{
    _observing_stream_names.insert(info.name);
}


void HostPipeline::consumePackets()
{
    Timer consume_dur;
    _consumed_packets.clear();

    std::unique_lock<std::mutex> guard(q_lock);
    _data_queue_lf.consume_all(
        [this]
        (std::shared_ptr<HostDataPacket>& data)
        {
            // std::cout << "===> c++ wait " << data->constructor_timer.ellapsed_us() << " us\n";            
            this->_consumed_packets.push_back(data);
        }
    );
    guard.unlock();

    if (!this->_consumed_packets.empty())
    {
        // std::cout << "===> c++ consumePackets " << consume_dur.ellapsed_us() / this->_consumed_packets.size() << " us (per 1)\n";
    }
}


