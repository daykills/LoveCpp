/*
 https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=534283&highlight=zoox
 We are working on a batch image processing pipeline. We want to be able to list
 the operations to be applied on all the images (and their parameters) in a config
 file. For example:
 
 ConvertToGrayScale
 Blur 3.1
 Resize 256 256
 BlendWith
 
 The idea is to load the config file, create the pipeline, and process all the
 images through the pipeline. We have access to a library for image manipulation
 (in the ImgLib namespace below) that has all the functions that we need for
 those operations.
 
 How would you design such a pipeline?
 
 Keep in mind that you have 40 minutes, so you are encouraged to first go for
 a decently simple solution, and then discuss extensions.
 
 In this case we will mock the behavior of image loading and image processing
 with print statements. This is because we don't have IO in coderpad.
 
 Also in this case we have 4 commands and 3 images, but think that in reality
 there could be a lot more images and commands.
*/

#include "Common.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Mock image class.
// Do not modify.
class Image {
public:
    Image (const string& name) : name_(name) {}
    const string& name() const { return name_; }
private:
    string name_;
};

// Mock image manipulation library.
// Do not modify.
namespace ImgLib {

void convertToGrayScale (Image & img) {
    cout << img.name() << ": Converting to gray scale" << endl;
}

void blur (Image & img, float factor) {
    cout << img.name() << ": Blurring with factor " << factor << endl;
}

void resize (Image & img, int x, int y) {
    cout << img.name() << ": Resizing img with x = " << x << " and y = " << y << endl;
}

void blend (Image & img, const Image& other) {
    cout << img.name() << ": Blending with " << other.name() << endl;
}

// ******************************************************************
// *                                                                *
// *  NOTE: There are at least 1000 additional functions.           *
// *  The rest have been omitted due to the scope of the exercise.  *
// *                                                                *
// ******************************************************************

} // namespace ImgLib

namespace BatchImgProcessor {

class ImgProcessor {
public:
    virtual void run(Image& img) = 0;
    virtual ~ImgProcessor() = default;
    virtual void setParam(const string& config)  = 0;
};

class ConvertToGrayScaleProcessor : public ImgProcessor {
public:
    void run(Image& img) override {
        ImgLib::convertToGrayScale(img);
    }
    void setParam(const string& config) override {}
};

class BlurProcessor : public ImgProcessor {
public:
    void run(Image& img) override {
        ImgLib::blur(img, m_factor);
    }
    void setParam(const string& config) override {
        istringstream is(config);
        is >> m_factor;
    }
protected:
    float m_factor;
};

class ResizeProcessor : public ImgProcessor {
public:
    void run(Image& img) override {
        ImgLib::resize(img, m_x, m_y);
    }
    void setParam(const string& config) override {
        istringstream is(config);
        is >> m_x >> m_y;
    }
protected:
    int m_x;
    int m_y;
};

class BlendProcessor : public ImgProcessor {
public:
    void run(Image& img) override {
        ImgLib::blend(img, *m_other);
    }
    void setParam(const string& config) override {
        istringstream is(config);
        string other;
        is >> other;
        m_other.reset(new Image(other));
    }
protected:
    unique_ptr<Image> m_other;
};

class ImgProcessorFactory {
public:
    static ImgProcessor* createImpProcessor(const string& operation) {
        istringstream is(operation);
        string command;
        is >> command;
        ImgProcessor* processor = nullptr;
        if (command == "ConvertToGrayScale") {
            processor = new ConvertToGrayScaleProcessor();
        } else if (command == "Blur") {
            processor = new BlurProcessor();
        } else if (command == "Resize") {
            processor = new ResizeProcessor();
        } else if (command == "BlendWith") {
            processor = new BlendProcessor();
        }
        assert(processor != nullptr);
        string rest;
        getline(is, rest);
        processor->setParam(rest);
        return processor;
    }
private:
    ImgProcessorFactory() = default;
};

using ImgProcessorRef = shared_ptr<ImgProcessor>;

class ImageTask {
public:
    ImageTask(Image& img) : m_img(img) {}
    void addProcessor(ImgProcessorRef processor) {
        m_processors.emplace_back(processor);
    }
    void run() {
        for (auto& processor : m_processors) {
            processor->run(m_img);
        }
    }
private:
    vector<ImgProcessorRef> m_processors;
    Image& m_img;
};

// Forward declaration of the process function that you have to write (below).
void process(const vector<string>& cmds, vector<Image>& imgs);

// Your work goes here
void process(const vector<string>& cmds, vector<Image>& imgs) {
    vector<ImgProcessorRef> processors;
    for (auto& cmd : cmds) {
        processors.emplace_back(ImgProcessorFactory::createImpProcessor(cmd));
    }
    
    vector<ImageTask> tasks;
    for (auto& img : imgs) {
        tasks.emplace_back(img);
        auto& task = tasks.back();
        for (auto& processor : processors)
            task.addProcessor(processor);
    }
    
    // parallelism
    for (auto& task : tasks) {
        task.run();
    }
    
    return;
}

// Simple main to allow testing the process function.
void Test() {
    // The "config file".
    // These commands are guaranteed to be error-free and are assumed to
    // be space delimited, with the first word being a command idenifier.
    // The arguments to each command are always of the same types.
    // Because coderpad does not have IO, we store an example config file
    // in a string format directly. This is a simple config file to let us
    // test the process function with a small number of operations.
    // Assume that the Image class constructor will take care of downloading
    // and loading the blend image used in the BlendWith operation.
    vector<string> operations = {
        "ConvertToGrayScale",
        "Blur 3.1",
        "Resize 256 256",
        "BlendWith XXX"};
    
    // The images to process.
    // This is a small number of images to allow testing the process function.
    // Again stored in memory as mock images because we don't have IOs.
    vector<Image> imgs = {
        Image ("one"),
        Image ("two"),
        Image ("three")};
    
    process(operations, imgs);
}

} // namespace BatchImgProcessor
