
#include "driver.h"
#include "events.h"
#include "communication.h"
#include "collector.h"
#include <Shared/macros.h>


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
    UNREFERENCED_PARAMETER(pRegistryPath);

    pDriverObject->DriverUnload = (PDRIVER_UNLOAD)UnloadDriver;

    DbgMsg("Driver loading...\n");

    Collector::Init();

    globals::Init();

    PsSetLoadImageNotifyRoutine(ImageLoadCallback);

    IoCreateDevice(pDriverObject,
        0, // For driver extension
        globals::dos,
        FILE_DEVICE_UNKNOWN,
        FILE_DEVICE_UNKNOWN,
        FALSE,
        &globals::pDeviceObject);
    IoCreateSymbolicLink(globals::dos, globals::dev);
    
    //for (int i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; i++) {
    //    pDriverObject->MajorFunction[i] = DispatchPassThru;
    //}
    pDriverObject->MajorFunction[IRP_MJ_CREATE] = Function_IRP_MJ_CREATE;
    pDriverObject->MajorFunction[IRP_MJ_CLOSE] = Function_IRP_MJ_CLOSE;
    pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = Function_IRP_DEVICE_CONTROL;
    
    if (globals::pDeviceObject) {
        DbgMsg("Device Object initialized\n");
    }
    else {
        DbgMsg("Device Object could not be initialized\n");
    }

    return STATUS_SUCCESS;
}

NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverObject)
{
    UNREFERENCED_PARAMETER(pDriverObject);

    DbgMsg("Driver unloading...\n");

    PsRemoveLoadImageNotifyRoutine(ImageLoadCallback);

    DbgMsg("Removed image notify callback\n");

    IoDeleteSymbolicLink(globals::dos);
    IoDeleteDevice(pDriverObject->DeviceObject);

    Collector::Clean();

    DbgMsg("Driver unloaded successfully\n");

    return STATUS_SUCCESS;
}
