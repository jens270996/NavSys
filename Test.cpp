#include <iostream>
#include <boosts/signals2>

    void f()
    {
        std::cout << "Hello" << std::endl;
    }
    struct HelloWorld
    {
        void operator() () const{
            std::cout << "hello, world!" << std::endl;

        }
    };
int main()
{
    boost::signals2::signal<void ()> sig;
    HelloWorld hello;
    sig.connect(&f);
    sig.connec(hello);
    sig();
    return 0;
}