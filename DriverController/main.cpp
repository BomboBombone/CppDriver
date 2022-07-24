
#include <iostream>

#define _CLIENT
#include <Shared/macros.h>

#include "kernelinterface.hpp"

int main()
{
    KernelInterface Driver = KernelInterface("\\\\.\\MyDriv");

    ULONG address = Driver.GetClientAddress();

    std::cout << "Module address: " << address << std::endl;

    system("pause");
}