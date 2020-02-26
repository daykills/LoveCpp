#include "Common.h"

// ==============================================================
namespace SensorSample {

// Data Structure Definition
struct SensorSample {
    int sensor_id;
    int sample_id;
    int value;
    bool operator ==(const SensorSample& rhs) const {
        return (sensor_id == rhs.sensor_id &&
                sample_id == rhs.sample_id &&
                value == rhs.value );
    }
};

// Constants
constexpr int      FILTER_THRESHOLD         = 100;
constexpr size_t   TOTAL_SAMPLE_COUNT       = 20;
constexpr size_t   MAX_WORK_QUEUE_ELEMENTS  = 10;
constexpr uint32_t TARGET_PUBLISH_PERIOD_MS = 200;

/* ===============================================================
 Exercise 1: Single Producer, Single Consumer
 
 1. Create a 'sensor driver' thread that will serve as a producer
 - Reads samples from the pre-defined dataset and "publishes" them to a work queue at a fixed rate (200ms)
 
 2. Create a 'Filter' thread that will serve as a sensor data consumer and produce filtered outputs
 - Sleeps until data is available and upon receiving data, filters out elements under threshhold value (100)
 - Prints the delta in time between each sample received by the consumer in milliseconds
 - Upon processing the pre-defined number of sensor samples (20), exit
 
 3. Create instances of the producer and consumer, and run such that the output container is populated with the results
 - Exercise method should evaluate test clause when both producer and consumer have finished their work
 
 +-------------+     +---------------+     +------------+     +--------------+     +-------------+
 |             |     | Sensor Driver |     |            |     |    Filter    |     |             |
 | Input Data  +---->+               +---->+ Work Queue +---->+              +---->+ Output Data |
 |             |     |   (Producer)  |     |            |     |  (Consumer)  |     |             |
 +-------------+     +---------------+     +------------+     +--------------+     +-------------+
 */


// Sample Data
std::vector<SensorSample> sensor_data{{
    { 0, 0, 77 },
    { 0, 1, 37 },
    { 0, 2, 43 },
    { 0, 3, 40 },
    { 0, 4, 43 },
    { 0, 5, 24 },
    { 0, 6, 45 },
    { 0, 7, 92 },
    { 0, 8, 27 },
    { 0, 9, 54 },
    { 0, 10, 13 },
    { 0, 11, 96 },
    { 0, 12, 77 },
    { 0, 13, 119 },
    { 0, 14, 111 },
    { 0, 15, 31 },
    { 0, 16, 3 },
    { 0, 17, 115 },
    { 0, 18, 105 },
    { 0, 19, 39 }
}};

// Exercise Answers
std::vector<SensorSample> correct_sensor0_filtered_data{{
    { 0, 13, 119 },
    { 0, 14, 111 },
    { 0, 17, 115 },
    { 0, 18, 105 }
}};

void test_equality( const std::vector<SensorSample>& a, const std::vector<SensorSample>& b ){
    if(a == b) {
        std::cout << "PASS" << std::endl;
    } else {
        std::cout << "FAIL" << std::endl;
    }
}

void producer() {
    
}

void consumer() {
    
}

void exercise() {
    std::vector<SensorSample> output;
    // your code here
    std::deque<SensorSample> taskQ;
    atomic<bool> workComplete = false;
    std::condition_variable cvQueueFull;
    std::condition_variable cvQueueEmpty;
    std::mutex mutQueueFull;
    std::mutex mutQueueEmpty;
    std::mutex mutQueueAccess;
    
    std::thread tProducer([&]() {
        for (auto& data : sensor_data) {
            // if queue is full, wait for new item processed
            if (taskQ.size() >= MAX_WORK_QUEUE_ELEMENTS) {
                std::unique_lock<std::mutex> lock(mutQueueFull);
                cvQueueFull.wait(lock);
            }
            {
                std::lock_guard<std::mutex> lck(mutQueueAccess);
                taskQ.push_front(data);
            }
            cvQueueEmpty.notify_one();
            if (workComplete)
                break;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    });
    
    std::thread tConsumer([&]() {
        for (auto i = 0; i < TOTAL_SAMPLE_COUNT; i++) {
            if (taskQ.empty()) {
                std::unique_lock<std::mutex> lckCV(mutQueueEmpty);
                cvQueueEmpty.wait(lckCV);
            }
            SensorSample data = taskQ.front(); taskQ.pop_front();
            // let producer start working
            cvQueueFull.notify_one();
            if (data.value > FILTER_THRESHOLD)
                output.push_back(data);
        }
        cvQueueFull.notify_all();
        workComplete = true;
    });
    
    tProducer.join();
    tConsumer.join();
    // Check results
    test_equality(output, correct_sensor0_filtered_data);
}

// ==============================================================
// Main Function: Enable/Disable methods to run each exercise
void Test() {
    exercise();
}

}
