Experiment in which I try of make C++ more "liquid".

The standard C++98 runtime type information is not very useful. You can use it to do three things in C++: to see the name of the type, to distinguish one type from another, and to dynamically cast from one type to another.

In this project I create a layer of abstraction, which provides notion of interfaces, properties, and automated interface queries.

Hypothetical example:

int frame = videoPlayer[ &IPlaybackControl::CurrentFrame ];

videoPlayer[ &IPlaybackControl::Start ]();

videoPlayer[ &IWindow::Close ]();
Features

    C++ Experiment
    Interfaces, Properties


